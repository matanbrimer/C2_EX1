#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"

static int x = -1;
typedef struct AdptArray_
{
    int size;
    PElement* pElemArr;
    DEL_FUNC deleteF;
	COPY_FUNC copyF;
    PRINT_FUNC printF;
}AdptArray;



PAdptArray CreateAdptArray(COPY_FUNC c, DEL_FUNC d,PRINT_FUNC p){

   PAdptArray st = (PAdptArray)malloc(sizeof(AdptArray));

    if(st == NULL){
        x =-1;
        return NULL;
    }
    st->pElemArr = (PElement*)malloc(sizeof(PElement));
    if(!st->pElemArr){
        free(st);
        return NULL;
    }
    st->size = 1;
    st->copyF = c;
    st->deleteF = d;
    st->printF = p;
    st->pElemArr[0] = NULL;
    x=0;
    return st;
}

void DeleteAdptArray(PAdptArray st){

    if(st == NULL)return;

    for (int i = 0; i < st->size; ++i)
    {   
            if(st->pElemArr[i])
                st->deleteF(st->pElemArr[i]);   
     
    }


    free(st->pElemArr);
    free(st);

}

PElement GetAdptArrayAt(PAdptArray st, int index){

     
    if(st == NULL ||  st->size <= index||   index < 0 || (st->pElemArr)[index] == NULL )
         return NULL;
      
    return st->copyF( (st->pElemArr)[index]);
}

int GetAdptArraySize(PAdptArray st){
    return (x == -1)?-1:st->size;
}


void PrintDB(PAdptArray st){
    if(x == -1){
        return;
    }
    
    for (int i = 0; i < st->size; i++)
    {
        if(st->pElemArr[i] != NULL)
            st->printF(st->pElemArr[i]);
        
    }
}




Result SetAdptArrayAt(PAdptArray st, int idx, PElement newElem){

  
    PElement* newArr;
    if (idx < 0 || st == NULL)
        return FAIL;
    if (idx >= st->size)// Extend Array
    {
    
    if ((newArr = (PElement*)realloc(st->pElemArr,(idx +1) *sizeof(PElement))) == NULL)
        return FAIL;
  
    st->pElemArr = newArr;

    for (int i = st->size; i < idx; i++)
        st->pElemArr[i] = NULL;
    
    st->size = idx +1;
    }
    st->pElemArr[idx] = st->copyF(newElem);

    return SUCCESS;

}



