#ifndef LRSS_PARSER_H_
#define LRSS_PARSER_H_

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "lrss_structs.h"

namespace lrss {
    enum LRSSContentType {
        LRSS_RSS, LRSS_ATOM, LRSS_INVALID
    };

    class LRSSParser {
    public:
        static LRSSFeed parseFeed(std::string content);
        static LRSSContentType decideContentType(std::string content);

    private:
        static LRSSFeed parseRSSFeed(std::string content);
        static LRSSFeed parseAtomFeed(std::string content);

        xmlDocPtr rawParseXML(std::string content);
    };
}

#endif // LRSS_PARSER_H_