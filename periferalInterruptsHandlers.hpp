#pragma once

#include "USB_THIS_PROGRAM_DEFS.hpp"
#include <functional>

#include <bit>
#include <vector>
enum class MyUSB_EP_INT : uint8_t
{
    EP0_INOUT=0, EP1_IN=1, EP2_IN=2, EP3_IN=3, EP4_IN=4, EP5_IN=5, EP6_IN=6, E7P_IN=7,
    EP8_IN=8, EP9_IN=9, EP10_IN=10, EP11_IN=11, EP12_IN=15, EP13_IN=13, EP14_IN=14, EP15_IN=15,
    EP1_OUT=16, EP2_OUT=17, EP3_OUT=18, EP4_OUT=19, EP5_OUT=20, EP6_OUT=21, EP7_OUT=22, EP8_OUT=23,
    EP9_OUT=24, EP10_OUT=25, EP11_OUT=26, EP12_OUT=27, EP13_OUT=28, EP14_OUT=29, EP15_OUT=30
};


/*constexpr unsigned EPIndex(uint32_t m)//плучаем номер младшего установленного бита
{                                     //на этапе компиляции вычислит и присвоит лямбды в какомто порядке- не важно
    unsigned b = std::__countr_zero(m);

    return (b < 16) ? (b - 1)       // IN
                    : (31 - b + 15);// OUT
};*/

template<uint32_t usb_base>//usb_base
class USB_COM_Handlers{
public:

inline static  std::function<void()> handlers[30];

static  void Execute(uint32_t int_COM_status){

  while (int_COM_status) {
   auto& h = handlers[USBWRP::COMInterruptIndex(int_COM_status)]; 
    if (h) h();
    int_COM_status &= int_COM_status - 1;//убирает последни установленны бит
  }
}
 static  void Register(uint32_t int_COM_status,std::function<void()> handler){
  handlers[USBWRP::COMInterruptIndex(int_COM_status)]=handler;
  }
};


////////////////////////////////////////////////////////////////////////////////////////////
inline std::array<uint32_t,ExtSetupHandlersCnt> T1= {
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
     FEAT_TEST_MODE<<8|0x00, 
     USB_CDC_SET_LINE_CODING<<8|0,          //0x2021
     USB_CDC_GET_LINE_CODING<<8|0,          //0x21A1
     USB_CDC_SET_CONTROL_LINE_STATE<<8|0   //0x2221           
};

inline   std::function<void( const _Buffer&, uint32_t& sup_data)> ExtSetupHandlers[ExtSetupHandlersCnt];


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

inline void ExtSetupHandlerRegister(std::function<void(const _Buffer&, uint32_t&)> h,
                                    uint32_t req,
                                    uint8_t ep_addr=0
                                    )
{
    ExtSetupHandlers[GetIndex((req << 8) | ep_addr, T1)] = std::move(h);
}

inline uint32_t dammyobj;
inline bool Execute_ExtSetupHandler(uint32_t req, uint8_t ep_addr=0,const _Buffer& buf={0,0,0,0,0,0,0,0},uint32_t& sup_data=dammyobj)
{
    auto& h = ExtSetupHandlers[GetIndex((req << 8) | ep_addr, T1)];
    if (!h)
        return false;

    h(buf,sup_data);
    return true;
}