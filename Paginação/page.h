/*DEFINIÇÕES DA "CLASSE" PÁGINA*/

#include "const.h"

/* SHIFTER REGISTER */

int getBit(shftr * ag, int adr){//retorna o bit indexado por adr, em ag
	if(-1 < adr && adr < sizeof(shftr) * 8 ) return (1 << adr) == (1<<adr & *ag);
	else return -1; 
}

void tick(shftr * ag){ *ag >>=  1; }//realiza o shift para a esquerda, necessário para o aging

void rfrsh(shftr * ag){ *ag += !(getBit(ag,AGE_N-1)) * AGE_RFRSH;}//insere um bit no maior digito signicativo, necessário para o aging

void binPrint(shftr * ag){//exibe ag em forma binária 
	int aux = AGE_N-1;
	while(aux > -1){
		printf("%d", getBit(ag,aux));  		
		aux--;
	}
}
/* SHIFTER REGISTER */


/*PAGE*/
pg crtPg(){ //cria uma página sem conteúdo, usado durante a inicialização
	pg rtrn = {0,0,0,0,NULL,-1}; 
	return rtrn;
}

void setPg(pgptr pg,int dat){//acessa uma página, trazendo dirty para cima
	pg->drty = true; 
	pg->dat = dat;
}

int getPg(pgptr pg){//acessa uma página trazendo ref para cima e realizando o rfrsh na idade
	pg->ref = true;
 	rfrsh(&pg->age);
 	return pg->dat; 
 }

 void prtPg(pgptr pg){//exibe os campos de uma página
 	printf("PG FIELDS:\tage: ");
 	binPrint(&pg->age);
 	printf(",\t\tref: %s,\t drty: %s,\t dat: %d\t usr: %ld\t usr_n: %d\n",BOOL[pg->ref],BOOL[pg->drty],pg->dat,(long int)pg->usr,pg->usr_n);
 }
/*PAGE*/

