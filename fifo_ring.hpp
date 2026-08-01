#pragma once
#ifdef __cplusplus extern "C"{
#endif
#include <stdint.h>
#include <stdbool.h>
#ifdef __cplusplus }
#endif

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