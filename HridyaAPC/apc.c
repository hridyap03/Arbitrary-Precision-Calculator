#include "apc.h"
#include <ctype.h>

int validation(int argc, char *argv[])  
{
    if (argc != 4)                          
    {
        printf("Error: Invalid number of arguments\n"); 
        printf("Usage: ./a.out <operand1> <operator> <operand2>\n");  
        return FAILURE;                     
    }

    int i = 0;                             
    if (argv[1][0] == '+' || argv[1][0] == '-') 
    {
        if (argv[1][1] == '\0')             
        {
            printf("Error: Invalid operand 1\n");  
            return FAILURE;                 
        }
        i = 1;                              
    }

    for (; argv[1][i] != '\0'; i++)         
    {
        if (!isdigit(argv[1][i]))           
        {
            printf("Error: Operand 1 should be numeric only\n");  
            return FAILURE;                 
        }
    }

    i = 0;                                 

    if (argv[3][0] == '+' || argv[3][0] == '-')  
    {
        if (argv[3][1] == '\0')             
        {
            printf("Error: Invalid operand 2\n");  
            return FAILURE;                 
        }
        i = 1;                              
    }

    for (; argv[3][i] != '\0'; i++)         
    {
        if (!isdigit(argv[3][i]))           
        {
            printf("Error: Operand 2 should be numeric only\n");  
            return FAILURE;                 
        }
    }

    return SUCCESS;                         
}
void create_linkedlist(char *opr, Dlist **head, Dlist **tail)
{
    int i = 0;
    

    while(opr[i] != '\0')
    {
        int digit =  opr[i] - '0';          //converting the numbers to digit 
        insert_last(head,tail,digit);         
        i++;                                
    
    }
}

int insert_last(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = (Dlist *)malloc(sizeof(Dlist));           
    if(new == NULL)                                     
    {
        return FAILURE;
    }
    new -> data = data;                             
    new -> prev = NULL;                             
    new -> next = NULL;                             

    if((*head == NULL)  && (*tail == NULL))             
    {
        *head = new;
        *tail = new;
    }
    else
    {
        (*tail) -> next = new;              
        new ->prev = *tail;
        *tail = new;
    }
    return SUCCESS;
}

int insert_first(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));                   
    if(new==NULL)                                      
    {
        return FAILURE;
       
    }
    new->data = data;                                  
    new->prev = NULL;
    new->next = NULL;
   
    if(*head == NULL)                            
    {
        *tail = new;
        *head = new;                                    
        return SUCCESS;
    }
    (*head)->prev = new;                                
    new->next = *head;
    *head = new;
    return SUCCESS;
}

void remove_pre_zeros(Dlist **head)
{
    while(*head!=NULL && (*head)->data ==0 && (*head)->next !=NULL)        
    {
        Dlist *temp = *head;                                                 
        *head = (*head)->next;
        (*head)->prev = NULL;                                               
        free(temp);
    }
}
void print_list(Dlist *head)
{
        if (head == NULL)                  
        {
            return;             
        }
        else
        {
        
            while (head)        
            {
                
                printf("%d", head -> data);       
                head = head -> next;
                
            }
            
        }
}

int list_len(Dlist *head)                                
{
    int count = 0;                              
    Dlist *temp = head;
    while(temp != NULL)
    {
        count++;                                    //finding the length of the list 
        temp = temp -> next;
        
    }
    return count;
}

int compare_list(Dlist *head1, Dlist *head2)
{
    int list1_len = list_len(head1);                        //storing two length of the list in variables
    int list2_len = list_len(head2);

    Dlist *temp1 = head1;
    Dlist *temp2 = head2;                                    //initialising two temp Dlists with two head

    if(list1_len > list2_len)
    {
        return OPERAND1;                                //checking the length of  operand 1 is greater or not
    }

    else if(list2_len > list1_len)
    {
        return OPERAND2;                                //checking the length of  operand 2 is greater or not
    }
    else
    {
        while(temp1!=NULL && temp2!= NULL)                  //checking each digit is greater or not according to that returning operand 1 and operand 2 
        {
            if((temp1 -> data) > (temp2 -> data))   
            {
                return OPERAND1;
            }
            else if((temp2 -> data) > (temp1 -> data))
            {
                return OPERAND2;
            }
            else
            {
                temp1 = temp1 -> next;
                temp2 = temp2 -> next;                          //if it is same then return same
            }
        }
        return SAME;
    }
}

int delete_list(Dlist **head, Dlist **tail)                       
{
    if(*head == NULL)                               //checking empty or not
    {
        return FAILURE;
    }
   
   
    if(*head == *tail)                             //if only one Dlist is there then free that Dlist and make head and tail as NULL
    {
        free(*head);
        *head = NULL;
        *tail = NULL;
        return SUCCESS;
    }
    Dlist *temp = (*head) -> next;                   //else move to next Dlist 
    while(temp != NULL)
    {

        free(temp -> prev);                     //delete each Dlist by traversing through each Dlist
        temp = temp -> next;
    }
    *head = NULL;                               //last make the head and tail as NULL
    *tail = NULL;
    return SUCCESS;
}

void operation_decider(char *op1, char *op2)
{
    pos_flag1 = neg_flag1 = 0;                              //initialising each flag = 0
    pos_flag2 = neg_flag2 = 0;

    // Operand 1
    if (op1[0] == '-')                                      //checking first operand is negative or not
        neg_flag1 = 1;                                      //else change flag value to 1
    else
        pos_flag1 = 1;                                         //change next flag to 1

    // Operand 2
    if (op2[0] == '-')                                  //checking operand 2 is negative or not
        neg_flag2 = 1;                                  //change the value to 1
    else
        pos_flag2 = 1;                                  //else change next flag as 1
}