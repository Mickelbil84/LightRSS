#include <catch.hpp>
#include <fmt/core.h>
#include "constants.h"
#include "core/lrss_fetcher.h"
#include "core/lrss_parser.h"
using namespace lrss;

TEST_CASE("Decide content type", "[parser]") {
    const char* urls[] = {LRSS_TEST_URL_YNET, LRSS_TEST_URL_BBC, LRSS_TEST_URL_IGN, LRSS_TEST_URL_NYT, LRSS_TEST_URL_VERGE};
    const LRSSContentType types[] = {
        LRSS_RSS, LRSS_RSS, LRSS_RSS, LRSS_RSS, LRSS_ATOM
    };

    for (size_t i = 0; i < sizeof(urls) / sizeof(char*); ++i) {
        std::string response = LRSSFetcher::fetchContent(urls[i]);
        REQUIRE(LRSSParser::decideContentType(response) == types[i]);
    }
}

TEST_CASE("Parsing YNET feed (RSS)", "[parser]") {
    std::string content = LRSSFetcher::fetchContent(LRSS_TEST_URL_YNET);
    LRSSFeed ynetFeed = LRSSParser::parseFeed(content);

    REQUIRE_FALSE(ynetFeed.invalid);
    REQUIRE(ynetFeed.channelInfo.copyright == "Ynet - news and content from Israel (Yedioth Ahronoth web site)");
    REQUIRE(ynetFeed.channelInfo.language == "he");
    REQUIRE(ynetFeed.articles.size() > 10);

    LRSSItem item = ynetFeed.articles[0];
    REQUIRE(item.guid.find("https://www.ynet.co.il/news/article") != std::string::npos);
}

TEST_CASE("Parsing Verge feed (Atom)", "[parser]") {
    std::string content = LRSSFetcher::fetchContent(LRSS_TEST_URL_VERGE);
    LRSSFeed vergeFeed = LRSSParser::parseFeed(content);

    REQUIRE_FALSE(vergeFeed.invalid);
    REQUIRE(vergeFeed.channelInfo.title == "The Verge");
    REQUIRE(vergeFeed.channelInfo.description == "The Verge is about technology and how it makes us feel. Founded in 2011, we offer our audience everything from breaking news to reviews to award-winning features and investigations, on our site, in video, and in podcasts.");
    REQUIRE(vergeFeed.articles.size() > 5);

    LRSSItem item = vergeFeed.articles[0];
    REQUIRE(item.guid.find("https://www.theverge.com/") != std::string::npos);
    REQUIRE(item.pubDate.size() > 0);
    REQUIRE(item.description.size() > 0);
}