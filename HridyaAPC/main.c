/******************************************************
Name : Hridya P
Date : 10-04-2026
Description : Arbitrary Precision Calculator to perform operations on large numbers
              by storing digits in a linked list and processing them step by step.
Input : ./a.out 9 + 6
Output: 15
Input : ./a.out 9 - 6
Output: 3
Input : ./a.out 9 x 6
Output: 54
Input : ./a.out 9 / 9
Output: 1
*****************************************************/
#include "apc.h"                                            

int pos_flag1 = 0, neg_flag1 = 0;                 // for operand1 sign
int pos_flag2 = 0, neg_flag2 = 0;                 // for operand2 sign

int main(int argc, char *argv[])
{
    Dlist *head1 = NULL, *tail1 = NULL;                      // Linked list for operand1
    Dlist *head2 = NULL, *tail2 = NULL;                      // Linked list for operand2
    Dlist *headR = NULL, *tailR = NULL;                      // Linked list for result

    // Validation
    if (validation(argc, argv) == FAILURE)              // Validate command line arguments
    {
        return FAILURE;                                     // Exit if invalid input
    }

    // Decide sign
    operation_decider(argv[1], argv[3]);                    // Set sign flags for operands

    // Remove sign before list creation
    char *op1 = (argv[1][0] == '-' || argv[1][0] == '+') ? argv[1] + 1 : argv[1];  // Skip sign for operand1
    char *op2 = (argv[3][0] == '-' || argv[3][0] == '+') ? argv[3] + 1 : argv[3];  // Skip sign for operand2

    // Create lists
    create_linkedlist(op1, &head1, &tail1);                        // Convert operand1 string to linked list
    create_linkedlist(op2, &head2, &tail2);                        // Convert operand2 string to linked list

    // Remove leading zeros
    remove_pre_zeros(&head1);                                // Remove leading zeros in operand1
    remove_pre_zeros(&head2);                                // Remove leading zeros in operand2

    char oper = argv[2][0];                                  // Store operator (+, -, *, /)

    switch (oper)
    {
    case '+':                                                // Addition case
    { 
        if (pos_flag1 && pos_flag2)                // + + case
        {
            addition(tail1, tail2, &headR, &tailR);          // Perform addition
        }
        else if (neg_flag1 && neg_flag2)           // - - case
        {
            addition(tail1, tail2, &headR, &tailR);         // Add 
            printf("-");                                    // Result is negative
        }
        else if (pos_flag1 && neg_flag2)          // + - case
        {
            int ret = compare_list(head1, head2);           // Compare magnitudes

            if (ret == OPERAND1)                             // op1 > op2
                subtraction(tail1, tail2, &headR, &tailR);   // op1 - op2
            else if (ret == OPERAND2)                        // op2 > op1
            {
                subtraction(tail2, tail1, &headR, &tailR);   // op2 - op1
                printf("-");                                // Result negative
            }
            else
                insert_first(&headR, &tailR, 0);            // Equal → result 0
        }
        else if (neg_flag1 && pos_flag2)          // - + case
        {
            int ret = compare_list(head1, head2);          // Compare magnitudes

            if (ret == OPERAND1)                           // op1 > op2
            {
                subtraction(tail1, tail2, &headR, &tailR);  // op1 - op2
                printf("-");                                // Result negative
            }
            else if (ret == OPERAND2)                        // op2 > op1
            {
                subtraction(tail2, tail1, &headR, &tailR);  // op2 - op1
            }
            else
                insert_first(&headR, &tailR, 0);            // Equal → result 0
        }
        break;   
    }

    case '-':                                               // Subtraction case
    {    
        if (pos_flag1 && pos_flag2)               // + - + case
        {
            int ret = compare_list(head1, head2);            // Compare values

            if (ret == OPERAND1)                            // op1 > op2
            {
                subtraction(tail1, tail2, &headR, &tailR);  // op1 - op2
            }
            else if (ret == OPERAND2)                       // op2 > op1
            {
                subtraction(tail2, tail1, &headR, &tailR);  // op2 - op1
                printf("-");                                // Result negative
            }
            else
            {
                insert_first(&headR, &tailR, 0);            // Equal → 0
            }
        }
        else if (pos_flag1 && neg_flag2)          // + - (-)
        {
            addition(tail1, tail2, &headR, &tailR);        // Convert to addition
        }
        else if (neg_flag1 && pos_flag2)         // - - (+)
        {
            addition(tail1, tail2, &headR, &tailR);       // Add magnitudes
            printf("-");                                  // Result negative
        }
        else if (neg_flag1 && neg_flag2)        // (- )-(-) 
        {  
            int ret = compare_list(head1, head2);          // Compare values

            if (ret == OPERAND1)                           // op1 > op2
            {
                subtraction(tail1, tail2, &headR, &tailR);  // op1 - op2
                printf("-");                               // Result negative
            }
            else if (ret == OPERAND2)                       // op2 > op1
            {
                subtraction(tail2, tail1, &headR, &tailR);  // op2 - op1
            }
            else
            {
                insert_first(&headR, &tailR, 0);             // Equal → 0
            }
        }
        break;
    }

    case 'x':                                               // Multiplication case
    case 'X':
    {
        multiplication(tail1, tail2, &headR, &tailR);       // Multiply numbers

        if ((pos_flag1 && neg_flag2) || (neg_flag1 && pos_flag2))
            printf("-");                                    // Result negative if signs differ
        break;
    }

    case '/':                                               // Division case
    {
        division(head1, head2, tail2, &headR, &tailR);       // Perform division

        if ((pos_flag1 && neg_flag2) || (neg_flag1 && pos_flag2))
            printf("-");                                    // Result negative if signs differ
        break;
    }

    default:
        printf("Invalid operator\n");                        // Handle invalid operator
    }

    remove_pre_zeros(&headR);                                // Remove leading zeros in result
    print_list(headR);                                      // Print result list
    printf("\n");                                         
}