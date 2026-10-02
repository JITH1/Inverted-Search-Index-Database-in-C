#include "function.h"

FLAG create_database(M_node *HT[],F_node **Head)
{

    for(int i = 0 ; i<27 ; i++)
    HT[i] = NULL;           // Make Hash table elements NULL

    F_node *f_ptr = *Head;  // Initiate Head Pointer to transverse the files 

    if(f_ptr == NULL)
    {
        printf(RED"\nCan't Find Any Files...!\n"RESET);
        return FAILED;
    }

    while(f_ptr != NULL)   // Transverse until the last file
    {
        FILE *open = fopen(f_ptr->f_name,"r");  // Open current file

        if(open == NULL)
        {
            printf(RED"\nCan't Open %s file\n",f_ptr->f_name);
            f_ptr = f_ptr->link;                              // Skip the current file 
            continue;
        }

        char buffer[30];
        int ch;
        int index = 0;

        while((ch = fgetc(open)) != EOF)
        {
            if(isalpha((unsigned char)ch))
            {
                 if(index < sizeof(buffer) - 1)
                 buffer[index++] = tolower((unsigned char)ch);
            }
            else
            {
                if(index > 0)
                {
                    buffer[index] = '\0';
                    store_word(HT, buffer, f_ptr->f_name);
                    index = 0;
                }
            }
        }

        buffer[index] = '\0';
        store_word(HT,buffer,f_ptr->f_name);
        
        fclose(open);
        f_ptr = f_ptr->link ;
    }

    return SUCCESS ;
}

void store_word(M_node *HT[], const char *word, const char *filename)
{
     int index = get_index(word[0]);

     M_node *prev = NULL;
     M_node *curr = HT[index];

     while(curr != NULL)
     {
         int match = strcmp(word,curr->word);

         if(match == 0)
         {
             S_node *node = find_file(curr,filename); 

             if(node != NULL)
             node->word_count++;
             else 
             create_node(curr,filename);
             
             return;
         }

         prev = curr;
         curr = curr->main_link;
     }
     
     M_node *new = (M_node *) malloc(sizeof(M_node));
    
     strncpy(new->word,word,sizeof(word)-1);

     new->word[sizeof(word)-1] = '\0'; 

     new->file_count = 0;
     
     new->sub_link = NULL;
     new->main_link = NULL;

     create_node(new,filename);

     if(HT[index] == NULL)
     HT[index] = new;
     else
     prev->main_link = new;

}

int get_index(char ch)
{
    if(isalpha(ch))
    {
        char alpha = tolower(ch);
        return (int)alpha - 'a';
    }
    else
    {
        return 26;
    }
}

S_node *find_file(M_node *HT,const char *filename)
{
    S_node *find = HT->sub_link ;

    while(find != NULL)
    {
        if(strcmp(find->file_name,filename) == 0)
        {
            return find;
        }

        find = find->sub_link;
    }

    return NULL;
}

void create_node(M_node *HT,const char *filename)
{
     S_node *new = malloc(sizeof(S_node));

     new->word_count = 1;
     strncpy(new->file_name,filename,sizeof(filename)-1);
     new->file_name[sizeof(filename) - 1] = '\0';
     new->sub_link = NULL;

     if(HT->sub_link == NULL)
     {
        HT->sub_link = new;
        HT->file_count = 1;
     }
     else
     {
        S_node *temp = HT->sub_link;

        while(temp->sub_link != NULL)
        {
            temp = temp->sub_link;
        }

        temp->sub_link = new ; 
        HT->file_count++;
     }


}