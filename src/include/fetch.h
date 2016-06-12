#ifndef __pipeline_Fetch_H__ 
#define __pipeline_Fetch_H__ 

#include "global.h"

struct Fetch 
{
    int pc;
    int top;
    char instruction[33];
    char cache[100][33];
    int sleep;

    void init(FILE *input);
    void print(FILE *output);
    int read(FILE *input);
    int tick();
};

#endif // __myBinder_ZIP_H__ 

