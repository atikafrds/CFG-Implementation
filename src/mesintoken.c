#include "mesintoken.h"

//primitif-primitif mesin Token
void Ignore_Blank() {
/*	Mengabaikan satu atau beberapa BLANK
	I.S. : CC sembarang
	F.S. : CC != BLANK atau CC == MARK
*/
	//ALGORITMA
	while (!EOP() && ((CC==blank)||(CC==tab))) {
		ADV();
	}
	if (EOP())
		EndToken=true;
}

void STARTTOKEN() {
/*	I.S. : CC sembarang
	F.S  : Salah satu dari dua kondisi dibawah.
		1. EndToken = true dan CC == Mark
		2. EndToken = false, CToken adalah Token yang sudah diakuisisi, dan CC adalah satu karakter setelah karakter terakhir Token

		Keterangan: CC mengacu pada yang disebut pada mesinkarakter
*/
	//ALGORITMA
	START();
	if (!EOP()) {
		Ignore_Blank();
		EndToken=false;
		SalinToken();
	}
	else {
		EndToken=true;
	}
}

void ADVTOKEN() {
/*	I.S. : EndToken = false; CC adalah karakter sesudah karakter terakhir
	dari Token yg sudah diakuisisi
	F.S. : Jika CC = MARK, maka EndToken = true
	atau EndToken = false, CToken adalah Token terakhir yang sudah diakuisisi;
	CC karakter pertama sesudah karakter terakhir Token
*/
	//ALGORITMA
	if (CC==mark) {
		EndToken=true;
		int i;
		for (i=0; i<CToken.Length; i++)
			CToken.TabToken[i]='\0';
	}
	else {
		Ignore_Blank();
		SalinToken();
	}
}

void SalinToken() {
/*	Mengakuisisi Token, menyimpan dalam CToken
	I.S. : CC adalah karakter pertama dari Token
	F.S. : CToken berisi Token yang sudah diakuisisi, jika karakternya melebihi
	NMax, sisa "Token" dibuang; CC = BLANK atau CC = MARK; CC adalah
	karakter sesudah karakter terakhir yang diakuisisi
*/
	//KAMUS LOKAL
	int i;
	//ALGORITMA

	//reset CToken terlebih dahulu
	for (i=0; i<CToken.Length; i++) {
		CToken.TabToken[i]='\0';
	}

	CToken.Length=0;
	if ((CC==newline)||(CC=='(')||(CC==')')||(CC=='+')||(CC=='-')||(CC=='*')||(CC=='=')||(CC=='>')||(CC=='<')||(CC=='{')||(CC=='}'))
	{
		CToken.TabToken[0] = CC;
		CToken.Length = 1;	
		ADV();
	}
	else {
		while (!EOP() && (CC!=blank) && (CC!=newline) && (CC!='(') && (CC!=')') && (CC!='+') && (CC!='-') && (CC!='*') && (CC!='=') && (CC!='>') && (CC!='<') && (CC!='{') && (CC!='}')) {
			if (CToken.Length<NMax) {
				CToken.Length+=1;
				CToken.TabToken[CToken.Length-1] = CC;
			}
			ADV();
		}		
	}

	if (EOP()) {
		EndToken = true;
	}
}

//operasi lain
boolean IsTokenSama(Token T1, Token T2) {
/*	Mengembalikan true jika K1 = K2; dua Token diTokenkan sama jika panjangnya sama dan
	urutan karakter yang menyusun Token juga sama. Sensitif terhadap uppercase dan lowercase
*/
	//KAMUS LOKAL
	int i;
	//ALGORITMA
	if (T1.Length==T2.Length) {
		i=0;
		while ((i<T1.Length) && (T1.TabToken[i]==T2.TabToken[i])) {
			i++;
		}
		if (i==T1.Length) {
			return true;
		}
		else { 
			return false;
		}
	}
	else return false;
}

void PrintToken(Token K) {
	/* KAMUS LOKAL */
	int i;
	/* ALGORITMA */
	for (i = 0; i <= K.Length-1; i++)
	{
		printf("%c", K.TabToken[i]);
	}
}