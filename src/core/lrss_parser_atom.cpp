#include "core/lrss_parser.h"
using namespace lrss;

LRSSFeed LRSSParser::parseAtomFeed(std::string guid, std::string content) {
    LRSSFeed feed;
    feed.channelInfo.guid = guid;

    xmlDocPtr doc = rawParseXML(content);
    xmlNodePtr root = xmlDocGetRootElement(doc);

    BEGIN_CHILDREN_FOR(root)
        XML_PROPERTY_TO_STRUCT(feed.channelInfo, title, title);
        XML_PROPERTY_TO_STRUCT(feed.channelInfo, description, subtitle);
        XML_PROPERTY_TO_STRUCT(feed.channelInfo, link, id);
        XML_PROPERTY_TO_STRUCT(feed.channelInfo, imageLink, icon);
        XML_PROPERTY_TO_STRUCT(feed.channelInfo, lastBuildDate, updated);
        if (NODE_NAME(curr) == "entry")
            parseAtomEntryNode(curr, &feed);
    END_CHILDREN_FOR()

    freeXML(doc);
    return feed;
}

void LRSSParser::parseAtomEntryNode(xmlNodePtr entryNode, LRSSFeed* feed) {
    LRSSItem item;

    BEGIN_CHILDREN_FOR(entryNode)
        XML_PROPERTY_TO_STRUCT(item, title, title);
        XML_PROPERTY_TO_STRUCT(item, description, content);
        XML_PROPERTY_TO_STRUCT(item, summary, summary);
        XML_PROPERTY_TO_STRUCT(item, author, author);
        XML_PROPERTY_TO_STRUCT(item, link, id);
        XML_PROPERTY_TO_STRUCT(item, guid, id);
        XML_PROPERTY_TO_STRUCT(item, pubDate, published);
    END_CHILDREN_FOR()

    feed->articles.push_back(item);
}