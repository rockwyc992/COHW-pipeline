#include "decode.h"

void Decode::init(Fetch *fetch) 
{
    IF = fetch;
    ReadData1 = 0;
    ReadData2 = 0;
    sign_ext = 0;
    Rs = 0;
    Rt = 0;
    Rd = 0;
    strncpy(ALUctr, "000", 3);
    strncpy(signals, "000000000", 9);
    sleep = 0;
    load_flag = 0;
}

void Decode::print(FILE *output) 
{
    fprintf(output, "ID/EX :\n");
    fprintf(output, "ReadData1 %3d\n", ReadData1);
    fprintf(output, "ReadData2 %3d\n", ReadData2);
    fprintf(output, "sign_ext %4d\n", sign_ext);
    fprintf(output, "Rs %6d\n", Rs);
    fprintf(output, "Rt %6d\n", Rt);
    fprintf(output, "Rd %6d\n", Rd);
    fprintf(output, "Control signals %s\n", signals);
    fprintf(output, "\n");
}

int Decode::tick() 
{
    if (bin2int(IF->instruction, 0, 32) == 0) {
        this->init(IF);
        return 0;
    }

    Rs = bin2int(IF->instruction, 6, 5);
    ReadData1 = reg[(unsigned)Rs];

    Rt = bin2int(IF->instruction, 11, 5);
    ReadData2 = reg[(unsigned)Rt];

    Rd = bin2int(IF->instruction, 16, 5);

    int op_code = bin2int(IF->instruction, 0, 6);
    if (op_code) {
        if (op_code == 4) { //beq
            if (Rs == load_flag || Rt == load_flag) {
                if (load_flag) {
                    sleep = 1;
                    IF->sleep = 1;
                }
            }
            strncpy(ALUctr, "110", 3);
            strncpy(signals, "001010000", 9);
            load_flag = 0;
        } else if (op_code == 8) { //addi
            if (Rs == load_flag) {
                if (load_flag) {
                    sleep = 1;
                    IF->sleep = 1;
                }
            }
            strncpy(ALUctr, "010", 3);
            strncpy(signals, "000100010", 9);
            load_flag = 0;
        } else if (op_code == 13) { //ori
            if (Rs == load_flag) {
                if (load_flag) {
                    sleep = 1;
                    IF->sleep = 1;
                }
            }
            strncpy(ALUctr, "001", 3);
            strncpy(signals, "011100010", 9);
            load_flag = 0;
        } else if (op_code == 35) { //lw
            if (Rs == load_flag) {
                if (load_flag) {
                    sleep = 1;
                    IF->sleep = 1;
                }
            }
            strncpy(ALUctr, "010", 3);
            strncpy(signals, "000101011", 9);
            load_flag = Rt;
        }
        sign_ext = bin2int(IF->instruction, 16, 16);
    } else {
        if (Rs == load_flag || Rt == load_flag) {
            if (load_flag) {
                sleep = 1;
                IF->sleep = 1;
            }
        }
        strncpy(signals, "110000010", 9);
        load_flag = 0;
        int func = bin2int(IF->instruction, 26, 6);
        if (func) {
            if (func == 32) { //add
                strncpy(ALUctr, "010", 3);
            } else if (func == 34) { //sub
                strncpy(ALUctr, "110", 3);
            } else if (func == 36) { //and
                strncpy(ALUctr, "000", 3);
            } else if (func == 37) { //or
                strncpy(ALUctr, "001", 3);
            }
        }
        sign_ext = 0;
    }

    if (signals[4] == '1') {
        if (ReadData1 == ReadData2) {
            IF->pc += sign_ext*4;
            IF->sleep = 1;
            memset(IF->instruction, '0', 32);
            IF->instruction[32] = '\0';
        }
    }

    return 1;
}
