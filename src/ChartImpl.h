#ifndef __CHART_H
#define __CHART_H

#include <functional>
#include <Arduino.h>
#include <ArduinoJson.h>

#include "vector.h"
#include "Widget.h"

enum {
  BAR_CHART,
};

enum GraphAxisType { INTEGER, FLOAT, STRING };

// Forward Declaration
class ESPDashImpl;
class TabImpl;

// Chart Class
class ChartImpl: public Widget{
  private:
    ESPDashImpl *_dashboard;
    TabImpl *_tab;

    GraphAxisType _x_axis_type;
    GraphAxisType _y_axis_type;
    /* X-Axis */
    Vector<int> _x_axis_i;
    Vector<float> _x_axis_f;
    Vector<String> _x_axis_s;
    /* Y-Axis */
    Vector<int> _y_axis_i;
    Vector<float> _y_axis_f;

  public:
    ChartImpl(ESPDashImpl *dashboard, const int type, const char* name);
    ChartImpl(TabImpl *tab, const int type, const char* name);
    void updateX(int arr_x[], size_t x_size);
    void updateX(float arr_x[], size_t x_size);
    void updateX(String arr_x[], size_t x_size);
    void updateY(int arr_y[], size_t y_size);
    void updateY(float arr_y[], size_t y_size);

    Widget::JsonDocument generateLayout() override;
    Widget::JsonDocument generateUpdate() override;

    ~ChartImpl();
};

#endif