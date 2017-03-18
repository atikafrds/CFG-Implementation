#include "parse.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

Token BEGIN, END, INPUT, OUTPUT, IF, THEN, ELSE, DO, WHILE, FOR, TO; //SYNTAX
Token VAR, NUM, CMP, OPT; //TYPE
Token KURUNGBUKA, KURUNGTUTUP, KURAWALBUKA, KURAWALTUTUP, SAMADENGAN, LEBIHDARI, KURANGDARI; //SYMBOL

int line, word;

void Compile()
{
	strcpy(BEGIN.TabToken,"begin");
	BEGIN.Length = 5;
	strcpy(END.TabToken,"end");
	END.Length = 3;
	strcpy(INPUT.TabToken,"input");
	INPUT.Length = 5;
	strcpy(OUTPUT.TabToken,"output");
	OUTPUT.Length = 6;
	strcpy(KURUNGBUKA.TabToken,"(");
	KURUNGBUKA.Length = 1;
	strcpy(KURUNGTUTUP.TabToken,")");
	KURUNGTUTUP.Length = 1;
	strcpy(KURAWALBUKA.TabToken,"{");
	KURAWALBUKA.Length = 1;
	strcpy(KURAWALTUTUP.TabToken,"}");
	KURAWALTUTUP.Length = 1;
	strcpy(IF.TabToken, "if");
	IF.Length = 2;
	strcpy(THEN.TabToken, "then");
	THEN.Length = 4;
	strcpy(ELSE.TabToken, "else");
	ELSE.Length = 4;
	strcpy(DO.TabToken, "do");
	DO.Length = 2;
	strcpy(WHILE.TabToken, "while");
	WHILE.Length = 5;
	strcpy(FOR.TabToken, "for");
	FOR.Length = 3;
	strcpy(TO.TabToken, "to");
	TO.Length = 2;
	strcpy(VAR.TabToken,"VAR");
	VAR.Length = 3;	
	strcpy(NUM.TabToken,"NUM");
	NUM.Length = 3;	
	strcpy(OPT.TabToken,"OPT");
	OPT.Length = 3;
	strcpy(SAMADENGAN.TabToken,"=");
	SAMADENGAN.Length = 1;
	strcpy(LEBIHDARI.TabToken,">");
	LEBIHDARI.Length = 1;
	strcpy(KURANGDARI.TabToken,"<");
	KURANGDARI.Length = 1;

	/* ALGORITMA */
	line = 1;

	IGNORENEWLINE();
	IS(BEGIN);
	ADVTOKEN();
	
	IGNORENEWLINE();
	ARGUMENT();

	IGNORENEWLINE();
	IS(END);
	
	if (EndToken) {
		printf("Compilation finished (%d lines). Syntax valid.\n",line);
	}
	else {
		ADVTOKEN();
		IGNORENEWLINE();
		printf("Compilation failed. Syntax error at line %d.\n", line);
	}
}


void ARGUMENT() {

	
	IGNORENEWLINE();

	if (IsTokenSama(INPUT,CToken)) {
		ADVTOKEN();
		TestInput();
		IGNORENEWLINE();
		ARGUMENT();
	}
	else if (IsTokenSama(OUTPUT,CToken)) {
		ADVTOKEN();
		TestOutput();
		IGNORENEWLINE();
		ARGUMENT();
	}
	else if (IsTokenSama(IF,CToken)) {
		ADVTOKEN();
		TestIf();
		IGNORENEWLINE();
		ARGUMENT();
	}
	else if (IsTokenSama(DO,CToken)) {
		ADVTOKEN();
		TestDo();
		IGNORENEWLINE();
		ARGUMENT();
	}
	else if (IsTokenSama(FOR, CToken)) {
		ADVTOKEN();
		TestFor();
		IGNORENEWLINE();
		ARGUMENT();
	} 
	else if (IsTokenSama(KURAWALBUKA,CToken)){
		ADVTOKEN();
		IGNORENEWLINE();
		while(!EndToken && !IsTokenSama(KURAWALTUTUP,CToken)) {
			ADVTOKEN();
			IGNORENEWLINE();
		}
		ADVTOKEN();
		ARGUMENT();
	}
	else if(!IsTokenSama(INPUT,CToken) && !IsTokenSama(OUTPUT,CToken) && !IsTokenSama(IF,CToken) && !IsTokenSama(DO,CToken) && !(IsTokenSama(WHILE,CToken)) && !IsTokenSama(FOR,CToken) && !IsTokenSama(KURAWALBUKA,CToken) && !(IsTokenSama(END,CToken)) && IsVar(CToken)) {
		ADVTOKEN();
		IS(SAMADENGAN);
		ADVTOKEN();
		TestMat();
		ARGUMENT();
	}
	else {

	}

}


void IGNORENEWLINE(){
	while (CToken.TabToken[0]==newline) {
		ADVTOKEN();
		line++;
	}
}


void TestInput()
{
    IS(KURUNGBUKA);
    ADVTOKEN();
    IS(VAR);
    ADVTOKEN();
    IS(KURUNGTUTUP);
    ADVTOKEN();
}


void TestOutput()
{
    IS(KURUNGBUKA);
    ADVTOKEN();
    TestMat();
    IS(KURUNGTUTUP);
    ADVTOKEN();
}

void TestMat()
{
	if (IsVar(CToken))
    {
        ADVTOKEN();
        if ((CToken.TabToken[0]=='+')||(CToken.TabToken[0]=='-')||(CToken.TabToken[0]=='*')) {
        	ADVTOKEN();
        }
        TestMat();
    }
    else if (IsNum(CToken))
    {
        ADVTOKEN();
        if ((CToken.TabToken[0]=='+')||(CToken.TabToken[0]=='-')||(CToken.TabToken[0]=='*')) {
        	ADVTOKEN();
        }
        TestMat();
    }
    else
    {

    }
}

void TestIf() {
	IS(KURUNGBUKA);
	ADVTOKEN();
	TestCondition();
	IS(KURUNGTUTUP);
	ADVTOKEN();
	IS(THEN);
	ADVTOKEN();
	IGNORENEWLINE();
	IS(BEGIN);
	ADVTOKEN();
	IGNORENEWLINE();
	ARGUMENT();
	IS(END);
	ADVTOKEN();
	IGNORENEWLINE();
	if (IsTokenSama(ELSE, CToken)) {
		ADVTOKEN();
		IGNORENEWLINE();
		IS(BEGIN);
		ADVTOKEN();
		IGNORENEWLINE();
		ARGUMENT();
		IGNORENEWLINE();
		IS(END);
		ADVTOKEN();
	}
}

void TestCondition() {
	TestMat();
	IS(CMP);
	if (IsTokenSama(KURANGDARI,CToken)) {
		ADVTOKEN();
		if (IsTokenSama(SAMADENGAN,CToken) || IsTokenSama(LEBIHDARI,CToken)) {
			ADVTOKEN();
		}
	}
	else if (IsTokenSama(LEBIHDARI,CToken)) {
		ADVTOKEN();
		if (IsTokenSama(SAMADENGAN,CToken)) {
			ADVTOKEN();
		}
	}
	else {
		ADVTOKEN();
	}

	TestMat();
}

void TestDo() {
	IGNORENEWLINE();
	ARGUMENT();
	IGNORENEWLINE();
	IS(WHILE);
	ADVTOKEN();
	IS(KURUNGBUKA);
	ADVTOKEN();
	TestCondition();
	IS(KURUNGTUTUP);
	ADVTOKEN();
}

void TestFor() {
	IS(KURUNGBUKA);
	ADVTOKEN();
	IS(VAR);
	ADVTOKEN();
	IS(SAMADENGAN);
	ADVTOKEN();
	if (IsVar(CToken)) {
		ADVTOKEN();
	}
	else if (IsNum(CToken)){
		ADVTOKEN();
	}
	IS(TO);
	ADVTOKEN();
	if (IsVar(CToken)) {
		ADVTOKEN();
	}
	else if (IsNum(CToken)){
		ADVTOKEN();
	}
	IS(KURUNGTUTUP);
	ADVTOKEN();
	IS(DO);
	ADVTOKEN();
	IGNORENEWLINE();
	IS(BEGIN);
	ADVTOKEN();
	IGNORENEWLINE();
	ARGUMENT();
	IGNORENEWLINE();
	IS(END);
	ADVTOKEN();
}

void IS(Token K)
{
    if (IsTokenSama(K, OPT))
    {
        if ((CToken.TabToken[0] != '+') && (CToken.TabToken[0] != '-') && (CToken.TabToken[0] != '*'))
        {
            printf("Compilation failed. Syntax error at line %d, expected an arithmetic operator here.\n", line);
            exit(0);
        }
        else
        {
        }
    }
    else if (IsTokenSama(K, VAR))
    {
        boolean alph;
        char c;
        if (K.Length == 1)
        {
        	c = 'a';
	        alph = false;
	        while ((c <= 'z') && (!alph))
	        {
	            if (CToken.TabToken[0] == c)
	            {
	            alph = true;
	            }
	            c++;
	        }
	        if (!alph)
	        {
	            c = 'A';
	            while ((c <= 'Z') && (!alph))
	            {
	                if (CToken.TabToken[0] == c)
	                {
	                    alph = true;
	                }
	                c++;
	            }
	            if (!alph)
	            {
	            printf("Compilation failed. Syntax error at line %d, expected a single variable of alphabet here.\n", line);
	            exit(0);
	            }
	            else
	            {
	            }
        	}
        }
        else
        {
        }
    }
    else if (IsTokenSama(K, CMP)) {
    	if ((strcmp(CToken.TabToken, "<") != 0) && (strcmp(CToken.TabToken, ">") != 0) && (strcmp(CToken.TabToken, "=") != 0)) {
            printf("Compilation failed. Syntax error at line %d, expected comparation operator here.\n", line);
            exit(0);
    	}
    	else {
    	}
    }
    else if (!IsTokenSama(K, CToken))
    {
        printf("Compilation failed. Syntax error at line %d, expected '", line);
        PrintToken(K);
        printf("' here.\n");
        exit(0);
    }
    else
    {
    }
}

boolean IsVar(Token input) {
	/* KAMUS LOKAL */
	boolean alph, found;
    char c,i;

	/*ALGORITMA */
    
    //Asumsi variable hanya boleh huruf saja
    if (input.Length == 1) {
	    alph = true;
	    i=0;
	    while(i<input.Length && alph) {
		    c = 'a';
		    found = false;
		    while ((c <= 'z') && !found) {
		        if (input.TabToken[i] == c) {
		        	found = true;
		        }
		        c++;
		    }

		    if (!found) {
		        c = 'A';
		        while ((c <= 'Z') && (!found)) {
		            if (CToken.TabToken[i] == c) {
		                found = true;
		            }
		            c++;
		        }
		    }
		    alph = found;
		    i++;
	    }
	    return alph;
	}
	else {
		return false;
	}
}

boolean IsNum(Token input) {
	/* KAMUS LOKAL */
	boolean num, found;
    char c,i;

	/*ALGORITMA */
    num = true;
    
    //Kasus khusus angka pertama
    c = '1';
    while ((c <= '9') && !found) {
        if (input.TabToken[0] == c) {
        	found = true;
        }
        c++;
    }
    num = found;
 
 	//Kasus untuk angka kedua dan selanjutnya
    i=1;
    while(i<input.Length && num) {
	    c = '0';
	    found = false;
	    while ((c <= '9') && !found) {
	        if (input.TabToken[i] == c) {
	        	found = true;
	        }
	        c++;
	    }
	    num = found;
	    i++;
    }
    return num;
}