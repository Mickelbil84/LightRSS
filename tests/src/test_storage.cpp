#if __has_include(<catch.hpp>)
    #include <catch.hpp>
#else
    #include <catch2/catch_all.hpp>
#endif
#include <fmt/core.h>
#include "constants.h"
#include "core/lrss_fetcher.h"
#include "core/lrss_parser.h"
#include "core/lrss_storage.h"
using namespace lrss;

TEST_CASE("Store subscriptions", "[storage]") {
    const char* urls[] = {LRSS_TEST_URL_YNET, LRSS_TEST_URL_BBC, LRSS_TEST_URL_IGN, LRSS_TEST_URL_NYT, LRSS_TEST_URL_VERGE};
    for (size_t i = 0; i < sizeof(urls) / sizeof(char*); ++i) {
        LRSSStorage::addNewSubscription(urls[i]);
        LRSSStorage::addNewSubscription(urls[i]);
        LRSSStorage::addNewSubscription(urls[i]);
    }

    int counts[] = {0, 0, 0, 0, 0};
    std::vector<std::string> subscriptions = LRSSStorage::getSubscriptions();
    for (std::string url : subscriptions) {
        for (size_t i = 0; i < sizeof(urls) / sizeof(char*); ++i) {
            if (url == urls[i]) {
                counts[i]++;
                break;
            }
        }
    }
    for (size_t i = 0; i < sizeof(urls) / sizeof(char*); ++i) {
        REQUIRE(counts[i] == 1);
    }
}