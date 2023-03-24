#include "../arduino-pico/libraries/WiFi/src/WiFi.h"
#include "../arduino-pico/libraries/HTTPClient/src/HTTPClient.h"
#ifndef STASSID
#define STASSID "your-ssid"
#define STAPSK "your-password"
#endif

class HTTPRequests
{
public:
    int countRequests = 0;

    void setup()
    {

        WiFi.begin(STASSID, STAPSK);

        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            printf(".");
        }
        printf("");
        printf("Connected! IP address: ");
        printf(WiFi.localIP());
    }

    void loop()
    {
        // wait for WiFi connection
        if ((WiFi.status() == WL_CONNECTED))
        {

            HTTPClient http;
            http.setInsecure();

            printf("[HTTP] begin...\n");
            // configure target server and url
            http.begin("https://httpbin.org/post");
            http.addHeader("Content-Type", "application/json");

            printf("[HTTP] POST...\n");
            // start connection and send HTTP header and body
            int httpCode = http.POST("{\"hello\":\"world\"}");

            // httpCode will be negative on error
            if (httpCode > 0)
            {
                // HTTP header has been send and Server response header has been handled
                printf("[HTTP] POST... code: %d\n", httpCode);

                // file found at server
                if (httpCode == HTTP_CODE_OK)
                {
                    const String &payload = http.getString();
                    printf("received payload:\n<<");
                    printf(payload);
                    printf(">>");
                }
            }
            else
            {
                printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
            }

            http.end();
        }

        delay(10000);
    }
};