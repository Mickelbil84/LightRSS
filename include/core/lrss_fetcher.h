#ifndef LRSS_FETCH_H_
#define LRSS_FETCH_H_

#include <string>

#define LRSS_ERR_CONTENT_PREFIX ":::"

namespace lrss {
    class LRSSFetcher {
    public:
        static std::string fetchContent(std::string url);
        static bool isBadContent(std::string content);
    };
}

#endif // LRSS_FETCH_H_