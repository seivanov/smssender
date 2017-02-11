#include <iostream>

/* libcurl4-gnutls-dev */
#include <curl/curl.h>
#include <string.h>

struct curl_fetch_st {
    char *payload;
    size_t size;
};

size_t curl_callback (void *contents, size_t size, size_t nmemb, void *userp) {

    size_t realsize = size * nmemb;
    struct curl_fetch_st *p = (struct curl_fetch_st *) userp;

    if(p->payload == NULL) {

        p->payload = new char[realsize+1];
        memcpy(p->payload, contents, realsize);
        p->size = realsize;

    } else {

        char *d = new char[p->size + realsize + 1];
        memcpy(d, p->payload, p->size);
        memcpy(&d[p->size], contents, realsize);
        delete p->payload;
        p->payload = d;
        p->size = p->size + realsize;

    }

    return realsize;

}


int main() {

    CURL *ch;
    char url[] = "https://smsc.ru/sys/send.php?login=<login>&psw=<password>&phones=<phones>&mes=<message>&cost=1";
    int rcode;
    struct curl_fetch_st curl_fetch;
    struct curl_fetch_st *cf = &curl_fetch;
    cf->size = 0;
    cf->payload = NULL;

    if ((ch = curl_easy_init()) == NULL) {
        fprintf(stderr, "ERROR: Failed to create curl handle in fetch_session");
        return 1;
    }

    curl_easy_setopt(ch, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(ch, CURLOPT_URL, url);
    curl_easy_setopt(ch, CURLOPT_WRITEFUNCTION, curl_callback);
    curl_easy_setopt(ch, CURLOPT_WRITEDATA, (void *) cf);

    std::cout << "ping" << std::endl;

    rcode = curl_easy_perform(ch);

    std::cout << "ping" << std::endl;

    std::cout << cf->payload << std::endl;

    std::cout << rcode << std::endl;

    return 0;
}