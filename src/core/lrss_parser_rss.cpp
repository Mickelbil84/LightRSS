#include "core/lrss_parser.h"
using namespace lrss;

#include <fmt/core.h>



LRSSFeed LRSSParser::parseRSSFeed(std::string guid, std::string content) {
    LRSSFeed feed;
    feed.channelInfo.guid = guid;

    xmlDocPtr doc = rawParseXML(content);
    xmlNodePtr root = xmlDocGetRootElement(doc);
        parseRSSRootNode(root, &feed);
    freeXML(doc);
    return feed;
}

void LRSSParser::parseRSSRootNode(xmlNodePtr rootNode, LRSSFeed* feed) {
    if (NODE_NAME(rootNode) != "rss") {
        feed->invalid = true;
        return;
    }

    xmlNodePtr channelNode = nullptr;
    BEGIN_CHILDREN_FOR(rootNode)
        if (NODE_NAME(curr) == "channel") {
            channelNode = curr;
            break;
        }
    END_CHILDREN_FOR()
    if (!channelNode) {
        feed->invalid = true;
        return;
    }

    parseRSSChannelNode(channelNode, feed);
}
void LRSSParser::parseRSSChannelNode(xmlNodePtr channelNode, LRSSFeed* feed) {
    BEGIN_CHILDREN_FOR(channelNode)
        XML_PROPERTY_TO_STRUCT(feed->channelInfo, title, title);
        XML_PROPERTY_TO_STRUCT(feed->channelInfo, description, description);
        XML_PROPERTY_TO_STRUCT(feed->channelInfo, link, link);
        XML_PROPERTY_TO_STRUCT(feed->channelInfo, copyright, copyright);
        XML_PROPERTY_TO_STRUCT(feed->channelInfo, lastBuildDate, lastBuildDate);
        XML_PROPERTY_TO_STRUCT(feed->channelInfo, pubDate, pubDate);
        XML_PROPERTY_TO_STRUCT(feed->channelInfo, language, language);
        if (NODE_NAME(curr) == "image") 
            parseRSSChannelImageNode(curr, feed);
        if (NODE_NAME(curr) == "item")
            parseRSSItemNode(curr, feed);
    END_CHILDREN_FOR()
}
void LRSSParser::parseRSSChannelImageNode(xmlNodePtr imageNode, LRSSFeed* feed) {
    BEGIN_CHILDREN_FOR(imageNode)
        XML_PROPERTY_TO_STRUCT(feed->channelInfo, imageLink, url);
    END_CHILDREN_FOR()
}
void LRSSParser::parseRSSItemNode(xmlNodePtr itemNode, LRSSFeed* feed) {
    LRSSItem item;

    BEGIN_CHILDREN_FOR(itemNode)
        XML_PROPERTY_TO_STRUCT(item, title, title);
        XML_PROPERTY_TO_STRUCT(item, description, description);
        XML_PROPERTY_TO_STRUCT(item, link, link);
        XML_PROPERTY_TO_STRUCT(item, guid, guid);
        XML_PROPERTY_TO_STRUCT(item, pubDate, pubDate);
    END_CHILDREN_FOR()
    
    feed->articles.push_back(item);
}