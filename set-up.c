#include <stdio.h>
#include <sqlite3.h>

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main()
{
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
   char s1[100] = "CREATE TABLE Passcode(username VARCHAR, code VARCHAR);";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, s1, callback, 0, &zErrMsg);
   char s2[100] = "CREATE TABLE USERS(username  NOT NULL UNIQUE, master_password NOT NULL );";
   rc = sqlite3_exec(db, s2, callback, 0, &zErrMsg);
   char s3[300] = "CREATE TRIGGER invalid_format "\
		   "BEFORE INSERT ON USERS "\
		   "BEGIN "\
		   "SELECT CASE "\
		   "WHEN ((NEW.username LIKE '% %') OR (NEW.username Like '')) THEN "\
		   "RAISE (ABORT, 'Invalid username format')"\
		   "END; END;";
   rc = sqlite3_exec(db, s3, callback, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }
   sqlite3_close(db);
   return 0;
}
