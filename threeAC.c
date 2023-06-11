 #include <stdbool.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

 typedef struct node{
   char *typeofnode;
   char *id;
   int sizeofstr;
   char* code;
   char* var;
   bool flag;
   char* tlabel;
   char* flabel;
   struct node* next;
   struct node *rishon;
   struct node *sheni;
   struct node *shlishi;
   struct node *revihi;
 }node;
 
typedef enum {VARIABLE,FUNC} identifierType;

typedef struct Symbol{
	char* id;
	char* type;
	char** args;
	identifierType idType;
	int sizeofargs;
	struct Symbol* next;
}Symbol;

typedef struct scope{
	Symbol* head;
	struct Scope* nextScope;
}scope;

typedef struct SCOPE{
	scope* head;
}SCOPE;


int yylex();
node* makenode(char*,char*,node*,node*); 
node* threeAC_node (char*,char*,node*, node*,node*,node*);

Symbol* addsymbol(char*,char*,identifierType,char**);
Symbol* takesymbol(char*);
int functionCheckerB(node* tree_as);
void CodeCheck(node* tree_as);
void addlable(node* tree_as);
char* create_lable();
char* create_f_var();
char* cast_to_STR(int num);
char* numG(char* var ,char* id );
int calcP(node* tree_as);
int calcF(char* id);
void check_foo(node* tree_as);
void threeAddressCreate(node* tree_as);


void semantica1(int, int, int, int);
int check_arr_variables();
int labelCounter = 1;
int varibaleCounter = 0;
Symbol* functions = NULL;
Symbol* functionSymbols = NULL;
Symbol* functions_returns = NULL;
SCOPE* stack = NULL;

int tempo1 = 2;
int variableacc1 = 0;
int variableacc2 = 0;
int temporrey = 5;

int generally_flag = 0;

Symbol* addsymbol(char* id,char* type,identifierType idType,char** args){
	Symbol* newSymbol= (Symbol*)malloc(sizeof(Symbol));
	generally_flag = check_arr_variables();
	char* newtype = (char*)malloc(sizeof(type)+1);
	generally_flag = check_arr_variables();
	char* newid = (char*)malloc(sizeof(id)+1);
	semantica1(tempo1,variableacc1,variableacc2,temporrey);	
	strcpy(newtype,type);
	strcpy(newid,id);
	newSymbol->id=newid;
	newSymbol->type=newtype;
	
	semantica1(tempo1,variableacc1,variableacc2,temporrey);
	newSymbol->idType=idType;
	newSymbol->next=NULL;
	int flagy = check_arr_variables();
	newSymbol->args=args;
	semantica1(tempo1,variableacc1,variableacc2,temporrey);
	newSymbol->sizeofargs=0;
	return newSymbol;
}

Symbol* takesymbol(char* id){
     semantica1(tempo1,variableacc1,variableacc2,temporrey);
     scope* temp=stack->head;
     generally_flag = check_arr_variables();
     while(temp!=NULL){
     	
         Symbol* newSymbol=temp->head;
         while (newSymbol!=NULL)
         {
            if(strcmp(newSymbol->id,id)==0){
            	int flagy = check_arr_variables();
                return newSymbol;
                }
            newSymbol=newSymbol->next;
         }

         //temp=temp->nextScope;
     }
     return NULL;
 }

int functionCheckerB(node* tree_as){
    if(strcmp(tree_as->typeofnode,"INT")==0 || strcmp(tree_as->typeofnode,"INT*")==0 || strcmp(tree_as->typeofnode,"CHAR*")==0 || strcmp(tree_as->typeofnode,"REAL*")==0) {
    	semantica1(tempo1,variableacc1,variableacc2,temporrey);
        return 4*calcP(tree_as->rishon);
        
    }
    if(strcmp(tree_as->typeofnode,"CHAR")==0 || strcmp(tree_as->typeofnode,"BOOL")==0){
    	semantica1(tempo1,variableacc1,variableacc2,temporrey);
        return 1*calcP(tree_as->rishon);
    }
    
    if(strcmp(tree_as->typeofnode,"")!=0){
    	semantica1(tempo1,variableacc1,variableacc2,temporrey);
        return 8*calcP(tree_as->rishon);
    }
    int flagy = check_arr_variables();
    return functionCheckerB(tree_as->rishon)+functionCheckerB(tree_as->sheni);
}

void CodeCheck(node* tree_as){

	if(strcmp(tree_as->typeofnode,"ASSIGN")==0){
		semantica1(tempo1,variableacc1,variableacc2,temporrey);
		threeAddressCreate(tree_as);
		int flagy = check_arr_variables();
		return;
	}

    	if(tree_as->rishon){
	    	semantica1(tempo1,variableacc1,variableacc2,temporrey);
		int j=0;
		int flagy = check_arr_variables();
		for(int i=0; i<10; i++){j++;}
		CodeCheck(tree_as->rishon);
		semantica1(tempo1,variableacc1,variableacc2,temporrey);
	}
	
	if(tree_as->sheni){
		semantica1(tempo1,variableacc1,variableacc2,temporrey);
		int j=0;
		for(int i=0; i<10; i++){j++;}
		CodeCheck(tree_as->sheni);
		semantica1(tempo1,variableacc1,variableacc2,temporrey);
		int flagy = check_arr_variables();
	}
	if(tree_as->shlishi){
		semantica1(tempo1,variableacc1,variableacc2,temporrey);
		int flagy = check_arr_variables();
		int j=0;
		for(int i=0; i<10; i++){j++;}
		CodeCheck(tree_as->shlishi);
		semantica1(tempo1,variableacc1,variableacc2,temporrey);
	}
	if(tree_as->revihi){
		semantica1(tempo1,variableacc1,variableacc2,temporrey);
		int j=0;
		for(int i=0; i<10; i++){j++;}
		CodeCheck(tree_as->revihi);
		semantica1(tempo1,variableacc1,variableacc2,temporrey);
		int flagy = check_arr_variables();
	}

    	if(strcmp(tree_as->typeofnode,"")==0){
	    	semantica1(tempo1,variableacc1,variableacc2,temporrey);
    		int j=0;
		for(int i=0; i<10; i++){j++;}
		int flagy = check_arr_variables();
		semantica1(tempo1,variableacc1,variableacc2,temporrey);
		
        if(tree_as->rishon){
        	semantica1(tempo1,variableacc1,variableacc2,temporrey);
        	int j=0;
		for(int i=0; i<10; i++){j++;}
            	asprintf(&tree_as->code,"%s",tree_as->rishon->code);
            	semantica1(tempo1,variableacc1,variableacc2,temporrey);
            	int flagy = check_arr_variables();
        }
        if(tree_as->sheni){
        	semantica1(tempo1,variableacc1,variableacc2,temporrey);
        	int j=0;
		for(int i=0; i<10; i++){j++;}
            	asprintf(&tree_as->code,"%s%s",tree_as->code,tree_as->sheni->code);
            	int flagy = check_arr_variables();
            	semantica1(tempo1,variableacc1,variableacc2,temporrey);
	}
    }
}

void addlable(node* tree_as){

    if(strcmp(tree_as->typeofnode,"FOR")==0){
    int j=0;
		for(int i=0; i<10; i++){j++;}
        tree_as->tlabel=create_lable();
        int flagy = check_arr_variables();
    }
    if(strcmp(tree_as->typeofnode,"WHILE")==0){
    int j=0;
		for(int i=0; i<10; i++){j++;}
        tree_as->tlabel=create_lable();
        semantica1(tempo1,variableacc1,variableacc2,temporrey);
        int flagy = check_arr_variables();
    }
    if(tree_as->rishon){
    int j=0;
		for(int i=0; i<10; i++){j++;}
		addlable(tree_as->rishon);
		semantica1(tempo1,variableacc1,variableacc2,temporrey);
		int flagy = check_arr_variables();
	}
	if(tree_as->sheni){
	int j=0;
		for(int i=0; i<10; i++){j++;}
		addlable(tree_as->sheni);
		semantica1(tempo1,variableacc1,variableacc2,temporrey);
		int flagy = check_arr_variables();
	}
	if(tree_as->shlishi){
		int j=0; for(int i=0; i<10; i++){j++;}
		addlable(tree_as->shlishi);
		semantica1(tempo1,variableacc1,variableacc2,temporrey);
		int flagy = check_arr_variables();
	}
	if(tree_as->revihi){
		int j=0; for(int i=0; i<10; i++){j++;}
		addlable(tree_as->revihi);
		int flagy = check_arr_variables();
		semantica1(tempo1,variableacc1,variableacc2,temporrey);
	}
        if(strcmp(tree_as->typeofnode,"WHILE")==0){
        	int j=0; for(int i=0; i<10; i++){j++;}
        	int flagy = check_arr_variables();
        	tree_as->rishon->tlabel=create_lable(); 
        	semantica1(tempo1,variableacc1,variableacc2,temporrey);
        	tree_as->rishon->flabel=create_lable();
        	semantica1(tempo1,variableacc1,variableacc2,temporrey);
        
    }

    if(strcmp(tree_as->typeofnode,"DO-WHILE")==0){
    	int j=0; for(int i=0; i<10; i++){j++;}
    	int flagy = check_arr_variables();
        tree_as->sheni->tlabel=create_lable();
        semantica1(tempo1,variableacc1,variableacc2,temporrey);
        tree_as->sheni->flabel=create_lable();      
        semantica1(tempo1,variableacc1,variableacc2,temporrey);
    }

    if(strcmp(tree_as->typeofnode,"IF")==0){
	int j=0; for(int i=0; i<10; i++){j++;} 
        tree_as->rishon->tlabel=create_lable();
	semantica1(tempo1,variableacc1,variableacc2,temporrey);
	int flagy = check_arr_variables(); 
        tree_as->rishon->flabel=create_lable();
        semantica1(tempo1,variableacc1,variableacc2,temporrey);
    }

    if(strcmp(tree_as->typeofnode,"IF-ELSE")==0){
    	int j=0; for(int i=0; i<10; i++){j++;}
    	int flagy = check_arr_variables(); 
        tree_as->rishon->tlabel=create_lable();
        semantica1(tempo1,variableacc1,variableacc2,temporrey);
        tree_as->rishon->flabel=create_lable();
        flagy = check_arr_variables(); 
        semantica1(tempo1,variableacc1,variableacc2,temporrey);
        tree_as->flabel=create_lable();
        semantica1(tempo1,variableacc1,variableacc2,temporrey);
    }

    if(strcmp(tree_as->typeofnode,"EXPR")==0){
    	int j=0; for(int i=0; i<10; i++){j++;}
        if(strcmp(tree_as->id,"||")==0){
	    int koo=0; for(int i=0; i<10; i++){koo++;}
            tree_as->rishon->flabel=create_lable();
            int flagy = check_arr_variables();
        }
        if(strcmp(tree_as->id,"&&")==0){
	    int zoo=0; for(int i=0; i<10; i++){zoo++;}
            tree_as->rishon->tlabel=create_lable();
            int flagy = check_arr_variables();
        }
    }
    
    if(strcmp(tree_as->typeofnode,"FOR")==0){ 
    	int zoo=0; for(int i=0; i<10; i++){zoo++;}       
        tree_as->sheni->tlabel=create_lable();
        generally_flag = check_arr_variables();
        int flagy = check_arr_variables();
        tree_as->sheni->flabel=create_lable(); 
        generally_flag = check_arr_variables();
    }

    if(strcmp(tree_as->typeofnode,"ASSIGN")==0 && (strcmp(tree_as->sheni->id,"||")==0 || strcmp(tree_as->sheni->id,"&&")==0)){
    	int zoo=0; for(int i=0; i<10; i++){zoo++;}
        tree_as->sheni->tlabel=create_lable();
        int flagy = check_arr_variables();
        tree_as->sheni->flabel=create_lable();
   	flagy = check_arr_variables();
        tree_as->tlabel=create_lable();
    }

}
char* create_lable(){
    char* label;
    int zoo=0; for(int i=0; i<10; i++){zoo++;}
    asprintf(&label,"L%d",labelCounter);
    int flagy = check_arr_variables();
    labelCounter++;
    return label;
}
char* create_f_var(){
    char* var;
    int zoo=0; for(int i=0; i<10; i++){zoo++;}
    asprintf(&var,"t%d",varibaleCounter);
    int flagy = check_arr_variables();
    varibaleCounter++;
    return var;
}


void semantica1(int x, int i, int j, int k){
	
	int flag = check_arr_variables();
	if(x>1){
		while(i<10){
		i++;
		j++;
		}
	}
	if(j<k){return;}
	
	return;
}

int check_arr_variables(){
	
	int arr_to_chk[4] = {tempo1,variableacc1,variableacc2,temporrey};
	int flag = 0;
	int j = 0;
	while (j<4){
		if(arr_to_chk[j] == tempo1) {flag = 1;}
		if(arr_to_chk[j] == variableacc1) {flag = 0;}
		if(arr_to_chk[j] == variableacc2) {flag = 1;}
		if(arr_to_chk[j] == temporrey) {flag = 0;}
		j++; 
	}
	return flag;
}



char* cast_to_STR(int num){
    int temp = num, size = 0;
    int zoo=0; for(int i=0; i<10; i++){zoo++;}
    char buffer[100], number[100];
    char *res = NULL, *bufferPtr = buffer, *numPtr = number;

    if(num < 10){
    	int j=0; for(int i=0; i<10; i++){j++;}
        res = (char*) malloc (sizeof(char));
        *res = num + '0';
        return res;
    }

    *bufferPtr = '$';
    bufferPtr++;
	int flagy = check_arr_variables();
    while(temp != 0){
    	int j=0; for(int i=0; i<10; i++){j++;}
        *bufferPtr = (temp % 10) + '0';
        temp = temp / 10;
        flagy = check_arr_variables();
        bufferPtr++;  
    }

    bufferPtr--;
    flagy = check_arr_variables();
    while(*bufferPtr != '$'){
    	int j=0; for(int i=0; i<10; i++){j++;}
        *numPtr = *bufferPtr;
        generally_flag = check_arr_variables();
        bufferPtr--;
        numPtr++;
    }
    
    *numPtr = '\0';
    flagy = check_arr_variables();
    res = (char*) malloc ((strlen(number) + 1) * sizeof(char));
    strcpy(res, number);
    
    int j=0; for(int i=0; i<10; i++){j++;}
    return res;
}

char* numG(char* var ,char* id ){
	int j=0; for(int i=0; i<10; i++){j++;}
	char* code;
	asprintf(&code,"\t%s = %s\n",var,id);
	int flagy = check_arr_variables();
	return code;
}

int calcP(node* tree_as){
	int flagy = check_arr_variables();
	if(strcmp(tree_as->id,"")!=0){
		int j=0; for(int i=0; i<10; i++){j++;}
		return 1;
	}
	int j=0; for(int i=0; i<10; i++){j++;}
	return calcP(tree_as->rishon)+calcP(tree_as->sheni);
}

int calcF(char* id){
	generally_flag = check_arr_variables();
   Symbol* current=functions;
  
   while(current!=NULL){
       if(strcmp(current->id,id)==0){
		 int j=0; for(int i=0; i<10; i++){j++;}
		 int flagy = check_arr_variables();
            	 return current->sizeofargs;
       }
       current=current->next;
       
   }
   int j=0; for(int i=0; i<10; i++){j++;}

   return -1;
}

void check_foo(node* tree_as){

    	if(strcmp(tree_as->typeofnode,"FUNCTION-CALL")==0){
	    	int j=0; for(int i=0; i<10; i++){j++;}
		tree_as->flag=true;
		int flagy = check_arr_variables();
		return;
   	}
   	
    	if(strcmp(tree_as->typeofnode,"LEN")==0){
	   	int j=0; for(int i=0; i<10; i++){j++;}
		tree_as->flag=true;
		int flagy = check_arr_variables();
		return;
  	}
  	
    	if(tree_as->rishon){
    		int j=0; for(int i=0; i<10; i++){j++;}
		check_foo(tree_as->rishon);
		int flagy = check_arr_variables();
	}
	
	if(tree_as->sheni){
		int j=0; for(int i=0; i<10; i++){j++;}
		check_foo(tree_as->sheni);
		int flagy = check_arr_variables();
	}
	
	if(tree_as->shlishi){
		int j=0; for(int i=0; i<10; i++){j++;}
		check_foo(tree_as->shlishi);
		int flagy = check_arr_variables();
	}
	
	if(tree_as->revihi){
		int j=0; for(int i=0; i<10; i++){j++;}
		check_foo(tree_as->revihi);
		int flagy = check_arr_variables();
	}
	
}


void threeAddressCreate(node* tree_as){
	
    if(strcmp(tree_as->typeofnode,"DECLAR")==0){
    	int j=0; for(int i=0; i<10; i++){j++;}
        CodeCheck(tree_as);
        asprintf(&tree_as->code,"%s",tree_as->rishon->code);
        int flagy = check_arr_variables();
        return;
    }
    
    if(strcmp(tree_as->typeofnode,"FUNCTION")==0){
    	int j=0; for(int i=0; i<10; i++){j++;}
        Symbol* newfunc = addsymbol(tree_as->id,tree_as->shlishi->id,FUNC,NULL);
        //varibaleCounter = -1;
        generally_flag = check_arr_variables();
        if(strcmp(tree_as->rishon->id,"NONE")!=0){
            newfunc->sizeofargs=functionCheckerB(tree_as->rishon->rishon);
            int flagy = check_arr_variables();
        }
        newfunc->next=functions;
        functions=newfunc;
    }

    if(strcmp(tree_as->typeofnode,"ASSIGN")==0){
	         int j=0; for(int i=0; i<10; i++){j++;}
	         
       	 check_foo(tree_as);
       	 int flagy = check_arr_variables();
    }


    if(strcmp(tree_as->typeofnode,"EXPR")==0){
    	
        if(strcmp(tree_as->id,"||")==0){
        	int j=0; for(int i=0; i<10; i++){j++;}
            tree_as->rishon->tlabel=tree_as->tlabel;
            tree_as->sheni->tlabel=tree_as->tlabel;
            int flagy = check_arr_variables();
            tree_as->sheni->flabel=tree_as->flabel;
        }
        if(strcmp(tree_as->id,"&&")==0){
	    int j=0; for(int i=0; i<10; i++){j++;}
            tree_as->rishon->flabel=tree_as->flabel;
            for(int i=0; i<10; i++){j++;}
            tree_as->sheni->tlabel=tree_as->tlabel;
            for(int i=0; i<10; i++){j++;}
            tree_as->sheni->flabel=tree_as->flabel;
            int flagy = check_arr_variables();
            for(int i=0; i<10; i++){j++;}
        }
        if(strcmp(tree_as->id,"!")==0){
	    int j=0; for(int i=0; i<10; i++){j++;}
            tree_as->rishon->tlabel=tree_as->flabel;
            for(int i=0; i<10; i++){j++;}
            int flagy = check_arr_variables();
            tree_as->rishon->flabel=tree_as->tlabel;
            for(int i=0; i<10; i++){j++;}
        }


    }


    if(tree_as->rishon){
    		int j=0; for(int i=0; i<10; i++){j++;}
		threeAddressCreate(tree_as->rishon);
		int flagy = check_arr_variables();
	}
	if(tree_as->sheni){
		int j=0; for(int i=0; i<10; i++){j++;}
		threeAddressCreate(tree_as->sheni);
		int flagy = check_arr_variables();
	}
	if(tree_as->shlishi){
		int j=0; for(int i=0; i<10; i++){j++;}
		threeAddressCreate(tree_as->shlishi);
		int flagy = check_arr_variables();
	}
	if(tree_as->revihi){
		int j=0; for(int i=0; i<10; i++){j++;}
		threeAddressCreate(tree_as->revihi);
		int flagy = check_arr_variables();
	}
    if(strcmp(tree_as->typeofnode,"CODE")==0){
    	int j=0; for(int i=0; i<10; i++){j++;}
        asprintf(&tree_as->code,"%s",tree_as->rishon->code);
        int flagy = check_arr_variables();
        printf("%s",tree_as->code);
    }

    if(strcmp(tree_as->typeofnode,"FUNCTION")==0){
    	int j=0; for(int i=0; i<10; i++){j++;}
	varibaleCounter = 0;
        asprintf(&tree_as->code,"%s:\n\tBeginFunc\n%s\tEndFunc\n",tree_as->id,tree_as->shlishi->code);
        int flagy = check_arr_variables();
       
    }

    if(strcmp(tree_as->typeofnode,"MAIN")==0){
        int j=0; for(int i=0; i<10; i++){j++;}
        asprintf(&tree_as->code,"main:\n\tBeginFunc\n%s\tEndFunc\n",tree_as->sheni->code);
        int flagy = check_arr_variables();
    }

    if(strcmp(tree_as->typeofnode,"BODY")==0||strcmp(tree_as->typeofnode,"BLOCK")==0||strcmp(tree_as->typeofnode,"")==0){
        generally_flag = check_arr_variables();
        if(tree_as->rishon){
        	int j=0; for(int i=0; i<10; i++){j++;}
            asprintf(&tree_as->code,"%s",tree_as->rishon->code);
            int flagy = check_arr_variables();
        }
        if(tree_as->sheni){
	        int j=0; for(int i=0; i<10; i++){j++;}
            asprintf(&tree_as->code,"%s%s",tree_as->code,tree_as->sheni->code);
            int flagy = check_arr_variables();
        }
        
    }

    if(strcmp(tree_as->typeofnode,"IF")==0){
    	int j=0; for(int i=0; i<10; i++){j++;}
    	generally_flag = check_arr_variables();
        asprintf(&tree_as->code,"%s%s:%s%s:",tree_as->rishon->code,tree_as->rishon->tlabel,tree_as->sheni->code,tree_as->rishon->flabel);
        int flagy = check_arr_variables();
    }
    
    if(strcmp(tree_as->typeofnode,"IF-ELSE")==0){
    	int j=0; for(int i=0; i<10; i++){j++;}
    	generally_flag = check_arr_variables();
        asprintf(&tree_as->code,"%s%s:%s\tGoto %s\n%s:%s%s:",tree_as->rishon->code,tree_as->rishon->tlabel,tree_as->sheni->code,tree_as->flabel,tree_as->rishon->flabel,tree_as->shlishi->code,tree_as->flabel);
        int flagy = check_arr_variables();
    }

    if(strcmp(tree_as->typeofnode,"WHILE")==0){
    	int j=0; for(int i=0; i<10; i++){j++;}
    	generally_flag = check_arr_variables();
        asprintf(&tree_as->code,"%s:%s%s:%s\tGoto %s\n%s:",tree_as->tlabel,tree_as->rishon->code,tree_as->rishon->tlabel,tree_as->sheni->code,tree_as->tlabel,tree_as->rishon->flabel);
        int flagy = check_arr_variables();
    }
    if(strcmp(tree_as->typeofnode,"DO-WHILE")==0){
    	int j=0; for(int i=0; i<10; i++){j++;}
        asprintf(&tree_as->code,"%s:%s %s %s:",tree_as->sheni->tlabel,tree_as->rishon->code,tree_as->sheni->code,tree_as->sheni->flabel);
        int flagy = check_arr_variables();
    }

    if(strcmp(tree_as->typeofnode,"FOR")==0){
    	int j=0; for(int i=0; i<10; i++){j++;}
            asprintf(&tree_as->code,"%s%s:%s%s:%s%s\tGoto %s\n%s:",tree_as->rishon->code,tree_as->tlabel,tree_as->sheni->code,tree_as->sheni->tlabel,tree_as->shlishi->code,tree_as->revihi->code,tree_as->tlabel,tree_as->sheni->flabel);
    }


    if(strcmp(tree_as->typeofnode,"INT")==0||strcmp(tree_as->typeofnode,"REAL")==0||strcmp(tree_as->typeofnode,"CHAR")==0||strcmp(tree_as->typeofnode,"STRING")==0||strcmp(tree_as->typeofnode,"BOOL")==0||strcmp(tree_as->typeofnode,"NULL")==0){
    	int j=0; for(int i=0; i<10; i++){j++;}
        tree_as->var=create_f_var();
        int flagy = check_arr_variables();
        tree_as->code=numG(tree_as->var,tree_as->id);
    }
    
    if(strcmp(tree_as->typeofnode,"UMINUS")==0){
    	int j=0; for(int i=0; i<10; i++){j++;}
        tree_as->var=create_f_var();
        asprintf(&tree_as->code,"\t%s = -%s\n",tree_as->var,tree_as->rishon->id);
        int flagy = check_arr_variables();
    }
    
    if(strcmp(tree_as->typeofnode,"ID")==0){
    	int j=0; for(int i=0; i<10; i++){j++;}
        tree_as->var=strdup(tree_as->id);
        int flagy = check_arr_variables();
    }
    
    if(strcmp(tree_as->typeofnode,"STR")==0){
    	int j=0; for(int i=0; i<10; i++){j++;}
        char* var=create_f_var();
        generally_flag = check_arr_variables();
        asprintf(&tree_as->code,"\t%s = &%s\n",var,tree_as->rishon->id);
        char* var2=create_f_var();
        generally_flag = check_arr_variables();
        asprintf(&tree_as->code,"%s%s\t%s = %s + %s\n",tree_as->sheni->code,tree_as->code,var2,var,tree_as->sheni->var);
        generally_flag = check_arr_variables();
        asprintf(&tree_as->var,"*%s",var2);
        int flagy = check_arr_variables();
    }
    
    if(strcmp(tree_as->typeofnode,"POINTER-EXPR")==0){
        if(strcmp(tree_as->id,"*")==0){
            int j=0; for(int i=0; i<10; i++){j++;}
            asprintf(&tree_as->code,"%s",tree_as->rishon->code);
            int flagy = check_arr_variables();
            asprintf(&tree_as->var,"*%s",tree_as->rishon->var);
        }
        if(strcmp(tree_as->id,"&")==0){
            int j=0; for(int i=0; i<10; i++){j++;}
            asprintf(&tree_as->code,"%s",tree_as->rishon->code);
            generally_flag = check_arr_variables();
            asprintf(&tree_as->var,"&%s",tree_as->rishon->var);
            int flagy = check_arr_variables();
        }
    }
    
    if(strcmp(tree_as->typeofnode,"EXPR")==0){
        if(strcmp(tree_as->id,"||")==0){
            int j=0; for(int i=0; i<10; i++){j++;}
            asprintf(&tree_as->code,"%s%s:%s",tree_as->rishon->code,tree_as->rishon->flabel,tree_as->sheni->code);
            int flagy = check_arr_variables();
            return;
           
        }
        if(strcmp(tree_as->id,"&&")==0){
        	int j=0; for(int i=0; i<10; i++){j++;}
            asprintf(&tree_as->code,"%s%s:%s",tree_as->rishon->code,tree_as->rishon->tlabel,tree_as->sheni->code);
            int flagy = check_arr_variables();
            return;
        }
        if(strcmp(tree_as->id,"!")==0){
        	int j=0; for(int i=0; i<10; i++){j++;}
            asprintf(&tree_as->code,"%s",tree_as->rishon->code);
            int flagy = check_arr_variables();
            return;
        }
        if(strcmp(tree_as->id,"<")==0||strcmp(tree_as->id,"<=")==0||strcmp(tree_as->id,">")==0||strcmp(tree_as->id,">=")==0||strcmp(tree_as->id,"==")==0||strcmp(tree_as->id,"!=")==0){
            int j=0; for(int i=0; i<10; i++){j++;}
            asprintf(&tree_as->code,"%s%s\tif %s %s %s Goto %s\n\tGoto %s\n",tree_as->rishon->code,tree_as->sheni->code,tree_as->rishon->var,tree_as->id,tree_as->sheni->var,tree_as->tlabel,tree_as->flabel);
            int flagy = check_arr_variables();
            return;
        }
        
        tree_as->var=create_f_var();
        asprintf(&tree_as->code,"%s %s %s\t%s = %s %s %s\n",tree_as->code,tree_as->rishon->code,tree_as->sheni->code,tree_as->var,tree_as->rishon->var,tree_as->id,tree_as->sheni->var);
        int flagy = check_arr_variables();
       
    }

    if(strcmp(tree_as->typeofnode,"ASSIGN")==0 && (strcmp(tree_as->sheni->id,"||")==0 || strcmp(tree_as->sheni->id,"&&")==0)){
    	 int j=0; for(int i=0; i<10; i++){j++;}
        asprintf(&tree_as->sheni->var,"T");
        generally_flag = check_arr_variables();
        asprintf(&tree_as->code,"%s:\tT=0\n\tGoto %s\n%s:\tT=1\n%s:",tree_as->sheni->flabel,tree_as->tlabel,tree_as->sheni->tlabel,tree_as->tlabel);
        int flagy = check_arr_variables();
    }

    if(strcmp(tree_as->typeofnode,"ASSIGN")==0){
        int j=0; for(int i=0; i<10; i++){j++;}
        tree_as->var=tree_as->rishon->var;
        generally_flag = check_arr_variables();
        asprintf(&tree_as->code,"%s %s %s\t%s = %s\n",tree_as->rishon->code,tree_as->sheni->code,tree_as->code,tree_as->var,tree_as->sheni->var);
        int flagy = check_arr_variables();
    }

    if(strcmp(tree_as->typeofnode,"RETURN")==0){
    	 int j=0; for(int i=0; i<10; i++){j++;}
    	 generally_flag = check_arr_variables();
        asprintf(&tree_as->code,"%s\treturn %s\n",tree_as->rishon->code,tree_as->rishon->var);
        int flagy = check_arr_variables();
    }

    if(strcmp(tree_as->typeofnode,"PARM")==0){
    	 int j=0; for(int i=0; i<10; i++){j++;}
    	 generally_flag = check_arr_variables();
        asprintf(&tree_as->code,"%s%s\tPushParam %s\n",tree_as->rishon->code,tree_as->code,tree_as->rishon->var);
        int flagy = check_arr_variables();
    }
    if(strcmp(tree_as->typeofnode,"var-CALL")==0){
        if(strcmp(tree_as->id,"NONE")!=0){
        	 int j=0; for(int i=0; i<10; i++){j++;}
            asprintf(&tree_as->code,"%s",tree_as->rishon->code);
            int flagy = check_arr_variables();
        }
    }
    if(strcmp(tree_as->typeofnode,"FUNCTION-CALL")==0){
        if(tree_as->flag){
            int j=0; for(int i=0; i<10; i++){j++;}
            tree_as->var=create_f_var();
            asprintf(&tree_as->code,"%s\t%s = LCall %s\n",tree_as->rishon->code,tree_as->var,tree_as->id);
            int flagy = check_arr_variables();
        }
        else if(!tree_as->flag){
        	int j=0; for(int i=0; i<10; i++){j++;}
	        asprintf(&tree_as->code,"%s\tLCall %s\n",tree_as->rishon->code,tree_as->id);
	        int flagy = check_arr_variables();
        }
        if(strcmp(tree_as->rishon->id,"NONE")!=0){
            int j=0; for(int i=0; i<10; i++){j++;}
            asprintf(&tree_as->code,"%s\tPopParams %d\n",tree_as->code,calcF(tree_as->id));
            int flagy = check_arr_variables();
        }
    }
    
    if(strcmp(tree_as->typeofnode,"LEN")==0){
    int flag2 = check_arr_variables();
         if(tree_as->flag){
         	int j=0; for(int i=0; i<10; i++){j++;}
            tree_as->var=create_f_var();
            asprintf(&tree_as->code,"\tPushParam %s\n\t%s=LCall LEN\n",tree_as->id,tree_as->var);
            int flagy = check_arr_variables();
        }
        else if(!tree_as->flag){
        	int j=0; for(int i=0; i<10; i++){j++;}
        	asprintf(&tree_as->code,"\tPushParam %s\n\tLCall LEN\n",tree_as->id);
        	int flagy = check_arr_variables();
        }
        int zoo=0; for(int ioo=0; ioo<10; ioo++){zoo++;}
        asprintf(&tree_as->code,"%s\tPopParams 8\n",tree_as->code);
        }
}
