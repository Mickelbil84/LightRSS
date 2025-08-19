#ifndef LRSS_PARSER_H_
#define LRSS_PARSER_H_

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "lrss_structs.h"

namespace lrss {
    class LRSSParser {
    public:
        static LRSSFeed fetchAndParseFeed(std::string url);

    private:
        
    };
}

#endif // LRSS_PARSER_H_