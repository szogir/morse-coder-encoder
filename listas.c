#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"listas.h"
#include "debugmalloc.h"

void lista_kiir(Betu *lista){
    Betu* iter;
    for(iter=lista; iter!=NULL; iter=iter->kov)
        printf("%s   %s\n", iter->norm, iter->jel);
    printf("\n");
}


Betu* lista_vegere(Betu* lista, char* ujnorm, char* ujjel){
    Betu* ujbetu=(Betu*) malloc(sizeof(Betu));
    strcpy(ujbetu->norm,ujnorm);
    strcpy(ujbetu->jel,ujjel);
    ujbetu->kov= NULL;
    if(lista==NULL)
        return ujbetu;
    Betu* iter;
    for(iter=lista; iter->kov!=NULL; iter=iter->kov);

    iter->kov=ujbetu;
return lista;
}

void abc_felszabad(Betu* lista){
    while (lista!=NULL){
        Betu* temp;
        temp=lista->kov;
        free(lista);
        lista=temp;
    }
}
