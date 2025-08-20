#ifndef LRSS_STRUCTS_H_
#define LRSS_STRUCTS_H_

#include <string>
#include <vector>

namespace lrss {
    struct LRSSChannel {
        std::string guid; // This should be the subscription url (in case not present in 'link' or different)
        std::string title;
        std::string description;
        std::string link, imageLink;
        std::string copyright, language;
        std::string lastBuildDate, pubDate;
    };

    struct LRSSItem {
        std::string title;
        std::string description, summary;
        std::string author;
        std::string link;
        std::string guid;
        std::string pubDate;
    };

    struct LRSSFeed {
        LRSSChannel channelInfo;
        std::vector<LRSSItem> articles;
        bool invalid = false;
    };
}

#endif // LRSS_STRUCTS_H_