#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "cpu_emu.hpp"

struct instruction {
    std::string op;
    std::vector<short> nums;
    std::string label;
};

std::vector<std::string> get_lines(std::string file_name) {
    std::vector<std::string> lines;

    std::string line;
    std::ifstream file_temp(file_name);

    if (file_temp.is_open()) {
        while(getline(file_temp, line)) {
            lines.push_back(line);
        }
    } else {
        std::cout << "failure to open file: " << file_name << std::endl;
    }

    file_temp.close();

    return lines;
}

std::vector<std::string> parse_line(std::string line) {
    std::vector<std::string> parsed_data;
    bool reading = true;
    std::string temp_str;

    for (int c = 0; c < line.size(); c++) {
        if (line[c] == ' ' || line[c] == '\t' || line[c] == ',' || line[c] == '(' || line[c] == ')') {
            if (reading) {
                parsed_data.push_back(temp_str);
                temp_str = "";
            }
            reading = false;
        } else {
            temp_str.push_back(std::tolower(line[c]));
            reading = true;
        }
    }

    if (reading)
        parsed_data.push_back(temp_str);\
    
    return parsed_data;
}

void process_instruction(CPU_emu *my_emu, std::string line) {
    std::vector<std::string> data = parse_line(line);

    if (data[0] == "addr") {
        my_emu->setRegister(CPU_emu::reg_stoi(data[1]),
                            my_emu->getRegister(CPU_emu::reg_stoi(data[2])) +
                            my_emu->getRegister(CPU_emu::reg_stoi(data[3])));
    }

    if (data[0] == "add") {
        my_emu->setRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[1])),
                            my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[2]))) +
                            my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[3]))));
    }

    if (data[0] == "sub") {
        my_emu->setRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[1])),
                            my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[2]))) -
                            my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[3]))));
    }

    if (data[0] == "sll") {
        my_emu->setRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[1])),
                            my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[2]))) <<
                            my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[3]))));
    }

    if (data[0] == "slli") {
        my_emu->setRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[1])),
                            my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[2]))) <<
                            (short)std::stoi(data[3]));
    }

    if (data[0] == "srl") {
        my_emu->setRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[1])),
                            my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[2]))) >>
                            my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[3]))));
    }

    if (data[0] == "srli") {
        my_emu->setRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[1])),
                            my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[2]))) >>
                            (short)std::stoi(data[3]));
    }

    if (data[0] == "sra") {
        // TO DO
    }

    if (data[0] == "srai") {
        // TO DO
    }

    if (data[0] == "and") {
        my_emu->setRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[1])),
                            my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[2]))) &
                            my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[3]))));
    }

    if (data[0] == "or") {
        my_emu->setRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[1])),
                            my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[2]))) |
                            my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[3]))));
    }

    if (data[0] == "xor") {
        my_emu->setRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[1])),
                            my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[2]))) ^
                            my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[3]))));
    }

    if (data[0] == "slt") {
        if (my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[2]))) < my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[3]))))
            my_emu->setRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[1])), 1);
        else
            my_emu->setRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[1])), 0);
    }

    if (data[0] == "addi") {
        my_emu->setRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[1])), my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[2]))) +
                                                                            (short)std::stoi(data[3]));
    }

    if (data[0] == "slti") {
        if (my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[2]))) < CPU_emu::reg_stoi(data[3]))
            my_emu->setRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[1])), 1);
        else
            my_emu->setRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[1])), 0);
    }

    if (data[0] == "beq") {
        if (my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[1]))) == my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[2]))))
            my_emu->setPC(my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[3]))));
    }

    if (data[0] == "bne") {
        if (my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[1]))) != my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[2]))))
            my_emu->setPC(my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[3]))));
    }

    if (data[0] == "bge") {
        if (my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[1]))) >= my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[2]))))
            my_emu->setPC(my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[3]))));
    }

    if (data[0] == "blt") {
        if (my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[1]))) < my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[2]))))
            my_emu->setPC(my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[3]))));
    }

    if (data[0] == "jal") {
        my_emu->setRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[1])), my_emu->getPC());
        my_emu->setPC(my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[3]))) + (short)std::stoi(data[2]));
    }

    if (data[0] == "jalr") {
        my_emu->setRegister(CPU_emu::reg_stoi(data[1]), my_emu->getPC());
        my_emu->setPC(my_emu->getRegister(CPU_emu::reg_stoi(data[3])) + (short)std::stoi(data[2]));
    }

    if (data[0] == "lui") {
        my_emu->setRegister(CPU_emu::reg_stoi(data[1]), (my_emu->getRegister(CPU_emu::reg_stoi(data[1])) & LOWER_MASK) +
                                                                            ((short)std::stoi(data[2]) << 8));
    }

    if (data[0] == "lli") {
        my_emu->setRegister(CPU_emu::reg_stoi(data[1]), (my_emu->getRegister(CPU_emu::reg_stoi(data[1])) & UPPER_MASK) +
                                                                            (short)std::stoi(data[2]));
    }

    if (data[0] == "laf") {
        const short f2_mask = 3840;
        const short f1_mask = 240;
        const short f0_mask = 15;
        my_emu->setFocus(2, my_emu->getRegister(CPU_emu::reg_stoi(data[1])) & f2_mask);
        my_emu->setFocus(1, my_emu->getRegister(CPU_emu::reg_stoi(data[1])) & f1_mask);
        my_emu->setFocus(0, my_emu->getRegister(CPU_emu::reg_stoi(data[1])) & f0_mask);
    }

    if (data[0] == "lfi") {
        my_emu->setFocus(CPU_emu::reg_stoi(data[1]), CPU_emu::reg_stoi(data[2]));
    }

    if (data[0] == "lf") {
        const short f_mask = 15;
        my_emu->setFocus(CPU_emu::reg_stoi(data[1]), my_emu->getRegister(CPU_emu::reg_stoi(data[2])) & f_mask);
    }

    if (data[0] == "mvf") {
        my_emu->setRegister(CPU_emu::reg_stoi(data[1]), my_emu->getFocus(CPU_emu::reg_stoi(data[2])));
    }

    if (data[0] == "lafi") {
        my_emu->setFocus(1, CPU_emu::reg_stoi(data[1]));
        my_emu->setFocus(2, CPU_emu::reg_stoi(data[2]));
        my_emu->setFocus(3, CPU_emu::reg_stoi(data[3]));
    }

    if (data[0] == "lb") {
        my_emu->setRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[1])),
                            my_emu->getMemByte(my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[3]))) +
                            (short)std::stoi(data[2])));
    }

    if (data[0] == "sb") {
        my_emu->setMemByte(my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[3]))) + (short)std::stoi(data[2]),
                            my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[1]))));
    }

    if (data[0] == "lw") {
        my_emu->setRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[1])),
                            my_emu->getMemWord(my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[3]))) +
                            (short)std::stoi(data[2])));
    }

    if (data[0] == "sw") {
        my_emu->setMemWord(my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[3]))) + (short)std::stoi(data[2]),
                            my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[1]))));
    }

    if (data[0] == "lwr") {
        my_emu->setRegister(CPU_emu::reg_stoi(data[1]),
                            my_emu->getMemWord(my_emu->getRegister(CPU_emu::reg_stoi(data[3])) +
                            (short)std::stoi(data[2])));
    }

    if (data[0] == "swr") {
        my_emu->setMemWord(my_emu->getRegister(CPU_emu::reg_stoi(data[3])) + (short)std::stoi(data[2]),
                            my_emu->getRegister(CPU_emu::reg_stoi(data[1])));
    }

    if (data[0] == "addri") {
        my_emu->setRegister(CPU_emu::reg_stoi(data[1]), my_emu->getRegister(CPU_emu::reg_stoi(data[2])) + (short)std::stoi(data[3]));
    }

    if (data[0] == "andi") {
        // TO DO
    }

    if (data[0] == "ori") {
        // TO DO
    }

    if (data[0] == "xori") {
        // TO DO
    }

    if (data[0] == "lbf") {
        my_emu->setFocus(CPU_emu::reg_stoi(data[1]),
                            my_emu->getMemByte(my_emu->getFocus(CPU_emu::reg_stoi(data[3])) +
                            (short)std::stoi(data[2])));
    }

    if (data[0] == "sbf") {
        my_emu->setMemByte(my_emu->getRegister(my_emu->getFocus(CPU_emu::reg_stoi(data[3]))) +
                            (short)std::stoi(data[2]),
                            my_emu->getFocus(CPU_emu::reg_stoi(data[1])));
    }

    if (data[0] == "lwf") {
        const short f2_mask = 3840;
        const short f1_mask = 240;
        const short f0_mask = 15;
        my_emu->setFocus(2, my_emu->getMemWord(my_emu->getRegister(CPU_emu::reg_stoi(data[2])) +
                            (short)std::stoi(data[1])) & f2_mask);
        my_emu->setFocus(1, my_emu->getMemWord(my_emu->getRegister(CPU_emu::reg_stoi(data[2])) +
                            (short)std::stoi(data[1])) & f1_mask);
        my_emu->setFocus(0, my_emu->getMemWord(my_emu->getRegister(CPU_emu::reg_stoi(data[2])) +
                            (short)std::stoi(data[1])) & f0_mask);
    }

    if (data[0] == "swf") {
        my_emu->setMemWord(my_emu->getRegister(CPU_emu::reg_stoi(data[2])) + (short)std::stoi(data[1]),
                            (my_emu->getFocus(2) << 8) + (my_emu->getFocus(1) << 4) + (my_emu->getFocus(0)));
    }

    if (data[0] == "csrrw") {
        // TO DO
    }

    if (data[0] == "ecall") {
        // TO DO
    }
}

int main() {
    CPU_emu *my_emu = new CPU_emu;

    //std::vector<std::string> lines = get_lines("examples/example1.txt");
    std::vector<std::string> lines = get_lines("examples/float_example.txt");

    for (my_emu->setPC(0); my_emu->getPC() < lines.size(); my_emu->setPC(my_emu->getPC() + 1)) {
        std::cout << "INPUT LINE: " << lines[my_emu->getPC()] << std::endl;
        process_instruction(my_emu, lines[my_emu->getPC()]);
    }

    my_emu->printInfo();

    delete my_emu;

    return 0;
}