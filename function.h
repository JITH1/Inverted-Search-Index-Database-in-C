#ifndef FUN_H
#define FUN_H

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

#endif