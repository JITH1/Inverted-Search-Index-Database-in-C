#include"function.h"

FLAG Update_database(M_node *HT[],F_node **f_node)
{
    char fname[25];

    printf(YELLOW"\nEnter the file name to update : \n");
    scanf(" %24[^\n]"RESET,fname);

    if(validate_fname(fname))
    {
        printf(GREEN"\n%s validation successfull...!\n"RESET,fname);
    }
    else
    {
        printf(RED"\n%s Invalid file format...!\n"RESET,fname);
        return FAILED;
    }

    FILE *fptr = fopen(fname,"r");

    if(!fptr)
    {
        printf(RED"\nCan't open file %s..!\n"RESET,fname);
        fclose(fptr);
        return FAILED;
    }

    fseek(fptr,0,SEEK_END);

    if(!ftell(fptr))
    {
        printf(RED"\nThe file is empty...!\n"RESET);
        fclose(fptr);
        return FAILED;
    }

    fclose(fptr);

    F_node *temp = *f_node;

    if(temp == NULL)
    {
        temp = malloc(sizeof(F_node));
        strncpy(temp->f_name,fname,sizeof(temp->f_name)-1);
        temp->f_name[sizeof(temp->f_name)-1] = '\0';

        temp->link = NULL;
    }
    else
    {
        while(temp->link != NULL)
        {
           temp = temp->link;
        }

        temp->link = malloc(sizeof(F_node));
        strncpy(temp->link->f_name,fname,sizeof(temp->link->f_name)-1);
        temp->link->f_name[sizeof(temp->link->f_name)-1] = '\0';

        temp->link->link = NULL;
    }

    FILE *open = fopen(fname,"r");  // Open current file

    char buffer[30];
    int ch;
    int index = 0;

    while((ch = fgetc(open)) != EOF)
    {
        if(isalpha((unsigned char)ch))
        {
            if((unsigned int)index < sizeof(buffer) - 1)
            buffer[index++] = tolower((unsigned char)ch);
        }
        else
        {
            if(index > 0)
            {
                buffer[index] = '\0';
                store_word(HT, buffer,fname);
                index = 0;
            }
        }
    }

    if(index > 0)
    {
        buffer[index] = '\0';
        store_word(HT,buffer,fname);
    }
        
    fclose(open);
    return SUCCESS ;

}

    
