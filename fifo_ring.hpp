#pragma once
 extern "C"{

#include <stdint.h>
#include <stdbool.h>
#include "stdio.h"
 }


template<uint32_t sz>
class FIFO_Ring{
private:
uint8_t buf[sz];
uint16_t buf_sz=sz;
uint32_t count=0;
uint32_t head=sz-1;
uint32_t tail=sz-1;
public:
void  clear() {
    head = buf_sz-1;
    tail = buf_sz-1;
    count = 0;
}
unsigned int Count(){return count;};

bool empty() { return count > 0 ? false : true; }
void add_byte(uint8_t b) {
		if (++head >= buf_sz) head = 0;
		buf[head] = b;
		if (tail == head) {
			if (++tail >= buf_sz) tail = 0;//если голова догнала хвост - хвост убегает
		}
		else {
			++count;
		}
	};
uint8_t byte_read() {

		if (count == 0)	return 0;

		if (++tail >= buf_sz)tail = 0;
		--count;
		if (tail == head) count = 0;//если хвост догнал голову - все ушло
		return buf[tail];
	};

private:
uint8_t byte_read_shadow(uint32_t& shadow_tail,uint32_t& shadow_count) {

		if (shadow_count == 0)	return 0;

		if (++shadow_tail >= buf_sz)shadow_tail = 0;
		--shadow_count;
		if (shadow_tail == head) shadow_count = 0;//если хвост догнал голову - все ушло
		return buf[shadow_tail];
	};
public:
////////////////
bool try_extractCommand(uint8_t* cmd){
    //cli;
    bool res=false;
    if(count<3)return res;
    uint32_t shadow_tail=tail;
    uint32_t shadow_count=count;
    uint8_t pref[]={'C','M','D'};
    uint8_t ch;
    uint8_t pref_pos=0;
    uint8_t cmd_max_len=15;
    uint8_t cmd_len=0;
    while(shadow_count>0)
    {
    printf("shadow_count1 %d\n",shadow_count);
        if((ch=byte_read_shadow(shadow_tail,shadow_count))!=pref[pref_pos])
            {
            pref_pos=0;
            continue; 
            }
        else{
            ++pref_pos;
            if (pref_pos>2)
                {
                pref_pos=0;
                if(shadow_count<1){
                    cmd[0]='\0';
                    return res;
                }

                do{
                    *cmd=byte_read_shadow(shadow_tail,shadow_count);
                     printf("shadow_count2 %d\n",shadow_count);
                    if(*cmd=='\0'){
                        res=true;
                        break;
                    }else{
                    if(--cmd_max_len<1)break;    
                    ++cmd;
                    ++cmd_len;
                    };
                }
                while(shadow_count>0&&ch=='\0');  
                if(res==true){
                    uint16_t p=tail;

                    while(p<cmd_len+3)buf[p++]='\0';

                } 
                return res;     
            }
        }
    //sie;
    }
}
////////////////
uint16_t read_range(uint8_t* dst,uint16_t cnt){
           if (count == 0) return 0;
           if (count < cnt) cnt=count;
           for (int i=0;i<cnt;++i){
           *dst = byte_read();
           ++dst;
           }
        return cnt;
        }; 
uint16_t write_range(uint8_t* src,uint16_t cnt){
        int i=0;
          for (i;i<cnt;++i){
           add_byte(*src);
           ++src;
           }
        return i;
        };
uint16_t read_all(uint8_t* dst){
        if (count == 0) return 0;
uint16_t cnt=0;
           while(count>0){
           *dst=byte_read();
           ++dst;
           ++cnt;
           }
        return cnt;
        }; 

  uint16_t read_string(uint8_t* dst){
        if(count==0)return 0;
        uint16_t len=0;
        --dst;
        do{
        ++dst;
        ++len;
        *dst=byte_read();
        } while(*dst!='\0'&&count>0);
        *dst='\0';
        dst++;
        return len;
        }; 

        uint16_t write_string(uint8_t* src){
        uint16_t len=0;
        do{
        ++len;
        ++src;
        add_byte(*src);
        } while (len<buf_sz&&*src!='\0');
        *src='0';
        };
};