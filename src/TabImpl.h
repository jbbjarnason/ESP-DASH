#ifndef __TAB_H
#define __TAB_H

#include <Arduino.h>
#include <ArduinoJson.h>

#include "vector.h"
#include "Widget.h"
#include "CardImpl.h"
#include "ChartImpl.h"

// Forward Declaration
class ESPDashImpl;

// Tab Class
class TabImpl {
  private:
    ESPDashImpl *_dashboard;

    uint32_t _id;
    String _name;
    String _navbarName;
    String _header;
    Vector<CardImpl*> _cards;
    Vector<ChartImpl*> _charts;

    // Helper functions
    using JsonDocument = Widget::JsonDocument;
    JsonDocument makeDocument(const String& command);
    template<class Object>
    void mergeEntitiesToJSON(Vector<Object*>& container, JsonArray& jsonEntities, bool changeOnly);



    // This method is called when a card/chart is added or removed
    void refreshLayout();

    // Add/remove either Card or Chart
    template<class Object>
    TabImpl& add(Object *object, Vector<Object*> &container);

    template<class Object>
    TabImpl& remove(Object *object, Vector<Object*> &container);

  public:
    TabImpl(ESPDashImpl *dashboard, const char* name, const char* navbarName, const char* header);

    // Add Card
    TabImpl& add(CardImpl *card);
    // Remove Card
    TabImpl& remove(CardImpl *card);

    // Add Chart
    TabImpl& add(ChartImpl *chart);
    // Remove Chart
    TabImpl& remove(ChartImpl *chart);

    // Internal methods to be called

    uint32_t getId() const {
      return _id;
    }

    const String& getName() const {
      return _name;
    }

    // Generate tab info as JSON document
    JsonDocument toJSON();

    // Generate layout json
    JsonDocument generateLayout();

    // Generate cards/charts update json
    JsonDocument generateUpdates(bool changeOnly = true);

    // Propel event to according card
    void resolveCardCallback(uint32_t id, int value);

    ~TabImpl();
};

#endif
