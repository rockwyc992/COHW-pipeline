#ifndef __pipeline_Memory_H__ 
#define __pipeline_Memory_H__ 

#include "execute.h"

struct Memory 
{
    Execute *EX;
    int ReadData;
    int ALUout;
    char Reg;
    char signals[3];

    void init(Execute *execute);
    void print(FILE *output);
    int tick();
};

#endif // __pipeline_Memory_H__ 

