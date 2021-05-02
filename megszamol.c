#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"megszamol.h"
#include "debugmalloc.h"

int megszamol(FILE *fajl,char tetsz){
        int tetszdb=0;
        //fseek(fajl, 0, SEEK_SET);                                              //visszamegy az elejére
        while (!feof(fajl)){
            char temp =fgetc(fajl);
            if(temp==tetsz)
                tetszdb+=1;
        }
return tetszdb;
}
