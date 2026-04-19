/*******************************************************************************************************************************************************************
*Title			: Addition
*Description		: This function performs addition of two given large numbers and store the result in the resultant list.
*Prototype		: int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first Dlist of the first double linked list.
			: tail1: Pointer to the last Dlist of the first double linked list.
			: head2: Pointer to the first Dlist of the second double linked list.
			: tail2: Pointer to the last Dlist of the second double linked list.
			: headR: Pointer to the first Dlist of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
// 

#include "apc.h"

void addition(Dlist *tail1, Dlist *tail2, Dlist **headR, Dlist **tailR)  
{
    Dlist *temp1 = tail1;           
    Dlist *temp2 = tail2;           
    int sum = 0, carry = 0;        

    while (temp1 != NULL || temp2 != NULL || carry != 0)  
    {
        sum = carry;               // Initialize sum with carry

        if (temp1 != NULL)         
        {
            sum = sum + temp1->data;  
            temp1 = temp1->prev;     
        }

        if (temp2 != NULL)         
        {
            sum = sum + temp2->data;  
            temp2 = temp2->prev;      
        }

        carry = sum / 10;          // Calculate carry
        sum = sum % 10;            // single digit result

        insert_first(headR, tailR, sum);  
    }
}