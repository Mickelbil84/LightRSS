#include <curl/curl.h>

#include "core/lrss_parser.h"
using namespace lrss;


LRSSFeed LRSSParser::fetchAndParseFeed(std::string url) {
    LRSSFeed feed;

    return feed;
}

// Example taken from: https://gist.github.com/alghanmi/c5d7b761b2c9ab199157
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string LRSSParser::fetchFeedXML(std::string url) {
    std::string response;
    CURL* curl = curl_easy_init();
    if (curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; Linux x86_64; rv:58.0) Gecko/20100101 Firefox/58.0");
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) response = "";
        curl_easy_cleanup(curl);
    }
    return response;
}