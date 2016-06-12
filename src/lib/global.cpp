#include "global.h"

#include "fetch.h"
#include "decode.h"
#include "execute.h"
#include "memory.h"
#include "write.h"

int round;

int reg[16];
int mem[8];

FILE *input;
FILE *output;

Fetch IF;
Decode ID;
Execute EX;
Memory MEM;
Write WB;

int bin2int(char *str, int from, int len)
{
    int tmp = 0;
    for (int i = 0 ; i < len; i++) {
        tmp *= 2;
        if (str[from + i] == '1') {
            tmp++;
        }
    }
    return tmp;
}

int init()
{
    if (input == NULL || output == NULL) {
        return 1;
    }
    round = 0;

    reg[0] = 0;
    reg[1] = 8;
    reg[2] = 7;
    reg[3] = 6;
    reg[4] = 3;
    reg[5] = 9;
    reg[6] = 5;
    reg[7] = 2;
    reg[8] = 7;

    mem[0] = 5;
    mem[1] = 5;
    mem[2] = 6;
    mem[3] = 8;
    mem[4] = 8;

    IF.init(input);
    ID.init(&IF);
    EX.init(&ID);
    MEM.init(&EX);
    WB.init(&MEM);

    return 0;
}

void show_all()
{
    fprintf(output, "CC %d:\n", round);
    fprintf(output, "\n");
    fprintf(output, "Registers:\n");
    fprintf(output, "$0: %-4d$1: %-4d$2: %-4d\n", reg[0], reg[1], reg[2]);
    fprintf(output, "$3: %-4d$4: %-4d$5: %-4d\n", reg[3], reg[4], reg[5]);
    fprintf(output, "$6: %-4d$7: %-4d$8: %-4d\n", reg[6], reg[7], reg[8]);
    fprintf(output, "\n");
    fprintf(output, "Data memory:\n");
    fprintf(output, "00: %d\n", mem[0]);
    fprintf(output, "04: %d\n", mem[1]);
    fprintf(output, "08: %d\n", mem[2]);
    fprintf(output, "12: %d\n", mem[3]);
    fprintf(output, "16: %d\n", mem[4]);
    fprintf(output, "\n");
    IF.print(output);
    ID.print(output);
    EX.print(output);
    MEM.print(output);
    WB.print(output);
    fprintf(output, "=================================================================\n");
}

int tick() 
{
    int flag = 0;
    flag += WB.tick();
    flag += MEM.tick();
    flag += EX.tick();
    flag += ID.tick();
    flag += IF.tick();
    round++;
    return flag;
}

