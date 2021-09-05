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
#include <cstdint>
#include <cstdlib>

#include <WString.h>
#include <ESPAsyncWebServer.h>
#include <esp_timer.h>

#include "webpage.h"
#include "vector.h"

#include "Widget.h"
#include "Card.h"
#include "Chart.h"
#include "Tab.h"


// ESPDASH Class
class ESPDash{
  private:
    AsyncWebServer* _server = nullptr;
    AsyncWebSocket* _ws = nullptr;

    Vector<Tab*> tabs;
    Tab* home_screen;
    uint32_t current_tab_id;
    bool stats_enabled = false;
    bool basic_auth = false;
    String username;
    String password;
    esp_timer_handle_t timer_handle;
    bool pending_update = false;

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
    Tab* getTab(uint32_t id);

    // Generate statistics layout json
    String generateStatsJSON();

    using JsonDocument = Widget::JsonDocument;
    // Generate layout for specific tab id
    JsonDocument generateLayout(uint32_t id);

    // This method is called when a card/chart is added or removed
    void refreshLayout();

  public:
    ESPDash();
    ESPDash(AsyncWebServer* server, bool enable_stats = true);

    // Enable/disable statistics
    ESPDash& displayStatistics(bool enable_stats);

    // Late initialize
    ESPDash& init(AsyncWebServer* server);

    // Set Authentication
    void setAuthentication(const char *user, const char *pass);

    // Add Tab
    void add(Tab *tab);
    // Remove Tab
    void remove(Tab *tab);

    // Add Card
    void add(Card *card);
    // Remove Card
    void remove(Card *card);

    // Add Chart
    void add(Chart *chart);
    // Remove Chart
    void remove(Chart *chart);

    // Notify client side to update values
    void sendUpdates();

    // Notify client when processor has finished its work
    void asyncUpdates();
  
    ~ESPDash();

    friend class Tab;
};

#endif
