#ifndef INV_H
#define INV_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct file
{
    char f_name[20];
    struct file *link;
}F_node;

typedef struct sub
{
    int word_count;
    char file_name[20];
    struct sub *sub_link;
}S_node;

typedef struct main
{
    char word[25];
    int file_count;
    S_node *sub_link;
    struct main *main_link;
}M_node;


#endif

