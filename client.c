#include<stdio.h>
#include<stdlib.h>
#include "utilities.h"
// void reg1()
// {
//     char user[20];
//     char pwd[20];
//     printf("Enter Username: \n");
//     (void)fgets(user,20,stdin);
//     clean_stdin();
//     printf("Set the master password: \n");
//     (void)fgets(pwd,20,stdin);
//     printf("%s  %s",user,pwd);
// }
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