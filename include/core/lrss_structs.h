#ifndef LRSS_STRUCTS_H_
#define LRSS_STRUCTS_H_

#include <string>
#include <vector>

namespace lrss {
    struct LRSSChannel {
        std::string title;
        std::string description;
        std::string link, imageLink;
        std::string copyright, language;
        std::string lastBuildDate, pubDate;
    };

    struct LRSSItem {
        std::string title;
        std::string description;
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