#include <fmt/core.h>

#include "core/lrss_fetcher.h"
#include "core/lrss_parser.h"
using namespace lrss;


int main() 
{
    // std::string URL = "https://www.ynet.co.il/Integration/StoryRss2.xml";
    std::string URL = "https://feeds.feedburner.com/ign/all";
    LRSSFetcher fetcher;
    std::string content = fetcher.fetchContent(URL);

    LRSSParser parser;
    LRSSFeed feed = parser.parseFeed(content);
    fmt::print("{}", feed.toString());

    return 0;
}