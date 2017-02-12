#include <iostream>

/* libcurl4-gnutls-dev */
#include <curl/curl.h>
#include <string.h>
#include <openssl/md5.h>

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

std::string md5(char *str) {

    std::string result;

    MD5_CTX md5handler;
    unsigned char *md5digest = new unsigned char[MD5_DIGEST_LENGTH];

    MD5_Init(&md5handler);
    MD5_Update(&md5handler, str, strlen(str));
    MD5_Final(md5digest,&md5handler);

    int i = 0;
    char p[10];
    for (i=0;i<MD5_DIGEST_LENGTH;i++) {
        sprintf(p, "%02x", md5digest[i]);
        result.append(p);
    };

    return result;

}


int main() {

    char tmp[] = "185031";
    std::string passwd = md5(tmp);

    CURL *ch;
    char url[] = "https://smsc.ru/sys/send.php?login=anton_t001&psw=<password>&phones=89111234545&mes=test&cost=1";

    std::string pre_url("https://smsc.ru/sys/send.php?login=anton_t001&psw=");
    pre_url += passwd + "&phones=89111234545&mes=test&cost=1";

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
    curl_easy_setopt(ch, CURLOPT_URL, pre_url.c_str());
    curl_easy_setopt(ch, CURLOPT_WRITEFUNCTION, curl_callback);
    curl_easy_setopt(ch, CURLOPT_WRITEDATA, (void *) cf);

    std::cout << "ping" << std::endl;

    rcode = curl_easy_perform(ch);

    std::cout << "ping" << std::endl;

    std::cout << cf->payload << std::endl;

    std::cout << rcode << std::endl;

    return 0;
}