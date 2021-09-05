#include "Widget.h"
#include <Arduino.h>

#include "ESPDash.h"
#include "Tab.h"

#if defined(ESP8266)
#define MAKE_ID() RANDOM_REG32
#elif defined(ESP32)
#define MAKE_ID() esp_random()
#endif

Widget::Widget(ESPDash* dash, const int type, const char* name):
_dashboard(dash),
_tab(nullptr),
_id(MAKE_ID()),
_type(type),
_name(name)
{
}
Widget::Widget(Tab* tab, const int type, const char* name):
_dashboard(nullptr),
_tab(tab),
_id(MAKE_ID()),
_type(type),
_name(name)
{
  _dashboard = _tab->_dashboard;
}

bool Widget::isChanged() const {
  return _changed;
}

uint32_t Widget::getId() const {
  return _id;
}

void Widget::makeChanged() {
  _changed = true;
  _dashboard->asyncUpdates();
}