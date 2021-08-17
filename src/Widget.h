#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include <cstdint>


#define WIDGET_JSON_SIZE 1024

struct WidgetNames {
  int value;
  const char* type;
};

class Tab;

class Widget {
  protected:
    uint32_t _id;
    String _name;
    int   _type;
    bool  _changed;

#if ARDUINOJSON_VERSION_MAJOR == 6
    using JsonDocument = DynamicJsonDocument; // TODO: this should be in the else statement
#else
    using JsonDocument = DynamicJsonBuffer;
#endif

    virtual JsonDocument generateLayout() = 0;
    virtual JsonDocument generateUpdate() = 0;

  public:
    Widget() {
      #if defined(ESP8266)
        _id = RANDOM_REG32;
      #elif defined(ESP32)
        _id = esp_random();
      #endif
    };
    bool isChanged() {
      return _changed;
    };
    uint32_t getId() const {
      return _id;
    };
    virtual ~Widget() = default;

    friend class Tab;
};