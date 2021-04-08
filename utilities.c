#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//storing the passwd in a file (temp)
static void store_master_password(char *usr,unsigned long pswd)
{
    FILE *fptr;
    
    fptr = fopen("./master_password.csv","a");
    if(fptr == NULL)
    {
        printf("Error!");   
        exit(0);             
    }
    fprintf(fptr,"%s,%lu\n",usr,pswd);
}

//djb hash function
static unsigned long hash(char *str)
{

    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

//alternative function to fflush(stdin)
void clean_stdin()
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

//function for registering user
void reg()
{
    char user[20];
    char pwd[20];
    printf("Enter Username: ");
    (void)fgets(user,20,stdin);
    user[strlen(user) - 1] = '\0';
    printf("Set the master password: ");
    (void)fgets(pwd,20,stdin);
    pwd[strlen(pwd) - 1] = '\0';
    unsigned long num;
    num = hash(user);
    printf("%s  %lu",user,num);
    store_master_password(user,num);
}