

enum COMPONENT{INS_MEM=0,REGS,ALU, MEM,CONTROL, OTHER}  choice;
#define N_CHOICE 6
int n_add[N_CHOICE];
int n_mul[N_CHOICE];
int time_add[N_CHOICE];
int time_mul[N_CHOICE];
#ifdef DEMO
	#define Signal int
#else
	#define Signal struct LweSample
#endif
 time_t timer;
struct tm y2k;
#define INIT_SIGNAL(s) init_signal(s)
#define COPY_SIGNAL(des,src) copy_signal(des,src)
#define ASSIGN_SIGNAL_BY_CHAR(des,src) assign_signal_by_char(des,src)
#define CREATE_SIGNAL(s) create_signal(s)
#define DEL_SIGNAL(s) del_signal(s)
#define XOR_SIGNAL(s,s1,s2) xor_signal(s,s1,s2)
#define NOT_SIGNAL(s,s1) not_signal(s,s1)
#define AND_SIGNAL(s,s1,s2) and_signal(s,s1,s2)
#define OR_SIGNAL(s,s1,s2) or_signal(s,s1,s2)
#define ASSIGN_SIGNAL(s,n) assign_signal(s,n)
#define SET_SIGNAL(s) set_signal(s)
#define UNSET_SIGNAL(s) unset_signal(s)
#define ONE_SIGNAL(s) one_signal(s)
#define ZERO_SIGNAL(s) zero_signal(s)
#define DISPLAY_SIGNAL(s) display_signal(s)
#define GET_SIGNAL_VALUE(s) get_signal_value(s)
#ifdef DEMO
void init_signal(Signal * s){
	*s=0;
}

void copy_signal(Signal* des,Signal* src) {
		*des=*src;
}

void assign_signal_by_char(Signal* des,char src)
{
	*des=(src=='0'?0:1);
}


void create_signal(Signal* &s){

	s= (Signal*)malloc(sizeof(Signal)); 
	
	  
 	INIT_SIGNAL(s);
}

 

void del_signal(Signal* &s) {free(s); s=NULL;}



void xor_signal(Signal* s,Signal* s1,Signal* s2){
	*s=(*s1+*s2)%2;
	n_add[choice]++;
}

void not_signal(Signal* s, Signal* s1){
	*s=(*s1)?0:1;
	n_add[choice]++;
}


void and_signal(Signal *s, Signal* s1,Signal * s2){
	(*s) =(*s1)*(*s2);
	n_mul[choice]++;
}





void or_signal(Signal* s,Signal* s1,Signal* s2)
{
	Signal* s1_;
	Signal* s2_;
	CREATE_SIGNAL(s1_);
	CREATE_SIGNAL(s2_);
	COPY_SIGNAL(s1_,s1);
	COPY_SIGNAL(s2_,s2);

	AND_SIGNAL(s,s1_,s2_);
	XOR_SIGNAL(s,s,s1_);
	XOR_SIGNAL(s,s,s2_);
}

void assign_signal(Signal *s, int n){
	*s=n;
}



void set_signal(Signal * s) {

	(*s)=1;
}

void unset_signal(Signal* s){
	*s=0;
}


void one_signal(Signal* &s){ CREATE_SIGNAL(s);SET_SIGNAL(s); }

void zero_signal(Signal* &s)  {  CREATE_SIGNAL(s);UNSET_SIGNAL(s);  }


void display_signal(Signal* s) 
{
	//std::cout<<*s<<std::endl;
	std::cout<<*s;
}
int get_signal_value(Signal* s){
	return *s;
}



#else

#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>

#define NUM_THREADS 4
#define OMP_NESTED TRUE


// initialize encryption variables
const int minimum_lambda = 128;
TFheGateBootstrappingParameterSet* params ;
TFheGateBootstrappingSecretKeySet* sk ;
const TFheGateBootstrappingCloudKeySet* ck;

void init_signal(Signal * s){
	bootsSymEncrypt(s, 0, sk);
	//*s=0;
}

void copy_signal(Signal* des,Signal* src) {
		//*des=*src;
		bootsCOPY(des, src, ck);
}

void assign_signal_by_char(Signal* des,char src)
{
	
	if(src=='0'){
		bootsSymEncrypt(des, 0, sk);
	}else{
		bootsSymEncrypt(des, 1, sk);
		}
}


void create_signal(Signal* &s){
	s=new_gate_bootstrapping_ciphertext_array(1, params);
	//s= (Signal*)malloc(sizeof(Signal)); 
	
	  
 	INIT_SIGNAL(s);
}

 

void del_signal(Signal* &s) {free(s); s=NULL;}



void xor_signal(Signal* s,Signal* s1,Signal* s2){
	double seconds;
	time(&timer);
	seconds = difftime(timer,mktime(&y2k));
	
	bootsXOR(s, s1, s2, ck);
	n_add[choice]++;

	double seconde;
	time(&timer);
	seconde = difftime(timer,mktime(&y2k));
	time_add[choice]+=seconde-seconds;
}

void not_signal(Signal* s, Signal* s1){
	double seconds;
	time(&timer);
	seconds = difftime(timer,mktime(&y2k));


	bootsNOT(s, s1, ck);
	n_add[choice]++;

	double seconde;
	time(&timer);
	seconde = difftime(timer,mktime(&y2k));
	time_add[choice]+=seconde-seconds;
}


void and_signal(Signal *s, Signal* s1,Signal * s2){
	double seconds;
	time(&timer);
	seconds = difftime(timer,mktime(&y2k));

	bootsAND(s, s1, s2, ck);
	n_mul[choice]++;
	
	double seconde;
	time(&timer);
	seconde = difftime(timer,mktime(&y2k));
	time_mul[choice]+=seconde-seconds;
}





void or_signal(Signal* s,Signal* s1,Signal* s2)
{
	Signal* s1_;
	Signal* s2_;
	CREATE_SIGNAL(s1_);
	CREATE_SIGNAL(s2_);
	COPY_SIGNAL(s1_,s1);
	COPY_SIGNAL(s2_,s2);

	AND_SIGNAL(s,s1_,s2_);
	XOR_SIGNAL(s,s,s1_);
	XOR_SIGNAL(s,s,s2_);
}

void assign_signal(Signal *s, int n){
	bootsSymEncrypt(s, n, sk);
}



void set_signal(Signal * s) {

	bootsSymEncrypt(s, 1, sk);
}

void unset_signal(Signal* s){
	bootsSymEncrypt(s, 0, sk);
}


void one_signal(Signal* &s){ CREATE_SIGNAL(s);SET_SIGNAL(s); }

void zero_signal(Signal* &s)  {  CREATE_SIGNAL(s);UNSET_SIGNAL(s);  }


void display_signal(Signal* s) 
{
	//std::cout<<*s<<std::endl;
	std::cout<<bootsSymDecrypt(s, sk);
}

int get_signal_value(Signal* s){
	return bootsSymDecrypt(s, sk);
}

 #endif






struct Value{
	int len;
	Signal** v;
};


void init_value(struct Value* value,int n) 
{
	value->len=n;
	value->v=(Signal**) malloc(sizeof(Signal*)*n);
}

void create_value(struct Value*& value,int n) 
{	
	value=(struct Value*) malloc(sizeof(Value));
	init_value(value,n);
	for(int i=0;i<n;i++){
		CREATE_SIGNAL(value->v[i]);

	}
}

void copy_value(struct Value* des,struct Value* src) 
{	
	//des->len=src->len;
	//des->v=(Signal**) malloc(sizeof(Signal*)*src->len);
	for(int i=0;i<src->len;i++){
			COPY_SIGNAL(des->v[i],src->v[i]);

		}
}

void display_value(struct Value*  v)
{

	for(int i=0;i<v->len;i++){
		DISPLAY_SIGNAL(v->v[i]);
	}

}

void assign_value(struct Value*  v,unsigned long int n)
{
	for(int i=0;i<v->len;i++){
		ASSIGN_SIGNAL(v->v[i],n%2);
		n=n/2;
	}
}

void assign_value(struct Value*  v,int n)
{
	assign_value(v,(unsigned long int) n);

}
void assign_value(struct Value*  v, const char* pattern)
{
	
	for(int i=0; pattern[i]!='\n';i++){
			if(pattern[i]=='0'){
				ASSIGN_SIGNAL(v->v[i],0);

			}else if(pattern[i]=='1'){

				ASSIGN_SIGNAL(v->v[i],1);
			}
		}

}

int get_value(struct Value*  v){
	unsigned long int r=0;
	for(int i=0;i<v->len;i++){
		r=r<<1;
		r=r+GET_SIGNAL_VALUE(v->v[v->len-i-1]);
		

	}
	//r=r>>1;
	return r;
}

void assign_data(struct Value** output, const char* fn, unsigned int cell_n, unsigned int line_n){
	std::ifstream infile(fn);
	std::string line;

	int ln=0;
	while (std::getline(infile, line))
	{	if(line[0]=='\n'){
			continue;
		}
	    for(int i=0;i<line_n/cell_n;i++){
	    	for(int j=0;j<cell_n;j++){
	    		ASSIGN_SIGNAL_BY_CHAR(output[ln*(line_n/cell_n)+line_n/cell_n-i-1]->v[cell_n-j-1],line[i*cell_n+j]);
	    	}
	    }
	    ln++;
	}

}


void subvalue(struct Value*& output,struct Value* v,int from, int to){
	create_value(output,to-from+1);

	for(int i=from;i<=to;i++){
		COPY_SIGNAL(output->v[i-from],v->v[i]);
	}

}

struct SignExtend{

	struct Value* output;
	struct Value* input;
	unsigned int length;

	SignExtend(unsigned int l){
		length=l;
		create_value(output,l);
	}

	void sign_extend(struct Value* inp){
		input=inp;
		sign_extend();
	}

	void sign_extend(){
		for(int i=0;i<input->len;i++){
			COPY_SIGNAL(output->v[i],input->v[i]);
		}

		for(int i=input->len;i<length;i++){
			COPY_SIGNAL(output->v[i],input->v[input->len-1]);
		}


	}

};

struct ShiftLeft{

	struct Value* output;
	struct Value* input;
	unsigned int offset;

	ShiftLeft(unsigned int l){
		offset=l;
		output=NULL;
	}

	void shift_left(struct Value* inp){
		input=inp;
		if(output==NULL){
			create_value(output,input->len);
		}
		shift_left();
	}

	void  shift_left(){
		assign_value(output,0);
		for(int i=0;i<input->len-offset;i++){
			COPY_SIGNAL(output->v[i+offset],input->v[i]);
		}

		


	}

};