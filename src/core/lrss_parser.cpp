#include "core/lrss_parser.h"
using namespace lrss;


LRSSFeed LRSSParser::parseFeed(std::string guid, std::string content) {
    LRSSContentType ct = decideContentType(content);
    if (ct == LRSSContentType::LRSS_RSS)
        return parseRSSFeed(guid, content);
    if (ct == LRSSContentType::LRSS_ATOM)
        return parseAtomFeed(guid, content);
    return {};
}

LRSSContentType LRSSParser::decideContentType(std::string content) {
    // Test for RSS
    bool rssTest1 = content.find("<rss") != std::string::npos;
    bool rssTest2 = content.find(" version=") != std::string::npos;
    bool rssTest3 = content.find("</rss>") != std::string::npos;
    if (rssTest1 && rssTest2 && rssTest3)
        return LRSSContentType::LRSS_RSS;

    // Test for Atom
    bool atomTest1 = content.find("/Atom\"") != std::string::npos;
    if (atomTest1)
        return LRSSContentType::LRSS_ATOM;

    return LRSSContentType::LRSS_INVALID;
}

xmlDocPtr LRSSParser::rawParseXML(std::string content) {
    return xmlParseMemory(&content.c_str()[0], (int)content.size());
}

void LRSSParser::freeXML(xmlDocPtr doc) {
    xmlFreeDoc(doc);
}