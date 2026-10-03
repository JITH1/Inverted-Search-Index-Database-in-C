#include"function.h"

void Search_database(void)
{
     char fname[30];

     printf(YELLOW"\nEnter the Database file to load : \n"RESET);
     scanf(" %29[^\n]",fname);

     if(!validate_fname(fname))
     {
        printf("\nFile %s validation failed...!\n",fname);
        return;
     }

     FILE *fptr = fopen(fname,"r");

    if(!fptr)
    {
        printf(RED"\nFAILED to Open File...!\n"RESET);
        return ;
    }

    fseek(fptr,0,SEEK_END);

    if(!ftell(fptr))
    {
        printf(RED"\nThe file is empty...!\n"RESET);
        return ;
    }

    fclose(fptr);

     // # 0 ; and ; 3 ; file1.txt ; 3 ; file2.txt ; 3 ; file3.txt ; 2 ; #

     M_node *HT[27] = {NULL};

     if(load_database(HT,fname))
     {
        printf(GREEN"\nThe %s database loaded successfully...!\n",fname);
     }
     else
     {
        printf(RED"\nCan't find %s database...!\n",fname);
        return;
     }

     char word[40];

     printf(YELLOW"\nEnter the word to search : \n");
     scanf(" %39[^\n]",word);
     
     char n = tolower(word[0]);

     int i = get_index(n);

     M_node *curr = HT[i];

     F_node *Empty = NULL;
         
    while(curr != NULL)
    {
        if(strcmp(word,curr->word) == 0)
        {
            printf(GREEN"\nThe word found...!\n\n");
            S_node *s = curr->sub_link;    // Point to the first S_node for this word
            
            printf("\nWord : %-10s ->  File Count : %-10d ",curr->word,curr->file_count);
            printf("\n--------------------------------------------------------\n");

            /* First file on same line as word */
            while(s)
            {
                printf("File : %-10s | Word Count : %-10d \n",s->file_name,s->word_count);
                s = s->sub_link;
            }

            printf("--------------------------------------------------------\n"RESET);

            Clear_database(HT,&Empty);

            return ;
        }

        curr = curr->main_link ;
    }


     printf(RED"\n-----------------------------------------------------\n");
     printf("\n# The Word \"%s\" Was Not Found In The Database : %s ...!\n",word,fname);
     printf("\n-----------------------------------------------------\n\n"RESET);

     Clear_database(HT,&Empty);

     return ;

     
}

FLAG load_database(M_node *HT[],const char *fname)
{

    FILE *ptr = fopen(fname,"r");

    if(ptr == NULL)
    {
        printf(RED"\nCan't Open Database File...!\n"RESET);
        return FAILED;
    }
    
    char line[256];

    while(fgets(line,sizeof(line),ptr) != NULL)
    {
        int index;
        char word[50];
        int s_no;
        
        M_node *curr ;

        sscanf(line,"# %d ; %49s ; %d ",&index,word,&s_no); // Get the hash index , word , S_node's

        if(HT[index] == NULL)
        {
            M_node *node = malloc(sizeof(M_node));
            strncpy(node->word,word,sizeof(node->word)-1);
            node->word[sizeof(node->word)-1] = '\0';
            node->file_count = s_no;
            node->sub_link = NULL;
            node->main_link = NULL;
            HT[index] = node;
            curr = node;
        }
        else
        {
            M_node *node = HT[index];

            while(node->main_link != NULL)
            {
                node = node->main_link;
            }
            
            node->main_link = malloc(sizeof(M_node));
            strncpy(node->main_link->word,word,sizeof(node->main_link->word)-1);
            node->main_link->word[sizeof(node->main_link->word)-1] = '\0';
            node->main_link->file_count = s_no;
            node->main_link->sub_link = NULL;
            node->main_link->main_link = NULL;

            curr = node->main_link;

        }
        
        char *ptr = line+1 ;
        
        S_node *s_link = NULL;

        while(ptr[0] != '\0')
        {

            while(ptr[0] == ' ' || ptr[0] == ';')
            ptr++;

            if(ptr[0] == '#' || ptr[0] == '\n' || ptr[0] == '\0')
            break;
             
             int semi = 0;

             while(*ptr && semi < 3) // Skip characters untill file names starts 
             {
                 if(*ptr == ';')
                 semi++;
        
                 ptr++;
             }

            while(ptr[0] == ' ' || ptr[0] == ';')
            ptr++;

            if(ptr[0] == '#' || ptr[0] == '\n' || ptr[0] == '\0')
            break;

             char f_name[20];
             int count;
             size_t i = 0;

             while(ptr[0]!= ' ' && ptr[0]!= ';' && i<sizeof(f_name)-1 && ptr[0]!='\0')
             {
                 f_name[i++] = ptr[0];
                 ptr++;
             }

             f_name[i] = '\0';

             while(ptr[0] == ' ' || ptr[0] == ';')
             ptr++;

             count = atoi(ptr);

             ptr = strchr(ptr,';');

             if(ptr != NULL)
             {
                ptr++;
             }

             S_node *s = malloc(sizeof(S_node));

             s->word_count = count;
             strncpy(s->file_name,f_name,sizeof(s->file_name)-1);
             s->file_name[sizeof(s->file_name)-1] = '\0';
             s->sub_link = NULL;

             if(curr->sub_link == NULL)
             {
                curr->sub_link = s;
             }
             else
             {
                s_link->sub_link = s;
             }   

             s_link = s;

        }
         
    }

    return SUCCESS ;

}

