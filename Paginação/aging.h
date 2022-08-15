/*IMPLEMNTA AS POLITÍCAS EM CASO DE PAGE MISS */

#include "memory.h"

int choosePg(mmptr	m){
	int older[2] = {(AGE_RFRSH << 1),0};
	
	int aux;
	for(aux = 0; aux < m->size; aux++){
		if(older[0] > m->mem[aux].age) older[0] = m->mem[aux].age, older[1] = aux;
		if(older[0] == 0) break;
	}
	return	older[1];
}
