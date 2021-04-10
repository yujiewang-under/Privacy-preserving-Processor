struct Processor{
	struct Instruction_Memory instruction_memory;

	struct MUX2 mux_RegDst;

	struct Registers registers;

	struct SignExtend signExtend;

	struct MUX2 mux_ALUSrc;

	struct ALU alu;

	struct Memory memory;

	struct MUX2 mux_MemToReg;

	struct Value* PC;

	struct Control control;

	struct Adder PCadder4;

	struct Adder PCadder;

	struct MUX2 mux_PCSrc;

	struct ShiftLeft shiftLeft;


	struct Value* curr_instruction;

	Processor():mux_RegDst(5),signExtend(NN),mux_ALUSrc(NN),mux_MemToReg(NN),mux_PCSrc(NN),shiftLeft(2){
		create_value(PC,NN);

	}
	void init_processor(const char* instruction_file, const char* register_file, const char* memory_file){
		assign_data(instruction_memory.cells,instruction_file,CELL_LENGTH,NN);
		assign_data(registers.registers,register_file,NN,NN);
		assign_data(memory.cells,memory_file,CELL_LENGTH,NN);
	}

	void display_status(){
		printf("PC:%d \n",get_value(PC));
		printf("instruction: ");
		display_value(instruction_memory.instruction);
		printf("\ncontrol: ");
		control.display_signals();

		printf("\nregisters:\n");
		registers.display(-1);
		printf("\nmemory:\n");
		memory.display(-1);


	}
	void execute(){

		choice=INS_MEM;
		printf("\nstarting get instruction;\n");

		curr_instruction =instruction_memory.get_instruction(PC);

		choice=CONTROL;

		printf("starting generating control signals;\n");

		control.generate_control_signals(curr_instruction);

		struct Value* read_reg1;
		subvalue(read_reg1,curr_instruction,21,25);

		struct Value* read_reg2;
		subvalue(read_reg2,curr_instruction,16,20);

		struct Value* write_reg;
		subvalue(write_reg,curr_instruction,11,15);

		choice=OTHER;
		mux_RegDst.select(read_reg2,write_reg,control.RegDst->v[0]);

		choice=REGS;

		printf("starting reading from registers;\n");

		registers.readFrom(read_reg1,read_reg2);


		struct Value* immediate;
		subvalue(immediate,curr_instruction,0,15);

		choice=OTHER;

		signExtend.sign_extend(immediate);

		

		mux_ALUSrc.select(registers.output_reg2,signExtend.output,control.ALUSrc->v[0]);

		choice=ALU;

		printf("starting ALU;\n");

		alu.compute(registers.output_reg1,mux_ALUSrc.output,control.ALUOp);

		choice=MEM;
		printf("starting memory update;\n");

		memory.update(alu.output,registers.output_reg2,control.MemRead,control.MemWrite);
		choice=OTHER;
		mux_MemToReg.select(alu.output,memory.output_reg,control.MemToReg->v[0]);

		choice= REGS;

		printf("starting wrting registers;\n");
		registers.writeTo(mux_RegDst.output,mux_MemToReg.output,control.RegWrite);

		choice=OTHER;
		shiftLeft.shift_left(signExtend.output);

		struct Value* const4;
		create_value(const4,NN);
		assign_value(const4,4);
		struct Value* const0;
		create_value(const0,1);

		PCadder4.add(PC,const4,const0);

		PCadder.add(PCadder4.sum,shiftLeft.output,const0);

		control.complete_PCSrc(alu.output);

		mux_PCSrc.select(PCadder4.sum,PCadder.sum,control.PCSrc_half->v[0]);

		copy_value(PC,mux_PCSrc.output);


		





	}

};