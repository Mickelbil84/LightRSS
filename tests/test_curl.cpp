#include <catch.hpp>
#include <fmt/core.h>
#include "constants.h"
#include "core/lrss_parser.h"
using namespace lrss;

TEST_CASE("Fetch example.com", "[curl]") {
    std::string response = LRSSParser::fetchFeedXML(LRSS_TEST_URL_EXAMPLECOM);
    REQUIRE(response.size() > 0);
    REQUIRE(response.find("<h1>Example Domain</h1>") != std::string::npos);
}
TEST_CASE("Fetch ynet", "[curl]") {
    std::string response = LRSSParser::fetchFeedXML(LRSS_TEST_URL_YNET);
    REQUIRE(response.size() > 0);
    REQUIRE(response.find("<h1>Example Domain</h1>") == std::string::npos); // RSS shouldn't have the example.com header
    REQUIRE(response.find("<rss version=") != std::string::npos);
}
TEST_CASE("Fetch multiple RSS sites", "[curl]") {
    // Test that we can fetch multiple different sites in the same function/loop
    // NYT was especially tricky
    const char* urls[] = {LRSS_TEST_URL_YNET, LRSS_TEST_URL_BBC, LRSS_TEST_URL_IGN, LRSS_TEST_URL_NYT, LRSS_TEST_URL_VERGE};
    for (size_t i = 0; i < sizeof(urls) / sizeof(char*); ++i) {
        std::string response = LRSSParser::fetchFeedXML(urls[i]);
        // fmt::print("{}\n{}\n-----------------------\n", urls[i], response);
        REQUIRE(response.size() > 0);
        if (response.find("/Atom\"") == std::string::npos) { // If not atom, should be RSS
            REQUIRE(response.find("<rss") != std::string::npos);
            REQUIRE(response.find(" version=") != std::string::npos);
            REQUIRE(response.find("</rss>") != std::string::npos);
        }
    }
}