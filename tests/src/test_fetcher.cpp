#if __has_include(<catch.hpp>)
    #include <catch.hpp>
#else
    #include <catch2/catch.hpp>
#endif

#include <fmt/core.h>
#include "constants.h"
#include "core/lrss_fetcher.h"
#include "core/lrss_parser.h"
using namespace lrss;

TEST_CASE("Fetch example.com", "[fetcher]") {
    std::string response = LRSSFetcher::fetchContent(LRSS_TEST_URL_EXAMPLECOM);
    REQUIRE(response.size() > 0);
    REQUIRE(response.find("<h1>Example Domain</h1>") != std::string::npos);
}
TEST_CASE("Fetch ynet", "[fetcher]") {
    std::string response = LRSSFetcher::fetchContent(LRSS_TEST_URL_YNET);
    REQUIRE(response.size() > 0);
    REQUIRE(response.find("<h1>Example Domain</h1>") == std::string::npos); // RSS shouldn't have the example.com header
    REQUIRE(response.find("<rss version=") != std::string::npos);
}
TEST_CASE("Fetch multiple RSS sites", "[fetcher]") {
    // Test that we can fetch multiple different sites in the same function/loop
    // NYT was especially tricky
    const char* urls[] = {LRSS_TEST_URL_YNET, LRSS_TEST_URL_BBC, LRSS_TEST_URL_IGN, LRSS_TEST_URL_NYT, LRSS_TEST_URL_VERGE};
    for (size_t i = 0; i < sizeof(urls) / sizeof(char*); ++i) {
        std::string response = LRSSFetcher::fetchContent(urls[i]);
        // fmt::print("{}\n{}\n-----------------------\n", urls[i], response);
        REQUIRE(response.size() > 0);
        REQUIRE(LRSSParser::decideContentType(response) != LRSSContentType::LRSS_INVALID);
    }
}