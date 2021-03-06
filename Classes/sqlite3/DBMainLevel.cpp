//
//  DBMainLevel.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-8-26.
//
//

#include "DBMainLevel.h"
#include "sqlite3.h"
#include "cex.h"
#include "cocos2d.h"
#include "sql_common.h"

using namespace std;
using namespace cex;
USING_NS_CC;

DBMainLevel::DBMainLevel()
{
    id = 0;
    level = 0;
    min_jiglevel = 0;
    max_jiglevel = 0;
}

DBMainLevel DBMainLevel::readby_level(int level)
{
    DBMainLevel data;

    string file = jigsql::database_file();
    sqlite3* db;
    int rc = sqlite3_open(file.c_str(), &db);
    if( rc ){
        CCLOG("Can't open database: %s\n", file.c_str());
        sqlite3_close(db);
        return data;
    }
    char *zErrMsg = 0;
    rc = sqlite3_exec(db, cstr("select * from MainLevel where level=%d", level), DBMainLevel::callback, &data, &zErrMsg);
    if( rc!=SQLITE_OK ){
        CCLOG("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
    return data;
}

int DBMainLevel::callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    DBMainLevel* data = (DBMainLevel*)NotUsed;
    data->id = atoi( argv[0] );
    data->level = atoi( argv[1] );
    data->min_jiglevel = atoi( argv[2] );
    data->max_jiglevel = atoi( argv[3] );
    return 0;
}