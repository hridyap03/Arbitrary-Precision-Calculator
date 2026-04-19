/*******************************************************
*Title			: Addition
*Description		: This function performs addition of two given large numbers and store the result in the resultant list.
*Prototype		: int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************/
#include "apc.h"                 

void subtraction(Dlist *tail1, Dlist *tail2, Dlist **headR, Dlist **tailR)
{
    int borrow = 0;               

    Dlist *temp1 = tail1;      
    Dlist *temp2 = tail2;       

    int sub;                    

    while (temp1 != NULL)       
    {
        int num1 = temp1->data; 
        int num2;               

        if (temp2 != NULL)     
            num2 = temp2->data; 
        else
            num2 = 0;           

        num1 = num1 - borrow;     // Subtract previous borrow

        if (num1 < num2)        // Check if borrow needed
        {
            sub = (num1 + 10) - num2;     // Perform borrow subtraction
            borrow = 1;    // Set borrow 
        }                 
        else
        {
            sub = num1 - num2;           
            borrow = 0;                   
        }

        insert_first(headR, tailR, sub); 
        temp1 = temp1->prev;             

        if (temp2 != NULL)              
            temp2 = temp2->prev;        
    }
}