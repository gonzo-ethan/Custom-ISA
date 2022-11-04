#ifndef _CPU_EMU_HPP_
#define _CPU_EMU_HPP_

#include <iostream>
#include <string>

#define UPPER_MASK 65280
#define LOWER_MASK 255
#define REG_COUNT 16
#define FOCUS_COUNT 4
#define MEM_SIZE 65536

class CPU_emu {
private:
    unsigned short pc;
    unsigned short stat;
    short *regs;
    short *focus;
    short *mem;
public:
    CPU_emu() : pc(0), stat(0), regs(new short[REG_COUNT]), focus(new short[FOCUS_COUNT]), mem(new short[MEM_SIZE / 2]) {}
    ~CPU_emu();
    static short reg_stoi(std::string reg_name); // converts register string name to short
    void printInfo(); // output register and memory info
    void setPC(short value); // setter for pc register
    short getPC(); // getter for pc register
    void setStat(short value); // setter for stat register
    short getStat(); // getter for stat register
    void setRegister(short reg_num, short value); // setter for accessible registers
    short getRegister(short reg_num); // getter for accessible registers
    void setFocus(short focus_num, short value); // setter for focus registers
    short getFocus(short focus_num); // getter for focus registers
    void setMemByte(short address, short value); // setter for byte at memory address
    short getMemByte(short address); // getter for byte at memory address
    void setMemWord(short address, short value); // setter for word at memory address
    short getMemWord(short address); // getter for word at memory address
};

#endif