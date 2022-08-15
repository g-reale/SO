#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
////////////////////////////////////////////////////////////
typedef enum{ none, and, or, pp, bkground, ln }opratr;//operadores possveís

typedef struct{
    int pos[2];
    opratr prev_next[2];
}cmd;

cmd createCmd(int start, int end, opratr prev, opratr next){
    cmd c;
    c.pos[0] = start;
    c.pos[1] = end;
    c.prev_next[0] = prev;
    c.prev_next[1] = next;

    return c;
}
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
typedef struct cl{
    cmd * list;
    int size;
}cmdList;

cmdList createCmdList(){
    cmdList l;
    l.list = (cmd*)malloc(sizeof(cmd));
    l.list[0] = createCmd(0,0,none,none);
    l.size = 0;
    return l;
}

void appendCmdList(cmdList* l, cmd value){
    l->size++;
    l->list = (cmd*)realloc(l->list,sizeof(cmd)*l->size);
    l->list[l->size-1] = value;
}

void printCmdList(cmdList l){
    int i;
    for(i = 1; i < l.size; i++){
        printf("cmd %d goes from: %d <-to-> %d, prev_nextOp is: %d <--> %d\n",i,l.list[i].pos[0],l.list[i].pos[1],l.list[i].prev_next[0],l.list[i].prev_next[1]);
    }
}
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
typedef struct ct{
    cmdList * table;
    int size;
}cmdTable;

cmdTable createCmdTable(){
    cmdTable t;
    t.table = (cmdList*)malloc(sizeof(cmdList));
    t.table[0] = createCmdList();
    t.size = 0;
    return t;
}

void appendCmdTable(cmdTable * t, cmdList value){
    t->size++;
    t->table = (cmdList*)realloc(t->table,sizeof(cmd)*t->size);
    t->table[t->size-1] = value;
}
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
opratr search(char * line){
    opratr out = none;

    if(line[0] == line[1]){
        if (line[0] == '|') out = or;
        else if(line[0] == '&') out = and;
    }
    else{
        if(line[0] == '|') out = pp;
        else if(line[0] == '&') out = bkground;
        else if(line[0] == ';') out = ln;
    }

    return out;
}

void printMatrix(char ** mtrx, int size){
    int i;
    for(i=0; i<size; i++){
        printf("%s ",mtrx[i]);
    }
}
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void closePp(int * pp_fd){
    close(pp_fd[0]);
    close(pp_fd[1]);
}

void hatch(int nChids, cmdList* ml, char ** argv, int * pp_fd){
    if(nChids){

        ///redirecionando o stdout caso necssário
        if(ml->list[nChids].prev_next[1] == pp){
            dup2(pp_fd[1],fileno(stdout));
            closePp(pp_fd);
        }
        ///o pipe fecha aqui

        ///abertura de pipe caso o pai seja precedido por pp
        if(ml->list[nChids].prev_next[0] == pp) pipe(pp_fd);
        ///o pipe abre aqui

        ///decodifica o comando
        int aux;
        char * mycmd[ml->list[nChids].pos[1] - ml->list[nChids].pos[0] + 2];
        for(aux = ml->list[nChids].pos[0]; aux <= ml->list[nChids].pos[1]; aux++){
            mycmd[aux - ml->list[nChids].pos[0]] = *(argv+aux);
        }
        mycmd[ml->list[nChids].pos[1] - ml->list[nChids].pos[0] + 1] = 0;
        ///

        pid_t son = fork();
        if(!son){
            nChids--;
            hatch(nChids,ml,argv,pp_fd);
        }
        else{
            int status;
            waitpid(son,&status,0);

            ///execução
            switch(ml->list[nChids].prev_next[0]){
                case and:
                    if(status == 0)execvp(mycmd[0],mycmd);//condicional cmd and
                    exit(1);
                case or:
                    if(status == 0) exit(1);//condicional cmd or
                    execvp(mycmd[0],mycmd);
                default:
                    if(ml->list[nChids].prev_next[0] == pp){//condicional instancia de escuta
                        dup2(pp_fd[0],fileno(stdin));
                        closePp(pp_fd);
                    }
                    execvp(mycmd[0],mycmd);
            }
            ///
        }
    }
}

///////////////////////////////////////////////////////////
int main(int argc, char **argv){
    if(argc == 1){
      printf("comando inválido\n");
      return 0;
	}

///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
    cmdTable source = createCmdTable();
    appendCmdTable(&source,createCmdList());
    appendCmdList(&source.table[0],createCmd(0,0,none,none));

    int start,end,lns=0;

    for(start = 1, end = 1; end <argc; end++){
        opratr hold = search(argv[end]);
        opratr aux;

        switch(hold){
        case or:
            aux = source.table[lns].list[source.table[lns].size-1].prev_next[1];
            appendCmdList(&source.table[lns],createCmd(start,end-1,aux,or));
            start = end + 1;
            break;

        case and:
            aux = source.table[lns].list[source.table[lns].size-1].prev_next[1];
            appendCmdList(&source.table[lns],createCmd(start,end-1,aux,and));
            start = end + 1;
            break;

        case pp:
            aux = source.table[lns].list[source.table[lns].size-1].prev_next[1];
            appendCmdList(&source.table[lns],createCmd(start,end-1,aux,pp));
            start = end + 1;
            break;

        case bkground:
            aux = source.table[lns].list[source.table[lns].size-1].prev_next[1];
            appendCmdList(&source.table[lns],createCmd(start,end-1,aux,bkground));
            start = end + 1;
            break;

        case ln:
            aux = source.table[lns].list[source.table[lns].size-1].prev_next[1];
            appendCmdList(&source.table[lns],createCmd(start,end-1,aux,ln));

            lns++;
            appendCmdTable(&source,createCmdList());
            appendCmdList(&source.table[lns],createCmd(0,0,none,none));
            start = end + 1;
            break;

        case none:
            if(end == argc-1)appendCmdList(&source.table[lns],createCmd(start,end,source.table[lns].list[source.table[lns].size-1].prev_next[1],none));
        }
    }

///////////////////////////////////////////////////////////

    int plchld[2];
    for(end = 0; end < source.size; end++){
        pid_t son = fork();
        if(!son){
            int nChild = source.table[end].size - 1;
            if(source.table[end].list[source.table[end].size-1].prev_next[1] == bkground) setsid();
            hatch(nChild,&source.table[end],argv,plchld);
        }
        if(source.table[end].list[source.table[end].size-1].prev_next[1] != bkground) wait(NULL);
    }
}
///////////////////////////////////////////////////////////


