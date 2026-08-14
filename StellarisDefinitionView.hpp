#pragma once
//#include "wrappers_headers.hpp"
#include "StellarisDefinition.hpp"

#include "StellarisDefinition.hpp"

#include "StellarisDefinition.hpp"

template<typename T>
struct VendorConstsView
{
    // ========================================================
    // Endpoint hardware
    // ========================================================

    struct Endpoint
    {
        uint32_t IDX;          // логический endpoint
        uint32_t ALIAS;        // hardware endpoint selector

        uint32_t TXMAXP;
        uint32_t TXCSRL;
        uint32_t TXCSRH;

        uint32_t RXMAXP;
        uint32_t RXCSRL;
        uint32_t RXCSRH;
        uint32_t RXCOUNT;

        uint32_t FIFO;

        uint32_t INTEP;
    };


    // ========================================================
    // Global USB hardware
    // ========================================================

    struct USB
    {
        uint32_t FADDR;
        uint32_t POWER;

        uint32_t TXIS;
        uint32_t RXIS;
        uint32_t TXIE;
        uint32_t RXIE;

        uint32_t IS;
        uint32_t IE;

        uint32_t FRAME;
        uint32_t EPIDX;

        uint32_t TXFIFOSZ;
        uint32_t RXFIFOSZ;
        uint32_t TXFIFOADD;
        uint32_t RXFIFOADD;

        // ...
    };


    // ========================================================
    // Hardware configuration
    // ========================================================

    static constexpr Endpoint EndpointRegs(uint8_t ep);

    static constexpr USB USBRegs();
};


class Stellaris;

template<>
struct VendorConstsView<Stellaris>
{
};



