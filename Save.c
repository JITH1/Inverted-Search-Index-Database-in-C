#include "function.h"

void Save_database(M_node *HT[])
{
    int found = 0;
    int index[27] = {0}; 

    for(int i = 0 ; i<27 ; i++)
    {
        if(HT[i] != NULL)
        {
            found++;
            index[i]++;
        }
    }

    if(!found)
    {
        printf(RED"\nThe database is empty...!\n"RESET);
        return;
    }

    printf("\nEnter the filename to save the Database : \n");
    char f_name[30];
    scanf(" %29[^\n]",f_name);
    
    if(!validate_fname(f_name))
    {
       printf(RED"\nInvalid file format...!\n"RESET);
       printf(RED"\nDatabase Creation Failed...!\n"RESET);
       return ; 
    }


    FILE *fptr = fopen(f_name,"w");

   //   # 0 ; a ; 2 ; f2.txt ; 1 ; f3.txt ; 1 ; #  
   //   # 5 ; flower ; 4 ; f1.txt ; 1 ; f2.txt ; 1 ; f3.txt ; 1 ; f4.txt ; 1 ; #

   for(int i = 0 ; i<27 ; i++)
   {
       M_node *curr = HT[i];

       while(curr != NULL)
       {
           fprintf(fptr,"# %d ; %s ; %d ; ",i,curr->word,curr->file_count);
           
           S_node *s_link = curr->sub_link;

           while(s_link)
           {
               fprintf(fptr,"%s ; %d ; ",s_link->file_name,s_link->word_count);
               s_link = s_link->sub_link;
           }

           fprintf(fptr,"#\n");

           curr = curr->main_link;
       }

   }

   printf(GREEN"\n\nDatabase Created Successfully...!\n\n"RESET);

}

FLAG validate_fname(const char *f_name)
{
        if(f_name[0] == '.')
        {
            printf(RED"\nInvalid file format : %s\n"RESET,f_name);
            return FAILED ;
        } 

        char *ptr = strchr(f_name,' ');

        if(ptr != NULL)
        {
            printf(RED"\nInvalid file format : %s\n"RESET,f_name);
            return FAILED ;
        }

        ptr = strstr(f_name,".txt");

        if(ptr == NULL)
        {
            printf(RED"\nInvalid file format : %s\n"RESET,f_name);
            return FAILED ;
        }

        if(ptr[4] != '\0')
        {
            printf(RED"\nInvalid file format : %s\n"RESET,f_name);
            return FAILED ;
        }

        if(isdigit(f_name[0]))
        {
            printf(RED"\nInvalid file format : %s\n"RESET,f_name);
            return FAILED ;
        }

        return SUCCESS ;
}