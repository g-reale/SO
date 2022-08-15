#include "process.h"

//ARRUMA ESSA MAIN ISSO TA UMA ZONA
int main()
{
	srand(time(NULL));
	printf("CONST AMOUNTS: N_PAGES %d, N_SW_PGS %d, N_RAM_PGS %d, N_PRCS %d, RAM_SIZE %d, SW_SIZE %d, UNIVERSE %d, CHANCE %f, CICLES %d, ENABLE %s \n",N_PGS,N_SW_PGS,N_RAM_PGS,N_PRCS,RAM_SIZE,SW_SIZE,UNIVERSE,CHANCE,CICLES,BOOL[ENABLE]);
	
	int cicle = 0, cursor, last = 0;

		mm ram = crtMem(RAM_SIZE);
		mm swap = crtMem(SW_SIZE);
		pcsptr list = crtPrcss(&ram,&swap);


			while(cicle != N_CICLES){
				for( cursor = 0; cursor < N_PRCS; cursor++){
					runPrcss(&list[cursor],&ram,&swap);
				}
				for( cursor = 0; cursor < RAM_SIZE; cursor++){
					tick(&ram.mem[cursor].age);
				}
				
				if(cicle % CICLES == 0){
					printf("%d\t%ld\n",cicle,N_PG_MISS);
					// last = N_PG_MISS;
				}
				cicle++;
			}
		
	return 0;
}
	



