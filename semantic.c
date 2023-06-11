#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lex.yy.c"


typedef struct node node;
typedef struct s_table s_table;
typedef struct func_node func_node;
typedef struct Block_node Block_node;
//Struct DEF
//------part1:--------
struct node
{
char *token;
struct node *first;
struct node *second;
struct node *third;
struct node *fourth;
};

//------part2:--------
struct s_table {
	char* vari_type;
	char* vari_name;
	s_table* next_var;

};

struct func_node {
	char* block_name;
	char* ret_type;
	char* aba;
	struct s_table* symbol_table;
	int level;
	int amount_of_acc_var;
	struct func_node* next_func;
	struct func_node* back_func;
	struct Block_node* first_block;
	struct Block_node* back_block;
	//struct func_node* inside_func;
};


struct Block_node {
	char* b_name;
	struct s_table* symbol_table;
	int block_level;
	struct Block_node* next_block;
	struct Block_node* back_block;
	struct func_node* back_func;
	
};


// Functions Prototypes:
//-------------------part1-------------------
node* makenode(char* token, node* first, node* second,node* third,node* fourth);
void Printtree(node *tree);
void printSpaces(node* tree,int space);
int yylex(void);
int yyerror(char* e);

//-------------------part2-------------------
void CheckSemantic();

void CheckAcc(node* tree);
char* CheckFuncType(char* kw);
void IsInList(func_node* node);
char* check_foo(char* func_name_check);
char* CheckvarType(char* kw);
void VoidBlock(node* tree);
void CheckTypeOfBlock(node* tree);

void Assfunc(node* tree);

void ForBlock(node* tree);

void VarBlock(node* tree);
void retBlock(node* tree);
int CheckType(char* kw);
void CondBlock(node* tree);
void FunctionBLock(node* tree);
void StringBlock(node* tree);
void IntCheckExp(node* tree);
void RealCheckExp(node* tree);


Block_node* bulid_block();
func_node* bulid_func();
void set_func(func_node*, char*, char*, char*);
void add_func(func_node*, func_node*);
void make_symbol(func_node*, char*, char*);
void make_symbol_block(Block_node* block, char* type, char* var);
char* search_var(func_node* func, char* x);
char* check_type_of_variable(char*);
int CheckOper(char* oper);
void IntRealCondExp(node* tree);
void Sametype(node* tree);
void CheckSendVar(node* tree);
void print_link_list();
void print_symbol_table(func_node* func);
void CheckTyepInSymbolTanle(char*,char*);
func_node* get_func(char* func_name_check);

func_node* head = NULL;
char* type_var = NULL;

func_node* current_func = NULL;
Block_node* current_block = NULL;

int current_level = 0;
char* last_block = NULL;
char* current_var_type = NULL;
char* exp_var_type = NULL;
int tempcount = 0;
char* temp_func_name = NULL;


//--------------Functions part2:-------------
func_node* bulid_func() {

	func_node* node = (func_node*)malloc(sizeof(func_node));

	node->block_name = NULL;
	node->ret_type = NULL;
	node->aba = NULL;

	node->next_func = NULL;
	node->back_func = NULL;

	node->level = 0;
	node->amount_of_acc_var = 0;
	node->symbol_table = NULL;
	node->first_block = NULL;
	node-> back_block = NULL;

	
	return node;

}


Block_node* bulid_block() {

	Block_node* node = (Block_node*)malloc(sizeof(Block_node));

	node->b_name = NULL;

	node->next_block = NULL;
	node->back_block = NULL;
	node->back_func = NULL;
	node->block_level = 0;
	node->symbol_table = NULL;
	//node->inside_func = NULL;
	//current_func = node;
	return node;

}



void set_block(Block_node* node, char* name){
	node->b_name = (char*)malloc(sizeof(char));
	strcpy(node->b_name, name);
	node->block_level = current_level;
	
	if(node->block_level == current_func->level + 1 && current_func!=NULL){
	//printf("i am func: %s\n",current_func->block_name);
		node->back_func = current_func;
	//	printf("i am back func .........: %s\n",node->back_func->block_name);

	}
	else if(current_block!=NULL){
		node->back_block = current_block;
	}
	current_block = node;
	//printf(".....................................%s\n", current_block->back_func->block_name);

}







void set_func(func_node* node, char* type, char* name, char* aba) {

	node->ret_type = (char*)malloc(sizeof(char)*16);
	strcpy(node->ret_type, type);

	node->block_name = (char*)malloc(sizeof(char)*16);
	strcpy(node->block_name, name);

	node->aba = (char*)malloc(sizeof(char)*16);
	strcpy(node->aba, aba);

	last_block = (char*)malloc(sizeof(char)*16);
	strcpy(last_block, name);

	node->level = current_level;
	if(node->level == 0)
	{
		node->back_func = NULL;	
	}
	else if(current_func != NULL && current_func->level==current_level-1)
	{
		node->back_func = current_func;
	}

	if(current_block!=NULL && current_block->block_level == current_level-1 ){
		node->back_block = current_block;
		//printf(".....................%s\n", node->block_name);
		//printf(".....................%s\n", node->back_block ->b_name);
	}

	current_func = node;

	

}


void add_func(func_node* first, func_node* node) {
	func_node* current = first;
	while (current->next_func != NULL) {
		current = current->next_func;
		
	}
	current->next_func = node;
	//node->back_func = current;
}

void add_block(func_node* first, Block_node* node) {
	if(first->first_block == NULL){
		first->first_block = node;
	}
	else{
		Block_node* current = first->first_block;
		while (current->next_block != NULL) {
			current = current->next_block;		
		}
		current->next_block = node;
	}
}

void print_symbol_table(func_node* func) {

	s_table* current = func->symbol_table;
	if(current!=NULL){
	printf("Symbol Table:\n");
	while (current->next_var != NULL) {
		printf("%s: %s\n", current->vari_type, current->vari_name);
		current = current->next_var;
	}
	printf("%s: %s\n", current->vari_type, current->vari_name);
	}
}

void print_blocks(func_node* func) {
	while(func!=NULL){
		
		if(func->first_block!=NULL){
			printf("Func %s blocks:\n\n", func->block_name);
			Block_node* current = func->first_block;
			
			while (current != NULL) {
				printf("current block: %s\n", current->b_name);
				
				if(current->back_block!=NULL){
					printf("father: %s\n", current->back_block->b_name);
				}

				if(current->back_func!=NULL){
					printf("father: %s\n", current->back_func->block_name);
				}

				if(current->symbol_table !=NULL){
					printf("Symbol Table:\n");
					s_table* c_symbol = current->symbol_table;
				
					while (c_symbol !=NULL){
						printf("%s: %s\n",c_symbol->vari_type,c_symbol->vari_name);
						c_symbol = c_symbol->next_var;
					}
				}
				current = current->next_block;
			}
		}
		func = func->next_func;
	}
}

void print_link_list() {

	func_node* current = head;
	while (current->next_func != NULL) {
		printf("%s %s %d\n", current->ret_type, current->block_name, current->amount_of_acc_var);
		//printf("%s\n", current->aba);
		if(current->back_func!=NULL)
		{
			printf("back func: %s\n", current->back_func->block_name);
			if( current->back_block)
				printf("back block: %s\n", current->back_block->b_name);
		}
		print_symbol_table(current);
		printf("------------------------------------------\n");
		current = current->next_func;
	}
	printf("%s %s %d\n", current->ret_type, current->block_name, current->amount_of_acc_var);
	if(current->back_func!=NULL)
	{
		printf("back func: %s\n", current->back_func->block_name);
		if(current->back_block!=NULL)
			printf("back block: %s\n", current->back_block->b_name);
	}
	print_symbol_table(current);
	printf("------------------------------------------\n");

}





void StringBlock(node* tree)
{
    if(tree->first){
        if(strcmp(tree->token,"STRING")==0)
        {           
			strcpy(type_var,tree->token);
			//printf("%s\n",tree->first->token);
        }
		
		if(strcmp(tree->first->token,"STRING")!=0 && strcmp(tree->first->token,"")!=0){
		   if(strcmp(tree->first->token,"[]")==0 ){		
			  if(tree->first->first!=NULL){
				   if(tree->first->first->first!=NULL){
						if(strcmp(check_type_of_variable(tree->first->first->first->token),tree->first->first->first->token)!=0 && strcmp(check_type_of_variable(tree->first->first->first->token),"INT")!=0){
								printf("Error: This value %s cannot be sent as a string size\n", check_type_of_variable(tree->first->first->first->token));
								exit(0);
						}
						else if(search_var(current_func, tree->first->first->first->token)!=NULL){
							if(strcmp(search_var(current_func, tree->first->first->first->token),"INT")!=0){
								printf("Error: This value %s cannot be sent as a string size\n", search_var(current_func, tree->first->first->first->token));
								exit(0);
							}
						}
						else if (search_var(current_func, tree->first->first->first->token)==NULL && (strcmp(tree->first->first->first->token,check_type_of_variable(tree->first->first->first->token))==0)){
							printf("1Error: Variable %s not delcared!\n",tree->first->first->first->token);
							exit(0);
						}
				   }
			   }
			 //  make_symbol(current_func,type_var,tree->token);
			}
			else if(strcmp(check_type_of_variable(tree->first->token),tree->first->token)==0){
				//printf("%s\n",search_var(current_func, tree->first->token));
					if(current_level == current_func->level+1){
						//printf("c_level:%d, func level: %d\n",current_level, current_func->level);
				 		make_symbol(current_func,type_var,tree->first->token);
					 
				 	}

					 else if(current_level == current_block->block_level + 1){
				 		make_symbol_block(current_block,type_var,tree->first->token);
					 
				 	}
			}
		}
		StringBlock(tree->first);
	}
	if(tree->second){
		   if(strcmp(tree->token,"STRING")==0)
        {           
			strcpy(type_var,tree->token);
			//printf("%s\n",tree->first->token);
        }
		
		if(strcmp(tree->second->token,"STRING")!=0 && strcmp(tree->second->token,"")!=0){
		   if(strcmp(tree->second->token,"[]")==0 ){		
			  if(tree->second->first!=NULL){
				   if(tree->second->first->first!=NULL){
						if(strcmp(check_type_of_variable(tree->second->first->first->token),tree->second->first->first->token)!=0 && strcmp(check_type_of_variable(tree->second->first->first->token),"INT")!=0){
								printf("Error: This value %s cannot be sent as a string size\n", check_type_of_variable(tree->second->first->first->token));
								exit(0);
						}
						else if(search_var(current_func, tree->second->first->first->token)!=NULL){
							if(strcmp(search_var(current_func, tree->second->first->first->token),"INT")!=0){
								printf("Error: This value %s cannot be sent as a string size\n", search_var(current_func, tree->second->first->first->token));
								exit(0);
							}
						}
						else if (search_var(current_func, tree->second->first->first->token)==NULL && (strcmp(tree->second->first->first->token,check_type_of_variable(tree->second->first->first->token))==0)){
							printf("2Error: Variable %s not delcared!\n",tree->second->first->first->token);
							exit(0);
						}
				   }
			   }
		   	}
			else if(strcmp(check_type_of_variable(tree->second->token),tree->second->token)==0){
				//printf("c_level:%d, func level: %d\n",current_level, current_func->level);
					if(current_level == current_func->level+1){
				 		make_symbol(current_func,type_var,tree->second->token);
				 	}
			}


			
		}

		StringBlock(tree->second);	
	}
}





void make_symbol(func_node* func, char* type, char* var) {
	
	if(func->symbol_table != NULL){
		s_table* current = func->symbol_table;
		while(current != NULL){
			if(strcmp(var,current->vari_name)==0){
				printf("Error: Duplicate variable name - %s\n",var);
				exit(0);
			}	
			current = current->next_var;
		
		}	
	}


	s_table* new_symbol = (s_table*)malloc(sizeof(s_table));
	new_symbol->vari_type = (char*)malloc(sizeof(char));
	new_symbol->vari_name = (char*)malloc(sizeof(char));
	strcpy(new_symbol->vari_type, type);
	strcpy(new_symbol->vari_name, var);
	new_symbol->next_var = NULL;

	if(func->symbol_table == NULL){
		func->symbol_table = new_symbol;
	
	}
	else {
		
		s_table* current = func->symbol_table;
		while (current->next_var != NULL) {
			current = current->next_var;
		}
		current->next_var = new_symbol;
	}

}


void make_symbol_block(Block_node* block, char* type, char* var) {
	
	if(block->symbol_table != NULL){
		s_table* current = block->symbol_table;
		while(current != NULL){
			if(strcmp(var,current->vari_name)==0){
				printf("Error: Duplicate variable name - %s\n",var);
				exit(0);
			}	
			current = current->next_var;
		
		}	
	}


	s_table* new_symbol = (s_table*)malloc(sizeof(s_table));
	new_symbol->vari_type = (char*)malloc(sizeof(char));
	new_symbol->vari_name = (char*)malloc(sizeof(char));
	strcpy(new_symbol->vari_type, type);
	strcpy(new_symbol->vari_name, var);
	new_symbol->next_var = NULL;

	if(block->symbol_table == NULL){
		block->symbol_table = new_symbol;
	
	}
	else {
		
		s_table* current = block->symbol_table;
		while (current->next_var != NULL) {
			current = current->next_var;
		}
		current->next_var = new_symbol;
	}

}



//------------------------------------haiel-----------------------

void CheckSemantic(node* tree){
	if(strcmp(tree->token,"IF")==0)
	{
		
		CondBlock(tree->first);
		//current_block++;
		set_block(bulid_block(), "IF");
		add_block(current_func,current_block);
			
	}
	if(strcmp(tree->token,"FOR")==0)
	{
		//printf("FOR\n");	
		Assfunc(tree->first);
		CondBlock(tree->second);
		Assfunc(tree->third);
		set_block(bulid_block(), "FOR");
		add_block(current_func,current_block);
			
	}
	if(strcmp(tree->token,"DO")==0)
	{
		//printf("DO\n");
		set_block(bulid_block(), "DO");
		//printf("current do %s\n", current_func->block_name );
		add_block(current_func,current_block);		
	}
	if(strcmp(tree->token,"WHILE")==0){		
		//printf("WHILE\n");
		CondBlock(tree->first);
	}
	if(strcmp(tree->token,"WHILE_LOOP")==0)
	{
		//printf("WHILE_LOOP\n");	
		CondBlock(tree->first);
		set_block(bulid_block(), "WHILE_LOOP");
		add_block(current_func,current_block);	
	}
	if(strcmp(tree->token,"ELSE")==0)
	{

		//printf("ELSE\n");	
		CondBlock(tree);
		set_block(bulid_block(), "ELSE");
		add_block(current_func,current_block);
			
	}
	if(strcmp(tree->token,"EMPTY_BLOCK")==0 || strcmp(tree->token,"VOID_EMPTY_BLOCK")==0)
	{

		//printf("ELSE\n");	
		CondBlock(tree);
		set_block(bulid_block(), "EMPTY_BLOCK");
		add_block(current_func,current_block);
			
	}
	if(strcmp(tree->token,"return")==0)
	{
		//printf("RETURN\n");	
		retBlock(tree);

	}
	if(strcmp(tree->token,"ASS")==0)
	{
		//printf("ASS\n");	
		Assfunc(tree);
	}
	if(strcmp(tree->token,"FUNCTION")==0 || strcmp(tree->token,"FUNCTION\nMAIN")==0)
	{
		//printf("FUNCTION\n");	
		FunctionBLock(tree);	
	}	
	if(strcmp(tree->token,"VAR")==0)
	{
		//printf("VAR\n");	
		VarBlock(tree);	
	}

	if(strcmp(tree->token,"STRING")==0)
	{
		//printf("VAR\n");	
		StringBlock(tree);	
	}
	
	if(strcmp(tree->token,"START_BLOCK")==0)
	{	
		current_level = current_level + 1;
	}
	if(strcmp(tree->token,"END_BLOCK")==0)
	{	
		current_level = current_level - 1;

		if(current_func->back_func!=NULL && current_func->back_func->level == current_level-1)
		{
			//printf(".........%s\n",current_func->block_name);
			current_func = current_func->back_func;
			//printf(".........%s\n",current_func->block_name);
		}
		else if(current_block!=NULL && current_block->back_func!=NULL && current_block->back_func->level == current_level-1){
			//printf("lalala %s\n", current_block->back_func->block_name);
			current_func = current_block->back_func;
		}
		else if(current_block!=NULL && current_block->back_block!=NULL && current_block->back_block->block_level == current_level-1){
			current_block = current_block->back_block;
		}
		else if(current_func!=NULL && current_func->back_block!=NULL && current_func->back_block->block_level == current_level-1){
			current_block = current_func->back_block;
		}
		if(current_level==1){
			current_block =NULL;
		}
	}


	if(tree->first){
		CheckSemantic(tree->first);
	}
	if(tree->second){
		CheckSemantic(tree->second);
	}
	if(tree->third){
		CheckSemantic(tree->third);
	}
	if(tree->fourth){
		CheckSemantic(tree->fourth);
	}
	
}

/*--------------------------------void start----------------------------------------------------*/
void CondBlock(node* tree)
{
	if(tree->first)
	{
		if(strcmp(tree->first->token, ""))
		{
			if(strcmp(tree->first->token,">")==0 || strcmp(tree->first->token,"<")==0 || strcmp(tree->first->token,">=")==0 || strcmp(tree->first->token,"<=")==0)
			{			
				IntRealCondExp(tree->first);
				IntRealCondExp(tree->second);
			}
			else if(strcmp(tree->first->token,"!=")==0 || strcmp(tree->first->token,"==")==0)
			{
				if(tree->second->first!=NULL)
				{
					if(search_var(current_func, tree->second->first->token)!=NULL)
					{
						
						//printf("%s\n", tree->second->first->token);
						//printf("%s\n", search_var(current_func, tree->second->first->token));
						current_var_type = search_var(current_func, tree->second->first->token);
					}
					else if(strcmp(check_type_of_variable(tree->second->first->token),tree->second->first->token)!=0)
					{
						//printf("%s\n", tree->second->first->token);
						//printf("%s\n", check_type_of_variable(tree->second->first->token));
						current_var_type = check_type_of_variable(tree->second->first->token);
					}
					else
					{
						printf("Error: Variable %s not delcared!\n",tree->second->first->token);
						exit(0);
					}
					if(strcmp(current_var_type, "CHAR")==0 || strcmp(current_var_type, "BOOL")==0 || strcmp(current_var_type, "INT")==0 ||
					strcmp(current_var_type, "REAL")==0 || strcmp(current_var_type, "PREAL")==0 || strcmp(current_var_type, "PINT")==0 ||
					strcmp(current_var_type, "PCHAR")==0)
					{
						Sametype(tree->first);
						Sametype(tree->second);
					}else
					{
						printf("Error: oper == and oper != cannot accept string type \n");
						exit(0);
					}
				}
			}else if(strcmp(tree->token,"!")==0 && /*(strcmp(check_type_of_variable(tree->first->token),"BOOL")!=0 ||*/
					 strcmp(search_var(current_func, tree->first->token),"BOOL")!=0)
			 	{
						printf("Error: oper ! support only in bool type \n");
						exit(0);
				}else if(strcmp(tree->token,"!")==0 && strcmp(check_type_of_variable(tree->first->token),"BOOL")!=0 && strcmp(check_type_of_variable(tree->first->token), tree->first->token)!=0)
				{
					printf("Error: oper ! support only in bool type \n");
					exit(0);
				}	
			}

		}	 	 if (tree->second!=NULL && strcmp(check_type_of_variable(tree->second->token),"FUNCTION")==0){
						if(check_foo(tree->second->token)!=NULL){
							if(strcmp(check_foo(tree->second->token),current_var_type)!=0){
								printf("Error: The return value of function %s are incorrect! \n",tree->second->token);
								exit(0);
						}
					}	
						else if(check_foo(tree->second->token)==NULL && strcmp(check_type_of_variable(tree->second->token),"FUNCTION")==0){
								printf("Error: Function %s not delcared!\n",tree->second->token);
								exit(0);
						}

						temp_func_name = (char*)malloc(sizeof(char));
						strcpy(temp_func_name,tree->second->token);
						CheckSendVar(tree->second);
						if(tempcount< get_func(temp_func_name)->amount_of_acc_var){
							printf("Error: Too few args were sent to function %s\n",temp_func_name);
							exit(0);
						}
						tempcount = 0;
						free(temp_func_name);
						temp_func_name = NULL;
				
				}

	/*if(tree->first)
		CondBlock(tree->first);
	if(tree->second){			
		CondBlock(tree->second);		
	}*/
}



void IntRealCondExp(node* tree)
{
	if(tree->first){
		if(strcmp(tree->first->token, ""))
		{
			if(CheckOper(tree->first->token)==1)
			{
				if(search_var(current_func, tree->first->token)!=NULL){
					if(strcmp(search_var(current_func, tree->first->token), "REAL")!=0 && strcmp(search_var(current_func, tree->first->token), "INT")!=0)
					{
						printf("1.Error: Type error of variable %s \n", tree->first->token);
						exit(0);
					}
				}
				else if(strcmp("REAL",check_type_of_variable(tree->first->token))!=0 && strcmp("INT",check_type_of_variable(tree->first->token))!=0 && (strcmp(tree->first->token,check_type_of_variable(tree->first->token))!=0))
				{
					printf("2.Error: Type error of variable %s \n", tree->first->token);
						exit(0);
				}
				else if(search_var(current_func, tree->first->token)==NULL && (strcmp(tree->first->token,check_type_of_variable(tree->first->token))==0))
				{
					printf("Error: Variable %s not delcared!\n",tree->first->token);
					exit(0);
				}
			}else if(strcmp(tree->first->token, "||")==0 || strcmp(tree->first->token, "&&")==0)
			{
				CondBlock(tree->first);
			}
		}
	}
	if(tree->second){
		if(strcmp(tree->second->token, ""))
		{
			if(CheckOper(tree->second->token)==1)
			{
				if(search_var(current_func, tree->second->token)!=NULL){
					if(strcmp(search_var(current_func, tree->second->token), "REAL")!=0 && strcmp(search_var(current_func, tree->second->token), "INT")!=0)
					{
						printf("3.Error: Type error of variable %s \n", tree->second->token);
						exit(0);
					}
				}
				else if(strcmp("REAL",check_type_of_variable(tree->second->token))!=0 && strcmp("INT",check_type_of_variable(tree->second->token))!=0 && (strcmp(tree->second->token,check_type_of_variable(tree->second->token))!=0))
				{
					printf("4.Error: Type error of variable %s \n", tree->second->token);
						exit(0);
				}
				else if(search_var(current_func, tree->second->token)==NULL && (strcmp(tree->second->token,check_type_of_variable(tree->second->token))==0))
				{
					printf("Error: Variable %s not delcared!\n",tree->second->token);
					exit(0);
				}
			}else if(strcmp(tree->second->token, "||")==0 || strcmp(tree->second->token, "&&")==0)
			{
				CondBlock(tree->second);
			}
		}
	}
	if(tree->first)
		IntRealCondExp(tree->first);
	if(tree->second)
		IntRealCondExp(tree->second);
	if(tree->third)
		IntRealCondExp(tree->third);
}



void Sametype(node* tree)
{
	if(tree->first){
		if(strcmp(tree->first->token, "")!=0)
		{
			if(CheckOper(tree->first->token)==1)
			{
				if(search_var(current_func, tree->first->token)!=NULL){
					if(strcmp(search_var(current_func, tree->first->token), current_var_type)!=0)
					{
						printf("%s\n" ,current_var_type);
						printf("16.Error: Type error of variable %s \n", tree->first->token);
						exit(0);
					}
				}
				else if(strcmp(current_var_type,check_type_of_variable(tree->first->token))!=0 && (strcmp(tree->first->token,check_type_of_variable(tree->first->token))!=0))
				{
					printf("%s\n" ,current_var_type);
					printf("5.Error: Type error of variable %s \n", tree->first->token);
						exit(0);
				}
				else if(search_var(current_func, tree->first->token)==NULL && (strcmp(tree->first->token,check_type_of_variable(tree->first->token))==0))
				{
					printf("Error: Variable %s not delcared!\n",tree->first->token);
					exit(0);
				}
			}else if(strcmp(tree->first->token, "||")==0 || strcmp(tree->first->token, "&&")==0)
			{
				CondBlock(tree->first);
			}
		}
	}
	if(tree->second){
		if(strcmp(tree->second->token, ""))
		{
			if(CheckOper(tree->second->token)==1)
			{
				if(search_var(current_func, tree->second->token)!=NULL){
					if(strcmp(search_var(current_func, tree->second->token), current_var_type)!=0)
					{
						printf("%s\n" ,current_var_type);
						printf("6.Error: Type error of variable %s \n", tree->second->token);
						exit(0);
					}
				}
				else if(strcmp(current_var_type,check_type_of_variable(tree->second->token))!=0 && (strcmp(tree->second->token,check_type_of_variable(tree->second->token))!=0))
				{
					printf("%s\n",current_var_type );
					printf("7.Error: Type error of variable %s \n", tree->second->token);
						exit(0);
				}
				else if(search_var(current_func, tree->second->token)==NULL && (strcmp(tree->second->token,check_type_of_variable(tree->second->token))==0))
				{
					printf("Error: Variable %s not delcared!\n",tree->second->token);
					exit(0);
				}
			}else if(strcmp(tree->second->token, "||")==0 || strcmp(tree->second->token, "&&")==0)
			{
				CondBlock(tree->second);
			}
		}
	}
	if(tree->first)
		Sametype(tree->first);
	if(tree->second)
		Sametype(tree->second);
	if(tree->third)
		Sametype(tree->third);
}








void ForBlock(node* tree){
	if(tree->first){
		if(strcmp(tree->first->token, "")){			
			printf("%s\n",tree->first->token);
		}
	}


	if(tree->first)
		ForBlock(tree->first);
	if(tree->second)			
		ForBlock(tree->second);				
	if(tree->third)
		ForBlock(tree->third);

}



void FunctionBLock(node* tree){
	if(tree->first || tree->second){			
		//printf("%s\n",tree->first->token);
		//printf("%s\n",tree->second->token);
		
		if (head!=NULL){							
			func_node* new_func;
			new_func = bulid_func();
			if(current_level==0)
			{
				strcpy(last_block,"NULL");
			}
	 		set_func(new_func, tree->first->token, tree->second->token, last_block);
			IsInList(new_func);
			
			//new_func ->level = current_level;
		//	printf("1.%d\n", new_func->level);
			//new_func->back_func = current_func;
			
			add_func(head, new_func);
			//current_func = new_func;
			
		}

		if (head==NULL){
			head = bulid_func();
			set_func(head, tree->first->token, tree->second->token,"NULL");
			//current_level = current_level + 1;
			//head ->level = current_level;
			
			//strcpy(current_func->block_name,tree->second->token);
			//printf("1.%s", current_func->block_name); 
			current_func = head;
		}	
	}	
		
						
	
	if(tree->third){			
		CheckAcc(tree->third);				
	}

}

void retBlock(node* tree){
	if(tree->first){
		if(strcmp(tree->first->token, "")){	

			if(strcmp("REAL",current_func->ret_type)!=0){	
				
				if(search_var(current_func, tree->first->token)!=NULL){
					if(strcmp(current_func->ret_type,search_var(current_func, tree->first->token))!=0)
					{	
						printf("Error: Return type of variable - %s inccorect!\n",tree->first->token);
						exit(0);
					}
				}

				else if(strcmp(current_func->ret_type,check_type_of_variable(tree->first->token))!=0 && (strcmp(tree->first->token,check_type_of_variable(tree->first->token))!=0)){
						printf("Error: Return type need to be %s and you return %s !\n",current_func->ret_type,check_type_of_variable(tree->first->token));
						exit(0);
				}
				else if(strcmp(tree->first->token,check_type_of_variable(tree->first->token))==0){
						printf("Error: Variable %s not delcared!\n",tree->first->token);
						exit(0);
				}		
			}
			else{

				if(search_var(current_func, tree->first->token)!=NULL){
					if(strcmp("INT",search_var(current_func, tree->first->token))!=0 && strcmp("REAL",search_var(current_func, tree->first->token))!=0)
					{	
						printf("Error: Return type of variable - %s are inccorect \n",tree->first->token);
						exit(0);
					}
				}

				else if(strcmp("INT",check_type_of_variable(tree->first->token))!=0 && (strcmp(tree->first->token,check_type_of_variable(tree->first->token))!=0) && strcmp("REAL",check_type_of_variable(tree->first->token))!=0){
						printf("Error: Return type need to be %s and you return %s !\n",current_func->ret_type,check_type_of_variable(tree->first->token));
						exit(0);
				}
				else if(strcmp(tree->first->token,check_type_of_variable(tree->first->token))==0){
						printf("Error: Variable %s not delcared!\n",tree->first->token);
						exit(0);
				}










			}

		}
	}	
}

char* check_type_of_variable(char* token)
{
	//printf("%s\n",token);

	if(strcmp(token,"true")==0 || strcmp(token,"TRUE")==0 || strcmp(token,"false")==0 || strcmp(token,"FALSE")==0){
		return "BOOL";
	}
	
	if(token[0] == '\'')
	{
		return "CHAR";
	}
	if(token[0] == '\"')
	{
		int i=1;
		while(token[i]!='\"')
		{
			i++;
		}
		if(token[i+1] == '\0'){
			return "STRING";
		}else{
			return "INT";
		}
	}

	int i = 0;
	int flag = 1;
	int dot = 0;
	
	while(token[i]!='\0'){
		if(isdigit(token[i])==0){
			flag = 0;
		}
		if(token[i]=='.'){
			flag = 1;
			dot++;
		}

		i++;
	}

	if(flag == 1 && dot == 0){
		return "INT";
	}

	if(flag == 1 && dot == 1){
		return "REAL";
	}

	i=0;
	while(token[i]!='\0'){
		if(token[i]=='(' && i>0){
			return "FUNCTION";
		}
		i++;
	}

	/*i=0;
	while(token[i]!='\0'){
		if(token[i]=='&' || token[i]=='*'){
			char* temp = (char*)malloc (sizeof(char));
			char* numbertemp = (char*)malloc (sizeof(char));
			int z =0;
			numbertemp = NULL;
			while (token[z]!='\0' && token[z]!='[')
			{
				strcpy(temp,&token[z]);
				z++;
			}
			//printf("%s\n",temp);
			int k = 0;
			while(token[k]!='\0'){
				if ( token[k]=='[')
				{
					while(token[k]!=']'){
						strcpy(numbertemp,&token[k]);
						k++;
					}
				}
			k++;
			}
				if(numbertemp!=NULL){
					if(strcmp(check_type_of_variable(numbertemp),"INT")!=0 && strcmp(check_type_of_variable(numbertemp),numbertemp)!=0){
						printf("Error: This value %s cannot be sent as a string size", numbertemp);
						exit(0);
					}
					else if(search_var(current_func, numbertemp)!=NULL){
						if(strcmp(search_var(current_func, numbertemp),"INT")!=0){
							printf("Error: This value %s cannot be sent as a string size", numbertemp);
							exit(0);
						}
					}
					else if(search_var(current_func, numbertemp)==NULL){
						printf("Error: Variable %s not delcared!\n",temp);
						exit(0);
			
					}
				}

			if(search_var(current_func, temp)!=NULL){
				if(strcmp(search_var(current_func, temp),"BOOL")==0){
					printf("Error: This value %s cannot be sent as a string size", numbertemp);
					exit(0);
				}
			}else if(search_var(current_func, temp)==NULL){
				printf("Error: Variable %s not delcared!\n",temp);
				exit(0);
			}
			//printf("%s\n",  search_var(current_func, temp));
			return search_var(current_func, temp);
		}
		i++;
	}*/

	return token;
}

void Assfunc(node* tree){
	if(tree->first){
		if(CheckOper(tree->first->token)==0)
		{		
			if(strcmp(tree->first->token,"=")==0)
			{
				if(search_var(current_func,tree->first->first->token)!=NULL)
				{
					//printf("i am here: %s\n", tree->first->first->token);
					current_var_type = search_var(current_func,tree->first->first->token);
				//	printf("%s %s\n", tree->first->first->token,  search_var(current_func,tree->first->first->token));
					if(strcmp(current_var_type,"STRING")==0){
							if(tree->first->first->first!=NULL){
								if(strcmp(tree->first->first->first->token,"[]")==0){
									if(tree->first->first->first->first!=NULL){
										if(tree->first->first->first->first->first!=NULL){
											if(strcmp(check_type_of_variable(tree->first->first->first->first->first->token),"INT")!=0 && strcmp(tree->first->first->first->first->first->token,check_type_of_variable(tree->first->first->first->first->first->token))!=0){
													printf("Error: An index in an array must be of type INT\n");
													exit(0);
												}else if(search_var(current_func,tree->first->first->first->first->first->token)!=NULL){
													if(strcmp(search_var(current_func,tree->first->first->first->first->first->token),"INT")!=0){
														printf("Error: An index in an array must be of type INT\n");
														exit(0);
													}
												}else if(search_var(current_func,tree->first->first->first->first->first->token)==NULL && (strcmp(tree->first->first->first->first->first->token,check_type_of_variable(tree->first->first->first->first->first->token))==0))
												{
													printf("Error: Variable %s not delcared!\n",tree->first->first->first->first->first->token);
													exit(0);
												}
										
										}
									}
							}
						}
					}
				}else
				{
					printf("Error: Variable %s not delcared!\n",tree->first->first->token);
					exit(0);
				}
				if(strcmp(current_var_type,"STRING")==0 || strcmp(current_var_type,"CHAR")==0)
				{	
					if(tree->first->second->first!=NULL)
					{
						if(strcmp(tree->first->second->first->token, "")!=0){
							
							if(search_var(current_func,tree->first->second->first->token)!=NULL){	
								
								//printf("%s\n",tree->first->second->first->token);
								//	printf("%s\n", tree->first->second->first->first->first->token);
								if(tree->first->second->first->first!=NULL){
									if(tree->first->second->first->first->first!=NULL){
										if(strcmp(search_var(current_func ,tree->first->second->first->token),"STRING")==0){
											if(search_var(current_func ,tree->first->second->first->first->first->token)!=NULL && strcmp(search_var(current_func ,tree->first->second->first->first->first->token),"INT")==0 || strcmp(check_type_of_variable(tree->first->second->first->first->first->token),"INT")==0){
												if(strcmp(current_var_type, "CHAR")!=0){
													printf("Error: You can't do this ass\n");
													exit(0);
												}
											}
											else{
												printf("Error: This vriable can't be index type!\n");
											}
										}
									}
								}
								else if(strcmp(search_var(current_func ,tree->first->second->first->token), current_var_type)!=0){

									printf("Error: you can't do ass between %s and %s\n",current_var_type, search_var(current_func ,tree->first->second->first->token));
									exit(0);
								
								}
							}

							else if(strcmp(check_type_of_variable(tree->first->second->first->token) ,current_var_type)!=0 && (strcmp(tree->first->second->first->token,check_type_of_variable(tree->first->second->first->token))!=0) && (strcmp("FUNCTION",check_type_of_variable(tree->first->second->first->token))!=0)){
									printf("1...Error: you can't do ass between %s and %s\n",current_var_type, check_type_of_variable(tree->first->second->first->token));
									exit(0);
							}

							else if(search_var(current_func,tree->first->second->first->token)==NULL && (strcmp(tree->first->second->first->token,check_type_of_variable(tree->first->second->first->token))==0) && (strcmp("FUNCTION",check_type_of_variable(tree->first->second->first->token))!=0)){
									printf("Error: Variable %s not delcared!\n",tree->first->second->first->token);
									exit(0);
							}
							
							else if(strcmp(check_foo(tree->first->second->first->token),current_var_type)!=0){
									printf("Error: The return value of function %s are incorrect! \n",tree->first->second->first->token);
									exit(0);
							}

							else if(check_foo(tree->first->second->first->token)==NULL){
								printf("Error: Function %s not delcared!\n",tree->first->second->first->token);
								exit(0);

							}

						}
						else if(strcmp(tree->first->second->token, "")){ 
							if(strcmp(check_type_of_variable(tree->first->second->token) ,current_var_type)!=0  && (strcmp(tree->first->second->token,check_type_of_variable(tree->first->second->token))!=0) && (strcmp("FUNCTION",check_type_of_variable(tree->first->second->token))!=0)){
								printf("Error: you can't do ass between %s and %s\n",current_var_type, check_type_of_variable(tree->first->second->token));
								exit(0);
							}
						
							else if(check_foo(tree->first->second->token)==NULL){
									printf("Error: Function %s not delcared!\n",tree->first->second->token);
									exit(0);
							}

							else if(strcmp(check_foo(tree->first->second->token),current_var_type)!=0){
									printf("Error: The return value of function %s are incorrect! \n",tree->first->second->token);
									exit(0);
							}			
					

							else if(search_var(current_func, tree->first->second->token)==NULL && (strcmp(tree->first->second->token,check_type_of_variable(tree->first->second->token))==0) && (strcmp("FUNCTION",check_type_of_variable(tree->first->second->token))!=0)){
									printf("Error: Variable %s not delcared!\n",tree->first->second->token);
									exit(0);
							}

							else if (strcmp(check_type_of_variable(tree->first->second->token),"FUNCTION")==0){
								if(check_foo(tree->first->second->token)!=NULL){
									if(strcmp(check_foo(tree->first->second->token),current_var_type)!=0){
										printf("Error: The return value of function %s are incorrect! \n",tree->first->second->token);
										exit(0);
									}
								}		
								else if(check_foo(tree->first->second->token)==NULL && strcmp(check_type_of_variable(tree->first->second->token),"FUNCTION")==0){
									printf("Error: Function %s not delcared!\n",tree->first->second->token);
									exit(0);
								}

								temp_func_name = (char*)malloc(sizeof(char));
								strcpy(temp_func_name,tree->first->second->token);
								CheckSendVar(tree->first->second);
								printf("%d\n",  get_func(temp_func_name)->amount_of_acc_var);
								if(tempcount< get_func(temp_func_name)->amount_of_acc_var)
								{
									printf("Error: Too few args were sent to  function %s\n",temp_func_name);
									exit(0);
								}
								tempcount = 0;
								free(temp_func_name);
								temp_func_name = NULL;
				
							}
						
						}
					}else if (tree->first->second){
						if(strcmp(check_type_of_variable(tree->first->second->token) ,current_var_type)!=0  && (strcmp(tree->first->second->token,check_type_of_variable(tree->first->second->token))!=0) && (strcmp("FUNCTION",check_type_of_variable(tree->first->second->token))!=0)){
								printf("Error: you can't do ass between %s and %s\n",current_var_type, check_type_of_variable(tree->first->second->token));
								exit(0);
							}		

							else if(search_var(current_func, tree->first->second->token)==NULL && (strcmp(tree->first->second->token,check_type_of_variable(tree->first->second->token))==0) && (strcmp("FUNCTION",check_type_of_variable(tree->first->second->token))!=0)){
									printf("Error: Variable %s not delcared!\n",tree->first->second->token);
									exit(0);
							}

							else if (strcmp(check_type_of_variable(tree->first->second->token),"FUNCTION")==0){
								if(check_foo(tree->first->second->token)!=NULL){
									if(strcmp(check_foo(tree->first->second->token),current_var_type)!=0){
										printf("Error: The return value of function %s are incorrect! \n",tree->first->second->token);
										exit(0);
									}
								}		
								else if(check_foo(tree->first->second->token)==NULL && strcmp(check_type_of_variable(tree->first->second->token),"FUNCTION")==0){
									printf("Error: Function %s not delcared!\n",tree->first->second->token);
									exit(0);
								}

								temp_func_name = (char*)malloc(sizeof(char));
								strcpy(temp_func_name,tree->first->second->token);
								CheckSendVar(tree->first->second);
								printf("%d\n",  get_func(temp_func_name)->amount_of_acc_var);
								if(tempcount< get_func(temp_func_name)->amount_of_acc_var)
								{
									printf("Error: Too few args were sent to  function %s\n",temp_func_name);
									exit(0);
								}
								tempcount = 0;
								free(temp_func_name);
								temp_func_name = NULL;
							}
						}

				}else if(strcmp(current_var_type,"INT")==0)
				{
					IntCheckExp(tree->first);
				}
				else if(strcmp(current_var_type,"REAL")==0)
				{
					RealCheckExp(tree->first);
				}
				else if(strcmp(current_var_type,"BOOL")==0){
					//printf("i am here:\n");
					CondBlock(tree->first);
				}
				
			}		
				
		}
	}
}



void RealCheckExp(node* tree)
{
	if(tree->first){
		if(strcmp(tree->first->token, ""))
		{
			if(CheckOper(tree->first->token)==1)
			{
				if(search_var(current_func, tree->first->token)!=NULL){
					if(strcmp(search_var(current_func, tree->first->token), "REAL")!=0 && strcmp(search_var(current_func, tree->first->token), "INT")!=0)
					{
						printf("8.Error: Type error of variable %s \n", tree->first->token);
						exit(0);
					}
				}
				else if(strcmp("REAL",check_type_of_variable(tree->first->token))!=0 && strcmp("INT",check_type_of_variable(tree->first->token))!=0 && (strcmp(tree->first->token,check_type_of_variable(tree->first->token))!=0) && (strcmp("FUNCTION",check_type_of_variable(tree->first->token))!=0))
				{
					printf("9.Error: Type error of variable %s \n", tree->first->token);
					exit(0);
				}
				else if(search_var(current_func, tree->first->token)==NULL && (strcmp(tree->first->token,check_type_of_variable(tree->first->token))==0) && (strcmp("FUNCTION",check_type_of_variable(tree->first->token))!=0))
				{
					printf("Error: Variable %s not delcared!\n",tree->first->token);
					exit(0);
				}
				/*else if (strcmp(check_type_of_variable(tree->first->token),"FUNCTION")==0){
						if(check_foo(tree->first->token)!=NULL){
							if(strcmp(check_foo(tree->first->token),"REAL")!=0 && strcmp(check_foo(tree->first->token),"INT")!=0){
							printf("Error: The return value of function %s are incorrect! \n",tree->first->token);
							exit(0);
						}
					}	
					else if(check_foo(tree->first->token)==NULL && strcmp(check_type_of_variable(tree->first->token),"FUNCTION")==0){
							printf("Error: Function %s not delcared!\n",tree->first->token);
							exit(0);
						}
					}*/
				}
			}
		}	
	if(tree->second){
		if(strcmp(tree->second->token, ""))
		{
			if(CheckOper(tree->second->token)==1)
			{
				if(search_var(current_func, tree->second->token)!=NULL){
					if(strcmp(search_var(current_func, tree->second->token), "REAL")!=0 && strcmp(search_var(current_func, tree->second->token), "INT")!=0)
					{
						printf("10.Error: Type error of variable %s \n", tree->second->token);
						exit(0);
					}
				}
				else if(strcmp("REAL",check_type_of_variable(tree->second->token))!=0 && strcmp("INT",check_type_of_variable(tree->second->token))!=0 && (strcmp(tree->second->token,check_type_of_variable(tree->second->token))!=0) && (strcmp("FUNCTION",check_type_of_variable(tree->second->token))!=0))
				{
					printf("11.Error: Type error of variable %s \n", tree->second->token);
						exit(0);
				}
				else if(search_var(current_func, tree->second->token)==NULL && (strcmp(tree->second->token,check_type_of_variable(tree->second->token))==0) && (strcmp("FUNCTION",check_type_of_variable(tree->second->token))!=0))
				{
					printf("Error: Variable %s not delcared!\n",tree->second->token);
					exit(0);
				}
				else if (strcmp(check_type_of_variable(tree->second->token),"FUNCTION")==0){
						if(check_foo(tree->second->token)!=NULL){
							if(strcmp(check_foo(tree->second->token),"REAL")!=0 && strcmp(check_foo(tree->second->token),"INT")!=0){
							printf("Error: The return value of function %s are incorrect! \n",tree->second->token);
							exit(0);
						}
					}	
					else if(check_foo(tree->second->token)==NULL && strcmp(check_type_of_variable(tree->second->token),"FUNCTION")==0){
							printf("Error: Function %s not delcared!\n",tree->second->token);
							exit(0);
						}	
						
						temp_func_name = (char*)malloc(sizeof(char));
						strcpy(temp_func_name,tree->second->token);
						CheckSendVar(tree->second);
						if(tempcount< get_func(temp_func_name)->amount_of_acc_var){
							printf("Error: Too few args were sent to function %s\n",temp_func_name);
							exit(0);
						}
						tempcount = 0;
						free(temp_func_name);
						temp_func_name = NULL;
					
					}
				}
			}
		}
	if(tree->first)
		RealCheckExp(tree->first);
	if(tree->second)
		RealCheckExp(tree->second);
	if(tree->third)
		RealCheckExp(tree->third);
}




void IntCheckExp(node* tree){

	int flag = 0;

	if(tree->first){
		if(strcmp(tree->first->token, ""))
		{
			if(CheckOper(tree->first->token)==1)
			{
				if(search_var(current_func, tree->first->token)!=NULL){
					int i = 0;
					while(tree->first->token[i]!='\0'){
						if(tree->first->token[i] == '|'){
							flag = 1;
						}

						i++;
					}
					if(strcmp(search_var(current_func, tree->first->token), current_var_type)!=0 && flag == 0)
					{
						printf("12.Error: Type error of variable %s \n", tree->first->token);
						exit(0);
					}
				}
				else if(strcmp(current_var_type,check_type_of_variable(tree->first->token))!=0 && (strcmp(tree->first->token,check_type_of_variable(tree->first->token))!=0) && (strcmp("FUNCTION",check_type_of_variable(tree->first->token))!=0))
				{
					printf("13.Error: Type error of variable %s \n", tree->first->token);
						exit(0);
				}

				else if(search_var(current_func, tree->first->token)==NULL && (strcmp(tree->first->token,check_type_of_variable(tree->first->token))==0) && (strcmp("FUNCTION",check_type_of_variable(tree->first->token))!=0))
				{

					printf("Error: Variable %s not delcared!\n",tree->first->token);
					exit(0);
				}
				/*else if (strcmp(check_type_of_variable(tree->first->token),"FUNCTION")==0){
							if(check_foo(tree->first->token)!=NULL){
								if(strcmp(check_foo(tree->first->token),current_var_type)!=0){
									printf("hiiii %s\n", check_foo(tree->first->token));
								printf("Error:1... The return value of function %s are incorrect! \n",tree->first->token);
								exit(0);
							}
						}	
						else if(check_foo(tree->first->token)==NULL && strcmp(check_type_of_variable(tree->first->token),"FUNCTION")==0){
							printf("Error: Function %s not delcared!\n",tree->second->token);
							exit(0);
						}	
						CheckSendVar(tree->first);
					}*/


			}
		}
	}

	if(tree->second){
		if(strcmp(tree->second->token, ""))
		{
			if(CheckOper(tree->second->token)==1)
			{
				if(search_var(current_func, tree->second->token)!=NULL){
					int i = 0;
					while(tree->second->token[i]!='\0'){
						if(tree->second->token[i] == '|'){
							flag = 1;
						}

						i++;
					}
					if(strcmp(search_var(current_func, tree->second->token), current_var_type)!=0 && flag == 0)
					{
						//printf("14.Error: Type error of variable %s \n", tree->first->token);
						printf("14.Error: Type error of variable \n");
						exit(0);
					}
				}
				else if(strcmp(current_var_type,check_type_of_variable(tree->second->token))!=0 && (strcmp(tree->second->token,check_type_of_variable(tree->second->token))!=0) && (strcmp("FUNCTION",check_type_of_variable(tree->second->token))!=0))
				{
					printf("%s\n", current_var_type);
					printf("15.Error: Type error of variable %s \n", tree->first->token);
						exit(0);
				}
				else if(search_var(current_func, tree->second->token)==NULL && (strcmp(tree->second->token,check_type_of_variable(tree->second->token))==0) && (strcmp("FUNCTION",check_type_of_variable(tree->second->token))!=0))
				{
					printf("Error: Variable %s not delcared!\n",tree->second->token);
					exit(0);
				}
				else if (strcmp(check_type_of_variable(tree->second->token),"FUNCTION")==0){
						if(check_foo(tree->second->token)!=NULL){
							if(strcmp(check_foo(tree->second->token),current_var_type)!=0){
								printf("Error: The return value of function %s are incorrect! \n",tree->second->token);
								exit(0);
						}
					}	
						else if(check_foo(tree->second->token)==NULL && strcmp(check_type_of_variable(tree->second->token),"FUNCTION")==0){
								printf("Error: Function %s not delcared!\n",tree->second->token);
								exit(0);
						}

						temp_func_name = (char*)malloc(sizeof(char));
						strcpy(temp_func_name,tree->second->token);
						CheckSendVar(tree->second);
						if(tempcount< get_func(temp_func_name)->amount_of_acc_var){
							printf("Error: Too few args were sent to function %s\n",temp_func_name);
							exit(0);
						}
						tempcount = 0;
						free(temp_func_name);
						temp_func_name = NULL;
				
				}
			
			
			
			
			}
		}
	}
	if(tree->first)
		IntCheckExp(tree->first);
	if(tree->second){
		IntCheckExp(tree->second);
	}
	if(tree->third){
		IntCheckExp(tree->third);
	}
}



void CheckSendVar(node* tree){

	if(tree->first){
		if(strcmp(tree->first->token, "")!=0){
			tempcount++;
			if(strcmp(check_type_of_variable(tree->first->token),tree->first->token)!=0 && (strcmp("FUNCTION",check_type_of_variable(tree->first->token))!=0)){
		 		CheckTyepInSymbolTanle(check_type_of_variable(tree->first->token),temp_func_name);
			}
			else if(search_var(current_func ,tree->first->token)!=NULL){
				CheckTyepInSymbolTanle(search_var(current_func ,tree->first->token),temp_func_name);
			}
			else if (strcmp(check_type_of_variable(tree->first->token),"FUNCTION")==0){
				if(check_foo(tree->first->token)!=NULL){
						CheckTyepInSymbolTanle(check_foo(tree->first->token),temp_func_name);
					}
				else if(check_foo(tree->first->token)==NULL && strcmp(check_type_of_variable(tree->first->token),"FUNCTION")==0){
								printf("Error: Function %s not delcared!\n",tree->first->token);
								exit(0);
							}

			}
		 }

		CheckSendVar(tree->first);
	}
	
	if(tree->second){
		CheckSendVar(tree->second);
	}
}



void CheckTyepInSymbolTanle(char* type,char* func_name){
	
	//printf("%d\n", tempcount);
	//printf("%s\n", func_name);
	func_node* current;
	current = get_func(func_name);

	if(tempcount>current->amount_of_acc_var){
		printf("Error: Too many entries were sent to function %s \n", func_name);
		exit(0);
	}

	int i = 0;
	s_table* current_symbol = NULL;
	if(current->symbol_table!=NULL){
		while(i<tempcount){
			if(current_symbol==NULL){
			current_symbol = current->symbol_table;
			}
			else{
			current_symbol = current_symbol->next_var;
			
			}
			i++;
			//printf("%d\n", i);
		}
	}
	if(strcmp(current_symbol->vari_type,"REAL")!=0){
		if(strcmp(type,current_symbol->vari_type)!=0){
			printf("Error: Unable to send value %s to value %s\n", type, current_symbol->vari_type);
			exit(0);
		}
	}
	else if(strcmp("REAL",type)!=0 && strcmp("INT",type)!=0){
			printf("Error: Unable to send value %s to value %s\n", type, current_symbol->vari_type);
			exit(0);	
		}
}




int CheckOper(char* oper)
{
	///////ASS/////////////
	if(strcmp(oper, "=")==0)
	{
		return 0;
	}
	if(strcmp(oper, "*")==0)
	{
		return 0;
	}
	if(strcmp(oper, "/")==0)
	{
		return 0;
	}
	if(strcmp(oper, "+")==0)
	{
		return 0;
	}
	if(strcmp(oper, "-")==0)
	{
		return 0;
	}
	///////COND/////////////
	if(strcmp(oper, "==")==0)
	{
		return 0;
	}
	if(strcmp(oper, ">=")==0)
	{
		return 0;
	}
	if(strcmp(oper, "<=")==0)
	{
		return 0;
	}
	if(strcmp(oper, ">")==0)
	{
		return 0;
	}
	if(strcmp(oper, "<")==0)
	{
		return 0;
	}
	if(strcmp(oper, "!=")==0)
	{
		return 0;
	}
	if(strcmp(oper, "||")==0)
	{
		return 0;
	}
	if(strcmp(oper, "&&")==0)
	{
		return 0;
	}
	if(strcmp(oper, "()")==0)
	{
		return 0;
	}

	return 1;
}




void VarBlock(node* tree){
    if(tree->first){
        if(strcmp(tree->token,"VAR")==0){           
            strcpy(type_var,tree->first->token);
        }
		else if(strcmp(tree->token,"VAR")!=0){
			//printf("c_level:%d, func level: %d\n",current_level, current_func->level);
			if(current_level == current_func->level+1){
            	make_symbol(current_func,type_var,tree->first->token);
			}

			else if(current_level == current_block->block_level+1){
				//cprintf("%s,%s,%s",current_block->b_name,type_var,tree->first->token);
				make_symbol_block(current_block,type_var,tree->first->token);
			}

		}
        

		if(strcmp(tree->token,"FUNCTION")==0){   
			       
            CheckAcc(tree);
		}
        
		VarBlock(tree->first);	
    }   

    if(tree->second){
		//printf("c_level:%d, func level: %d\n",current_level, current_func->level);
        if(strcmp(tree->first->token,"VAR")==0)
        {           
            strcpy(type_var,tree->second->token);
        }

		else if(current_level == current_func->level+1){
			
            make_symbol(current_func,type_var,tree->second->token);
        }

		else if(current_level == current_block->block_level+1){
				//printf("%s,%s,%s\n",current_block->b_name,type_var,tree->second->token);
				make_symbol_block(current_block,type_var,tree->second->token);
			}
	
		VarBlock(tree->second);
    }

    if(tree->third)
        VarBlock(tree->third);
    if(tree->fourth)
		VarBlock(tree->fourth);
        
}

int CheckType(char* kw){
	if(strcmp(kw,"IF")==0){
		return 0; 
	} 	
	if(strcmp(kw,"WHILE")==0){
		return 0;	
	}
	if( strcmp(kw,"DO")==0){
		return 0;	
	}
	if(strcmp(kw,"VAR")==0){
		return 0;	
	} 
	if(strcmp(kw,"return")==0){			
		return 0;
	}
	return 1;
}

/*--------------------------------void end----------------------------------------------------*/
void CheckAcc(node* tree){
			
	if(tree->first){
		if(strcmp(tree->first->token,"")){
			if(strcmp(tree->token,"TYPE")==0){
				//printf("%s\n", tree->first->token);
				strcpy(type_var,tree->first->token);

			}
			else if(strcmp(tree->first->token,"TYPE")!=0){
			//	printf("c_level:%d, func level: %d\n",current_level, current_func->level);
				if(current_level == current_func->level){
					make_symbol(current_func,type_var,tree->first->token);
					current_func->amount_of_acc_var++;
				}
			}
		}		
		CheckAcc(tree->first);
	}
	if(tree->second){
		if(strcmp(tree->second->token,"")){
			if(strcmp(tree->token,"TYPE")==0){
				//printf("%s\n", tree->second->token);
				strcpy(type_var,tree->second->token);

			}
			else if(strcmp(tree->second->token,"TYPE")!=0){
				if(current_level == current_func->level){
					make_symbol(current_func,type_var,tree->second->token);
					current_func->amount_of_acc_var++;
				}
			}
		}
		CheckAcc(tree->second);
	}
	
	if(tree->third){
		CheckAcc(tree->third);
	
	}
	if(tree->fourth){
		CheckAcc(tree->fourth);
	}
}


char* CheckvarType(char* kw)
{
	if(strcmp(kw,"INT")==0){
		return kw; 
	} 	
	if(strcmp(kw,"CHAR")==0){
		return kw;	
	}
	if( strcmp(kw,"STRING")==0){
		return kw;	
	}
	if(strcmp(kw,"BOOL")==0){
		return kw;	
	} 
	if(strcmp(kw,"REAL")==0){			
		return kw;
	}
	if(strcmp(kw,"INT*")==0){ 
		return kw;	
	} 	
	if(strcmp(kw,"CHAR*")==0){ 
		return kw;	
	} 
	if(strcmp(kw,"REAL*")==0){ 
		return kw;
	} 		
	return NULL;
}

char* CheckFuncType(char* kw){
	if(strcmp(kw,"VOID")==0){			
		return kw;
	}
	if(strcmp(kw,"INT")==0){
		return kw; 
	} 	
	if(strcmp(kw,"CHAR")==0){
		return kw;	
	}
	if( strcmp(kw,"STRING")==0){
		return kw;	
	}
	if(strcmp(kw,"BOOL")==0){
		return kw;	
	} 
	if(strcmp(kw,"REAL")==0){			
		return kw;
	}
	if(strcmp(kw,"INT*")==0){ 
		return kw;	
	} 	
	if(strcmp(kw,"CHAR*")==0){ 
		return kw;	
	} 
	if(strcmp(kw,"REAL*")==0){ 
		return kw;
	} 		
	return NULL;
}

char* search_var(func_node* func, char* x){	

	char* y = (char*)malloc(sizeof(char));
	strcpy(y,x);

	int i=0;
	while(y[i]!='\0'){
		if(y[i]=='|'){
			y = strtok(y,"|");

			if(search_var(current_func,y)!=NULL && strcmp(search_var(current_func,y),"STRING")==0){
				return "INT";
			}
			else{
				break;
			}
		}
		i++;
	}
	i=0;
	while(y[i]!='\0'){
		if(y[i]=='*'){
			 y = strtok(y,"*");
			break;
		}
		if(y[i]=='&'){
			 y = strtok(y,"&");
			break;
		}

		i++;
	}


	//printf("%s\n",y);

	func_node* tempf = current_func;
	Block_node* tempb = current_block;
	int k = current_level;
	//printf("i am K: %d\n", k);
	//printf("%d %s\n",current_func->level, current_func->block_name);
	while(k>0){
			/*if(tempb!=NULL){
				printf("i am K: %d\n",tempb->block_level);
			}*/
		if (tempf!=NULL && k == tempf->level+1){
			//printf("iter numb: %d, func search:  %s, value: %s\n", k,tempf->block_name, y);
			if(tempf->symbol_table!=NULL){
				s_table* current = tempf->symbol_table;
				for (;current; current = current->next_var){
					if(strcmp(y,current->vari_name)==0){
						//printf("i am here %s, %s %s %d \n", y , current->vari_type, tempf->block_name, k);
						return current->vari_type;
					}	
				}
			}
			if(tempf != NULL && tempf->back_func != NULL){
					tempf=tempf->back_func;
			}
			else if(tempf != NULL && tempf->back_block != NULL){
				tempb = tempf->back_block;
			}
		}

		else if(tempb!=NULL && k == tempb->block_level+1){
					//printf("iter numb: %d, block search:  %s  value: %s\n", k,tempb->b_name, y);
					if(tempb->symbol_table!=NULL){
							s_table* current = tempb->symbol_table;
							for (;current; current = current->next_var){
							if(strcmp(y,current->vari_name)==0){
								//printf("i am here %s, %s\n", y , current->vari_type);
								return current->vari_type;
							}	
						}
					}
					if(tempb != NULL && tempb->back_func != NULL){
						tempf=tempb->back_func;
					}
					else if(tempb != NULL && tempb->back_block != NULL){
						tempb = tempb->back_block;
					}
			}

		
			/*if(tempf != NULL && tempf->back_func != NULL){
				tempf=tempf->back_func;
				//printf("fuuuuuuuuuunnnnnccccccc rreettt func........: %s\n", tempf->back_func->block_name);
			}

			/*if(tempb != NULL && tempb->back_block != NULL){
				tempb=tempb->back_block;
			}*/
			
			/*if(tempb != NULL && tempb->back_func != NULL){
				printf("can't do it\n");
				printf("bbbbblllloooocckkkk rreettt func........: %s\n", tempb->back_func->block_name);
				//tempf=tempb->back_func;
			}*/

			k--;
	}
	return NULL;
}
	
/*	
	if (current_level == current_func->level){
		if(current_func->symbol_table!=NULL){
			s_table* current = current_func->symbol_table;
			for (;current; current = current->next_var){
				if(strcmp(y,current->vari_name)==0){
					return current->vari_type;
				}	
			}
		}

		if(current_level-1 == current_func->back_func->level){
			
		}


	}
*/


/*
	if(func->symbol_table!=NULL){
		s_table* current = func->symbol_table;
		for (;current; current = current->next_var){
			if(strcmp(y,current->vari_name)==0){
				return current->vari_type;
			}	
		}
	}

	if(func->back_func != NULL){
		func = func->back_func;
		while(func != NULL){
			if(func->symbol_table!=NULL){
				s_table* current = func->symbol_table;
				for (;current; current = current->next_var){
					if(strcmp(y,current->vari_name)==0){
						return current->vari_type;
					}	
				}
			}
			func = func->back_func;
		}
	}
	*/


char* check_foo(char* func_name_check)
{	
	//printf("hii Iam : %s\n",func_name_check);
	if(head!=NULL){

		func_node* checker = head;
		//printf("first function %s\n",checker->block_name);
		while(checker!=NULL)
		{	
			//printf("%s\n",checker->block_name);
			if(strcmp(checker->block_name,func_name_check)==0){
				return checker->ret_type;
			}
			checker = checker->next_func;
		}

	}
	
	return NULL;

}

func_node* get_func(char* func_name_check)
{	
	//printf("hii Iam : %s\n",func_name_check);
	if(head!=NULL){

		func_node* checker = head;
		//printf("first function %s\n",checker->block_name);
		while(checker!=NULL)
		{	
			//printf("%s\n",checker->block_name);
			if(strcmp(checker->block_name,func_name_check)==0){
				return checker;
			}
			checker = checker->next_func;
		}

	}
	
	return NULL;

}


void IsInList(func_node* node)
{
	if(head!=NULL){

		func_node* checker = head;
		while(checker!=NULL)
		{
			if(strcmp(checker->block_name,node->block_name)==0){
				printf("Error: Duplicate function name - %s\n",node->block_name);
				exit(0);
			}
			checker = checker->next_func;
		}

	}
}


//--------------Functions part1:-------------
node* makenode(char* token,node* first,node* second,node* third,node* fourth){
	node* newnode=(node*)malloc(sizeof(node));
	newnode->token=(char*)malloc(sizeof(token) + 1);
	strcpy(newnode->token,token);
	newnode->first=first;
	newnode->second=second;
	newnode->third=third;
	newnode->fourth=fourth;
	
	return newnode;
}


void Printtree(node* tree){
    printSpaces(tree,0);
}


void printSpaces(node* tree,int space){
	for(int i=0;i<space;i++){
		printf("  ");
	}
	
	if(!tree->first && !tree->second && !tree->third && !tree->fourth){
		printf("(");
		printf("%s",tree->token);
		printf(")\n");
		return;
	}
	
	printf("(");
	space++;
	printf("%s\n",tree->token);
	
	if(tree->first)
		printSpaces(tree->first,space);
	if(tree->second)
		printSpaces(tree->second,space);
	if(tree->third)
		printSpaces(tree->third,space);
	if(tree->fourth)
		printSpaces(tree->fourth,space);

	for(int i=0;i<space;i++){
		printf("  ");
	}
	
	printf(")\n");
}

//------------------------------------------
int main(){
	type_var = (char*)malloc(sizeof(char));

	yyparse();
	//printf("\n\n\n%s\n", type_var);
	//print_link_list();
	//print_blocks(head);
	return 0;
	
}

int yyerror(char* e){
	int yydebug=1;
	fflush(stdout);
	fprintf(stderr,"Error %s at line %d\n" ,e,yylineno);
	fprintf(stderr, "does not accept '%s'\n",yytext);
	exit(0);
	return 0;
}