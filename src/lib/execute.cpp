#include "execute.h"

void Execute::init(Decode *decode) 
{
    ID = decode;
    ALUout = 0;
    WriteData = 0;
    Reg = 0;
    RegDst = 0;
    ALUsrc = 0;
    strncpy(signals, "00000", 5);
}

void Execute::print(FILE *output) 
{
    fprintf(output, "EX/MEM :\n");
    fprintf(output, "ALUout      %d\n", ALUout);
    fprintf(output, "WriteData %3d\n", WriteData);
    fprintf(output, "R%c %6d\n", RegDst?'d':'t', Reg);
    fprintf(output, "Control signals %s\n", signals);
    fprintf(output, "\n");
}

int Execute::tick() {
    if (ID->sleep) {
        this->init(ID);
        ID->sleep = 0;
        return 0;
    }

    if (bin2int(ID->signals, 0, 9) == 0) {
        this->init(ID);
        Reg_forward = Reg;
        ALUout_forward = ALUout;
        return 0;
    }

    strncpy(signals, ID->signals+4, 5);

    if (ID->signals[0] == '1') {
        RegDst = 1;
    } else {
        RegDst = 0;
    }

    if (ID->signals[3] == '1') {
        ALUsrc = 1;
    } else {
        ALUsrc = 0;
    }

    int Data1 = ID->ReadData1;
    int Data2 = ID->ReadData2;

    if (ID->Rs == Reg) {
        Data1 = ALUout;
    } else if (ID->Rs == Reg_forward) {
        Data1 = Reg_forward;
    }

    if (ID->Rt == Reg) {
        Data2 = ALUout;
    } else if (ID->Rt == Reg_forward) {
        Data2 = ALUout_forward;
    }

    Reg_forward = Reg;
    ALUout_forward = ALUout;

    WriteData = Data2;
    if (ALUsrc) {
        Data2 = ID->sign_ext;
    }

    if (RegDst) {
        Reg = ID->Rd;
    } else {
        Reg = ID->Rt;
    }

    int control = bin2int(ID->ALUctr, 0, 3);
    if (control == 0) { //and
        ALUout = Data1 & Data2;
    } else if (control == 1) { //or
        ALUout = Data1 | Data2;
    } else if (control == 2) { //add
        ALUout = Data1 + Data2;
    } else if (control == 6) { //sub
        ALUout = Data1 - Data2;
    }

    return 1;
}

