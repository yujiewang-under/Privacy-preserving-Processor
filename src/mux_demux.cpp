
void mux(struct Value* output,struct Value** values, struct Value* signals)
{
		assign_value(output,0);
	int len=pow(2,signals->len);

	Signal** ss = (Signal**) malloc(len*sizeof(Signal*));

	for(int i=0;i<len;i++){
		ONE_SIGNAL(ss[i]);

	}

	//int tmp=len/2;
	int tmp=1;
	for(int i=0;i<signals->len;i++){
		Signal * no;
		CREATE_SIGNAL(no);
		NOT_SIGNAL(no,signals->v[i]);

		for(int j=0;j<len;j++){
			if((j/tmp)%2 == 0){
				AND_SIGNAL(ss[j],ss[j],no);
			}else{
				AND_SIGNAL(ss[j],ss[j],signals->v[i]);
			}


		}
		tmp=tmp*2;


	}

	Signal* tmp2;
	CREATE_SIGNAL(tmp2);


	for(int j=0;j<len;j++){
			
			for(int i=0;i<output->len;i++){

				AND_SIGNAL(tmp2,ss[j],values[j]->v[i]);
				XOR_SIGNAL(output->v[i],output->v[i],tmp2);
			}


		}
      
	free(ss);

}

void demux(struct Value* output,struct Value* signals){
	assign_value(output,0);
	int len=pow(2,signals->len);

	for(int j=0;j<len;j++){
		ONE_SIGNAL(output->v[j]);
	}




  	int tmp=1;
	for(int i=0;i<signals->len;i++){
		Signal * no;
		CREATE_SIGNAL(no);
		NOT_SIGNAL(no,signals->v[i]);
	
		for(int j=0;j<len;j++){
			if((j/tmp)%2 == 0){
				AND_SIGNAL(output->v[j],output->v[j],no);
			}else{
				AND_SIGNAL(output->v[j],output->v[j],signals->v[i]);
			}


		}
		tmp=tmp*2;


	}

}


struct MUX2{

	struct Value* output;
	struct Value* input0;
	struct Value* input1;
	Signal* signal;

	unsigned int length;

	MUX2(unsigned int l){
		length=l;
		create_value(output,l);
	}

	void select(struct Value* i0,struct Value* i1,Signal* s){
		input0=i0;
		input1=i1;
		signal=s;
		select();
	}

	void select(){

		struct Value* vs[2];
		vs[0]=input0;
		vs[1]=input1;
		struct Value* ss;
		create_value(ss,1);
		COPY_SIGNAL(ss->v[0],signal);
		mux(output,vs, ss);



	}


};