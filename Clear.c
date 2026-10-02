#include "function.h"

FLAG Clear_database(M_node *HT[],F_node **f_node)
{
    int found = 0;

    for(int i = 0 ; i<27 ; i++)
    {
        M_node *curr = HT[i];

        while(curr != NULL)
        {
           found = 1;

           if(curr->main_link != NULL)
           {
               M_node *temp = curr ;
               curr = curr->main_link;
               
               S_node *s1 = temp->sub_link;

               while(s1 != NULL)
               {
                  S_node *s2 = s1->sub_link ;
                  free(s1);
                  s1 = s2;
               }

               free(temp);
           }
           else
           {
               M_node *temp = curr ;
               curr = curr->main_link;
               
               S_node *s1 = temp->sub_link;
        
               while(s1 != NULL)
               {
                  S_node *s2 = s1->sub_link ;
                  free(s1);
                  s1 = s2;
               }

               free(temp);
           } 
        }

        HT[i] = NULL ;

    }

    if(!found)
    {
        return FAILED;
    }

    if(*f_node)
    {
        F_node *f1 = *f_node;
        
        while(f1 != NULL)
        {
            F_node *f2 = f1->link;
            free(f1);
            f1 = f2;
        }

        *f_node = NULL;
    }

    return SUCCESS ;
}