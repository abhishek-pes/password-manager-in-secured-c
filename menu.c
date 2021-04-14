#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "utilities.h"
#include "menu.h"
#include <sqlite3.h>

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
   
   if( rc != SQLITE_OK ){
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
      fprintf(stderr, "Opened database successfully\n");
   }
   

   char s1[100] = "INSERT INTO ";
   strcat(s1,user);
   char s2[30] = " VALUES('";
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

   sqlite3_close(db);
   printf("\n data stored succesfully.");
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
      fprintf(stderr, "Opened database successfully\n");
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
   rc = sqlite3_exec(db, s1, callback, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }

   sqlite3_close(db);
   logged_in(user);

}

static void delete_password(char *site_name , char *user)
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
   char s1[30] = "DELETE FROM ";
   strcat(s1,user);
   char s2[50] =" WHERE WEBSITE_NAME='";
   strcat(s2,site_name);
   char s3[10] = "';";
   strcat(s2,s3);
   strcat(s1,s2);
   rc = sqlite3_exec(db, s1, callback, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } 

   sqlite3_close(db);
   printf("\n data deleted");
   logged_in(user);
}



void logged_in(char *str)
{
    printf("\nHello %s you have succesfully logged in\n",str);
    create_table(str);
    printf("\n\n1. Store Passwords");
    printf("\n2. Delete Password");
    printf("\n3. Modify passwords");
    printf("\n4. Check a password");
    printf("\n5. Check all passwords");
    printf("\n6. Logout\n");
    int choice;
    (void)scanf("%d",&choice);
    clean_stdin();
    switch(choice)
    {
        case 1:
                printf("\nthis is the store password page\n");
                char website_name[50];
                char passwd[20];
                printf("\nEnter the website name: ");
                fgets(website_name,50,stdin);
                website_name[strlen(website_name) - 1] = '\0';
                printf("\nEnter the password: ");
                fgets(passwd,20,stdin);
                passwd[strlen(passwd) - 1] = '\0';
                store(website_name,passwd,str);
                break;

        case 2:
                printf("this is the delete password page\n");
                char name[50];
                printf("\n Enter the website name to delete: ");
                fgets(name,50,stdin);
                name[strlen(name) - 1] = '\0';
                delete_password(name,str);
                break;

        case 3:
                printf("this is the modify password page\n");
                char old_name[50];
                char new_name[50];
                char new_password[50];
                printf("\n Enter the website name to modify: ");
                fgets(old_name,50,stdin);
                old_name[strlen(old_name) - 1] = '\0';
                printf("\n Enter the new website name: ");
                fgets(new_name,50,stdin);
                new_password[strlen(new_name) - 1] = '\0';
                printf("\n Enter the new password: ");
                fgets(new_password,50,stdin);
                new_password[strlen(new_password) - 1] = '\0';
                store(new_name,new_password,str);
                break;
        case 4:
                printf("this is the check password page\n");
                char site_name[50];
                printf("\n Enter the website name to get the password for it: ");
                fgets(site_name,50,stdin);
                site_name[strlen(site_name) - 1] = '\0';
                get_single_pass(site_name,str);

                break;
        
        case 5:
               printf("this is the check all passwords page\n");
               show_all_passwords(str);
               break;
        
        case 6: 
                printf("this is the logout page\n");
                exit(0);
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

    if (strcmp(sqlite3_column_text(res, 0), pwd)==0) {
        sqlite3_finalize(res);
    	sqlite3_close(db);
        printf("\n\twelcome %s ",str);
        logged_in(str);
    } 
    else {
	printf("\nINVALID USER NAME OR PASSWORD");
    }
    sqlite3_finalize(res);
    sqlite3_close(db);
}
    