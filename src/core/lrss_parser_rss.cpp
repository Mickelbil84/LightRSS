#include "core/lrss_parser.h"
using namespace lrss;

#include <fmt/core.h>

LRSSFeed LRSSParser::parseRSSFeed(std::string content) {
    LRSSFeed feed;

    xmlDocPtr doc = rawParseXML(content);
    xmlNodePtr root = xmlDocGetRootElement(doc);
        parseRSSRootNode(root, &feed);
    freeXML(doc);
    return feed;
}

void LRSSParser::parseRSSRootNode(xmlNodePtr rootNode, LRSSFeed* feed) {
    if (std::string((char*)rootNode->name) != "rss") {
        feed->invalid = true;
        return;
    }

    xmlNodePtr channelNode = nullptr;
    for (xmlNodePtr curr = rootNode->children; curr != nullptr; curr = curr->next) {
        if (std::string((char*)curr->name) == "channel") {
            channelNode = curr;
            break;
        }
    }
    if (!channelNode) {
        feed->invalid = true;
        return;
    }

    parseRSSChannelNode(channelNode, feed);
}
void LRSSParser::parseRSSChannelNode(xmlNodePtr channelNode, LRSSFeed* feed) {
    for (xmlNodePtr curr = channelNode->children; curr != nullptr; curr = curr->next) {
        
    }

}
void LRSSParser::parseRSSItemNode(xmlNodePtr itemNode, LRSSFeed* feed) {

}