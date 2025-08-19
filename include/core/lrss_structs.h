#include <string>

namespace lrss {
    struct LRSSChannel {
        std::string title;
        std::string description;
        std::string link, imageLink;
        std::string copyright;
        std::string lastBuildDate, pubDate;
        int ttl;
    };

    struct LRSSItem {
        std::string title;
        std::string description;
        std::string link;
        std::string guid;
        std::string pubDate;
    };
}