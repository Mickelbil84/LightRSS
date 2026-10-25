#include "core/lrss_structs.h"
using namespace lrss;

#include <fmt/format.h>

#define SEP1 "#################################\n"
#define SEP2 "---------------------------------\n"

std::string LRSSChannel::toString() 
{
    std::string res = "";
    res += fmt::format("Title:\t{}\n", this->title);
    res += fmt::format("Description:\t{}\n", this->description);
    res += fmt::format("Link:\t{}\n", this->link);
    res += fmt::format("Image Link:\t{}\n", this->imageLink);
    res += fmt::format("Copyright:\t{}\n", this->copyright);
    res += fmt::format("Language:\t{}\n", this->language);
    res += fmt::format("Last Build Date:\t{}\n", this->lastBuildDate);
    res += fmt::format("Publish Date:\t{}\n", this->pubDate);
    return res;
}

std::string LRSSItem::toString() 
{
    std::string res = "";
    res += fmt::format("Title:\t{}\n", this->title);
    res += fmt::format("Description;\t{}\n", this->description);
    res += fmt::format("Summary:\t{}\n", this->summary);
    res += fmt::format("Author:\t{}\n", this->author);
    res += fmt::format("Link:\t{}\n", this->link);
    res += fmt::format("GUID:\t{}\n", this->guid);
    res += fmt::format("Publish Date:\t{}\n", this->pubDate);
    return res;
}

std::string LRSSFeed::toString()
{
    std::string res = "";
    res += SEP1;
    res += this->channelInfo.toString();
    res += SEP1;
    for (LRSSItem article : this->articles) {
        res += article.toString();
        res += SEP2;
    }
    return res;
}