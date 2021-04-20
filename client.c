#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "menu.h"
#include "utilities.h"

void main_menu()
{
    int choice;
    do
    {
        printf("\n*****************************************************************\n\n");
        printf("\t\tPASSWORD MANAGER\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Forgot password\n");
        printf("4. Exit\n");
        printf("\nEnter Your Choice: ");
        (void)scanf("%d",&choice);
        clean_stdin();
        switch(choice)
        {
            case 1:
                    logging();
                    break;

            case 2:
                    reg();
                    break;
            case 3:
                forgot_password();
                break;
            case 4:
                exit(0);
            default:
                    printf("invalid choice!\n");
                    break;
        }
    }while(choice != 4);

}

int main()
{
    main_menu();
    return 0;
}