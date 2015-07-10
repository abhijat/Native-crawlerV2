#include "string_buffer.h"
#include <curl/curl.h>

size_t write_callback(void* content, size_t size, size_t nmemb, void* data)
{
    size_t total = size * nmemb;
    string_buffer_t* s = (string_buffer_t*) data;
    copy_sbuf(s, content, total);
    return total;
}

string_buffer_t* fetch_url_memory(const char* url)
{
    CURL* curl = curl_easy_init();
    string_buffer_t* s = new_sbuf(0);
    if (curl) {

        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, 
                "reddit native crawler by /u/abhijat0");

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, s);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        CURLcode result = curl_easy_perform(curl);
        if (result != CURLE_OK) {
            printf("Failed :: %s\n", curl_easy_strerror(result));
        }
        curl_easy_cleanup(curl);
    }
    return s;
}

int main()
{
    string_buffer_t* s = fetch_url_memory("http://www.reddit.com/r/all");
    printf("%s\n", s->buffer);
    free_sbuf(&s);
}
