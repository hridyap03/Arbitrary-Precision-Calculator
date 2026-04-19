#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define SUCCESS		1
#define FAILURE		0

#define SAME		0
#define OPERAND1	1
#define OPERAND2	2



typedef struct Dlist
{
    struct Dlist *prev;
    int data;
    struct Dlist *next;
}Dlist;

void addition(Dlist *tail1, Dlist *tail2, Dlist **headR, Dlist **tailR);
void subtraction(Dlist *tail1, Dlist *tail2, Dlist **headR, Dlist **tailR);
void multiplication(Dlist *tail1, Dlist *tail2, Dlist **headR, Dlist **tailR);
int division(Dlist *head1_L1, Dlist *head_OPR1,Dlist *tail2_OPR2, Dlist **headR, Dlist **tailR);

int validation(int argc, char *argv[]);
void create_linkedlist(char *opr, Dlist **head, Dlist **tail);
void operation_decider(char *op1, char *op2);

extern int pos_flag1, neg_flag1;
extern int pos_flag2, neg_flag2;

int insert_first(Dlist **head, Dlist **tail, int data);
int insert_last(Dlist **head, Dlist **tail, int data);
int delete_list(Dlist **head, Dlist **tail);
void print_list(Dlist *head);

int compare_list(Dlist *head1, Dlist *head2);
int list_len(Dlist *head);
void remove_pre_zeros(Dlist **head);




#endif
