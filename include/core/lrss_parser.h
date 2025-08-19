#ifndef LRSS_PARSER_H_
#define LRSS_PARSER_H_

#include "lrss_structs.h"

namespace lrss {
    class LRSSParser {
    public:
        static LRSSFeed fetchAndParseFeed(std::string url);

    public: // These are public for the sake of tests. Shouldn't be used otherwise
        static std::string fetchFeedXML(std::string url);
    };
}

#endif // LRSS_PARSER_H_