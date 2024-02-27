# Virtual-Machine-C-
This projects implement an assembly language interpreter that will run assembly language instructions with accordance to a given simplified virtual machine architecture.


The interpreter is expected to execute an assembly program and generate a display of the content of the virtual machine after the execution of the program.


The assembly language for the given virtual machine supports various operations such as:
1. Move operations,
2. Mathematical operations,
3. Rotation and shifting operations,
4. Basic I/O operations,
5. Loading data from memory,
6. Storing data to memory.


**1. Data Registers**
7 general-purpose data registers: R0, R1, R2, R3, R4, R5, R6. Each register is represented as a one byte (8 bits) in size. The contents of these registers are updated after executing each assembly instruction by the runner. These registers can contain signed bytes (values between -128 and 127).

**2. Program Counter (PC)**
The program counter starts always with the value 0, then it is incremented whenever the runner (interpreter) executes an assembly instruction.

**3. Flags**
- _Overflow Flag (OF)_: A single bit flag (or a byte) indicating arithmetic overflow. It is set when an arithmetic operation results in a value greater than 127.
- _Underflow Flag (UF)_: A single bit flag (or byte) indicating arithmetic underflow. Set when an arithmetic operation results in a value smaller than -128.
- _Carry Flag (CF)_: A single bit flag (or a byte) indicating carry in arithmetic operations. Set when an arithmetic operation results in a carry. An addition can generate a value larger then 8 bits, therefore the carry flag is set.
- _Zero Flag (ZF)_: A single bit flag indicating the result of an operation is zero. Set when the result of an operation is zero.

**4. Memory**
The memory can be represented as a one-dimensional array of 64 signed bytes. Memory addresses are numbered from 0 to 63. Memory can e accessed only by a load or store operations.

**5. Assembly Language Runner (interpreter)**
The interpreter reads an assembly program from a ".asm" file (text file). It must execute the instructions sequentially on the virtual machine updating the PC (program counter) after each instruction. At the end of execution, it will produce a dump of all registers and memory to the screen in addition to the output window (results of the I/O operations).
