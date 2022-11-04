#include "cpu_emu.hpp"

/*
TO DO:
    * Implement exepections to make error handling and debugging simpler
*/

// destructor for cpu_emu to free memory when done
CPU_emu::~CPU_emu() {
    delete[] regs;
    delete[] focus;
    delete[] mem;
}

// converts string register name into a short
short CPU_emu::reg_stoi(std::string reg_name) {
    if (reg_name == "zero" || reg_name == "x0" || reg_name == "0" || reg_name == "f0")
        return 0;
    if (reg_name == "ra" || reg_name == "x1" || reg_name == "1" || reg_name == "f1")
        return 1;
    if (reg_name == "sp" || reg_name == "x2" || reg_name == "2" || reg_name == "f2")
        return 2;
    if (reg_name == "t0" || reg_name == "x3" || reg_name == "3" || reg_name == "f3")
        return 3;
    if (reg_name == "s0" || reg_name == "x4" || reg_name == "4")
        return 4;
    if (reg_name == "s1" || reg_name == "x5" || reg_name == "5")
        return 5;
    if (reg_name == "s2" || reg_name == "x6" || reg_name == "6")
        return 6;
    if (reg_name == "s3" || reg_name == "x7" || reg_name == "7")
        return 7;
    if (reg_name == "a0" || reg_name == "x8" || reg_name == "8")
        return 8;
    if (reg_name == "a1" || reg_name == "x9" || reg_name == "9")
        return 9;
    if (reg_name == "t1" || reg_name == "x10" || reg_name == "10")
        return 10;
    if (reg_name == "t2" || reg_name == "x11" || reg_name == "11")
        return 11;
    if (reg_name == "s4" || reg_name == "x12" || reg_name == "12")
        return 12;
    if (reg_name == "s5" || reg_name == "x13" || reg_name == "13")
        return 13;
    if (reg_name == "a2" || reg_name == "x14" || reg_name == "14")
        return 14;
    if (reg_name == "a3" || reg_name == "x15" || reg_name == "15")
        return 15;
    return -1;
}

// prints register/memory info to the console
void CPU_emu::printInfo() {
    std::cout << "-- REGISTERS --" << std::endl;
    std::cout << "  pc:" << "\t" << pc << std::endl;
    std::cout << "  stat:" << "\t" << stat << std::endl;

    for (int i = 0; i < REG_COUNT; i++) {
        std::cout << "  x" << i << ":" << "\t" << regs[i] << std::endl;
    }

    std::cout << std::endl;
    std::cout << "-- FOCUS REGISTERS --" << std::endl;
    std::cout << "  f0:" << "\t" << focus[0] << std::endl;
    std::cout << "  f1:" << "\t" << focus[1] << std::endl;
    std::cout << "  f2:" << "\t" << focus[2] << std::endl;
    std::cout << "  f3:" << "\t" << focus[3] << std::endl;
}

// pc register setter and getter
void CPU_emu::setPC(short value) { pc = value; }
short CPU_emu::getPC() { return pc; }

// stat register setter and getter
void CPU_emu::setStat(short value) { stat = value; }
short CPU_emu::getStat() { return stat; }

// accessible registers setter and getter
void CPU_emu::setRegister(short reg_num, short value) { if (reg_num > 0) regs[reg_num] = value; }
short CPU_emu::getRegister(short reg_num) { return regs[reg_num]; }

// focus registers setter and getter
void CPU_emu::setFocus(short focus_num, short value) { if (focus_num > 0) focus[focus_num] = value; }
short CPU_emu::getFocus(short focus_num) { return focus[focus_num]; }

// memory setters and getters
void CPU_emu::setMemByte(short address, short value) {
    short upper = mem[address] & UPPER_MASK;
    short lower = mem[address] & LOWER_MASK;

    if (address % 2 == 0)
        lower = value;
    else
        upper = value;
    
    mem[address / 2] = (upper << 8) | lower;
}

short CPU_emu::getMemByte(short address) { return ((address % 2) == 0 ? (mem[address / 2] & LOWER_MASK) : ((mem[address / 2] & UPPER_MASK) >> 8)); }

void CPU_emu::setMemWord(short address, short value) {
    if (address % 2 == 0) {
        mem[address / 2] = value;
    } else {
        short value_upper = (value & UPPER_MASK) >> 8;
        short value_lower = value & LOWER_MASK;
        short mem_temp_upper = (mem[(address / 2) + 1] & UPPER_MASK) >> 8;
        short mem_temp_lower = mem[address / 2] & LOWER_MASK;

        mem[address / 2] = (value_lower << 8) | mem_temp_lower;
        mem[(address / 2) + 1] = (mem_temp_upper << 8) | value_upper;
    }
}

short CPU_emu::getMemWord(short address) {
    if (address % 2 == 0) {
        return mem[address / 2];
    } else {
        return (((mem[(address / 2) + 1] & LOWER_MASK) << 8) | ((mem[address / 2] & UPPER_MASK) >> 8));
    }
}