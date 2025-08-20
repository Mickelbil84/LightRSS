#ifndef LRSS_FETCH_H_
#define LRSS_FETCH_H_

#include <string>

namespace lrss {
    class LRSSFetcher {
    public:
        static std::string fetchContent(std::string url);
        static bool isBadContent(std::string content);
    };

    #define LRSS_ERR_CONTENT_PREFIX ":::"
}

#endif // LRSS_FETCH_H_