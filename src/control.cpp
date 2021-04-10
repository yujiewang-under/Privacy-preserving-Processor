struct Control{

	struct Value* instruction;

	struct Value* op;
	struct Value* func;

	struct Value* RegDst;
	struct Value* RegWrite;
	struct Value* ALUSrc;
	struct Value* ALUOp;
	struct Value* MemWrite;
	struct Value* MemRead;
	struct Value* MemToReg;

	struct Value* PCSrc_half;

	struct Value* select;

	Control(){

		create_value(op,OP_LEN);
		create_value(func,FUNC_LEN);

		create_value(RegDst,1);
		create_value(RegWrite,1);
		create_value(ALUSrc,1);
		create_value(ALUOp,3);
		create_value(MemWrite,1);
		create_value(MemRead,1);
		create_value(MemToReg,1);

		create_value(PCSrc_half,1);

		create_value(select,9);

	}

	void compare(Signal* output, struct Value* code, const char* pattern){
		SET_SIGNAL(output);

		
		Signal* tmp;
		CREATE_SIGNAL(tmp);

		for(int i=0; pattern[i]!='\n';i++){
			if(pattern[i]=='0'){
				NOT_SIGNAL(tmp,code->v[i]);
				AND_SIGNAL(output,output,tmp);

			}else if(pattern[i]=='1'){
				AND_SIGNAL(output,output,code->v[i]);
			}
		}


	}

	void complete_PCSrc(struct Value* alu_out){
		Signal* no;
		CREATE_SIGNAL(no);
		for(int i=0; i<NN;i++){
			NOT_SIGNAL(no,alu_out->v[i]);
			AND_SIGNAL(PCSrc_half->v[0],PCSrc_half->v[0],no);

		}
		//AND_SIGNAL(PCSrc_half->v[0],PCSrc_half->v[0],no);


	}

	void xor_if(struct Value* output,Signal* s, const char* pattern){
		/*Signal* one;
		ONE_SIGNAL(one);

		Signal* zero;
		ONE_SIGNAL(zero);*/

		Signal* tmp;
		CREATE_SIGNAL(tmp);

		for(int i=0; pattern[i]!='\n';i++){
			if(pattern[i]=='0'){
				

			}else if(pattern[i]=='1'){

				XOR_SIGNAL(output->v[i],output->v[i],s);
			}
		}

	}

	void generate_control_signals(struct Value* ins){
		instruction=ins;

		for(int i=0;i<OP_LEN;i++){
			COPY_SIGNAL(op->v[i],instruction->v[i+OP_START]);
		}
		for(int i=0;i<FUNC_LEN;i++){
			COPY_SIGNAL(func->v[i],instruction->v[i+FUNC_START]);
		}
		generate_control_signals();


	}

	void generate_control_signals(){

		assign_value(RegDst,0);
		assign_value(RegWrite,0);
		assign_value(ALUSrc,0);
		assign_value(ALUOp,0);
		assign_value(MemWrite,0);
		assign_value(MemRead,0);
		assign_value(MemToReg,0);

		assign_value(PCSrc_half,0);


		assign_value(select,511);
		Signal * r_code;
		CREATE_SIGNAL(r_code);
		compare(r_code,op,R_OP);

		compare(select->v[0],func,ADD_CODE_FUNC);
		AND_SIGNAL(select->v[0],select->v[0],r_code);

		compare(select->v[1],func,SUB_CODE_FUNC);
		AND_SIGNAL(select->v[1],select->v[1],r_code);

		compare(select->v[2],func,AND_CODE_FUNC);
		AND_SIGNAL(select->v[2],select->v[2],r_code);

		compare(select->v[3],func,OR_CODE_FUNC);
		AND_SIGNAL(select->v[3],select->v[3],r_code);

		compare(select->v[4],func,SLT_CODE_FUNC);
		AND_SIGNAL(select->v[4],select->v[4],r_code);


		compare(select->v[5],op,LW_CODE);
		compare(select->v[6],op,SW_CODE);

		compare(select->v[7],op,BEQ_CODE);

		compare(select->v[8],op,ADD_I_CODE);
		//compare(select->v[8],J_CODE);


		COPY_SIGNAL(RegDst->v[0],r_code);

		COPY_SIGNAL(RegWrite->v[0],r_code);
		XOR_SIGNAL(RegWrite->v[0],RegWrite->v[0],select->v[5]);
		XOR_SIGNAL(RegWrite->v[0],RegWrite->v[0],select->v[8]);

		COPY_SIGNAL(ALUSrc->v[0],select->v[5]);
		XOR_SIGNAL(ALUSrc->v[0],ALUSrc->v[0],select->v[6]);
		XOR_SIGNAL(ALUSrc->v[0],ALUSrc->v[0],select->v[8]);

		xor_if(ALUOp,select->v[0],"010\n");
		xor_if(ALUOp,select->v[1],"110\n");
		xor_if(ALUOp,select->v[2],"000\n");
		xor_if(ALUOp,select->v[3],"001\n");
		xor_if(ALUOp,select->v[4],"111\n");
		xor_if(ALUOp,select->v[5],"010\n");
		xor_if(ALUOp,select->v[6],"010\n");
		xor_if(ALUOp,select->v[7],"110\n");
		xor_if(ALUOp,select->v[8],"010\n");

		COPY_SIGNAL(MemWrite->v[0],select->v[6]);

		COPY_SIGNAL(MemRead->v[0],select->v[5]);

		COPY_SIGNAL(MemToReg->v[0],select->v[5]);

		COPY_SIGNAL(PCSrc_half->v[0],select->v[7]);
		//xor_if(RegDst,r_code,R_REGDST);
		//xor_if(RegDst,select->v[5],"0\n");


	}

	void display_signals(){
		display_value(RegDst);
		printf(" ");
		display_value(RegWrite);
		printf(" ");
		display_value(ALUSrc);
		printf(" ");
		display_value(ALUOp);
		printf(" ");
		display_value(MemWrite);
		printf(" ");
		display_value(MemRead);
		printf(" ");
		display_value(MemToReg);
		printf(" ");
		display_value(PCSrc_half);
		printf(" ");
		display_value(select);
		printf("\n");
	}

};