#include "function.h"

void display_database(M_node *HT[])
{
    int found = 0;                         // Tracks whether any entries exist in the table
    
    printf(YELLOW"\n--------------------------------------------------------------------------------\n");
    printf("\n%-8s %-25s %-12s %-20s %-8s\n","INDEX", "WORD", "FILE_COUNT", "FILENAME", "WORD_COUNT");
    printf("\n--------------------------------------------------------------------------------\n\n"RESET);

    for (int i = 0; i < 27; i++)          // Iterate over all 27 hash buckets
    {
        M_node *curr = HT[i];

        while (curr != NULL)
        {
            found = 1;                     // At least one entry found in the table

            S_node *s = curr->sub_link;    // Point to the first S_node for this word

            /* First file on same line as word */
            printf(YELLOW"%-8d %-25s %-12d %-20s %-10d\n"RESET,i,curr->word,curr->file_count,s ? s->file_name : "-",s ? s->word_count : 0);

            /* Remaining files on new lines, word/index/filecount columns blank */
            if(s)
            s = s->sub_link;               // Advance past the first S_node already printed

            while (s != NULL)
            {
                printf(YELLOW"%-8s %-25s %-12s %-20s %-10d\n"RESET,"", "", "", s->file_name, s->word_count);  // Print only filename and count for subsequent files
                s = s->sub_link;
            }

            printf("--------------------------------------------------------------------------------\n");  // Separator after each word entry

            curr = curr->main_link;        // Advance to the next word in this bucket
        }
    }

    if(!found)
    {
        printf(RED"\n----------------------------------------------------\n\n"RESET);
        printf(RED"# Database is empty...Create the database first...!\n"RESET);  // Warn user to create the database first
        printf(RED"\n----------------------------------------------------\n\n"RESET);
    }

    printf("\n");

}