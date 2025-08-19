#include "lrss_structs.h"

namespace lrss {
    class LRSSParser {
    public:
        static LRSSFeed fetchAndParseFeed(std::string url);
    private:

        static std::string fetchFeedXML(std::string url);
    };
}