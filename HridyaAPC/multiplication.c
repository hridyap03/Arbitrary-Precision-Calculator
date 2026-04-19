/*******************************************************************************************************************************************************************
*Title			: Multiplication
*Description		: This function performs multiplication of two given large numbers and store the result in the resultant list.
*Prototype		: int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first Dlist of the first double linked list.
			: tail1: Pointer to the last Dlist of the first double linked list.
			: head2: Pointer to the first Dlist of the second double linked list.
			: tail2: Pointer to the last Dlist of the second double linked list.
			: headR: Pointer to the first Dlist of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"

void multiplication(Dlist *tail1, Dlist *tail2, Dlist **headR1, Dlist **tailR1)  
{
    Dlist *temp2 = tail2;                  
    int count = 0;                        // Count for adding zeros

    while (temp2 != NULL)                 
    {
        Dlist *temp1 = tail1;              
        Dlist *headR2 = NULL;              // Temporary list for partial product
        Dlist *tailR2 = NULL;

        int carry = 0;                    // Variable to store carry 

        
        while (temp1 != NULL)
        {
            int prdt = (temp1->data * temp2->data) + carry;  // Calculate product with carry

            insert_first(&headR2, &tailR2, prdt % 10);      
            carry = prdt / 10;                               // Update carry

            temp1 = temp1->prev;                             
        }

        
        if (carry > 0)
        {
            insert_first(&headR2, &tailR2, carry);           
        }

        
        for (int i = 0; i < count; i++)
        {
            insert_last(&headR2, &tailR2, 0);                
        }

        
        if (*headR1 == NULL)                                
        {
            *headR1 = headR2;                               // Assign first partial result
            *tailR1 = tailR2;
        }
        else
        {
            Dlist *head_AR = NULL;                           // Temporary list for addition result
            Dlist *tail_AR = NULL;

            addition(tailR2, *tailR1, &head_AR, &tail_AR);  // Add partial result with  result

            delete_list(headR1, tailR1);                    // Delete old result 

            *headR1 = head_AR;                              // Update result 
            *tailR1 = tail_AR;

            delete_list(&headR2, &tailR2);                  // Delete temporary partial list
        }

        temp2 = temp2->prev;                                
        count++;                                           
    }
}