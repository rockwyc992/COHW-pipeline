#include "fetch.h"

void Fetch::init(FILE *input)
{
    top = 0;
    pc = 0;
    sleep = 0;
    while(read(input)) {
        strncpy(cache[top/4], instruction, 32);
        top += 4;
    }
    memset(instruction, '0', 32);
    instruction[32] = '\0';
}

void Fetch::print(FILE *output) 
{
    fprintf(output, "IF/ID :\n");
    fprintf(output, "PC      %d\n", pc);
    fprintf(output, "Instruction %s\n", instruction);
    fprintf(output, "\n");
}

int Fetch::read(FILE *input) 
{
    for (int i = 0 ; i < 32; i++) {
        int tmp = fgetc(input);
        if (tmp == EOF) {
            memset(instruction, '0', 32);
            instruction[32] = '\0';
            return 0;
        } else if (tmp != '0' && tmp != '1') {
            i--;
            continue;
        }
        instruction[i] = tmp;
    }
    instruction[32] = '\0';
    return 1;
}

int Fetch::tick() 
{
    if (sleep) {
        sleep = 0;
        return 0;
    }
    if (pc >= top) {
        memset(instruction, '0', 32);
        instruction[32] = '\0';
        pc += 4;
        return 0;
    } else {
        strncpy(instruction, cache[pc/4], 32);
        pc += 4;
        return 1;
    }
}

