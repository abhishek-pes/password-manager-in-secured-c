#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "menu.h"
#include "utilities.h"

int main()
{
    printf("\t\tPASSWORD MANAGER\n");
    printf("1. Login\n");
    printf("2. Register\n");
    printf("3. Forgot password\n");
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
	case 3:
		printf("this is login page\n");
		char user[20], pass[20];
		printf("Enter Username: ");
    		(void)fgets(user,20,stdin);
    		user[strlen(user) - 1] = '\0';
    		printf("Enter master password: ");
    		(void)fgets(pass,20,stdin);
    		pass[strlen(pass) - 1] = '\0';
		check_passcode(user, pass);
		break;
        default:
                printf("invalid choice!\n");
                break;
    }
    return 0;

}