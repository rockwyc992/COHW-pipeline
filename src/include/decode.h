#ifndef __pipeline_Decode_H__ 
#define __pipeline_Decode_H__ 

#include "global.h"
#include "fetch.h"

struct Decode 
{
    Fetch *IF;
    int ReadData1;
    int ReadData2;
    int sign_ext;
    char Rs;
    char Rt;
    char Rd;
    char signals[10];
    char ALUctr[4];
    int sleep;
    int load_flag;

    void init(Fetch *fetch);
    void print(FILE *output);
    int tick();
};

#endif // __pipeline_Decode_H__ 

