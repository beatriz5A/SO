#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <error.h>

void *function_p0(void *ptr );
void *function_p1(void *ptr );

int count = 0;

//variavel global que controla a 'vez'
int vez = 0;

//estrutura que representa uma thread e guarda tambem seu id e a variavel 'outro'
typedef struct {
    pthread_t thread;
    int meu_id;
    int outro;
} Posix, *P;

//metodo que aloca memoria para uma estrutura do tipo P
P criarThread(int meu_id, int outro){

    P res = (P) malloc(sizeof(Posix));
    res->meu_id = meu_id;
    res->outro = outro;

    return res;
}

int main() {

    int i = 0;
    
    printf("Valor inicial de count: %d\n\n", count);
    while(i<=9){

        
        //cria duas threads, p0 e p1
        P p0 = criarThread(0, 1);
        P p1 = criarThread(1, 0);

        //começa a execução das threads
        pthread_create(&(p0->thread), NULL, function_p0, (void*) "Executando");

        pthread_create(&(p1->thread), NULL, function_p1, (void*) "Executando");
        
        i++;
    }

    exit(0);

    return 0;
}

//metodo que representa a secao critica
void secao_critica(P p) {

    printf("Thread %d na seção crítica\n", p->meu_id);
    count++;
    printf("Count: %d\n", count); 
    
}

//metodo que representa a secao nao critica
void secao_nao_critica(int id) {

    printf("A thread %d saiu da seção crítica\n\n", id);
}

//metodo de execucao da thread p0. controla todo o funcionamento da exclusao mutua
void *function_p0(void *ptr ){

    P p0 = criarThread(0, 1);

    while(vez != p0->meu_id);

    secao_critica(p0);
    vez = p0->outro;
    secao_nao_critica(p0->meu_id);
}

//idem function_p1
void *function_p1(void *ptr ){

    P p1 = criarThread(1, 0);

    while(vez != p1->meu_id);

    secao_critica(p1);
    vez = p1->outro;
    secao_nao_critica(p1->meu_id);
}