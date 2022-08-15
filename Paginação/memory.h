/*DEFINIÇÕES DA "CLASSE" MEMÓRIA*/
#include "page.h"

/*GENERIC MEMORY*/
void fillMem(mmptr m){//preeche uma mémoria com páginas vazias, necessário durante a inicialização
	int aux;
	for(aux = 0; aux < m->size; aux++){
		m->mem[aux] = crtPg();
	}
}

mm crtMem(int size){//cria uma mémoria, alocando o espaço necessário para as páginas, e inicializando-a
	mm rtrn = {malloc(sizeof(pg) * size),size};
	fillMem(&rtrn);
	return rtrn;
}

void swap(mmptr m1,int adr1,mmptr m2, int adr2){//troca duas páginas entre mémorias
	pg format1 = {0,0,0,m1->mem[adr1].dat,m1->mem[adr1].usr,m1->mem[adr1].usr_n};
	pg format2 = {0,0,0,m2->mem[adr2].dat,m2->mem[adr2].usr,m2->mem[adr2].usr_n};
	
	m1->mem[adr1] = format2;
	m2->mem[adr2] = format1;
}

void prtMem(mmptr m){//exibe os conteúdos de uma mémoria
	printf("PRINTING MEMORY CONTENTS:\n");

	int aux;
	for(aux = 0; aux < m->size; aux++){
		printf("(%d)   ",aux);
		prtPg(&m->mem[aux]);
	}

	printf("MEMORY SIZE: %d\n",m->size);
}
/*GENERIC MEMORY*/





