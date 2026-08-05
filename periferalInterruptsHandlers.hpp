#pragma once

#include "USB_THIS_PROGRAM_DEFS.hpp"
#include <functional>

#include <bit>
#include <vector>
/*
#define USB_INTEP_DEV_OUT_15    0x80000000  // Endpoint 15 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_14    0x40000000  // Endpoint 14 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_13    0x20000000  // Endpoint 13 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_12    0x10000000  // Endpoint 12 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_11    0x08000000  // Endpoint 11 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_10    0x04000000  // Endpoint 10 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_9     0x02000000  // Endpoint 9 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_8     0x01000000  // Endpoint 8 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_7     0x00800000  // Endpoint 7 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_6     0x00400000  // Endpoint 6 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_5     0x00200000  // Endpoint 5 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_4     0x00100000  // Endpoint 4 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_3     0x00080000  // Endpoint 3 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_2     0x00040000  // Endpoint 2 Device OUT Interrupt
#define USB_INTEP_DEV_OUT_1     0x00020000  // Endpoint 1 Device OUT Interrupt


#define USB_INTEP_DEV_IN_15     0x00008000  // Endpoint 15 Device IN Interrupt
#define USB_INTEP_DEV_IN_14     0x00004000  // Endpoint 14 Device IN Interrupt
#define USB_INTEP_DEV_IN_13     0x00002000  // Endpoint 13 Device IN Interrupt
#define USB_INTEP_DEV_IN_12     0x00001000  // Endpoint 12 Device IN Interrupt
#define USB_INTEP_DEV_IN_11     0x00000800  // Endpoint 11 Device IN Interrupt
#define USB_INTEP_DEV_IN_10     0x00000400  // Endpoint 10 Device IN Interrupt
#define USB_INTEP_DEV_IN_9      0x00000200  // Endpoint 9 Device IN Interrupt
#define USB_INTEP_DEV_IN_8      0x00000100  // Endpoint 8 Device IN Interrupt
#define USB_INTEP_DEV_IN_7      0x00000080  // Endpoint 7 Device IN Interrupt
#define USB_INTEP_DEV_IN_6      0x00000040  // Endpoint 6 Device IN Interrupt
#define USB_INTEP_DEV_IN_5      0x00000020  // Endpoint 5 Device IN Interrupt
#define USB_INTEP_DEV_IN_4      0x00000010  // Endpoint 4 Device IN Interrupt
#define USB_INTEP_DEV_IN_3      0x00000008  // Endpoint 3 Device IN Interrupt
#define USB_INTEP_DEV_IN_2      0x00000004  // Endpoint 2 Device IN Interrupt
#define USB_INTEP_DEV_IN_1      0x00000002  // Endpoint 1 Device IN Interrupt*/



constexpr unsigned EPIndex(uint32_t m)//плучаем номер младшего установленного бита
{                                     //на этапе компиляции вычислит и присвоит лямбды в какомто порядке- не важно
    unsigned b = std::__countr_zero(m);

    return (b < 16) ? (b - 1)       // IN
                    : (31 - b + 15);// OUT
};

template<uint32_t usb_base>//usb_base
class USB_COM_Handlers{

inline static  std::function<void()> handlers[30];

static  void Execute(uint32_t int_COM_status){

  while (int_COM_status) {
   auto& h = handlers[EPIndex(int_COM_status)]; 
    if (h) h();
    int_COM_status &= int_COM_status - 1;

  }
}
 static  void Register(uint32_t int_ep,std::function<void()> handler){
  handlers[EPIndex(int_ep)]=handler;
  }
};


////////////////////////////////////////////////////////////////////////////////////////////
std::array<uint32_t,ExtSetupHandlersCnt> T1= {
    GET_STATUS_DEVICE<<8|0x00,      
    GET_STATUS_INTERF<<8|0x00,    
   GET_STATUS_ENDPNT<<8|0x05,  
   GET_STATUS_ENDPNT<<8|0x01,
   GET_STATUS_ENDPNT<<8|0x02, 
   GET_STATUS_ENDPNT<<8|0x03,
   GET_STATUS_ENDPNT<<8|0x04,
   GET_STATUS_ENDPNT<<8|0x85,
   GET_STATUS_ENDPNT<<8|0x81,
   GET_STATUS_ENDPNT<<8|0x82,
   GET_STATUS_ENDPNT<<8|0x83,
   GET_STATUS_ENDPNT<<8|0x84, 
     CLEAR_FEATURE_DEVICE<<8|0x00,   
     CLEAR_FEATURE_INTERF<<8|0x00,  
     CLEAR_FEATURE_ENDPNT<<8|0x05, 
   CLEAR_FEATURE_ENDPNT<<8|0x01,
   CLEAR_FEATURE_ENDPNT<<8|0x02, 
   CLEAR_FEATURE_ENDPNT<<8|0x03,
   CLEAR_FEATURE_ENDPNT<<8|0x04,

   CLEAR_FEATURE_ENDPNT<<8|0x85,
   CLEAR_FEATURE_ENDPNT<<8|0x81,
   CLEAR_FEATURE_ENDPNT<<8|0x82,
   CLEAR_FEATURE_ENDPNT<<8|0x83,
   CLEAR_FEATURE_ENDPNT<<8|0x84,
  
     SET_FEATURE_DEVICE<<8|0x00,    
     SET_FEATURE_INTERF<<8|0x00,
     
     SET_FEATURE_ENDPNT<<8|0x00, 

     CLEAR_FEATURE_ENDPNT<<8|0x05, 
   CLEAR_FEATURE_ENDPNT<<8|0x01,
   CLEAR_FEATURE_ENDPNT<<8|0x02, 
   CLEAR_FEATURE_ENDPNT<<8|0x03,
   CLEAR_FEATURE_ENDPNT<<8|0x04,

   CLEAR_FEATURE_ENDPNT<<8|0x85,
   CLEAR_FEATURE_ENDPNT<<8|0x81,
   CLEAR_FEATURE_ENDPNT<<8|0x82,
   CLEAR_FEATURE_ENDPNT<<8|0x83,
   CLEAR_FEATURE_ENDPNT<<8|0x84,
    
     SET_ADDRESS<<8|0x00,            
     GET_DESCRIPTOR_DEVICE<<8|0x00,  
     GET_DESCRIPTOR_INTERF<<8|0x00,  
     GET_DESCRIPTOR_ENDPNT<<8|0x00,  
     SET_DESCRIPTOR<<8|0x00,        
     GET_CONFIGURATION<<8|0x00,      
     SET_CONFIGURATION<<8|0x00,      
     GET_INTERFACE<<8|0x00,          
     SET_INTERFACE<<8|0x00,          
     SYNCH_FRAME<<8|0x00,            
     GET_REPORT<<8|0x00,             
     SET_IDLE<<8|0x00,               
     FEAT_ENDPOINT_HALT<<8|0x00,        
     FEAT_DEVICE_REMOTE_WAKEUP<<8|0x00, 
     FEAT_TEST_MODE<<8|0x00            
};

std::function<void( const _Buffer&, uint32_t sup_data)> ExtSetupHandlers[ExtSetupHandlersCnt];


template <size_t N>
constexpr uint8_t GetIndex(uint32_t val, const std::array<uint32_t, N>& array)
{
    for (uint8_t i = 0; i < N; ++i)
    {
        if (array[i] == val)
            return i;
    }

   std::unreachable();
}

inline void ExtSetupHandlerRegister(std::function<void(const _Buffer&, uint32_t)> h,
                                    uint32_t req,
                                    uint8_t ep_addr=0
                                    )
{
    ExtSetupHandlers[GetIndex((req << 8) | ep_addr, T1)] = std::move(h);
}

inline bool Execute_ExtSetupHandler(uint32_t req, uint8_t ep_addr=0,const _Buffer& buf={0,0,0,0,0,0,0,0},uint32_t sup_data=0)
{
    auto& h = ExtSetupHandlers[GetIndex((req << 8) | ep_addr, T1)];
    if (!h)
        return false;

    h(buf,sup_data);
    return true;
}