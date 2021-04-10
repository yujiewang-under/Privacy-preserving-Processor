struct Registers{

	
	struct Value* read_reg1;
	struct Value* read_reg2;
	struct Value* write_reg;
	struct Value* write_data;
	struct Value* RegWrite;


	struct Value* output_reg1;
	struct Value* output_reg2;

	struct Value** registers;

	Registers(){

		create_value(output_reg1,NN);
		create_value(output_reg2,NN);
		registers=new struct Value*[N_REGISTER];

		for(int i=0;i<N_REGISTER;i++){
			create_value(registers[i],NN);
		}
	}

	void readFrom(struct Value* r1, struct Value* r2){
		read_reg1=r1;
		read_reg2=r2;
		readFrom();
	}
	void readFrom(){
		assign_value(output_reg1,0);
		assign_value(output_reg2,0);
		mux(output_reg1,registers,read_reg1);
		mux(output_reg2,registers,read_reg2);
	}

	void writeTo(struct Value* r, struct Value* d,struct Value* rw){
				write_reg=r;
				write_data=d;
				RegWrite=rw;
				writeTo();

	}

	void writeTo(){

		struct Value* select;
		int len=pow(2,write_reg->len);
		create_value(select,len);
		//printf("add %d\n",get_value(write_reg));
		demux(select,write_reg);
		///printf("here select %d\n",get_value(select));
		for(int i=0;i<len;i++){
			AND_SIGNAL(select->v[i],select->v[i],RegWrite->v[0]);
		}

		struct Value* to_write_data;
		create_value(to_write_data,NN);
		/*for(int i=0;i<N;i++){

			AND_SIGNAL(to_write_data->v[i],RegWrite->v[0],write_data->v[i]);
		}*/

		Signal* no;
		CREATE_SIGNAL(no);
		Signal* tt;
		CREATE_SIGNAL(tt);
		for(int i=0;i<len;i++){
			
			NOT_SIGNAL(no,select->v[i]);

			for(int j=0;j<NN;j++){
				AND_SIGNAL(registers[i]->v[j],registers[i]->v[j],no);
				AND_SIGNAL(tt,select->v[i],write_data->v[j]);
				XOR_SIGNAL(registers[i]->v[j],registers[i]->v[j],tt);

			}

		}



	}

	void display(int n){

		if(n<0){
			for(int i=0;i<N_REGISTER;i++)
			{
				printf("%d: %d\n",i,get_value(registers[i]));
			}

		}else{
			printf("%d: %d\n",n,get_value(registers[n]));
		}

	}



};

struct Memory{

	
	struct Value* reg_addr;
	
	struct Value* write_data;
	struct Value* RegWrite;

	struct Value* RegRead;

	struct Value* output_reg;
	
	struct Value** cells;

	Memory(){

		create_value(output_reg,NN);
		
		cells=new struct Value*[N_MEMORY];

		for(int i=0;i<N_MEMORY;i++){
			create_value(cells[i],CELL_LENGTH);
		}
	}

	

	void update(struct Value* addr, struct Value* d,struct Value* r,struct Value* w){
				reg_addr=addr;
				write_data=d;
				RegWrite=w;
				RegRead=r;
				update();

	}

	void update(){
		assign_value(output_reg,0);

		struct Value* select;
		int len=pow(2,N_MEMORY_BIT);
		create_value(select,len);

		struct Value* addr;
		create_value(addr,N_MEMORY_BIT);
		for(int i=0;i<N_MEMORY_BIT;i++){
			COPY_SIGNAL(addr->v[i],reg_addr->v[i]);

		}
		//printf("address %d\n",get_value(addr));
		demux(select,addr);
		//printf("here select %d, len: %d\n",get_value(select),select->len);


		struct Value* select_r;
		create_value(select_r,len);
		copy_value(select_r,select);

		struct Value* select_w;
		create_value(select_w,len);
		copy_value(select_w,select);

		for(int i=0;i<len;i++){
			AND_SIGNAL(select_r->v[i],select_r->v[i],RegRead->v[0]);
			AND_SIGNAL(select_w->v[i],select_w->v[i],RegWrite->v[0]);
		}

		
		
		Signal* no_r;
		CREATE_SIGNAL(no_r);
		//Signal* tt_r;
		//sCREATE_SIGNAL(tt_r);

		Signal* no_w;
		CREATE_SIGNAL(no_w);
		Signal* tt_w;
		CREATE_SIGNAL(tt_w);

		for(int i=0;i<len;i++){
			
			NOT_SIGNAL(no_r,select_r->v[i]);

			NOT_SIGNAL(no_w,select_w->v[i]);

			for(int j=0;j<NN/CELL_LENGTH && j+i<N_MEMORY;j++){

					for(int k=0;k<CELL_LENGTH ;k++){
						AND_SIGNAL(cells[i+j]->v[k],cells[i+j]->v[k],no_w);
						AND_SIGNAL(tt_w,select_w->v[i],write_data->v[j*CELL_LENGTH+k]);
						XOR_SIGNAL(cells[i+j]->v[k],cells[i+j]->v[k],tt_w);

						AND_SIGNAL(tt_w,select_r->v[i],cells[i+j]->v[k]);
						AND_SIGNAL(output_reg->v[j*CELL_LENGTH+k],output_reg->v[j*CELL_LENGTH+k],no_r);
						XOR_SIGNAL(output_reg->v[j*CELL_LENGTH+k],output_reg->v[j*CELL_LENGTH+k],tt_w);
				}

			}

		}



	}

	void display(int n){

		if(n<0){
			for(int i=0;i<N_MEMORY;i++)
			{
				printf("%d: %d\n",i,get_value(cells[i]));
			}

		}else{
			printf("%d: %d\n",n,get_value(cells[n]));
		}

	}



};

struct Instruction_Memory{

	
	struct Value* pc;
	
	struct Value* instruction;
	struct Value** cells;

	Instruction_Memory(){

		create_value(instruction,NN);
		
		cells=new struct Value*[N_INSTRUCTION];

		for(int i=0;i<N_INSTRUCTION;i++){
			create_value(cells[i],CELL_LENGTH);
		}
	}

	

	struct Value* get_instruction(struct Value* p){
				pc=p;
				return get_instruction();

	}

	struct Value* get_instruction(){
		assign_value(instruction,0);

		struct Value* select;
		int len=pow(2,N_INSTRUCTION_BIT);
		create_value(select,len);

		struct Value* addr;
		create_value(addr,N_INSTRUCTION_BIT);
		for(int i=0;i<N_INSTRUCTION_BIT;i++){
			COPY_SIGNAL(addr->v[i],pc->v[i]);

		}
		//printf("address %d\n",get_value(addr));
		demux(select,addr);
		//printf("here select %d, len: %d\n",get_value(select),select->len);


		
		
		
		Signal* no_r;
		CREATE_SIGNAL(no_r);
		//Signal* tt_r;
		//sCREATE_SIGNAL(tt_r);

		
		Signal* tt_w;
		CREATE_SIGNAL(tt_w);

		for(int i=0;i<len;i++){
			
			NOT_SIGNAL(no_r,select->v[i]);

			

			for(int j=0;j<NN/CELL_LENGTH && j+i<N_INSTRUCTION;j++){

					for(int k=0;k<CELL_LENGTH ;k++){

						AND_SIGNAL(tt_w,select->v[i],cells[i+j]->v[k]);
						AND_SIGNAL(instruction->v[j*CELL_LENGTH+k],instruction->v[j*CELL_LENGTH+k],no_r);
						XOR_SIGNAL(instruction->v[j*CELL_LENGTH+k],instruction->v[j*CELL_LENGTH+k],tt_w);
				}

			}

		}

		return instruction;


	}

	void display(int n){

		if(n<0){
			for(int i=0;i<N_INSTRUCTION;i++)
			{
				printf("%d: %d\n",i,get_value(cells[i]));
			}

		}else{
			printf("%d: %d\n",n,get_value(cells[n]));
		}

	}



};
