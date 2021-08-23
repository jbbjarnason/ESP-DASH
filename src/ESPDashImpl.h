/*
____ ____ ___  ___  ____ ____ _  _ 
|___ [__  |__] |  \ |__| [__  |__| 
|___ ___] |    |__/ |  | ___] |  | 
                                   
ESP-DASH V3
---------------------
Author: Ayush Sharma
First Commit: Nov 5, 2017
Github URL: https://github.com/ayushsharma82/ESP-DASH

*/

#ifndef ESPDash_h
#define ESPDash_h

#include <functional>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "Arduino.h"
#include "stdlib_noniso.h"
#include "webpage.h"
#include "vector.h"

#if defined(ESP8266)
    #define HARDWARE "ESP8266"
    #include "ESP8266WiFi.h"
    #include "ESPAsyncTCP.h"
#elif defined(ESP32)
    #define HARDWARE "ESP32"
    #include "WiFi.h"
    #include "AsyncTCP.h"
#endif

#include "ESPAsyncWebServer.h"
#include "ArduinoJson.h"
#include "Widget.h"
#include "CardImpl.h"
#include "ChartImpl.h"
#include "TabImpl.h"


// ESPDASH Class
class ESPDashImpl{
  private:
    AsyncWebServer* _server = nullptr;
    AsyncWebSocket* _ws = nullptr;

    Vector<TabImpl*> tabs;
    TabImpl* home_screen;
    uint32_t current_tab_id;
    bool stats_enabled = false;
    bool basic_auth = false;
    const char *username;
    const char *password;

    using OnWebServerRequest = std::function<void(AsyncWebServerRequest*)>;
    OnWebServerRequest onWebServerRequest();
    using OnWebSocketEvent = std::function<void(
            AsyncWebSocket*,
            AsyncWebSocketClient*,
            AwsEventType,
            void*,
            uint8_t*,
            size_t)>;
    OnWebSocketEvent onWebSocketEvent();

    // Get tab pointer from tab id
    TabImpl* getTab(uint32_t id);

    // Propagate event to cards in play
    void resolveCardCallback(uint32_t id, int value);

    // Generate statistics layout json
    String generateStatsJSON();

    using JsonDocument = Widget::JsonDocument;
    // Generate layout for specific tab id
    JsonDocument generateLayout(uint32_t id);

  public:

    ESPDashImpl(AsyncWebServer* server, bool enable_stats = true);

    // Set Authentication
    void setAuthentication(const char *user, const char *pass);

    // Add Tab
    void add(TabImpl *tab);
    // Remove Tab
    void remove(TabImpl *tab);

    // Add Card
    void add(CardImpl *card);
    // Remove Card
    void remove(CardImpl *card);

    // Add Chart
    void add(ChartImpl *chart);
    // Remove Chart
    void remove(ChartImpl *chart);

    // Notify client side to update values
    void sendUpdates();

    // This method is called when a card/chart is added or removed. Internally
    void refreshLayout();
  
    ~ESPDashImpl();
};

#endif
