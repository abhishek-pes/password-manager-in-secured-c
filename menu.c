#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "utilities.h"
#include "menu.h"
#include <sqlite3.h>
#include <time.h>

void passcode(char* user);

void logged_in(char *str);

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}



static int create_table(char *str) {
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   rc = sqlite3_open("test.db", &db);
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }
   /* Create SQL statement */
   char s1[100] = "CREATE TABLE ";
   strcat(s1,str);
   char s2[50] = "(" \
                "WEBSITE_NAME TEXT,"\
                "PASSWORD VARCHAR);";
   strcat(s1,s2);

   /* Execute SQL statement */
   rc = sqlite3_exec(db, s1, callback, 0, &zErrMsg);
   char s3[300] = "CREATE TRIGGER format_";
   strcat(s3,str);
   char s4[250] = " BEFORE INSERT ON ";
   strcat(s4,str);
   char s5[200] = " BEGIN SELECT CASE "\
		   "WHEN ((NEW.WEBSITE_NAME LIKE '% %') OR (NEW.WEBSITE_NAME Like '') OR (NEW.PASSWORD LIKE '% %') OR (NEW.PASSWORD Like '') ) THEN "\
		   "RAISE (ABORT, 'Invalid format') END;"\
		   "END;";
   strcat(s4, s5);
   strcat(s3, s4);
   int RC = sqlite3_exec(db, s3, callback, 0, &zErrMsg);
   
   if( rc != SQLITE_OK || RC != SQLITE_OK){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }
   sqlite3_close(db);
   return 0;
}

static void store(char *name , char * pwd , char *user)
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   rc = sqlite3_open("test.db", &db);
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      logged_in(user);
   } else {
      fprintf(stderr, "\nSTORING DATA...");
   }
   

   char s1[100] = "INSERT INTO ";
   strcat(s1,user);
   char s2[50] = " VALUES('";
   strcat(s2,name);
   char s3[30] = "','";
   strcat(s3,pwd);
   char s4[30] = "');";
   strcat(s3,s4);
   strcat(s2,s3);
   strcat(s1,s2);

   rc = sqlite3_exec(db, s1, callback, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } 
   else {
	printf("\nTHE DATA IS STORED SUCCESFULLY.");
   }
   sqlite3_close(db);
   
   logged_in(user);
}

static void show_all_passwords(char *user)
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   rc = sqlite3_open("test.db", &db);
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
   logged_in(user);
   } else {
      fprintf(stderr, "\nOpened database successfully\n");
   }
   char s1[30] = "SELECT * FROM ";
   strcat(s1,user);
   rc = sqlite3_exec(db, s1, callback, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } 

   sqlite3_close(db);
   logged_in(user);

}

static void get_single_pass(char * website_name , char *user)
{
   sqlite3 *db;
   char *zErrMsg = 0;
   sqlite3_stmt *res;
   int rc;
   const char* data = "Callback function called";
   rc = sqlite3_open("test.db", &db);
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
   logged_in(user);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }

   char s1[50] = "SELECT * FROM ";
   strcat(s1,user);
   char s2[50] = " WHERE WEBSITE_NAME='";
   strcat(s2,website_name);
   char s3[50] = "';";
   strcat(s2,s3);
   strcat(s1,s2);

   rc = sqlite3_prepare_v2(db, s1, -1, &res, 0);
   int step = sqlite3_step(res);
   if(step == SQLITE_ROW)
   {
   rc = sqlite3_exec(db, s1, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   }
   else{
      printf("\nNO SUCH DATA FOUND");
   }

   sqlite3_close(db);
   logged_in(user);

}

static void delete_password(char *site_name , char *user)
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   sqlite3_stmt *res;
   rc = sqlite3_open("test.db", &db);
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
   logged_in(user);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }
   char s1[30] = "DELETE FROM ";
   strcat(s1,user);
   char s2[50] =" WHERE WEBSITE_NAME='";
   strcat(s2,site_name);
   char s3[10] = "';";
   strcat(s2,s3);
   strcat(s1,s2);
   rc = sqlite3_prepare_v2(db, s1, -1, &res, 0);
   int step = sqlite3_step(res);
   if(step == SQLITE_ROW)
   {
   rc = sqlite3_exec(db, s1, callback, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } 
   }
   else
   {
      printf("\nNO SUCH DATA FOUND");
      sqlite3_close(db);
      logged_in(user);

   }
   sqlite3_close(db);
   printf("\nDATA DELETED SUCCESFULLY");
   logged_in(user);
}


static void modify_password(char * website_name , char *user, char *newpwd)
{
   sqlite3 *db;
   char *zErrMsg = 0;
   sqlite3_stmt *res;
   int rc;
   const char* data = "Callback function called";
   rc = sqlite3_open("test.db", &db);
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
   logged_in(user);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }
   char st_check[50] = "SELECT * FROM ";
   strcat(st_check,user);
   char st[30] = " WHERE WEBSITE_NAME='";
   strcat(st,website_name);
   char st1[30]="';";
   strcat(st,st1);
   strcat(st_check,st);
   rc = sqlite3_prepare_v2(db, st_check, -1, &res, 0);
   int step = sqlite3_step(res);
   if(step == SQLITE_ROW)
{
   char s1[50] = "UPDATE ";
   strcat(s1,user);
   char s2[50] = " SET PASSWORD='";
   strcat(s2,newpwd);
   char s3[50] = "' WHERE WEBSITE_NAME='";
   strcat(s3,website_name);
   char s4[50] = "';";
   strcat(s3,s4);
   strcat(s2,s3);
   strcat(s1,s2);
   printf("\n the statement is %s",s1);
   
   rc = sqlite3_exec(db, s1, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
}
   else{
      printf("\nNO SUCH DATA FOUND");
   }

   sqlite3_close(db);
   logged_in(user);

}

void show_all_passcode(char *user)
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   rc = sqlite3_open("test.db", &db);
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
   logged_in(user);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }
   char s1[80] = "SELECT * FROM Passcode WHERE username='";
   strcat(s1,user);
   char s2[10] = "';";
   strcat(s1,s2);
   rc = sqlite3_exec(db, s1, callback, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } 

   sqlite3_close(db);
   logged_in(user);

}

void delete_passcode(char* user, char* pass)
{
	sqlite3 *db;
   	char *zErrMsg = 0;
   	int rc;
   	rc = sqlite3_open("test.db", &db);
   	if( rc ) {
      	    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
   	    return;
   	} else {
      	    fprintf(stderr, "Opened database successfully\n");
   	}
	char s1[80] = "DELETE FROM Passcode WHERE code='";
   	strcat(s1, pass);
   	char s2[10] = "';";
   	strcat(s1,s2);
   	rc = sqlite3_exec(db, s1, callback, 0, &zErrMsg);

   	if( rc != SQLITE_OK ){
      		fprintf(stderr, "SQL error: %s\n", zErrMsg);
      		sqlite3_free(zErrMsg);
   	}
	//check the remaining number of passcodes for a username
   	sqlite3_stmt *stmt;
   	char query[100] = "SELECT COUNT(*) FROM Passcode WHERE username='";
   	strcat(query, user);
   	char qEND[10] = "';";
   	strcat(query, qEND);
   	rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
   	if(rc != SQLITE_OK)
   	{
	   fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
   	}
   	rc = sqlite3_step(stmt);
   	if(rc != SQLITE_ROW)
   	{
	   fprintf(stderr, "No rows returned: %s\n", sqlite3_errmsg(db));
   	}
   	int row_count = sqlite3_column_int(stmt, 0);
	if(row_count < 1)
	{
		passcode(user);
	}
}

void check_passcode(char* user, char* pass)
{
    sqlite3 *db;
    sqlite3_stmt *res;
    
    int rc = sqlite3_open("test.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return;
    }
    
    char *sql = "SELECT username FROM Passcode WHERE code = ?";
        
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    
    if (rc == SQLITE_OK) {
        
        sqlite3_bind_text(res, 1, pass, -1, 0);
    } else {
        
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    
    int step = sqlite3_step(res);
    if(step == SQLITE_ROW)
{
    if (strcmp(sqlite3_column_text(res, 0), user)==0) {
         sqlite3_finalize(res);
    	   sqlite3_close(db);
	      delete_passcode(user, pass);
         printf("\n\twelcome %s ",user);
         logged_in(user);
    } 
}
    else {
	printf("\nInvalid Passcode\n");
    }
    sqlite3_finalize(res);
    sqlite3_close(db);
}

void logged_in(char *str)
{
    int r; 
    printf("\n===========================================================");
    printf("\nUSER: %s   STATUS: LOGGED-IN\n",str);
    printf("\n\n1. Store Passwords");
    printf("\n2. Delete Password");
    printf("\n3. Modify passwords");
    printf("\n4. Check a password");
    printf("\n5. Check all passwords");
    printf("\n6. Show all passcodes");
    printf("\n7. Logout\n");
    int choice;
    printf("\nEnter Your Choice: ");
    (void)scanf("%d",&choice);
    clean_stdin();
    switch(choice)
    {
        case 1:
                printf("\n--------------------------------------------------------------\n");
                char website_name[50];
                char passwd[20];
                printf("\nEnter the website name: ");
                fgets(website_name,50,stdin);
                website_name[strlen(website_name) - 1] = '\0';
                printf("\nEnter the password: ");
                fgets(passwd,20,stdin);
                passwd[strlen(passwd) - 1] = '\0';
                r  = password_strength(passwd);
                if(r==1)
                {
                  printf("\n--------------------------------------------------------------\n");
                  store(website_name,passwd,str);
                }
                else
                {
                  printf("\nYour Password is weak , use a password with 6 characters or more , uppercase , lowercase , numbers and special characters (!,@,#,$,%c,^,&,*\n",'%');
                  logged_in(str);
                }
                break;

        case 2:
                printf("\n--------------------------------------------------------------\n");
                char name[50];
                printf("\n Enter the website name to delete: ");
                fgets(name,50,stdin);
                name[strlen(name) - 1] = '\0';
                printf("\n--------------------------------------------------------------\n");
                delete_password(name,str);
                break;

        case 3:
                printf("\n--------------------------------------------------------------\n");
                char old_name[50];
                char new_password[50];
                printf("\n Enter the website name to modify: ");
                fgets(old_name,50,stdin);
                old_name[strlen(old_name) - 1] = '\0';
                printf("\n Enter the new password: ");
                fgets(new_password,50,stdin);
                new_password[strlen(new_password) - 1] = '\0';
                int r  = password_strength(new_password);
                if(r==1)
                {
                  printf("\n--------------------------------------------------------------\n");
                  modify_password(old_name,str,new_password);
                }
                else
                {
                  printf("\nYour Password is weak , use a password with 6 characters or more , uppercase , lowercase , numbers and special characters (!,@,#,$,%c,^,&,*\n",'%');
                  logged_in(str);
                }
                break;
        case 4:
                printf("\n--------------------------------------------------------------\n");
                char site_name[50];
                printf("\n Enter the website name to get the password for it: ");
                fgets(site_name,50,stdin);
                site_name[strlen(site_name) - 1] = '\0';
                printf("\n--------------------------------------------------------------\n");
                get_single_pass(site_name,str);

                break;
        
        case 5:
               printf("\n--------------------------------------------------------------\n");
               show_all_passwords(str);
               break;
        
	     case 6:
               printf("\n--------------------------------------------------------------\n");
               show_all_passcode(str);
               printf("\n--------------------------------------------------------------\n");
               break;

        case 7: 
                printf("\nLOGGING OUT...\n\n");
                main_menu();
                break;

        default:
                printf("invalid choice! please chose again\n");
                logged_in(str);
                break;
    }
}

//Inserting username and password into database
int register_user(char *str, unsigned long num)
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   rc = sqlite3_open("test.db", &db);
   if( rc ) {
      	fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
   } else {
      	fprintf(stderr, "Opened database successfully\n");
   }
   /*SQL statements*/
   char s1[200] = "INSERT INTO USERS ";
   char s2[200] = " VALUES('";
   strcat(s2,str);
   char s3[130] = "','";
   char passwd[100];
   sprintf(passwd, "%lu", num);
   strcat(s3,passwd);
   char s4[30] = "');";
   strcat(s3,s4);
   strcat(s2,s3);
   strcat(s1,s2);

   rc = sqlite3_exec(db, s1, callback, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      fprintf(stderr, "Error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return 1;
   } 

   sqlite3_close(db);
   passcode(str);
   create_table(str);
   return 0;
}	

//Searching the database for user password
void searchrecord(char *str,unsigned long num)
{
   sqlite3 *db;
   char *err_msg = 0;
   sqlite3_stmt *res;
    
    int rc = sqlite3_open("test.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return;
    }
    
    char *sql = "SELECT master_password FROM USERS WHERE username = ?";
        
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    
    if (rc == SQLITE_OK) {
        
        sqlite3_bind_text(res, 1, str, -1, 0);

    } else {
        
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    
    int step = sqlite3_step(res);
    char pwd[200];
    sprintf(pwd, "%lu", num);
    if(step == SQLITE_ROW)
    {
    if (strcmp(sqlite3_column_text(res, 0), pwd)==0) {
        sqlite3_finalize(res);
    	sqlite3_close(db);
        printf("\n\t\t WELCOME %s ",str);
        logged_in(str);
    }
    } 
    else {
      printf("\nINVALID USER NAME OR PASSWORD\n");
    }
    sqlite3_finalize(res);
    sqlite3_close(db);
}

void passcode(char* user)
{
	srand(time(NULL));
	sqlite3 *db;
   	char *zErrMsg = 0;
   	int rc;
   	rc = sqlite3_open("test.db", &db);
  	if( rc ) {
      	    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	    return;
         }
   	for(int i=0;i<3;i++)
	{
		char* passnum = random_number();
		char s1[100] = "INSERT INTO Passcode ";
   		char s2[30] = " VALUES('";
   		strcat(s2, user);
   		char s3[30] = "','";
		strcat(s3, passnum);
		char* s4 = "');";
		strcat(s3, s4);
   		strcat(s2,s3);
   		strcat(s1,s2);
   		rc = sqlite3_exec(db, s1, callback, 0, &zErrMsg);

   		if( rc != SQLITE_OK ){
      	    	    fprintf(stderr, "SQL error: %s\n", zErrMsg);
            	    sqlite3_free(zErrMsg);
   		}
	}

   	sqlite3_close(db);
}

