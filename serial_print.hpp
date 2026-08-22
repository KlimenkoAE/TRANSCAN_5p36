#pragma once
#include "fifo_ring.hpp"
#include<stdarg.h>
//#include<stdio.h>
 extern "C"{
#include "hw_types.h"
#include "sysctl.h"
#include "hw_sysctl.h"
#include "uart.h"
 }
 #include <stdlib.h>
#include <functional>


class Serial_Print{

public:

    std::function<void(uint8_t)> fn;

public:
    Serial_Print(std::function<void(uint8_t)> f) : fn(f) {}

    void add_byte(uint8_t b) { fn(b); }

///////////////
  void    Print(unsigned char* str){
  st_Print(this, str);
  }

  void Print32_t_0x(uint32_t val){
st_Print32_t_0x(this, val);
  }

   void Print32_t(uint32_t val){
   st_Print32_t(this,val);
  }

   void Print64_t(uint64_t val){
  st_Print64_t(this,val);
  }


   void Print16_t(uint16_t val){
   st_Print16_t(this,val);
  }

   void PrintWord(uint16_t reg){
   st_PrintWord(this,reg);
  }
   void PrintByte(uint8_t reg){
st_PrintByte(this,reg);
  }
   void PrintByteArary(uint32_t len, uint8_t* arr){
   st_PrintByteArary(this,len, arr);
      };

void printf(const char* strf, ... ){
    va_list args;
    va_start(args, strf);              // инициализация списка
    st_printf(this, strf, args);       // передаём весь «ракет» в st_printf
    va_end(args);
//va_list args;
//st_printf(this,strf, args);
  }




 static void    st_Print(Serial_Print* self,unsigned char* str){
  	uint8_t p=0;
  	while(*(str+p)!='\0'){
          self->add_byte(*(str+p++));
  	}
   }

static void _itos0x(const uint64_t* p, uint8_t* out, uint8_t t_sz) {
  	out += t_sz * 2 - 1;
  	*(out + 1) = '\0';
  	for (uint8_t i = 0; i < t_sz*2; ++i) {
  		*(out - i) = (*p>>i*4) & 0x0F;
  		if (*(out - i) > 0x09)
  		*(out - i) += 0x37;
  		else
  		*(out - i) += 0x30;
  	}
  }


static   void st_Print32_t_0x(Serial_Print* self,uint32_t val){
  	unsigned char buf[9];
  	//itoa(val,(char*)buff,10);
  	_itos0x((uint64_t*)&val,buf,4);
         self->add_byte('0');
         self->add_byte( 'x');
          for(int i=0;i<8;++i)
  	 self->add_byte(buf[i]);
  }

static    void st_Print32_t(Serial_Print* self,uint32_t val){
          unsigned char buff[10];
  	itoa(val,(char*)buff,10);
  	self->st_Print(self,buff);
  }

static    void st_Print64_t(Serial_Print* self,uint64_t val){
  	unsigned char buff[17];
  	itoa(val,(char*)buff,10);
  	self->st_Print(self,buff);
  }


static    void st_Print16_t(Serial_Print* self,uint16_t val){
  	unsigned char buff[5];
  	itoa(val,(char*)buff,16);
  	self->st_Print(self,buff);
  }

static    void st_PrintWord(Serial_Print* self,uint16_t reg){
  	unsigned char buf[5];
  	itoa(reg,(char*)buf,16);
  	self->Print(buf);
  }
static    void st_PrintByte(Serial_Print* self,uint8_t reg){

  	unsigned char buf[3];
  	itoa(reg,(char*)buf,16);
  	self->Print(buf);
  }
static    void st_PrintByteArary(Serial_Print* self,uint32_t len, uint8_t* arr){
      for(int b=0;b<len;++b){
      st_PrintByte(self,arr[b]);
      self->add_byte( ' ');

        };
       self->add_byte( '\r');
       self->add_byte( '\n');
      };



      //std::printf("strf",previousTMCnt);
/*static  void st_printf(Serial_Print* self,const char* strf,va_list args){

  const char* p=strf;
  uint8_t va_cnt=0;
  do{
  if(*p=='%')++va_cnt;
  }
  while(*++p!='\0');

 // va_list args;

  va_start(args,va_cnt);

  p=strf;
  while(*p!='\0'){
    if(*p=='%'){
      switch(*++p){
       case 'x':
       case 'X':
        st_Print32_t_0x(self,va_arg(args,uint32_t));
       break;
       case 'd':
       st_Print32_t(self,va_arg(args,uint32_t));
       break;
       case 's':
       st_Print(self,va_arg(args,unsigned char*));
       break;
      }
      ++p;
    }
    else{
       self->add_byte(*p++);
      }
  }
  va_end(args);
  }*/
static void st_printf(Serial_Print* self, const char* strf, va_list args) {
    const char* p = strf;
    while (*p != '\0') {
        if (*p == '%') {
            switch (*++p) {
            case 'x':
            case 'X':
                st_Print32_t_0x(self, va_arg(args, uint32_t));
                break;
            case 'd':
                st_Print32_t(self, va_arg(args, uint32_t));
                break;
            case 's':
                st_Print(self, va_arg(args, unsigned char*));
                break;
            }
            ++p;
        } else {
            self->add_byte(*p++);
        }
    }
}
};

