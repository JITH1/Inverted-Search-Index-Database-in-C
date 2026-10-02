#include"function.h"

int main(int argc,char *argv[])
{
    F_node *Head = NULL;
    M_node *HT[27] = {NULL};

    if(!validate_argumnets(argc,argv,&Head))
    {
        printf(RED"File Validation Failed...!\n\n"RESET);
        return FAILED;    
    }
    else
    {
        printf(GREEN"\nArgument Validation Successfull...!\n"RESET);
    }
    
    int option ;
    do
    {
       printf(YELLOW"\nSelect your choice among following operations:\n1. Create Database\n2. Display Database\n3. Save Database\n4. Search\n5. Update Database\n6. Exit\n\nEnter your choice : "RESET);
	    scanf("%d", &option);

       switch(option)
       {
          case 1:
          if(create_database(HT,&Head))
          {
             printf(GREEN"\nData Base Created Successfully...!\n"RESET);
          }
          else
          {
             printf(RED"\nCan't Create Database...!\n"RESET);
          }
          break;

          case 2:
          display_database(HT);
          break;

          case 3:
          Save_database(HT);
          break;

          case 4:
          break;

          case 5:
          break;

          case 6:
          break;

          default:
          printf(YELLOW"\nPlease enter a valid option...!\n"RESET);
          break;
       }

    }while(option != 6);
    
    
    return 0;
}