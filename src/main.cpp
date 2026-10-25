#include <fmt/core.h>

#include "core/lrss_fetcher.h"
#include "core/lrss_parser.h"
using namespace lrss;

#define SEP1 "#################################\n"
#define SEP2 "---------------------------------\n"

int main() 
{
    // std::string URL = "https://www.ynet.co.il/Integration/StoryRss2.xml";
    std::string URL = "https://feeds.feedburner.com/ign/all";
    LRSSParser parser;
    LRSSFetcher fetcher;
    
    std::string content = fetcher.fetchContent(URL);
    LRSSContentType contentType = parser.decideContentType(content);
    switch (contentType) {
        case LRSS_RSS: fmt::print("LRSSContentType: LRSS_RSS\n"); break;
        case LRSS_ATOM: fmt::print("LRSSContentType: LRSS_ATOM\n"); break;
        default: fmt::print("LRSSContentType: LRSS_INVALID\n"); break;
    }
    LRSSFeed feed = parser.parseFeed(content);

    if (feed.invalid) {
        fmt::print("Fetch invalid! Exiting...\n");
    }

    fmt::print(SEP1);
    fmt::print("URL:\t{}\n", URL);
    fmt::print("Title:\t{}\n", feed.channelInfo.title);
    fmt::print("Description:\t{}\n", feed.channelInfo.description);
    fmt::print("Link:\t{}\n", feed.channelInfo.link);
    fmt::print("Image Link:\t{}\n", feed.channelInfo.imageLink);
    fmt::print("Copyright:\t{}\n", feed.channelInfo.copyright);
    fmt::print("Language:\t{}\n", feed.channelInfo.language);
    fmt::print("Last Build Date:\t{}\n", feed.channelInfo.lastBuildDate);
    fmt::print("Publish Date:\t{}\n", feed.channelInfo.pubDate);
    fmt::print(SEP1);
    fmt::print(SEP1);

    for (LRSSItem article : feed.articles) {
        fmt::print("Title:\t{}\n", article.title);
        fmt::print("Description;\t{}\n", article.description);
        fmt::print("Summary:\t{}\n", article.summary);
        fmt::print("Author:\t{}\n", article.author);
        fmt::print("Link:\t{}\n", article.link);
        fmt::print("GUID:\t{}\n", article.guid);
        fmt::print("Publish Date:\t{}\n", article.pubDate);
        fmt::print(SEP2);
    }

    return 0;
}