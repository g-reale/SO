/*
	CONTÉM OS PARÂMETROS DA SIMULAÇÃO E AS BIBLIOTECAS UTILIZADAS  
*/

/*LIBRARIES*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
/*LIBRARIES*/



/*------------------------------------------------------------------------------------------*/
/*STRINGS*/
const char BOOL[2][4] = {{'N','O',0,0},{'Y','E','S',0}};
const char MEM[2][5] = {{'S','W','A','P',0},{'R','A','M',' ',0}};
/*STRINGS*/
/*------------------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------------------*/
/* PROCESS CONFIG */
#define N_PRCS   100
#define N_SW_PGS   2
#define N_PGS  (RAM_SIZE/N_PRCS) + N_SW_PGS
#define N_RAM_PGS N_PGS - N_SW_PGS
#define UNIVERSE 10000
#define CHANCE UNIVERSE * 0.99
/* PROCESS CONFIG */
/*------------------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------------------*/
/* MEM CONFIG */
#define RAM_SIZE  1000
#define SW_SIZE   RAM_SIZE + N_SW_PGS * N_PRCS
/* MEM CONFIG */
/*------------------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------------------*/
/* AGING CONFIG */
typedef unsigned char shftr;
#define AGE_N  sizeof(shftr) * 8
#define AGE_RFRSH  1 << (AGE_N - 1)
/* AGING  CONFIG */
/*------------------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------------------*/
/* SIMULATION DATA */
#define CICLES	    10
#define N_CICLES 100000
#define ENABLE 0 
long int N_PG_MISS = 0;
/* SIMULATION DATA */
/*------------------------------------------------------------------------------------------*/



typedef struct process{
	int pages[N_PGS];
	bool adrs[N_PGS];
}prcs;
typedef prcs * pcsptr;



typedef struct page{
	shftr age;
	bool ref;
	bool drty;
	int dat;
	pcsptr usr;
	int usr_n;
}pg;
typedef pg * pgptr;



typedef struct memory{
	pgptr mem;
	int size;
}mm;
typedef mm * mmptr;