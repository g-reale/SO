#include "aging.h"
#define RAM 1
#define SWAP 0

void prtPrcss(pcsptr p){//exibe as ocess de todos os processos
	int aux,_aux;
	printf("PRINTING PROCESES POSETIONS\n");
	for (aux = 0; aux < N_PRCS; ++aux){
		printf("PRCS: %d\n",aux);
		for(_aux = 0; _aux < N_PGS;	_aux++){
			printf("\tPG: %d %s\n",p[aux].pages[_aux],MEM[p[aux].adrs[_aux]]);
		}
	}
}

void crt1Prcss(mmptr ram, mmptr swap, int  adr[], pcsptr rtrn){//cria 1 processo
	int r_end, swp_end;
	
	int aux = adr[0];	
	for(r_end = adr[0] + N_RAM_PGS; adr[0] < r_end ;adr[0]++){
		rtrn->pages[adr[0] - aux] = adr[0];
		rtrn->adrs[adr[0] - aux] = RAM;
		
		ram->mem[adr[0]].usr = rtrn;
		ram->mem[adr[0]].usr_n = adr[0] - aux;
	}
	aux = adr[1] + aux - adr[0];
	for(swp_end = adr[1] + N_SW_PGS; adr[1] < swp_end ; adr[1]++){
		rtrn->pages[adr[1] - aux] = adr[1];
		rtrn->adrs[adr[1] - aux] = SWAP;
		
		swap->mem[adr[1]].usr = rtrn;
		swap->mem[adr[1]].usr_n = adr[1] - aux;
	}
}

pcsptr crtPrcss(mmptr ram,mmptr swap){ //cria todos os processos, apossando-se de palavras tanto em rma quanto em swap
	pcsptr rtrn = malloc(sizeof(prcs) * N_PRCS);
	int aux, hold[2] = {0,0};

	for(aux = 0; aux < N_PRCS; aux++){
		crt1Prcss(ram,swap,hold,&rtrn[aux]);
	}
	return rtrn;
}



int dice(int min, int faces){return (rand() % faces) + min;}//gera um numero entre min e min + faces

int pageMiss(int adrs, mmptr ram,mmptr hd){//determina oque fazer em caso de pageMiss
	N_PG_MISS++;
	int new_adrs = ENABLE ? choosePg(ram) : dice(0,RAM_SIZE);
	
	pgptr out = &ram->mem[new_adrs];
	pgptr in = &hd->mem[adrs];

	out->usr->adrs[out->usr_n] = 0;
	out->usr->pages[out->usr_n] = adrs;

	in->usr->adrs[in->usr_n]= 1;
	in->usr->adrs[in->usr_n]= new_adrs;

	swap(ram,new_adrs,hd,adrs);

	return getPg(&ram->mem[new_adrs]);
}

void runPrcss(pcsptr p, mmptr ram, mmptr hd){//executa um processo
	int aux, luck = CHANCE;

	for(aux = 0; aux < N_PGS; aux++){
		
		if(luck >= dice(0,UNIVERSE)){
			if(p->adrs[aux] == 0) pageMiss(aux,ram,hd);
			else setPg(&ram->mem[aux],getPg(&ram->mem[aux]));
		}
		luck /= 2;
	}
}



