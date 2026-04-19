/*******************************************************************************************************************************************************************
*Title			: Division
*Description		: This function performs division of two given large numbers and store the result in the resultant list.
*Prototype		: int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"

int division(Dlist *head1_L1, Dlist *head2_OPR2, Dlist *tail2_OPR2, Dlist **headR, Dlist **tailR)  
{
    Dlist *head_OPR1 = NULL, *tail_OPR1 = NULL;  
    Dlist *head_SR = NULL, *tail_SR = NULL;      

    Dlist *L1_temp = head1_L1;                  

    int count = 0;                              

    if (head2_OPR2->data == 0 && head2_OPR2->next == NULL)  // Check if divisor is zero
    {
        printf("Error: Division by zero\n");   
        return 0;                              
    }

    if (compare_list(head1_L1, head2_OPR2) == OPERAND2)  // Check if dividend < divisor
    {
        insert_first(headR, tailR, 0);         
        return 0;                              
    }

    
    insert_last(&head_OPR1, &tail_OPR1, L1_temp->data);  

    while (compare_list(head_OPR1, head2_OPR2) == OPERAND2)  //  OPR1 < divisor
    {
        L1_temp = L1_temp->next;               

        if (L1_temp == NULL)                  
            break;                             

        insert_last(&head_OPR1, &tail_OPR1, L1_temp->data); 
        remove_pre_zeros(&head_OPR1);          
    }

    if (L1_temp != NULL)                       
        L1_temp = L1_temp->next;               

    
    while (L1_temp != NULL)                    
    {
        count = 0;                            

        
        while (compare_list(head_OPR1, head2_OPR2) != OPERAND2)  
        {
            subtraction(tail_OPR1, tail2_OPR2, &head_SR, &tail_SR);  

            delete_list(&head_OPR1, &tail_OPR1);  // Delete old OPR1

            head_OPR1 = head_SR;              
            tail_OPR1 = tail_SR;

            head_SR = NULL;                  
            tail_SR = NULL;

            remove_pre_zeros(&head_OPR1);    

            count++;                         // Increment quotient digit
        }

        insert_last(headR, tailR, count);    // Store quotient digit

        insert_last(&head_OPR1, &tail_OPR1, L1_temp->data);  
        remove_pre_zeros(&head_OPR1);       

        L1_temp = L1_temp->next;             
    }

    
    count = 0;                                // Reset count

    while (compare_list(head_OPR1, head2_OPR2) != OPERAND2)  
    {
        subtraction(tail_OPR1, tail2_OPR2, &head_SR, &tail_SR);  

        delete_list(&head_OPR1, &tail_OPR1);  

        head_OPR1 = head_SR;             
        tail_OPR1 = tail_SR;

        head_SR = tail_SR = NULL;           

        remove_pre_zeros(&head_OPR1);       

        count++;                            
    }

    insert_last(headR, tailR, count);   

    remove_pre_zeros(headR);                 

    return 1;                                
}
