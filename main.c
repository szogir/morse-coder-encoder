#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include"megszamol.h"
#include"listas.h"
#include"debugmalloc.h"

//----------------------------------------------------------------------------------------------------
int main(){

    char alphabet[260];
    char bemenet[260];;
    char kimenet[260];;

    printf("Adja meg az ABC-t tartalmazo fajl nevet es kiterjeszteset:");
    scanf("%s",&alphabet);
    printf("Adja meg a BEMENETI fajl nevet es kiterjeszteset:");
    scanf("%s",&bemenet);
    printf("Adja meg a KIMENETI fajl nevet es kiterjeszteset:");
    scanf("%s",&kimenet);
    getchar();                                                              //ez azért, hogy a felhasznalo ENTER-jét ne olvassa be

        FILE *abc;                                                                  //abc fájl megnyitas
    abc = fopen(alphabet, "rt");
    if (abc==NULL)
        printf("Nem talalom az abc-t!");

    FILE *be;                                                                  //bemeneti fájl megnyitasa
    be = fopen(bemenet,"rt");
    if (be==NULL)
        printf("Nem talalom a bemenetet!");

    FILE *ki;                                                                  //kimeneti fájl megnyitasa
    fclose(fopen(kimenet, "w"));                                                //torli a kimenet tartalmat
    ki = fopen(kimenet,"r+t");
    if (ki==NULL)
        printf("Nem talalom a kimenetet!");

//-------------------------------------------------------------------------------------------------------------
 /*   FILE *abc;                                                                  //abc fájl megnyitas
    abc = fopen("abc.txt", "rt");
    if (abc==NULL)
        printf("Nem talalom az abc-t!");

    FILE *be;                                                                  //bemeneti fájl megnyitasa
    be = fopen("bemenet.txt","rt");
    if (be==NULL)
        printf("Nem talalom a bemenetet!");

    FILE *ki;                                                                  //kimeneti fájl megnyitasa
    fclose(fopen("kimenet.txt", "w"));                          //törli a kimenet tartalmat
    ki = fopen("kimenet.txt","r+t");
    if (ki==NULL)
        printf("Nem talalom a kimenetet!");

*/
    Betu* l = NULL;
    char tempnorm[2];
    char tempjel[7];
    while (!feof(abc)){                                                             //abc beolvasás a bemenetrol
        fscanf(abc,"%s\n%s",tempnorm, tempjel);
        fscanf(abc,"%*[^\n]%*c");
        l=lista_vegere(l, tempnorm, tempjel);                                 //az abc-bõl beolvasott latin betut és morse jelet  a lista vegere fuzi
    }
  //  lista_kiir(l);                                                              //lista kiiratás ellenőrzés végett
     printf("\n----------------------------------------------------------------------\n\n") ;



    char tetsz;                                                                             //tetszőleges karakter megszámlása
    int tetszdb;
    printf("Kerem adja meg a karaktert, aminek a BEMENETI darabszamara kivancsi!\n");
    scanf("%c",&tetsz);
    tetszdb=megszamol(be,tetsz);
    printf("A bemeneten %d db '%c' karakter van!\n", tetszdb, tetsz);
    printf("\n----------------------------------------------------------------------\n\n") ;

    fseek(be, 0, SEEK_SET);
    int hossz=0;                                                                    //és a bemenet hosszanak szamolasa a dinamikus tombhoz
    while (!feof(be)){
        hossz+=1;
        fgetc(be);
    }
    if(fseek(be, 0, SEEK_SET)!=0)                                               //visszamegy a bemenet elejére
        printf("nem megy vissza az elejere");
    char* kisszoveg=(char*) malloc (sizeof(char)*(hossz+1));                   //lérehoz dinamikusan egy karaktertömbot a bemenet kisbetüsitett valtozatanak
    int i=0;
    while (!feof(be)){
        kisszoveg[i]=tolower(fgetc(be));                                        //a bemenetet karakterenként kisbetűsíti
        i++;
     }
    kisszoveg[i]='\0';

    printf("KISBETUSITETT BEMENET: \n");                                     //kisbetusitett tömb kiiras -- helyes működés ellenőrzése végett
    for(int i=0; kisszoveg[i]!='\0';i++)
        printf("%c", kisszoveg[i]);


    printf("\n \n");
     printf("\n----------------------------------------------------------------------\n\n") ;
    getchar();                                                              //ez azért, hogy a felhasznalo ENTER-jét ne olvassa be
     printf("Adja meg a konverzio iranyat: (L/l)  latinrol morzere  VAGY (M/m)  morzerol latinra:\n");
     char irany;
     scanf("%c",&irany);
     getchar();                                                              //ez azért, hogy a felhasznalo ENTER-jét ne olvassa be
     irany=tolower(irany);
     Betu* iter;
     Betu* futo;
     char bejel[7];
     switch (irany){
        case 'l':
                if(fseek(be, 0, SEEK_SET)!=0)                                               //visszamegy a bemenet elejére
                    printf("nem megy vissza az elejere");

                for(int i=0; kisszoveg[i]!='\0';i++){                             //a tomb karaktereit veszi egyesével és a nekik megfelelo jelet kiirja a kimenetre
                    if (isspace(kisszoveg[i])){
                        fprintf(ki,"....... ");
                    }
                    for(iter=l; iter!=NULL; iter=iter->kov){
                        if(kisszoveg[i]== *iter->norm){
                            fprintf(ki,"%s",iter->jel);
                            fprintf(ki," ");
                        }
                    }
                }
            break;
        case 'm':
                if(fseek(be, 0, SEEK_SET)!=0)                                               //visszamegy a bemenet elejére
                    printf("nem megy vissza az elejere");

                while (!feof(be)){
                    fscanf(be,"%s ",bejel);
                    if (!strcmp(bejel,".......")){
                        fprintf(ki," ");
                    }else{
                        // printf("BEJEL:%s\n",bejel);
                        for(futo=l; futo!=NULL; futo=futo->kov){
                            if(!strcmp(bejel,futo->jel)){
                                fprintf(ki,"%s",futo->norm);
                                }
                            }
                        }
                    }

            break;
        default: printf("Hibas valasztas a konverzio iranyara!\n");
            break;

     }
     printf("\n----------------------------------------------------------------------\n\n") ;


    tetszdb=0;                                                                           //tetszőleges karakter megszámlása
    printf("Kerem adja meg a karaktert, aminek a KIMENETI darabszamara kivancsi!\n");
    scanf("%c",&tetsz);                                                                       //és a kimenet hosszanak szamolasa
    fseek(ki, 0, SEEK_SET);                                                             //visszamegy a kimenet elejére
    tetszdb=megszamol(ki,tetsz);
    printf("A kimeneten %d db '%c' karakter van!\n", tetszdb, tetsz);
     printf("\n----------------------------------------------------------------------\n\n") ;


    free(kisszoveg);
    abc_felszabad(l);
    //fclose(seged);
    fclose(be);
    fclose(ki);
    fclose(abc);
    printf("A program futasa befejezodott!!!!!negy!!4! :D ");
return 0;
}
