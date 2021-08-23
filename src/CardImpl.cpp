#include "CardImpl.h"
#include "ESPDashImpl.h"
#include "TabImpl.h"

// Integral type to string pairs events
// ID, type
struct WidgetNames cardTags[] = {
  {GENERIC_CARD, "generic"},
  {TEMPERATURE_CARD, "temperature"},
  {HUMIDITY_CARD, "humidity"},
  {STATUS_CARD, "status"},
  {SLIDER_CARD, "slider"},
  {BUTTON_CARD, "button"},
  {PROGRESS_CARD, "progress"},
};

/*
  Constructor
*/
CardImpl::CardImpl(ESPDashImpl *dashboard, const int type, const char* name, const char* symbol, const int min, const int max):
Widget()
{
  _dashboard = dashboard;
  _tab = nullptr;
  _type = type;
  _name = name;
  _symbol = symbol;
  _value_min = min;
  _value_max = max;
  _dashboard->add(this);
}
CardImpl::CardImpl(TabImpl *tab, const int type, const char* name, const char* symbol, const int min, const int max):
Widget()
{
  _dashboard = nullptr;
  _tab = tab;
  _type = type;
  _name = name;
  _symbol = symbol;
  _value_min = min;
  _value_max = max;
  _tab->add(this);
}

/*
  Attach Function Callback
*/
void CardImpl::attachCallback(std::function<void(int value)> cb){
  _callback = cb;
}


/*
  Value update methods
*/
void CardImpl::update(int value, const char* symbol){
  /* Clear String if it was used before */
  if(_value_type == CardImpl::STRING){
    _value_s = "";
  }
  /* Store new value */
  _value_type = CardImpl::INTEGER;
  _symbol = symbol;
  if(_value_i != value)
    _changed = true;
  _value_i = value;
}

void CardImpl::update(int value){
  /* Clear String if it was used before */
  if(_value_type == CardImpl::STRING){
    _value_s = "";
  }
  /* Store new value */
  _value_type = CardImpl::INTEGER;
  if(_value_i != value)
    _changed = true;
  _value_i = value;
}

void CardImpl::update(float value, const char* symbol){
  /* Clear String if it was used before */
  if(_value_type == CardImpl::STRING){
    _value_s = "";
  }
  /* Store new value */
  _value_type = CardImpl::FLOAT;
  _symbol = symbol;
  if(_value_f != value)
    _changed = true;
  _value_f = value;
}

void CardImpl::update(float value){
  /* Clear String if it was used before */
  if(_value_type == CardImpl::STRING){
    _value_s = "";
  }
  /* Store new value */
  _value_type = CardImpl::FLOAT;
  if(_value_f != value)
    _changed = true;
  _value_f = value;
}

void CardImpl::update(const String &value, const char* symbol){
  update(value.c_str(), symbol);
}

void CardImpl::update(const String &value){
  update(value.c_str());
}

void CardImpl::update(const char* value, const char* symbol){
  if(_value_type == CardImpl::STRING){
    if(strcmp(_value_s.c_str(), value) != 0)
      _changed = true;
  }
  
  _value_type = CardImpl::STRING;
  _symbol = symbol;
  _value_s = value;
}

void CardImpl::update(const char* value){
    if(_value_type == CardImpl::STRING){
    if(strcmp(_value_s.c_str(), value) != 0)
      _changed = true;
  }
  
  _value_type = CardImpl::STRING;
  _value_s = value;
}

void CardImpl::update(bool value, const char* symbol){
  /* Clear String if it was used before */
  if(_value_type == CardImpl::STRING){
    _value_s = "";
  }
  /* Store new value */
  _value_type = CardImpl::INTEGER;
  _symbol = symbol;
  if(_value_i != value)
    _changed = true;
  _value_i = value;
}

void CardImpl::update(bool value){
  /* Clear String if it was used before */
  if(_value_type == CardImpl::STRING){
    _value_s = "";
  }
  /* Store new value */
  _value_type = CardImpl::INTEGER;
  if(_value_i != value)
    _changed = true;
  _value_i = value;
}

void CardImpl::resolveCallback(int value) {
  if (_callback) _callback(value);
}

Widget::JsonDocument CardImpl::generateLayout() {
  auto doc = generateUpdate();
  doc["name"] = _name;
  doc["type"] = cardTags[_type].type;
  doc["value_min"] = _value_min;
  doc["value_max"] = _value_max;
  return std::move(doc);
}

Widget::JsonDocument CardImpl::generateUpdate() {
  Widget::JsonDocument doc(256);
  doc["id"] = _id;
  doc["symbol"] = _symbol;
  switch (_value_type) {
    case CardImpl::INTEGER: doc["value"] = _value_i; break;
    case CardImpl::FLOAT: doc["value"] = _value_f; break;
    case CardImpl::STRING: doc["value"] = _value_s; break;
    default: doc["value"] = "ERROR"; break;
  }
  return std::move(doc);
}

/*
  Destructor
*/
CardImpl::~CardImpl() {
  if (_dashboard)
    _dashboard->remove(this);
  if (_tab)
    _tab->remove(this);
}
