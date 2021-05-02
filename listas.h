#ifndef LISTAS_H_INCLUDED
#define LISTAS_H_INCLUDED

typedef struct Betu{
    char norm[2];
    char jel[7];
    struct Betu*kov;
}Betu;

void lista_kiir(Betu *lista);
Betu* lista_vegere(Betu* lista, char* ujnorm, char* ujjel);
void abc_felszabad(Betu* lista);

#endif // LISTAS_H_INCLUDED
