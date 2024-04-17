// yerrrr
// HodginsC_Lab5.c
/*
|--------------------------------------------------------------------------------------------------
| Programmers Name: Charles Hodgins 
| Course:           CS-212: Data Structures for Engineers
| Program  Name:    Lab #7
| Date:             4/15/2024
|
|--------------------------------------------------------------------------------------------------
| Program Description:
|   Program uses linked lists as stacks to convert infix to post fix form math problems
|
|
|--------------------------------------------------------------------------------------------------
| Inputs:
|   No outside inputs. Only program inputs are taken from using scanf("%d", &<variable>)
|  
|
|--------------------------------------------------------------------------------------------------
| Processing:
|   Reads data in from file that are entered into stack and output files. Operations are performed on these
|  lists such as inserting and appending.
|
|--------------------------------------------------------------------------------------------------
| Outputs:
|   Outputs are outputted into .txt files
|
|
|--------------------------------------------------------------------------------------------------
*/
#include "HodginsC_Lab7.h"

int main(){
    queueType happy;
    queueType angry;
    nodeType* newRecord = NULL;

    initializeNode(newRecord);
    initializeQueue(&happy);
    initializeQueue(&angry);

    char readInCode[12];
    uint32_t code;

    FILE* pInput = NULL; 
    FILE* pOutHappy = NULL;
    FILE* pOutAngry = NULL;
    pInput = fopen("Lab7_Input.txt","r");
    pOutHappy = fopen("HappyCustomers.txt", "w");
    pOutAngry = fopen("AngryCustomers.txt", "w");

    PrintHeader(pOutAngry);
    PrintHeader(pOutHappy);

    printTableHeader(&happy,pOutHappy);
    printTableHeader(&angry,pOutAngry);
    if (pInput != NULL && pOutHappy != NULL && pOutHappy != NULL){
        while(fgets(readInCode,12,pInput)!=NULL){
            code = atoi(readInCode);

            newRecord = (nodeType*)malloc(sizeof(nodeType));
            createNodeNode(&newRecord,code);

            // printf("%d\n",newRecord->record.reason);
            enqueueNewNode(&happy,&angry,newRecord,code);
        }
        while(!queueEmpty(&happy)){
            printRowOfData(&happy,pOutHappy);
            dequeue(&happy);
        }
        while(!queueEmpty(&angry)){
            printRowOfData(&angry,pOutAngry);
            dequeue(&angry);
        }
    }
    //free(newRecord);
    fclose(pInput);
    fclose(pOutAngry);
    fclose(pOutHappy);
}