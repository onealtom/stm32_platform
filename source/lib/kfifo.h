#ifndef _KFIFO_H_
#define _KFIFO_H


//声明 一个 结构体 kfifo

struct KFIFO
{   
    unsigned char *buffer;    /* the buffer holding the data */   
    unsigned int size;            /* the size of the allocated buffer */   
    unsigned int in;                /* data is added at offset (in % size) */   
    unsigned int out;                /* data is extracted from off. (out % size) */   
        /*STM32 只有一个核心，同一时刻只能写或者读，因此不需要*/
        //    volatile unsigned int *lock; /* protects concurrent modifications */  
};

unsigned int roundup_pow_of_two( unsigned int date_roundup_pow_of_two );

struct KFIFO *kfifo_alloc(unsigned int size);

unsigned int __kfifo_put(struct KFIFO *fifo, unsigned char *buffer, unsigned int len);

unsigned int __kfifo_get(struct KFIFO *fifo, unsigned char *buffer, unsigned int len);

#endif
