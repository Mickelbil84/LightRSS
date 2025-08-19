#include <catch.hpp>
#include <fmt/core.h>
#include "constants.h"
#include "core/lrss_fetcher.h"
#include "core/lrss_parser.h"
using namespace lrss;

TEST_CASE("Decide content type", "[curl]") {
    const char* urls[] = {LRSS_TEST_URL_YNET, LRSS_TEST_URL_BBC, LRSS_TEST_URL_IGN, LRSS_TEST_URL_NYT, LRSS_TEST_URL_VERGE};
    const LRSSContentType types[] = {
        LRSS_RSS, LRSS_RSS, LRSS_RSS, LRSS_RSS, LRSS_ATOM
    };

    for (size_t i = 0; i < sizeof(urls) / sizeof(char*); ++i) {
        std::string response = LRSSFetcher::fetchContent(urls[i]);
        REQUIRE(LRSSParser::decideContentType(response) == types[i]);
    }
}