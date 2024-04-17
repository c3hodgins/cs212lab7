#ifndef HEADER_H
#define HEADER_H

#define _CRT_SECURE_NO_WARNINGS

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Macros
#define STAR '*'
#define SCREEN_WIDTH 65
#define SCHOOL "Binghamton University"
#define PROGRAMMER "Charles Hodgins"
#define LAB "Lab 6"
#define ARRAYSIZE 50 
#define ROW_SIZE 10

// Constants

// Structures
typedef struct record{
    int ID;
    int reason;
    char message[50];
} recordType;
 
typedef struct node{ 
    recordType record;  
    struct node* pNext;
} nodeType;

typedef struct{   
    nodeType* front;
    nodeType* back;
}queueType;

// Prototypes
// void push(stackType* stack, nodeType* element);
// nodeType pop(stackType* stack);
void initializeQueue(queueType* queue);
void initializeNode(nodeType** node);
int queueEmpty(queueType* queue);
void enqueue(queueType* queue, nodeType* node);
void enqueueNewNode(queueType* happy,queueType*angry, nodeType* node,uint32_t code);
void createNodeNode(nodeType** node, uint32_t code);
void dequeue(queueType* queue);
void printTableHeader(queueType* pQueue,FILE* pOutput);
void printRowOfData(queueType* queue,FILE* pOutput);
void setAngryMessage(nodeType* node);
void setHappyMessage(nodeType* node);

//Foos Function Prototypes
void PrintHeader(FILE* pOutput);
void PrintDivider(FILE* pOutput, char symbol, int numberOf);
void CenterString(FILE* pOutput, char string[], int lengthToCenterAcross);

#endif