# Privacy-preserving Processor
 a MIPS-like processor supported by TFHE that can run encrypted instructions

###Dependency
Install  tfhe from https://github.com/tfhe/tfhe

###Installation
`cd ./src`
`make demo` for running non-encrypted instructions
`make` for running encrypted instructions
###Configure setting
in the config.h file, change the parameters to set **the number of execution**, **memory size**, **initialization data**, etc.

### Run your  own instructions
I built a very raw assembler(assembler.py), put your 'assembly code' in a file, to translate it into machine instruction, run
`python assembler.py input_assembly_file output_instruction_file`

Please notice that, this MIPS-like processor support limited  types of operation, please see the report for details.

