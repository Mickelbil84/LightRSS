#include <curl/curl.h>
#include <fmt/core.h>

#include "core/lrss_fetcher.h"
using namespace lrss;

// Example taken from: https://gist.github.com/alghanmi/c5d7b761b2c9ab199157
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string LRSSFetcher::fetchContent(std::string url) {
    std::string response;
    CURL* curl = curl_easy_init();
    if (curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; Linux x86_64; rv:58.0) Gecko/20100101 Firefox/58.0");
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            int responseCode = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
            response = fmt::format("{}HTTP{}|CURLCODE:={}", LRSS_ERR_CONTENT_PREFIX, responseCode, (int)res);
        }
        curl_easy_cleanup(curl);
    }
    return response;
}

bool LRSSFetcher::isBadContent(std::string content) {
    return content.find(LRSS_ERR_CONTENT_PREFIX) != std::string::npos;
}