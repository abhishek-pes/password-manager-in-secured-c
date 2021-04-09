#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "menu.h"

//splint utilities.c +charintliteral -predboolint +charint -temptrans  ---> 0 warnings 0 hazards 0 errors
struct test{
    char name[20];
    unsigned long pin;
};

static void test(char *str,unsigned long num)
{
    struct test p;
    printf("\nenter name :");
    strcpy(p.name,str);
    p.pin = num;
    printf("name --> %s",p.name);
    printf("pin --> %lu",p.pin);
    FILE *f;
    f =fopen("Record1","ab+");
    if(f == NULL)
    {
        printf("Error!");   
        exit(0);             
    }
   (void)fwrite(&p,sizeof(p),1,f);
}

//searching the binary file
static void searchrecord(char *str,unsigned long num)
{
    struct test p;
    FILE *f;

    f=fopen("Record1","rb");
    if(f==NULL)
    {
        printf("\n error in opening\a\a\a\a");
        exit(0);

    }

    int test = -1;
    while(fread(&p,sizeof(p),1,f)==1)
    {
        if(strcmp(p.name,str)==0 && p.pin == num)
        {
            test = 0;
            printf("\n\twelcome %s ",str);
            logged_in();
        }
            

    }
    if(test == -1)
        printf("\nINVALID USER NAME OR PASSWORD");
    (void)fclose(f);
}


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

//ceaser cypher encryption function
static char* ceaser_cipher_encrypt(char *message)
{
    char ch;
	int i, key;
	// printf("Enter key: ");
	// scanf("%d", &key);
    key = 5;
	
	for(i = 0; message[i] != '\0'; ++i){
		ch = message[i];
		
		if(ch >= 'a' && ch <= 'z'){
			ch = ch + key;
			
			if(ch > 'z'){
				ch = ch - 'z' + 'a' - 1;
			}
			
			message[i] = ch;
		}
		else if(ch >= 'A' && ch <= 'Z'){
			ch = ch + key;
			
			if(ch > 'Z'){
				ch = ch - 'Z' + 'A' - 1;
			}
			
			message[i] = ch;
		}
	}
	return message;
}

//function for registering user
void reg()
{
    char user[20];
    char pwd[20];
    char *encrp_1;
    printf("Enter Username: ");
    (void)fgets(user,20,stdin);
    user[strlen(user) - 1] = '\0';
    printf("Set the master password: ");
    (void)fgets(pwd,20,stdin);
    pwd[strlen(pwd) - 1] = '\0';
    encrp_1 = ceaser_cipher_encrypt(pwd); //first layer of encryption
    printf("encryption complete");
    unsigned long num;
    num = hash(encrp_1);                  //second layer of encryption
    printf("%s  %lu",user,num);
    store_master_password(user,num);      //storing it in a .csv file for observation only.
    test(user,num);
}

//function for logging
void logging()
{
    char user[20];
    char pwd[20];
    char *encrp_1;
    printf("Enter Username: ");
    (void)fgets(user,20,stdin);
    user[strlen(user) - 1] = '\0';
    printf("Enter master password: ");
    (void)fgets(pwd,20,stdin);
    pwd[strlen(pwd) - 1] = '\0';
    encrp_1 = ceaser_cipher_encrypt(pwd); //first layer of encryption
    unsigned long num;
    num = hash(encrp_1);                  //second layer of encryption
    //store_master_password(user,num);
    searchrecord(user,num);
}