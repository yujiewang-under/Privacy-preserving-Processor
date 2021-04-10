


#define N_MEMORY 64
#define N_MEMORY_BIT 6

#define N_INSTRUCTION 64
#define N_INSTRUCTION_BIT 6






#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>

#define NN 32
#define CELL_LENGTH 8

#define N_ALU_CONTROL 3

#define N_REGISTER 32




#define OP_START 26
#define OP_LEN   6
#define FUNC_START 0
#define FUNC_LEN   6

#define R_OP           "000000\n"

#define ADD_CODE_FUNC "000001\n"
#define SUB_CODE_FUNC "010001\n"
#define AND_CODE_FUNC "001001\n"
#define OR_CODE_FUNC  "101001\n"
#define SLT_CODE_FUNC "010101\n"


#define LW_CODE  "110001\n"
#define SW_CODE  "110101\n"

#define BEQ_CODE  "001000\n"

#define ADD_I_CODE     "000100\n"
//#define J_CODE    "010000\n"

#define R_REGDST "1\n"
#define R_REGWRITE "1\n"
#define R_ALUSRC "0\n"
#define R_MEMWITE "0\n"
#define R_MEMREAD "0\n"
#define R_MEMTOREG "0\n"


