#pragma once

#include <cstdint>
#include <cstddef>
#include <type_traits>
#include <limits>
#include <bit>


// ============================================================================
// MemPool
//
// Fixed-size memory pool.
//
// T - object type stored in the pool.
// Storage - policy responsible for initialization/releasing T.
// S - unsigned integer used as allocation bitmap.
//
// One bit of S corresponds to one object of T.
//
//     bit = 1 -> object is free
//     bit = 0 -> object is occupied
//
// Therefore the maximum number of objects is:
// 
//     sizeof(S) * 8
//
// The pool does not know anything about T.
// Resource-specific initialization is delegated to Storage.
//
// Required Storage interface:
//
//     static void Init(T&);
//     static void Release(T&);
// ============================================================================

template<class T, class Storage, class S = uint32_t>
class MemPool
{
    static_assert(
        std::is_unsigned_v<S>,
        "MemPool bitmap type must be unsigned"
    );


public:

    // Number of objects that can be stored in the pool.
    static constexpr size_t Capacity = sizeof(S) * 8;


private:

    // Actual object storage.
    inline static T Pool[Capacity]{};

    // Allocation bitmap.
    //
    // 1 = free
    // 0 = occupied
    //
    // Initially all objects are free.
    inline static S FreeMap =
        std::numeric_limits<S>::max();


    // ------------------------------------------------------------------------
    // Find and reserve one free object.
    //
    // Returns Capacity if the pool is full.
    // ------------------------------------------------------------------------

    static size_t AllocateIndex()
    {
        if (FreeMap == 0)
            return Capacity;

        // Find the first set bit.
        const size_t index =
            std::countr_zero(FreeMap);

        // Mark this object as occupied.
        FreeMap &= ~(S(1) << index);

        return index;
    }


public:

    // ------------------------------------------------------------------------
    // Get
    //
    // Allocates one object from the pool.
    //
    // Returns:
    //     pointer to object
    //     nullptr if the pool is full
    // ------------------------------------------------------------------------

    static T* Get()
    {
        const size_t index = AllocateIndex();

        if (index >= Capacity)
            return nullptr;

        Storage::Init(Pool[index]);

        return &Pool[index];
    }


    // ------------------------------------------------------------------------
    // Release
    //
    // Returns an object to the pool.
    //
    // The object must have been obtained from this pool.
    // ------------------------------------------------------------------------

    static void Release(T* object)
    {
        if (object == nullptr)
            return;

        const ptrdiff_t index = object - Pool;

        // Ignore pointers that do not belong to this pool.
        if (index < 0 ||
            static_cast<size_t>(index) >= Capacity)
            return;

        // Resource-specific cleanup.
        Storage::Release(*object);

        // Mark object as free.
        FreeMap |= S(1) << index;
    }


    // ------------------------------------------------------------------------
    // Capacity
    //
    // Maximum number of objects in the pool.
    // ------------------------------------------------------------------------

    static constexpr size_t GetCapacity()
    {
        return Capacity;
    }
};


// ============================================================================
// DataPool
//
// Fixed-size pool for raw data buffers.
//
// Size  - size of one buffer in bytes.
// Count - number of buffers.
//
// Every buffer has exactly Size bytes.
//
// The actual amount of data used by the message is specified separately,
// for example by CAN_Message::dlc.
//
// Example:
//
//     using CAN_DataPool = DataPool<8, 32>;
//
// gives:
//
//     32 buffers
//     each buffer = 8 bytes
//
// The pool uses a bitmap, therefore Count must fit into uint32_t.
// ============================================================================

template<size_t Size, size_t Count>
struct DataPool
{
    static_assert(
        Size > 0,
        "DataPool buffer size must be greater than zero"
    );

    static_assert(
        Count > 0,
        "DataPool must contain at least one buffer"
    );

        static_assert(
        Count > 0 && Count <= 32,
        "DataPool Count must be 1..32"
    );

    inline static uint8_t memory[Count][Size];

    inline static uint32_t FreeMap = []()
    {
        if constexpr (Count == 32)
            return 0xFFFFFFFFu;
        else
            return (uint32_t(1) << Count) - 1u;
    }();


public:

    // ------------------------------------------------------------------------
    // Get
    //
    // Allocates one fixed-size data buffer.
    //
    // Returns nullptr if no buffer is available.
    // ------------------------------------------------------------------------

    static uint8_t* Get()
    {
        if (FreeMap == 0)
            return nullptr;

        const size_t index =
            std::countr_zero(FreeMap);

        FreeMap &= ~(uint32_t(1) << index);

        return memory[index];
    }


    // ------------------------------------------------------------------------
    // Release
    //
    // Returns a buffer to the pool.
    //
    // The pointer must have been returned by Get().
    // ------------------------------------------------------------------------

    static void Release(uint8_t* data)
    {
        if (data == nullptr)
            return;

        // Check that the pointer lies inside Memory.
        uint8_t* begin = &memory[0][0];
        uint8_t* end   = &memory[Count - 1][Size - 1] + 1;

        if (data < begin || data >= end)
            return;

        // Pointer must point exactly to the beginning of a buffer.
        const size_t offset =
            static_cast<size_t>(data - begin);

        if ((offset % Size) != 0)
            return;

        const size_t index = offset / Size;

        if (index >= Count)
            return;

        // Mark buffer as free.
        FreeMap |= uint32_t(1) << index;
    }
};


// ============================================================================
// Example:
//
//     CAN_Message contains only a pointer to its data.
//
//     CAN_DataPool supplies the actual 8-byte storage.
//
//     CAN_MessageStorage connects the two resources.
//
// ============================================================================
//
// struct CAN_Message
// {
//     uint8_t  dlc;
//     uint8_t* data;
// };
//
//
// using CAN_DataPool = DataPool<8, 32>;
//
//
// struct CAN_MessageStorage
// {
//     static void Init(CAN_Message& msg)
//     {
//         msg.dlc  = 0;
//         msg.data = CAN_DataPool::Get();
//     }
//
//
//     static void Release(CAN_Message& msg)
//     {
//         CAN_DataPool::Release(msg.data);
//
//         msg.data = nullptr;
//         msg.dlc  = 0;
//     }
// };
//
//
// using CAN_MessagePool =
//     MemPool<CAN_Message, CAN_MessageStorage>;
//
//
// Example:
//
//     CAN_Message* msg = CAN_MessagePool::Get();
//
//     if (msg)
//     {
//         msg->dlc = 8;
//
//         // use msg->data[0 ... 7]
//
//         CAN_MessagePool::Release(msg);
//     }
//
// ============================================================================



// ============================================================================
// FIFO
//
// FIFO stores pointers to objects.
//
// FIFO does NOT allocate or release the objects.
//
// Therefore ownership is:
//
//     MemPool  -> owns the object memory
//
//     FIFO     -> temporarily holds the pointer
//
//     Application/backend -> owns the object after Pop()
//
// This allows the FIFO to sit on top of MemPool without knowing anything
// about the actual object type or its storage.
//
// Example:
//
//     FIFO<CAN_Message, 8> RxFIFO;
//
//     CAN_Message* msg = CAN_MessagePool::Get();
//
//     if (msg)
//     {
//         if (!RxFIFO.Push(msg))
//         {
//             // FIFO is full.
//             CAN_MessagePool::Release(msg);
//         }
//     }
// ============================================================================

template<class T, size_t N>
class FIFO
{
    static_assert(
        N > 0,
        "FIFO size must be greater than zero"
    );


private:

    // Ring buffer containing pointers to objects.
    T* Buffer[N]{};

    // Index of the next object to read.
    size_t Head = 0;

    // Index where the next object will be inserted.
    size_t Tail = 0;

    // Number of objects currently in FIFO.
    size_t Count = 0;


public:

    // ------------------------------------------------------------------------
    // Push
    //
    // Adds an existing object to the FIFO.
    //
    // FIFO does not take ownership of the object.
    //
    // Returns false if:
    //
    //     object == nullptr
    //     FIFO is full
    // ------------------------------------------------------------------------

    bool Push(T* object)
    {
        if (object == nullptr)
            return false;

        if (Count == N)
            return false;

        Buffer[Tail] = object;

        Tail++;

        if (Tail == N)
            Tail = 0;

        Count++;

        return true;
    }


    // ------------------------------------------------------------------------
    // Pop
    //
    // Removes and returns the oldest object.
    //
    // Returns nullptr if FIFO is empty.
    // ------------------------------------------------------------------------

    T* Pop()
    {
        if (Count == 0)
            return nullptr;

        T* object = Buffer[Head];

        Head++;

        if (Head == N)
            Head = 0;

        Count--;

        return object;
    }


    // ------------------------------------------------------------------------
    // Empty
    // ------------------------------------------------------------------------

    bool Empty() const
    {
        return Count == 0;
    }


    // ------------------------------------------------------------------------
    // Full
    // ------------------------------------------------------------------------

    bool Full() const
    {
        return Count == N;
    }


    // ------------------------------------------------------------------------
    // Number of objects currently stored in FIFO.
    // ------------------------------------------------------------------------

    size_t Size() const
    {
        return Count;
    }


    // ------------------------------------------------------------------------
    // Maximum number of objects FIFO can contain.
    // ------------------------------------------------------------------------

    static constexpr size_t Capacity()
    {
        return N;
    }
};