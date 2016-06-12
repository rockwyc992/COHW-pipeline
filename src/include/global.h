#ifndef __pipeline_Global_H__ 
#define __pipeline_Global_H__ 

#include <stdio.h>
#include <string.h>

extern int round;

extern int reg[16];
extern int mem[8];

extern FILE *input;
extern FILE *output;

int bin2int(char *str, int from, int len);
int init();
void show_all();
int tick();

#endif // __pipeline_Global_H__ 

