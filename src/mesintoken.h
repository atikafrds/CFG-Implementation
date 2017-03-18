#include "mesinkarakter.h"

#ifndef MESINTOKEN_H
#define MESINTOKEN_H
#define mark '.'
#define blank ' '
#define NMax 50


//definisi tipe Token
typedef struct {
	char TabToken[NMax];
	int	 Length;
} Token;

//definisi state mesin Token
boolean EndToken;
Token	CToken;


/* Primitif-primitif mesin Token */
void Ignore_Blank();
/*	Mengabaikan satu atau beberapa BLANK
	I.S. : CC sembarang
	F.S. : CC != BLANK atau CC == MARK
*/

void STARTTOKEN();
/*	I.S. : CC sembarang
	F.S  : Salah satu dari dua kondisi dibawah.
		1. EndToken = true dan CC == Mark
		2. EndToken = false, CToken adalah Token yang sudah diakuisisi, dan CC adalah satu karakter setelah karakter terakhir Token

		Keterangan: CC mengacu pada yang disebut pada mesinkarakter
*/

void ADVTOKEN();
/*	I.S. : EndToken = false; CC adalah karakter sesudah karakter terakhir
	dari Token yg sudah diakuisisi
	F.S. : Jika CC == MARK, maka EndToken == true
	atau EndToken = false, CToken adalah Token terakhir yang sudah diakuisisi;
	CC karakter pertama sesudah karakter terakhir Token
*/

void SalinToken();
/*	Mengakuisisi Token, menyimpan dalam CToken
	I.S. : CC adalah karakter pertama dari Token
	F.S. : CToken berisi Token yang sudah diakuisisi, jika karakternya melebihi
	NMax, sisa "Token" dibuang; CC == BLANK atau CC == MARK; CC adalah
	karakter sesudah karakter terakhir yang diakuisisi
*/

/* Operasi Lain */
boolean IsTokenSama(Token T1, Token T2);
/*	Mengembalikan true jika K1 = K2; dua Token diTokenkan sama jika panjangnya sama dan
	urutan karakter yang menyusun Token juga sama. Sensitif terhadap uppercase dan lowercase
*/

void PrintToken(Token K);

#endif
