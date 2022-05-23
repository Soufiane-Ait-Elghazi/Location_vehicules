#include  <stdlib.h>
#include   <stdio.h>
#include "Common_functions.h"




typedef struct Date
{
    int j;
    int m;
    int a;
}date;
/*********************************************************************************/

/*
int is_empty(struct Agences *A) //Verifier si la liste est vide
{
	if(A == NULL)
		return 1;
	return 0;

}

*/

/*********************************************************************************/
int FileEmpty(FILE *file){
    long savedOffset = ftell(file);
    fseek(file, 0, SEEK_END);

    if (ftell(file) == 0){
        return 1;
    }
    fseek(file, savedOffset, SEEK_SET);
    return 0;
}
/*********************************************************************************/
