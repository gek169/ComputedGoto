#include <stdio.h>
#include <stdint.h>
#include "stringutil.h"

uint8_t interp(unsigned char* code, uint8_t initval) {
    /* The indices of labels in the dispatch_table are the relevant opcodes
    */
    //static void* dispatch_table[] = {
    //    &&do_halt, &&do_inc, &&do_dec, &&do_mul2,
    //    &&do_div2, &&do_add7, &&do_neg, &&do_load};
    //#define DISPATCH() goto *dispatch_table[code[pc++]]
    #define DISPATCH()\
    switch(code[pc++] & 7){       \
         default: goto do_halt;   \
         case 1: goto do_dec;\
         case 2: goto do_inc;\
         case 3: goto do_mul2;\
         case 4: goto do_div2;\
         case 5: goto do_add7;\
         case 6: goto do_neg;\
         case 7: goto do_load;\
    }

    size_t pc = 0;
    uint8_t val = initval;

    DISPATCH();
    {
        do_halt:
            return val;
        do_inc:
            val++;
            DISPATCH();
        do_dec:
            val--;
            DISPATCH();
        do_mul2:
            val <<= 1;
            DISPATCH();
        do_div2:
            val >>= 1;
            DISPATCH();
        do_add7:
            val += 7;
            DISPATCH();
        do_neg:
            val = -val;
            DISPATCH();
        do_load:
        	val = code[pc++];
        	DISPATCH();
    }
}

int main(int argc, char** argv){
	char code[1024];
	read_until_terminator(stdin, code, 1024, '0');
	printf("\n%d\n", interp((unsigned char*)code, 0));
}
