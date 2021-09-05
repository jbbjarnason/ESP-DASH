#pragma once

#include <cstdint>
#include <WString.h>

#define WIDGET_JSON_SIZE 1024

struct WidgetNames {
  int value;
  const char* type;
};

class ESPDash;
class Tab;
namespace ArduinoJson {
  template<typename allocator>
  class BasicJsonDocument;
  class DefaultAllocator;
}

class Widget {
  public:
    using JsonDocument = ArduinoJson::BasicJsonDocument<ArduinoJson::DefaultAllocator>;

    Widget(ESPDash*, const int type, const char* name);
    Widget(Tab*, const int type, const char* name);
    bool isChanged() const;
    uint32_t getId() const;
    virtual ~Widget() = default;

  protected:
    ESPDash *_dashboard;
    Tab *_tab;

    uint32_t _id;
    int   _type;
    String _name;
    bool  _changed;

    virtual JsonDocument generateLayout() = 0;
    virtual JsonDocument generateUpdate() = 0;

    void makeChanged();

    friend class Tab;
};
