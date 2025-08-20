#ifndef LRSS_STORAGE_H_
#define LRSS_STORAGE_H_

#include <map>
#include <set>
#include <vector>
#include <sqlite3.h>
#include <fmt/core.h>

namespace lrss {
    class LRSSStorage {
    public:
        static void addNewSubscription(std::string url);
        static std::vector<std::string> getSubscriptions();

    private:
        static constexpr const char* LRSS_STORAGE_PATH = "storage.db3";

        static void createSubscriptionsTable();
        static void createChannelsTable();
        static void createItemsTable();

        static sqlite3* openDB();
        static void closeDB(sqlite3* db);
        static void runDBQuery(sqlite3* db, std::string query, int (*callback)(void*, int, char**, char**) = nullptr);
        static void runDBQuery(std::string query, int (*callback)(void*, int, char**, char**) = nullptr);

        static int _getSubscriptionsCallback(void* data, int argc, char** argv, char** azColName);
        static std::vector<std::pair<std::string, int>> _getSubscriptionsResult;
    };
}

#endif // LRSS_STORAGE_H_