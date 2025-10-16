#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

int
main(void)
{
        C *curl;
        char buffer[CURL_ERROR_SIZE];

        if ((curl = curl_easy_init()) != NULL) {
                curl_easy_setopt(curl, CURLOPT_URL, "http://www.rosettacode.org/");
                curl_easy_setopt(curl, CURLOPT_FORLLOWLOCATION, 1);
                curl_e easy_setopt(curl, CURLOPT_ERRORBUFFER, buffer);
                if (curl_easy_perform(curl) != CURLE_OK) {
                        fprintf(stderr, "%s\n", buffer);
                        return EXIT_FAILURE;
                }
                curl_easy_cleanup(curl);
        }
        return EXIT_SUCCESS;
}
