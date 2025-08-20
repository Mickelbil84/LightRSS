#include "core/lrss_storage.h"
using namespace lrss;

std::vector<std::pair<std::string, int>> LRSSStorage::_getSubscriptionsResult;

void LRSSStorage::init() {
    createSubscriptionsTable();
    createChannelsTable();
    createItemsTable();
}

void LRSSStorage::addNewSubscription(std::string url) {
    std::vector<std::string> existingSubscriptions = getSubscriptions();
    for (std::string existingUrl : existingSubscriptions)
        if (existingUrl == url) return;

    std::string query = fmt::format("INSERT INTO SUBSCRIPTIONS (ID, URL) VALUES (NULL, '{}');", url);
    runDBQuery(query);
}

std::vector<std::string> LRSSStorage::getSubscriptions() {
    _getSubscriptionsResult.clear();
    std::string query = "SELECT * FROM SUBSCRIPTIONS;";
    runDBQuery(query, LRSSStorage::_getSubscriptionsCallback);

    std::vector<std::string> result;
    for (std::pair<std::string, int> x : _getSubscriptionsResult)
        result.push_back(x.first);
    return result;
}

void LRSSStorage::deleteChannel(LRSSChannel* channelInfo) {
    std::string query = fmt::format("DELETE FROM CHANNELS WHERE GUID='{}';", channelInfo->guid);
    runDBQuery(query);
}

void LRSSStorage::updateChannel(LRSSChannel* channelInfo) {
    deleteChannel(channelInfo);
    std::string query = fmt::format(
        "INSERT INTO CHANNELS (ID, GUID, TITLE, DESCRIPTION, LINK, IMAGE_LINK, COPYRIGHT, LANGUAGE, LAST_BUILD, PUB_DATE) "\
        "VALUES (NULL, '{}', '{}', '{}', '{}', '{}', '{}', '{}', {}, {})",
        channelInfo->guid, channelInfo->title, channelInfo->description, channelInfo->link, channelInfo->imageLink,
        channelInfo->copyright, channelInfo->language, 0, 0
    );
    runDBQuery(query);
}

int LRSSStorage::_getSubscriptionsCallback(void* data, int argc, char** argv, char** azColName) {
    int priority = -1;
    std::string url = "";
    for (int i = 0; i < argc; i++) {
        if (std::string(azColName[i]) == "URL") {
            url = argv[i];
        }
        if (std::string(azColName[i]) == "PRIORITY" && argv[i]) {
            priority = atoi(argv[i]);
        }
    }
    _getSubscriptionsResult.push_back(std::pair<std::string, int>(url, priority));
    return 0;
}

sqlite3* LRSSStorage::openDB() {
    sqlite3* db;
    if(sqlite3_open(LRSS_STORAGE_PATH, &db)) {
        fmt::print("Cannot open storage: {}\n", sqlite3_errmsg(db));
        return nullptr;
    }
    return db;
}
void LRSSStorage::closeDB(sqlite3* db) {
    if (db)
        sqlite3_close(db);
}

void LRSSStorage::createSubscriptionsTable() {
    const char* query = "CREATE TABLE IF NOT EXISTS SUBSCRIPTIONS("\
        "ID INTEGER PRIMARY KEY,"\
        "URL  CHAR(256) NOT NULL,"\
        "PRIORITY INT"\
        ");";
    runDBQuery(query);
}
void LRSSStorage::createChannelsTable() {
    const char* query = "CREATE TABLE IF NOT EXISTS CHANNELS("\
        "ID INTEGER PRIMARY KEY,"\
        "GUID           CHAR(256) NOT NULL,"
        "TITLE          CHAR(1024),"\
        "DESCRIPTION    CHAR(4096),"\
        "LINK           CHAR(256),"\
        "IMAGE_LINK     CHAR(256),"\
        "COPYRIGHT      CHAR(1024),"\
        "LANGUAGE       CHAR(32),"\
        "LAST_BUILD     INTEGER,"\
        "PUB_DATE       INTEGER"\
        ");";
    runDBQuery(query);
}
void LRSSStorage::createItemsTable() {
    
}

void LRSSStorage::runDBQuery(sqlite3* db, std::string query, int (*callback)(void*, int, char**, char**)) {
    char* errMsg = 0;
    if (sqlite3_exec(db, query.c_str(), callback, 0, &errMsg) != SQLITE_OK) {
        fmt::print("SQL error: {}\n", errMsg);
        sqlite3_free((void*)errMsg);
    }
}

void LRSSStorage::runDBQuery(std::string query, int (*callback)(void*, int, char**, char**)) {
    sqlite3* db = openDB();
    runDBQuery(db, query, callback);
    closeDB(db);
}