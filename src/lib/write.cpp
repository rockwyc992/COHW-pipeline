#include "write.h"

void Write::init(Memory *memory)
{
    MEM = memory;
}

void Write::print(FILE *output)
{
}

int Write::tick()
{
    if (bin2int(MEM->signals, 0, 2) == 0) {
        this->init(MEM);
        return 0;
    }

    if (MEM->signals[0] == '1') {
        if (MEM->signals[1] == '1') {
            reg[(unsigned)MEM->Reg] = MEM->ReadData;
        } else {
            reg[(unsigned)MEM->Reg] = MEM->ALUout;
        }
    }
    return 1;
}
