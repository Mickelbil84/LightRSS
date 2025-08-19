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
        static void parseRSSRootNode(xmlNodePtr rootNode, LRSSFeed* feed);
        static void parseRSSChannelNode(xmlNodePtr channelNode, LRSSFeed* feed);
        static void parseRSSChannelImageNode(xmlNodePtr imageNode, LRSSFeed* feed);
        static void parseRSSItemNode(xmlNodePtr itemNode, LRSSFeed* feed);

        static LRSSFeed parseAtomFeed(std::string content);
        static void parseAtomEntryNode(xmlNodePtr entryNode, LRSSFeed* feed);

        static xmlDocPtr rawParseXML(std::string content);
        static void freeXML(xmlDocPtr doc); // Release the memory
    };
}

#define XML_STDSTR(s) (std::string((char*)(s)))
#define NODE_NAME(n) (XML_STDSTR((n)->name))
#define NODE_CONTENT(n) (XML_STDSTR(xmlNodeGetContent((n))))

// Get struct "pointer" (e.g., `feed->channelInfo`, `article`)
// Get the property name as it appears in the struct and in the xml
// Then take the `curr` node content from the xml into the correct location/offset in the struct.
#define XML_PROPERTY_TO_STRUCT(ptr, structName, xmlName) {\
    if (NODE_NAME(curr) == #xmlName) {\
        ptr.##structName = NODE_CONTENT(curr);\
    }\
}

#define BEGIN_CHILDREN_FOR(node) for (xmlNodePtr curr = node->children; curr != nullptr; curr = curr->next) {
#define END_CHILDREN_FOR() }

#endif // LRSS_PARSER_H_