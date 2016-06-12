#ifndef __pipeline_Execute_H__ 
#define __pipeline_Execute_H__ 

#include "decode.h"

struct Execute 
{
    Decode *ID;
    int ALUout;
    int WriteData;
    char Reg;
    char RegDst;
    char ALUsrc;
    char signals[6];
    char Reg_forward;
    int ALUout_forward;

    void init(Decode *decode);
    void print(FILE *output);
    int tick();
};

#endif // __pipeline_Execute_H__ 

