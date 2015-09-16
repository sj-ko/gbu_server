#include "stdafx.h"

#define DB_PATH ("E:/Working/GBU/Demo/GBU_Server/GBU_Server/sqlite/data.db")

class Database {
	
public:
	Database(char* dbpath);
	~Database();

	int GetCameraList();
	int InsertCamera();
	int CreateCameraTable();

private:
	int Query(int(*callback)(void*, int, char**, char**));

	sqlite3 *db;

	string lastQuery;
	char* lastErrorMsg;
};

Database::Database(char* dbpath)
{
	if (dbpath == NULL)
		dbpath = DB_PATH;

	this->lastErrorMsg = NULL;

	int result = sqlite3_open(DB_PATH, &this->db);
	if (result){
		string error = sqlite3_errmsg(this->db);
		sqlite3_close(this->db);
		this->db = NULL;
	}
	
	return;
}

Database::~Database()
{
	if (this->db) {
		sqlite3_close(this->db);
	}
	if (this->lastErrorMsg)
		sqlite3_free(this->lastErrorMsg);
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
	int i;
	for (i = 0; i<argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int Database::Query( int(*callback)(void*, int, char**, char**) )
{
	if (this->lastErrorMsg) {
		sqlite3_free(this->lastErrorMsg);
		this->lastErrorMsg = NULL;
	}

	int result = sqlite3_exec(this->db, this->lastQuery.c_str(), callback, 0, &this->lastErrorMsg);
	if (result != SQLITE_OK){
		wchar_t buffer[1024];
		wsprintf(buffer, TEXT("SQL error: %s\n"), this->lastErrorMsg);
		OutputDebugString(buffer);
	}

	return 0;
}

int Database::InsertCamera()
{


	return 0;
}

int Database::CreateCameraTable()
{
	this->lastQuery = "CREATE TABLE Camera ( \
					   	id INTEGER PRIMARY KEY AUTOINCREMENT \
						name VARCHAR \
						rtspurl VARCHAR \
					)";
	Query(callback);

	return 0;
}

int Database::GetCameraList()
{
	int num_camera = 0;

	if (this->lastErrorMsg) {
		sqlite3_free(this->lastErrorMsg);
		this->lastErrorMsg = NULL;
	}

	int result = sqlite3_exec(this->db, "SELECT name WHERE type = 'table'", callback, 0, &this->lastErrorMsg);
	if (result != SQLITE_OK){
		wchar_t buffer[1024];
		wsprintf(buffer, TEXT("SQL error: %s\n"), this->lastErrorMsg);
		OutputDebugString(buffer);
	}

	return num_camera;
}

void dbtest()
{
	sqlite3 *db;
	char *zErrMsg = 0;

	int rc = sqlite3_open(DB_PATH, &db);
	if (rc){
		string error = sqlite3_errmsg(db);
		sqlite3_close(db);
		return;
	}


	//rc = sqlite3_exec(db, argv[2], callback, 0, &zErrMsg);
	//if (rc != SQLITE_OK){
	//	fprintf(stderr, "SQL error: %s\n", zErrMsg);
	//	sqlite3_free(zErrMsg);
	//}

	sqlite3_close(db);
	return;
}