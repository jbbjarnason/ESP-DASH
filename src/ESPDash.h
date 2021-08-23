#pragma once

#include <memory>
#include <WString.h>

class AsyncWebServer;

class ESPDashImpl;
class TabImpl;
class CardImpl;
class ChartImpl;

namespace ESPDash {

class Tab;
class Card;
class Chart;

class ESPDash {
public:
  ESPDash(AsyncWebServer* server);

  // Set Authentication
  ESPDash& setAuthentication(const char *user, const char *pass);

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

  friend class Tab;
  friend class Card;
  friend class Chart;
private:
  std::shared_ptr<ESPDashImpl> _pimpl;

};

class Tab {
public:
  Tab(ESPDash *dashboard, const char* name, const char* navbarName, const char* header);

  // Add Card
  Tab& add(Card *card);
  // Remove Card
  Tab& remove(Card *card);

  // Add Chart
  Tab& add(Chart *chart);
  // Remove Chart
  Tab& remove(Chart *chart);

  friend class ESPDash;
  friend class Card;
  friend class Chart;
private:
  std::shared_ptr<TabImpl> _pimpl;
};

enum {
  GENERIC_CARD,
  TEMPERATURE_CARD,
  HUMIDITY_CARD,
  STATUS_CARD,
  SLIDER_CARD,
  BUTTON_CARD,
  PROGRESS_CARD
};
class Card {
public:
  Card(ESPDash *dashboard, const int type, const char* name, const char* symbol = "", const int min = 0, const int max = 0);
  Card(Tab *tab, const int type, const char* name, const char* symbol = "", const int min = 0, const int max = 0);
  void attachCallback(std::function<void(int)> cb);
  void update(int value);
  void update(int value, const char* symbol);
  void update(bool value);
  void update(bool value, const char* symbol);
  void update(float value);
  void update(float value, const char* symbol);
  void update(const char* value);
  void update(const char* value, const char* symbol);
  void update(const String &value);
  void update(const String &value, const char* symbol);

  friend class ESPDash;
  friend class Tab;
private:
  std::shared_ptr<CardImpl> _pimpl;
};

enum {
  BAR_CHART,
};
class Chart {
public:
  Chart(ESPDash *dashboard, const int type, const char* name);
  Chart(Tab *tab, const int type, const char* name);
  void updateX(int arr_x[], size_t x_size);
  void updateX(float arr_x[], size_t x_size);
  void updateX(String arr_x[], size_t x_size);
  void updateY(int arr_y[], size_t y_size);
  void updateY(float arr_y[], size_t y_size);

  friend class ESPDash;
  friend class Tab;
private:
  std::shared_ptr<ChartImpl> _pimpl;
};

}