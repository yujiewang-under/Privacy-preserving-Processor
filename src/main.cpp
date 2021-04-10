#include"include.h"


int main(void){

	
	#ifndef DEMO
	
	 params = new_default_gate_bootstrapping_parameters(minimum_lambda);
	sk = new_random_gate_bootstrapping_secret_keyset(params);
	 ck = &sk->cloud;

	 #endif


	 //time(&timer);
	 y2k = {0};
	// double seconds;

  	y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
 	y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

	for(int i=0;i<N_CHOICE;i++){
		n_add[i]=0;
		n_mul[i]=0;
		time_add[i]=0;
		time_mul[i]=0;
	}
	struct Processor cpu;
	cpu.init_processor(INSTRUCTION_FILE,REGISTER_FILE,MEMORY_FILE);
	cpu.display_status();

	for(int i=0;i<NUM_EXECUTION;i++){
		printf("%d th:\n",i);
		cpu.execute();
		cpu.display_status();

	}

	printf("statics:\n");
	for(int i=0;i<N_CHOICE;i++){
		printf("%d: add= %d | %d, mul=%d | %d \n", i,n_add[i],time_add[i],n_mul[i],time_mul[i]);
		//n_add[i]=0;
		//n_mul[i]=0;
	}
	//printf("value: %d\n",get_value(memory.output_reg) );



}
