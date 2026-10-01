#ifndef FUN_H
#define FUN_H

#include "inverted.h"

typedef enum 
{
    FAILED,
    SUCCESS
}FLAG;

#define RED     "\x1b[1;31m"
#define GREEN   "\x1b[1;32m"
#define YELLOW  "\x1b[1;33m"
#define RESET   "\x1b[0m"


FLAG validate_argumnets(int argc,char *argv[],F_node **Head);
FLAG create_database(M_node *HT[],F_node **Head);
void store_word(M_node *HT[], const char *word, const char *filename);
S_node *find_file(M_node *HT,const char *filename);
void create_node(M_node *HT,const char *filename);
int get_index(char ch);

#endif