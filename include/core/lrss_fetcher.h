#ifndef LRSS_FETCH_H_
#define LRSS_FETCH_H_

#include <string>

namespace lrss {
    class LRSSFetcher {
    public:
        static std::string fetchContent(std::string url);
    };
}

#endif // LRSS_FETCH_H_