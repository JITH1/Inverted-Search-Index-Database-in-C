#include"inverted.h"
#include"function.h"

FLAG validate_argumnets(int argc,char *argv[],F_node **Head)
{
    if(argc == 1)
    {
        printf(RED"\nInsufficient Number of arguments...!\n"RESET);
        return FAILED;
    }

    for(int i = 1 ; argv[i]!= NULL ; i++)
    {
        if(argv[i][0] == '.')
        {
            printf(RED"\nInvalid file format : %s\n"RESET,argv[i]);
            return FAILED ;
        } 

        char *ptr = strchr(argv[i],' ');

        if(ptr != NULL)
        {
            printf(RED"\nInvalid file format : %s\n"RESET,argv[i]);
            return FAILED ;
        }

        ptr = strstr(argv[i],".txt");

        if(ptr == NULL)
        {
            printf(RED"\nInvalid file format : %s\n"RESET,argv[i]);
            return FAILED ;
        }

        if(ptr[4] != '\0')
        {
            printf(RED"\nInvalid file format : %s\n"RESET,argv[i]);
            return FAILED ;
        }

        if(isdigit(argv[i][0]))
        {
            printf(RED"\nInvalid file format : %s\n"RESET,argv[i]);
            return FAILED ;
        }

        FILE *fptr = fopen(argv[i],"r");

        if(!fptr)
        {
            printf(RED"\nCan't open file : %s\n"RESET,argv[i]);
            return FAILED;
        }
        
        fseek(fptr,0,SEEK_END);

        if(!ftell(fptr))
        {
            printf(RED"\nFile Empty : %s\n"RESET,argv[i]);
            fclose(fptr);
            return FAILED ;
        }

        fclose(fptr);
    }

    int i = 1;

    while(argv[i]!= NULL)
    {
        if(*Head == NULL)
        {
            F_node *new = malloc(sizeof(F_node));
            strcpy(new->f_name,argv[i]);
            new->link = NULL;
            *Head = new ;
            i++;
        }
        else
        {
            F_node *temp = *Head;
        
            while(temp->link != NULL)
            {
               temp = temp->link;
            }

            F_node *new = malloc(sizeof(F_node));
            strcpy(new->f_name,argv[i]);
            new->link = NULL;
            temp->link = new;
            i++;
        }
        
    } 

    return SUCCESS;

}