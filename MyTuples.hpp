#pragma once
#include <utility>
////////////////////////////////////////////////////////////////

/*template<std::size_t I, class T>
struct CTupleElement
{
    T value;
};

template<class IndexSeq, class... T>
struct CTupleImpl;

template<std::size_t... I, class... T>
struct CTupleImpl<std::index_sequence<I...>, T...>
    : CTupleElement<I, T>...
{
};

template<class... T>
struct CTuple
    : CTupleImpl<std::index_sequence_for<T...>, T...>
{
};

template<class T>
struct CTupleSize;

template<class... T>
struct CTupleSize<CTuple<T...>>
{
    static constexpr std::size_t value = sizeof...(T);
};
//////////////////////////////////////////////////
template<class... T>//рекурсивный кортеж
struct CTuple;

template<>
struct CTuple<> //база
{
};

template<class T, class... Rest>
struct CTuple<T, Rest...>
{
    T value;
    CTuple<Rest...> rest;
};



template<std::size_t I, class T, class... Rest>
constexpr auto& get(CTuple<T, Rest...>& t)
{
    if constexpr (I == 0)
        return t.value;
    else
        return get<I - 1>(t.rest);
}

template<std::size_t I, class T, class... Rest>
constexpr const auto& get(const CTuple<T, Rest...>& t)
{
    if constexpr (I == 0)
        return t.value;
    else
        return get<I - 1>(t.rest);
}



//////////////////////////////////////////////////


template<class... T>
struct CTuple;

template<>
struct CTuple<>
{
    static constexpr std::size_t size = 0;
};

template<class T, class... Rest>
struct CTuple<T, Rest...>
{
    static constexpr std::size_t size = 1 + CTuple<Rest...>::size;

    T value;
    CTuple<Rest...> rest;
};
*/

//////////////////////////////
#pragma once

#include <cstddef>
#include <utility>

////////////////////////////////////////////////////////////
// Compile-time tuple
////////////////////////////////////////////////////////////

/*template<class... T>
struct CTuple;

// Empty tuple
template<>
struct CTuple<>
{
    static constexpr std::size_t size = 0;
};

// Tuple<T, Rest...>
template<class T, class... Rest>
struct CTuple<T, Rest...>
{
    static constexpr std::size_t size = 1 + CTuple<Rest...>::size;

    T value;
    CTuple<Rest...> rest;
};*/
template<class... T>
struct CTuple;

template<class T>
struct CTuple<T>
{
    T value;
    static constexpr std::size_t size = 1;
};

template<class T, class... Rest>
struct CTuple<T, Rest...>
{
    T value;
    CTuple<Rest...> rest;
    static constexpr std::size_t size = 1 + CTuple<Rest...>::size;
};

template<>
struct CTuple<>
{
    static constexpr std::size_t size = 0;
};


template<std::size_t I, class T>
constexpr auto& get(CTuple<T>& t)
{
    static_assert(I == 0);
    return t.value;
}

template<std::size_t I, class T, class... Rest>
constexpr auto& get(CTuple<T, Rest...>& t)
{
    if constexpr (I == 0)
        return t.value;
    else
        return get<I - 1>(t.rest);
}

template<std::size_t I, class T>
constexpr const auto& get(const CTuple<T>& t)
{
    static_assert(I == 0);
    return t.value;
}

template<std::size_t I, class T, class... Rest>
constexpr const auto& get(const CTuple<T, Rest...>& t)
{
    if constexpr (I == 0)
        return t.value;
    else
        return get<I - 1>(t.rest);
}

////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Проверка
////////////////////////////////////////////////////////////

static_assert(CTuple<>::size == 0);
static_assert(CTuple<int>::size == 1);
static_assert(CTuple<int, char, double>::size == 3);



////////////////////////////////////////////////////////////
// get<I>()
////////////////////////////////////////////////////////////

/*template<std::size_t I, class T, class... Rest>
constexpr auto& get(CTuple<T, Rest...>& t)
{
    if constexpr (I == 0)
        return t.value;
    else
        return get<I - 1>(t.rest);
}

template<std::size_t I, class T, class... Rest>
constexpr const auto& get(const CTuple<T, Rest...>& t)
{
    if constexpr (I == 0)
        return t.value;
    else
        return get<I - 1>(t.rest);
}*/