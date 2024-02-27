#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

int const REGISTER_SIZE = 7;
int const MEMORY_SIZE = 64;

struct VirtualMachine {
    int registers[REGISTER_SIZE];
    int memory[MEMORY_SIZE];
    bool overflowFlag, underflowFlag, carryFlag, zeroFlag;
    int programCounter; // Added program counter to track the current instruction
};


// Function declarations
void MOV(int registers[], int memory[], char src, int rsrc, int rdst, int value1);
void STORE(int registers[], int memory[], char dst, int rsrc, int rdst, int value2);
void LOAD(int registers[], int memory[], char dst, int rsrc, int rdst, int value2);
void OUT(int registers[], int rsrc);
void IN(int registers[], int rsrc);
void ADD(int registers[], char src, int rdst, int rsrc,int value1, VirtualMachine&vm);
void MUL(int registers[], char src, int rdst, int rsrc, int value1, VirtualMachine&vm);
void DIV(int registers[], char src, int rdst, int rsrc, int value1, VirtualMachine&vm);
void SUB(int registers[], char src, int rdst, int rsrc, int value1, VirtualMachine&vm);
void INC(int registers[], int rdst, VirtualMachine&vm);
void DEC(int registers[], int rdst, VirtualMachine&vm);
void ROL(int registers[], int rsrc, int value2);
void ROR(int registers[], int rsrc, int value2);
void SHL(int registers[], int rsrc, int value2);
void SHR(int registers[], int rsrc, int value2);


string trim(string s);

int main() {
    ifstream infile;
    infile.open("fileInput1.asm");

    if (infile.fail()) {
        cout << "File not found." << endl;
        return EXIT_FAILURE;
    }

    // Initialize your Virtual Machine
    VirtualMachine vm;
    // Initialize registers and memory
    for (int i = 0; i < REGISTER_SIZE; ++i) {
        vm.registers[i] = 0;
    }
    for (int i = 0; i < MEMORY_SIZE; ++i) {
        vm.memory[i] = 0;
    }
    vm.overflowFlag = false;
    vm.underflowFlag = false;
    vm.carryFlag = false;
    vm.zeroFlag = false;
    vm.programCounter = 0;


    string line;

    while (getline(infile, line)) {
        stringstream ss(line);
        string word;
        bool isLineParsed = false;

        while (getline(ss, word, '\n') && !isLineParsed) {

            // Determining the first parameters of functions
            int m = 2; // to get register num without R
            int rsrc,
                rdst,
                value1,
                value2;
            char src,
                dst;

            while (m < word.length() && word.substr(m, 1) != " ") {
                m++;
            }


            if (word.substr(m+1,1) == "R") // Register
            {
                src = 'R';
                rsrc = stoi(word.substr(m+2));
            }
            else if (word.substr(m+1,1) == "[") // Memory adress in register
            {
                src = 'M';
                rsrc = stoi(word.substr(m+3,1));
            }
            else // Just an integer
            {
                src = 'V';
                value1 = stoi(word.substr(m+1));
            }

            // Determining the second parameters of functions
            if(word.substr(0,2) != "IN" && word.substr(0,3) != "OUT" && word.substr(0,3) != "INC" && word.substr(0,3) != "DEC")
            {
                int a = 5; // to get register num without R

                while (a < word.length() && word.substr(a, 1) != ",") {
                    a++;
                }

                if (word.substr(a+2,1) == "R") // Register
                {
                    dst = 'R';
                    rdst = stoi(word.substr(a+3,1));
                }
                else if (word.substr(a+2,1) == "[") // Memory adress in register
                {
                    dst = 'M';
                    rdst = stoi(word.substr(a+4,1));
                }
                else // Just an integer
                {
                    dst = 'V';
                    value2 = stoi(word.substr(a+2));
                }
            }


            word = trim(word);

            if (word.substr(0, 3) == "MOV") {
                isLineParsed = true;
                vm.overflowFlag = false;
                vm.underflowFlag = false;
                vm.carryFlag = false;
                vm.zeroFlag = false;
                MOV(vm.registers, vm.memory, src, rsrc, rdst, value1);
                vm.programCounter++;

            } else if (word.substr(0, 3) == "ADD") {
                isLineParsed = true;
                vm.overflowFlag = false;
                vm.underflowFlag = false;
                vm.carryFlag = false;
                vm.zeroFlag = false;
                ADD(vm.registers, src, rdst, rsrc, value1, vm);
                vm.programCounter++;

            } else if (word.substr(0, 5) == "STORE") {
                isLineParsed = true;
                vm.overflowFlag = false;
                vm.underflowFlag = false;
                vm.carryFlag = false;
                vm.zeroFlag = false;
                STORE(vm.registers, vm.memory, dst, rsrc, rdst, value2);
                vm.programCounter++;

            } else if (word.substr(0, 3) == "INC") {
                isLineParsed = true;
                vm.overflowFlag = false;
                vm.underflowFlag = false;
                vm.carryFlag = false;
                vm.zeroFlag = false;
                INC(vm.registers, rsrc, vm);
                vm.programCounter++;

            } else if (word.substr(0, 3) == "DEC") {
                isLineParsed = true;
                vm.overflowFlag = false;
                vm.underflowFlag = false;
                vm.carryFlag = false;
                vm.zeroFlag = false;
                DEC(vm.registers, rsrc, vm);
                vm.programCounter++;

            } else if (word.substr(0, 2) == "IN") {
                isLineParsed = true;
                vm.overflowFlag = false;
                vm.underflowFlag = false;
                vm.carryFlag = false;
                vm.zeroFlag = false;
                IN(vm.registers, rsrc);
                vm.programCounter++;

            } else if (word.substr(0, 3) == "OUT") {
                isLineParsed = true;
                vm.overflowFlag = false;
                vm.underflowFlag = false;
                vm.carryFlag = false;
                vm.zeroFlag = false;
                OUT(vm.registers, rsrc);
                vm.programCounter++;

            } else if (word.substr(0, 4) == "LOAD") {
                isLineParsed = true;
                vm.overflowFlag = false;
                vm.underflowFlag = false;
                vm.carryFlag = false;
                vm.zeroFlag = false;
                LOAD(vm.registers, vm.memory, dst, rsrc, rdst, value2);
                vm.programCounter++;

            } else if (word.substr(0, 3) == "MUL") {
                isLineParsed = true;
                vm.overflowFlag = false;
                vm.underflowFlag = false;
                vm.carryFlag = false;
                vm.zeroFlag = false;
                MUL(vm.registers, src, rdst, rsrc, value1, vm);
                vm.programCounter++;

            } else if (word.substr(0, 3) == "DIV") {
                isLineParsed = true;
                vm.overflowFlag = false;
                vm.underflowFlag = false;
                vm.carryFlag = false;
                vm.zeroFlag = false;
                DIV(vm.registers, src, rdst, rsrc, value1, vm);
                vm.programCounter++;

            } else if (word.substr(0, 3) == "SUB") {
                isLineParsed = true;
                vm.overflowFlag = false;
                vm.underflowFlag = false;
                vm.carryFlag = false;
                vm.zeroFlag = false;
                SUB(vm.registers, src, rdst, rsrc, value1, vm);
                vm.programCounter++;

            } else if (word.substr(0,3) == "ROL") {
                isLineParsed = true;
                vm.overflowFlag = false;
                vm.underflowFlag = false;
                vm.carryFlag = false;
                vm.zeroFlag = false;
                ROL(vm.registers, rsrc, value2);
                vm.programCounter++;

            } else if (word.substr(0,3) == "ROR") {
                isLineParsed = true;
                vm.overflowFlag = false;
                vm.underflowFlag = false;
                vm.carryFlag = false;
                vm.zeroFlag = false;
                ROR(vm.registers, rsrc, value2);
                vm.programCounter++;

            } else if (word.substr(0,3) == "SHL") {
                isLineParsed = true;
                vm.overflowFlag = false;
                vm.underflowFlag = false;
                vm.carryFlag = false;
                vm.zeroFlag = false;
                SHL(vm.registers, rsrc, value2);
                vm.programCounter++;

            } else if (word.substr(0,3) == "SHR") {
                isLineParsed = true;
                vm.overflowFlag = false;
                vm.underflowFlag = false;
                vm.carryFlag = false;
                vm.zeroFlag = false;
                SHR(vm.registers, rsrc, value2);
                vm.programCounter++;

            } else {
                cout << "this line cannot be parsed: " << line << endl;
            }
        }
    }

    infile.close();

    ofstream myfile ("fileOutput1.txt"); // print PC on txt file

    // Output the state of the Virtual Machine
    myfile << "Registers: ";
    for (int k = 0; k < REGISTER_SIZE; k++) {
        myfile << setw(4) << setfill('0') << vm.registers[k] << " ";
    }
    myfile << "#" << endl;
    myfile << "Flags: " << vm.carryFlag << " " << vm.overflowFlag << " " << vm.underflowFlag  << " " << vm.zeroFlag << " " << "#" << endl;
    myfile << "PC: " << vm.programCounter << endl;
    myfile << "Memory:" << endl;
    for (int l = 0; l < MEMORY_SIZE; l += 8) {
        for (int i = 0; i < 8; i++) {
            int index = l + i;
            if (index < MEMORY_SIZE) {
                myfile << setw(4) << setfill('0') << vm.memory[index] << " ";
            } else {
                myfile << "0000 ";
            }
        }
        myfile << endl;
    }
    myfile << "#" << endl;

    // Dump to screen
    cout << "Registers: ";
    for (int k = 0; k < REGISTER_SIZE; k++) {
        cout << setw(4) << setfill('0') << vm.registers[k] << " ";
    }
    cout << "#" << endl;
    cout << "Flags: " << vm.carryFlag << " " << vm.overflowFlag << " " << vm.underflowFlag  << " " << vm.zeroFlag << " " << "#" << endl;
    cout << "PC: " << vm.programCounter << endl;
    cout << "Memory:" << endl;
    for (int l = 0; l < MEMORY_SIZE; l += 8) {
        for (int i = 0; i < 8; i++) {
            int index = l + i;
            if (index < MEMORY_SIZE) {
                cout << setw(4) << setfill('0') << vm.memory[index] << " ";
            } else {
                cout << "0000 ";
            }
        }
        cout << endl;
    }
    cout << "#" << endl;


    return 0;
}

// Implement your MOV, ADD, store, OUT, IN, and other functions here
// MOV
void MOV(int registers[], int memory[], char src, int rsrc, int rdst, int value1) {
    if (src == 'V')
        registers[rdst] = value1;
    else if (src == 'R')
        registers[rdst] = registers [rsrc];
    else if (src == 'M')
        registers[rdst] = memory[registers[rsrc]];
    }

// ADD
void ADD(int registers[], char src, int rdst, int rsrc,int value1, VirtualMachine&vm){
    if (src == 'R')
        registers[rdst] = registers[rdst] + registers[rsrc];
    else if (src == 'V')
        registers[rdst] = registers[rdst] + value1;

    vm.underflowFlag =(vm.registers[rdst]< 0);
    vm.overflowFlag =(vm.registers[rdst]>127);
    vm.carryFlag = ((vm.registers[rdst] < 0)||(vm.registers[rdst] > 127));
    vm.zeroFlag = (vm.registers[rdst] ==0);
    }

// STORE
void STORE(int registers[], int memory[], char dst, int rsrc, int rdst, int value2) {
    if (dst == 'V')
        memory[value2] = registers[rsrc];
    else if (dst == 'M')
        memory[registers[rdst]] = registers[rsrc];
    }

// INC
void INC(int registers[], int rsrc, VirtualMachine&vm) {
    registers[rsrc]++;

    vm.underflowFlag =(vm.registers[rsrc] < 0);
    vm.overflowFlag =(vm.registers[rsrc] > 127);
    vm.carryFlag = ((vm.registers[rsrc] < 0)||(vm.registers[rsrc] > 127));
    vm.zeroFlag = (vm.registers[rsrc] == 0);

    }

// DEC
void DEC(int registers[], int rsrc, VirtualMachine&vm) {
    registers[rsrc]--;

    vm.underflowFlag =(vm.registers[rsrc] < 0);
    vm.overflowFlag =(vm.registers[rsrc] > 127);
    vm.carryFlag = ((vm.registers[rsrc] < 0)||(vm.registers[rsrc] > 127));
    vm.zeroFlag = (vm.registers[rsrc] == 0);

    }

// LOAD
void LOAD (int registers[], int memory[], char dst, int rsrc, int rdst, int value2) {
    if (dst == 'V')
        registers[rsrc] = memory[value2];
    else if (dst == 'M')
        registers[rsrc] = memory[registers[rdst]];
    }

// MUL
void MUL(int registers[], char src, int rdst, int rsrc, int value1, VirtualMachine&vm){
    if (src == 'R')
        registers[rdst] = registers[rdst] * registers[rsrc];
    else if (src == 'V')
        registers[rdst] = registers[rdst] * value1;

    vm.underflowFlag =(vm.registers[rdst] < 0);
    vm.overflowFlag =(vm.registers[rdst] > 127);
    vm.carryFlag = ((vm.registers[rdst] < 0)||(vm.registers[rdst] > 127));
    vm.zeroFlag = (vm.registers[rdst] == 0);
    }

// DIV
void DIV(int registers[], char src, int rdst, int rsrc, int value1, VirtualMachine&vm){

    if (src == 'R'){
        if (registers[rsrc] == 0)
            registers[rdst] = 0;
        else
            registers[rdst] = registers[rdst] / registers[rsrc];
    } else if (src == 'V') {
         if (value1 == 0)
            registers[rdst] = 0;
        else
            registers[rdst] = registers[rdst] / value1;

    }

    vm.underflowFlag =(vm.registers[rdst] < 0);
    vm.overflowFlag =(vm.registers[rdst] > 127);
    vm.carryFlag = ((vm.registers[rdst] < 0)||(vm.registers[rdst] > 127));
    vm.zeroFlag = (vm.registers[rdst] == 0);
    }

// SUB
void SUB(int registers[], char src, int rdst, int rsrc, int value1, VirtualMachine&vm){
    if (src == 'R')
        registers[rdst] = registers[rdst] - registers[rsrc];
    else if (src == 'V')
        registers[rdst] = registers[rdst] - value1;

    vm.underflowFlag =(vm.registers[rdst] < 0);
    vm.overflowFlag =(vm.registers[rdst] > 127);
    vm.carryFlag = ((vm.registers[rdst] < 0)||(vm.registers[rdst] > 127));
    vm.zeroFlag = (vm.registers[rdst] == 0);
    }

// OUT
void OUT(int registers[], int rsrc) {
        cout << registers[rsrc] << endl;
    }

// IN
void IN(int registers[], int rsrc) {
        cout << "User input for R" << rsrc << " -> ";
        cin >> registers[rsrc];
    }

// ROL
void ROL(int registers[], int rsrc, int value2) {

    int binary[8];
    int num = registers[rsrc];
    // determining if number is negative or positive
    if(num < 0)
    {
        binary[0] = 1;
        num = num * -1;
    }
    else
        binary[0] = 0;

    // converting the numbers into binary
    int i;
    for(i=7; i>0; i--)
    {
        binary[i] = (num % 2);
        num = num / 2;
    }

    // rorating binary to left by value2 times
    int rotate = 0;
    while (rotate < value2) {
        int firstBit = binary[0];
        for (int i = 0; i <= 6; i++) {
            binary[i] = binary[i + 1];
        }
        binary[7] = firstBit;
        rotate++;
    }

    int count = 0,
    decimalValue = 0;

    for (int i = 7; i >= 1; i--) {

        decimalValue += (binary[i] * pow(2,count));
        count ++;
    }

    if (binary[0] == 0)
        decimalValue = decimalValue * 1;
    else if (binary[0] == 1)
        decimalValue = decimalValue * -1;

    registers[rsrc] = decimalValue;

}

// ROR
void ROR(int registers[], int rsrc, int value2) {

    int binary[8];
    int num = registers[rsrc];
    // determining if number is negative or positive
    if(num < 0)
    {
        binary[0] = 1;
        num = num * -1;
    }
    else
        binary[0] = 0;

    // converting the numbers into binary
    int i;
    for(i=7; i>0; i--)
    {
        binary[i] = (num % 2);
        num = num / 2;
    }

    // rorating binary to right by value2 times
    int rotate = 0;
    while (rotate < value2) {
        int lastBit = binary[7];
        for (int i = 7; i > 0; i--) {
            binary[i] = binary[i - 1];
        }
        binary[0] = lastBit;
        rotate++;
    }

    int count = 0,
    decimalValue = 0;

    for (int i = 7; i >= 1; i--) {

        decimalValue += (binary[i] * pow(2,count));
        count ++;
    }

    if (binary[0] == 0)
        decimalValue = decimalValue * 1;
    else if (binary[0] == 1)
        decimalValue = decimalValue * -1;

    registers[rsrc] = decimalValue;

}

// SHL
void SHL(int registers[], int rsrc, int value2) {

    int binary[8];
    int num = registers[rsrc];
    // determining if number is negative or positive
    if(num < 0)
    {
        binary[0] = 1;
        num = num * -1;
    }
    else
        binary[0] = 0;

    // converting the numbers into binary
    int i;
    for(i=7; i>0; i--)
    {
        binary[i] = (num % 2);
        num = num / 2;
    }

    // shifting binary to left by value2 times
    int shift = 0;
    while (shift < value2) {
        for (int i = 0; i < 7; i++) {
            binary[i] = binary[i + 1];
        }
        binary[7] = 0;
        shift++;
    }

    int count = 0,
    decimalValue = 0;

    for (int i = 7; i >= 1; i--) {

        decimalValue += (binary[i] * pow(2,count));
        count ++;
    }

    if (binary[0] == 0)
        decimalValue = decimalValue * 1;
    else if (binary[0] == 1)
        decimalValue = decimalValue * -1;

    registers[rsrc] = decimalValue;

}

// SHR
void SHR(int registers[], int rsrc, int value2) {

    int binary[8];
    int num = registers[rsrc];
    // determining if number is negative or positive
    if(num < 0)
    {
        binary[0] = 1;
        num = num * -1;
    }
    else
        binary[0] = 0;

    // converting the numbers into binary
    int i;
    for(i=7; i>0; i--)
    {
        binary[i] = (num % 2);
        num = num / 2;
    }

    // shifting binary to right by value2 times
    int shift = 0;
    while (shift < value2) {
        for (int i = 7; i > 0; i--) {
            binary[i] = binary[i - 1];
        }
        binary[0] = 0;
        shift++;
    }

    int count = 0,
    decimalValue = 0;

    for (int i = 7; i >= 1; i--) {

        decimalValue += (binary[i] * pow(2,count));
        count ++;
    }

    if (binary[0] == 0)
        decimalValue = decimalValue * 1;
    else if (binary[0] == 1)
        decimalValue = decimalValue * -1;

    registers[rsrc] = decimalValue;

}


string trimLeft(string s)
{
    for (int c = 0; c < s.length(); c++)
    {
        if (s[0] == ' ')
        {
            s.erase(0, 1);
        }
    }
    return s;
}

string trimRight(string s)
{
    for (int c = s.length() - 1; c >= 0; c--)
    {
        if (s[s.length() - 1] == ' ')
        {
            s.erase(s.length() - 1, 1);
        }
    }
    return s;
}

string trim(string s)
{
    s = trimLeft(s);
    s = trimRight(s);
    return s;
}
