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

        std::string toString();
    };

    struct LRSSItem {
        std::string title;
        std::string description, summary;
        std::string author;
        std::string link;
        std::string guid;
        std::string pubDate;

        std::string toString();
    };

    struct LRSSFeed {
        LRSSChannel channelInfo;
        std::vector<LRSSItem> articles;
        bool invalid = false;

        std::string toString();
    };
}

#endif // LRSS_STRUCTS_H_