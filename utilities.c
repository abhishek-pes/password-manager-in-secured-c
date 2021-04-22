#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "menu.h"
#include<stdbool.h>  

//splint utilities.c +charintliteral -predboolint +charint -temptrans  ---> 0 warnings 0 hazards 0 errors

//function to check password strength


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
unsigned long hash(char *str)
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

int password_strength(char *message)
{
    bool has_lower,has_upper,has_special,has_number,has_size;
    has_lower = false;
    has_upper = false;
    has_special = false;
    has_number = false;
    has_size = false; 
    int i;
    if(strlen(message)>=6)
        has_size = true;
    for(i = 0; message[i] != '\0'; i++)
    {
        if(message[i]>='A' && message[i]<='Z')
            has_upper=true;
        if(message[i]>='a' && message[i]<='z')
            has_lower=true;
        if(message[i]>='1' && message[i]<='9')
            has_number=true;
        if(message[i] == '!' || message[i] == '@' || message[i] == '#' || message[i] == '$' || message[i] == '%' || message[i] == '^' ||  message[i] == '*')
            has_special=true;

    }
    if(has_lower == true && has_upper == true && has_size == true && has_number == true && has_special == true)
        return 1;
    else
    {
        return 0;
    }
}


//ceaser cypher encryption function
char* ceaser_cipher_encrypt(char *message)
{
    char ch;
	int i, key;
	// printf("Enter key: ");
	// scanf("%d", &key);
    key = message[0];
	
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
    int r = password_strength(pwd);
    if(r == 1)
    {
        encrp_1 = ceaser_cipher_encrypt(pwd); //first layer of encryption
        printf("encryption complete");
        unsigned long num;
        num = hash(encrp_1);                  //second layer of encryption
        printf("%s  %lu",user,num);
        if (register_user(user, num) != 0)
        {
            printf("Registered Successfully\n");
        }
    }
    else
    {
        printf("\nYour Password is weak , use a password with 6 characters or more , uppercase , lowercase , numbers and special characters (!,@,#,$,%c,^,&,*",'%');
    }
    
    
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


//function for forgot password
void forgot_password()
{
    char user[20], pass[20]; 
    printf("Enter Username: ");
    (void)fgets(user,20,stdin);
    user[strlen(user) - 1] = '\0';
    printf("Enter passcode: ");
    (void)fgets(pass,20,stdin);
    pass[strlen(pass) - 1] = '\0';
    check_passcode(user,pass);
}
char* random_number()
{
        int ind;
		static  char pass[12];
		for(ind=0; ind<12; ind++)
		{
				int num = rand()%10;
				pass[ind] = num + '0';
		}
		return pass;
}

