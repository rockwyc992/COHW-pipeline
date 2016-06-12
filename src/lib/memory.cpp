#include "memory.h"

void Memory::init(Execute *execute) 
{
    EX = execute;
    ReadData = 0;
    ALUout = 0;
    Reg = 0;
    strncpy(signals, "00", 2);
}

void Memory::print(FILE *output) 
{
    fprintf(output, "MEM/WB :\n");
    fprintf(output, "ReadData %4d\n", ReadData);
    fprintf(output, "ALUout      %d\n", ALUout);
    fprintf(output, "Control signals %s\n", signals);
}

int Memory::tick()
{
    if (bin2int(EX->signals, 0, 5) == 0) {
        this->init(EX);
        return 0;
    }

    strncpy(signals, EX->signals+3, 2);
    Reg = EX->Reg;

    ALUout = EX->ALUout;
    if (EX->signals[1] == '1') {
        ReadData = mem[ALUout/4];
        EX->Reg_forward = Reg;
        EX->ALUout_forward = ReadData;
    } else {
        ReadData = 0;
    }

    return 1;
}

