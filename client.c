#include<stdio.h>
#include<stdlib.h>
#include "utilities.h"

int main()
{
    printf("\t\tPASSWORD MANAGER\n");
    printf("1. Login\n");
    printf("2. Register\n");
    int choice;
    (void)scanf("%d",&choice);
    clean_stdin();
    switch(choice)
    {
        case 1:
                printf("this is the login page\n");
                logging();
                break;

        case 2:
                printf("this is the register page\n");
                reg();
                break;

        default:
                printf("invalid choice!\n");
                break;
    }
    return 0;

}