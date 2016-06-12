#ifndef __pipeline_Write_H__ 
#define __pipeline_Write_H__ 

#include "memory.h"

struct Write 
{
    Memory *MEM;

    void init(Memory *memory);
    void print(FILE *output);
    int tick();
};

#endif // __pipeline_Write_H__ 

