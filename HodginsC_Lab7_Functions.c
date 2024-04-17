#include "HodginsC_Lab7.h"

//-----------------------------------------------------------------------------
// Function Name: initializeQueue
// Description:	
//   This function takes in a queue and initializes the memory to NULL
//
//-----------------------------------------------------------------------------
void initializeQueue(queueType* queue){
    queue->back = NULL;
    queue->front = NULL;
}

//-----------------------------------------------------------------------------
// Function Name: initializeNode
// Description:	
//   This function assigns the memory in the structure to NULL
//
//-----------------------------------------------------------------------------
void initializeNode(nodeType** node){
    *node = NULL; //maybe???
    (*node)->pNext = NULL;
}

//-----------------------------------------------------------------------------
// Function Name: queueEmpty()
// Description:	
//   This function returns whether or not a queue is empty
//
//-----------------------------------------------------------------------------
int queueEmpty(queueType* queue){
    return queue->front == NULL;
}

//-----------------------------------------------------------------------------
// Function Name: enqueue()
// Description:	
//   This function adds a node to the back of the queue
//
//-----------------------------------------------------------------------------
void enqueue(queueType* queue, nodeType* node){
    if (node == NULL){
        printf("Node is empty\n");
    }else{
        if (queueEmpty(queue)){
            queue->front = node;
            queue->back = node;
        }else{
            //assign the last node to point to our new node
            queue->back->pNext = node;
            //assign the last node to be the new node
            queue->back = node;
            //node->pNext = NULL;
        }
    }
}

//-----------------------------------------------------------------------------
// Function Name: enqueueNewNode()
// Description:	
//   This function adds a node to the back of the queue
//
//-----------------------------------------------------------------------------
void enqueueNewNode(queueType* happy,queueType*angry, nodeType* node,uint32_t code){
    //if angry
    if (code &(1<<7)){
        enqueue(angry,node);
    }else if(code & (1<<6)){
        enqueue(happy,node);
    }
}

//-----------------------------------------------------------------------------
// Function Name: enqueueNewNode()
// Description:	
//   This function adds a node to the back of the queue
//
//-----------------------------------------------------------------------------
void createNodeNode(nodeType** node, uint32_t code){
    if (code & (1<<7)){
        //capture the 1st and second bit
        (*node)->record.reason = (code>>1) & 3;
        setAngryMessage(*node);
    }else if(code&(1<<6)){
        (*node)->record.reason = (code>>3) & 3;
        setHappyMessage(*node);
    }
    (*node)->record.ID = (code >> 8) & 0xFF;
}


//-----------------------------------------------------------------------------
// Function Name: dequeue()
// Description:	
//   This function removes a node from the front of the queue
//
//-----------------------------------------------------------------------------
void dequeue(queueType* queue){
    if (queueEmpty(queue)){
        printf("Queue is already empty\n");
    }else{
        nodeType* pTemp = queue->front;
        queue->front = queue->front->pNext;

        if (queueEmpty(queue)){
            queue->back = NULL;
        }
        free(pTemp);
    }
}

//-----------------------------------------------------------------------------
// Function Name: printTableHeader
// Description:	
//   This function when called creates a header for the table of customers
//
//-----------------------------------------------------------------------------
void printTableHeader(queueType* pQueue,FILE* pOutput){
    fprintf(pOutput,"Customer ID    |    Reason");
    PrintDivider(pOutput,'-',SCREEN_WIDTH);
}

//-----------------------------------------------------------------------------
// Function Name: printRowofData()
// Description:	
//   This function takes a node in and prints the record into the table
//
//-----------------------------------------------------------------------------
void printRowOfData(queueType* queue,FILE* pOutput){
    fprintf(pOutput,"%d",queue->front->record.ID);
    fprintf(pOutput,"\t|\t");
    fprintf(pOutput,"%s",queue->front->record.message);
}

//-----------------------------------------------------------------------------
// Function Name: setAngryMessage()
// Description:	
//   This function takes in a node pointer and copies a value into the struct
//
//-----------------------------------------------------------------------------
void setAngryMessage(nodeType* node){
    switch(node->record.reason){
        case 0:
            strcpy(node->record.message,"This store is terrible, I’m never coming back!\n");
            break;
        case 1:
            strcpy(node->record.message,"I’m too busy for this! Maybe I come back later.\n");
            break;
        case 2:
            strcpy(node->record.message,"Too much to do, too little time! \n");
            break;
        case 3:
            strcpy(node->record.message,"<yawn> I’m too lazy to wait in line. \n");
            break;
        default: 
            printf("[ERROR]: Reason code invalid\n");
    }
}

//-----------------------------------------------------------------------------
// Function Name: setHappyMessage()
// Description:	
//   This function takes in a node pointer and copies a value into the struct
//
//-----------------------------------------------------------------------------
void setHappyMessage(nodeType* node){
    switch(node->record.reason){
        case 0:
            strcpy(node->record.message,"AWESOME SERVICE! Can’t wait to come back.\n");
            break;
        case 1:
            strcpy(node->record.message,"Checkout was a breeze!\n");
            break;
        case 2:
            strcpy(node->record.message,"Got what I needed, very good store!\n");
            break;
        case 3:
            strcpy(node->record.message,"Smiling customer will be happy to return\n");
            break;
        default: 
            printf("[ERROR]: Reason code invalid\n");
            break;
    }
}

//FOOS FUNCTIONS
//-----------------------------------------------------------------------------
// Function Name: PrintHeader
// Description:	
//   This function will call the functions needed to print a header to the 
//  screen. 
//
//-----------------------------------------------------------------------------
void PrintHeader(FILE* pOutput)
{
	// Call function to print a divider to the screen
	PrintDivider(pOutput, STAR, SCREEN_WIDTH);

	// Call functions to print three strings to center to the screen
	CenterString(pOutput, (char*)SCHOOL, SCREEN_WIDTH);
	CenterString(pOutput, (char*)PROGRAMMER, SCREEN_WIDTH);
	CenterString(pOutput, (char*)LAB, SCREEN_WIDTH);

	// Call function to print a divider to the screen
	PrintDivider(pOutput, STAR, SCREEN_WIDTH);

} // End PrintHeader

//-----------------------------------------------------------------------------
// Function Name: PrintDivider
// Description:
//   Symbols will be printed to the screen. 
//
//-----------------------------------------------------------------------------
void PrintDivider(FILE* pOutput, char symbol, int numberOf)
{
	// Initialize LCV (Loop Control Variable) to 0
	int counter = 0;

	// Print a bunch of symbols across the screen
	while (counter < numberOf)
	{
		// Print one character to the screen
		fprintf(pOutput, "%c", symbol);

		// Increment counter
		counter++;
	}

	// Move the cursor down to the next line
	fprintf(pOutput, "\n");

} // END PrintDivider

//-----------------------------------------------------------------------------
// Function Name: CenterString
// Description:
//   The array of characters passed into the function will be centered
//  across the screen using the following formula:
//  
//    (lengthToCenterAcross + the string length) / 2
//
//-----------------------------------------------------------------------------
void CenterString(FILE* pOutput, char string[], int lengthToCenterAcross)
{
	// Capture how long the string is
	// Cast to an integer because strlen technically returns size_t
	int stringLength = (int)strlen(string);

	// Calculate the width to print the string in
	int width = (lengthToCenterAcross + stringLength) / 2;

	// Calculate how many blank spaces are needed before printing the string
	int numberOfBlankSpaces = width - stringLength;

	// Initialize LCV (Loop Control Variable) to 0
	int counter = 0;

	// Print the spaces needed to center the string
	while (counter < numberOfBlankSpaces)
	{
		// Print one space
		fprintf(pOutput, " ");

		// Increment counter
		counter++;
	}

	// Print the string
	fprintf(pOutput, "%s\n", string);

} // END CenterString