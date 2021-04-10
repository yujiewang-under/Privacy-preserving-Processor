struct Adder{

	int len;
	struct Value* input1;
	struct Value* input2;
	struct Value* carrier_in;
	struct Value* carrier_out;
	struct Value* sum;
	Adder(){
		len=NN;
		create_value(sum,len);
		create_value(carrier_out,1);
	}
	Adder(int n){
		len=n;
		create_value(sum,len);
		create_value(carrier_out,1);
	}
	void add(struct Value* in1, struct Value* in2, struct Value* c_in){
			input1=in1;
			input2=in2;
			carrier_in=c_in;
            add();

	}
	void add(){
		assign_value(carrier_out,(unsigned long int)0);
		assign_value(sum,(unsigned long int)0);
		Signal * tmp;
            CREATE_SIGNAL(tmp);
            COPY_SIGNAL(carrier_out->v[0],carrier_in->v[0]);
            //COPY_SIGNAL(tmp,carrier_in->v[0]);
            
			for(int i=0;i<len;i++){

				XOR_SIGNAL(sum->v[i],input1->v[i],input2->v[i]);

				COPY_SIGNAL(tmp,carrier_out->v[0]);

				AND_SIGNAL(carrier_out->v[0],sum->v[i],carrier_out->v[0]);

				XOR_SIGNAL(sum->v[i],sum->v[i],tmp);

				AND_SIGNAL(tmp,input1->v[i],input2->v[i]);

				OR_SIGNAL(carrier_out->v[0],tmp,carrier_out->v[0]);

				//std::cout<< *(sum->v[i])<<*(carrier_out->v[0])<<*(input1->v[i])<<*(input2->v[i])<<std::endl;

			}


	}

	


};


struct ALU
{
	struct Adder* adder;
	struct Value* alu_control;
	//N_ALU_CONTROL
	struct Value* input1;
	struct Value* input2;

	struct Value* output;

	ALU(){
		adder=new Adder(NN);
		create_value(output,NN);
		
	}

	void compute(struct Value* in1,struct Value* in2,struct Value* alu_c)
	{
		input1=in1;
		input2=in2;
		alu_control=alu_c;
		compute();

	}
	void compute()
	{	assign_value(output,(unsigned long int)0);
		//Signal* carrier_in;
		//CREATE_SIGNAL(carrier_in);
		//XOR_SIGNAL(carrier_in,alu_control->v[1]);
		struct Value* in2;
		create_value(in2,NN);

		for(int i=0;i<NN;i++){
			XOR_SIGNAL(in2->v[i],alu_control->v[0],input2->v[i]);
		}
		
		struct Value* a_c;
		create_value(a_c,1);
		a_c->v[0]=alu_control->v[0];
		adder->add(input1,in2,a_c); 

		//struct Value* and_or_output;
		//create_value(and_or_output,N);

		struct Value* and_output;
		create_value(and_output,NN);

		struct Value* or_output;
		create_value(or_output,NN);

		Signal* not_3;
		CREATE_SIGNAL(not_3);
		NOT_SIGNAL(not_3,alu_control->v[2]);
		//struct Value* or_output;
		//create_value(or_output,N);
		for(int i=0;i<NN;i++){
			AND_SIGNAL(and_output->v[i],input1->v[i],input2->v[i]);
			AND_SIGNAL(and_output->v[i],and_output->v[i],not_3);

			OR_SIGNAL(or_output->v[i],input1->v[i],input2->v[i]);
			AND_SIGNAL(or_output->v[i],or_output->v[i],alu_control->v[2]);


		}

		
		struct Value* lessthan;
		create_value(lessthan,NN);
		COPY_SIGNAL(lessthan->v[0],adder->sum->v[adder->len-1]);

		struct Value** values=new struct Value*[4];
		values[0]=and_output;
		values[2]=or_output;
		values[1]=adder->sum;
		values[3]=lessthan;

		struct Value* signals;
		create_value(signals,2);
		signals->v[0]=alu_control->v[1];
		signals->v[1]=alu_control->v[2];


		 
		mux(output,values,signals);
		//display_value(output);
		//printf("result: %d, and: %d, or:%d, add_sub_less: %d \n",get_value(output),get_value(and_output),get_value(or_output),get_value(adder->sum));

	}
};

