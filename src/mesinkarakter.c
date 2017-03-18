#include "mesinkarakter.h"

static FILE *filecode;
static int retval;

extern void START() {
/* 	I.S. sembarang
	F.S. CC adalah karakter pertama pita (stdin)
		 Bila Kondisi EOP terpenuhi, nyalakan EOP
*/
	filecode = fopen("CompilerBin.txt", "r");

	ADV();
}

extern void ADV() {
/*	I.S. CC!=mark
	F.S. CC adalah karakter berikutnya yang dapat diakuisisi
		 contoh untuk pita "IF", bila CC menunjuk 'I', maka CC berikutnya adalah 'F'
		 Bila Kondisi EOP terpenuhi, nyalakan EOP
*/
	//ALGORITMA
	retval = fscanf(filecode,"%c", &CC);
	if (EOP())
	{
		fclose(filecode);
	}
}

extern boolean EOP() {
/*	true jika CC==mark */
	return (CC==mark);
}
