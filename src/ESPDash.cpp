#include "ESPDash.h"

#include "ESPDashImpl.h"

namespace ESPDash {

ESPDash::ESPDash(AsyncWebServer *server) {
  _pimpl = std::shared_ptr<ESPDashImpl>(new ESPDashImpl(server, true));
}

ESPDash& ESPDash::setAuthentication(const char *user, const char *pass) {
  _pimpl->setAuthentication(user, pass);
  return *this;
}

void ESPDash::add(Tab *tab) {
  _pimpl->add(tab->_pimpl.get());
}

void ESPDash::remove(Tab *tab) {
  _pimpl->remove(tab->_pimpl.get());
}

void ESPDash::add(Card *card) {
  _pimpl->add(card->_pimpl.get());
}

void ESPDash::remove(Card *card) {
  _pimpl->remove(card->_pimpl.get());
}

void ESPDash::add(Chart *chart) {
  _pimpl->add(chart->_pimpl.get());
}

void ESPDash::remove(Chart *chart) {
  _pimpl->remove(chart->_pimpl.get());
}

void ESPDash::sendUpdates() {
  _pimpl->sendUpdates();
}

Tab::Tab(ESPDash *dashboard, const char *name, const char *navbarName, const char *header) {
  _pimpl = std::shared_ptr<TabImpl>(new TabImpl(dashboard->_pimpl.get(), name, navbarName, header));
}

Tab &Tab::add(Card *card) {
  _pimpl->add(card->_pimpl.get());
  return *this;
}

Tab &Tab::remove(Card *card) {
  _pimpl->remove(card->_pimpl.get());
  return *this;
}

Tab &Tab::add(Chart *chart) {
  _pimpl->add(chart->_pimpl.get());
  return *this;
}

Tab &Tab::remove(Chart *chart) {
  _pimpl->remove(chart->_pimpl.get());
  return *this;
}

Card::Card(ESPDash *dashboard, const int type, const char *name, const char *symbol, const int min, const int max) {
  _pimpl = std::shared_ptr<CardImpl>(new CardImpl(dashboard->_pimpl.get(), type, name, symbol, min, max));
}

Card::Card(Tab *tab, const int type, const char *name, const char *symbol, const int min, const int max) {
  _pimpl = std::shared_ptr<CardImpl>(new CardImpl(tab->_pimpl.get(), type, name, symbol, min, max));
}

void Card::attachCallback(std::function<void(int)> cb) {
  _pimpl->attachCallback(std::move(cb));
}

void Card::update(int value) {
  _pimpl->update(value);
}

void Card::update(int value, const char *symbol) {
  _pimpl->update(value, symbol);
}

void Card::update(bool value) {
  _pimpl->update(value);
}

void Card::update(bool value, const char *symbol) {
  _pimpl->update(value, symbol);
}

void Card::update(float value) {
  _pimpl->update(value);
}

void Card::update(float value, const char *symbol) {
  _pimpl->update(value, symbol);
}

void Card::update(const char *value) {
  _pimpl->update(value);
}

void Card::update(const char *value, const char *symbol) {
  _pimpl->update(value, symbol);
}

void Card::update(const String &value) {
  _pimpl->update(value);
}

void Card::update(const String &value, const char *symbol) {
  _pimpl->update(value, symbol);
}

Chart::Chart(ESPDash *dashboard, const int type, const char *name) {
  _pimpl = std::shared_ptr<ChartImpl>(new ChartImpl(dashboard->_pimpl.get(), type, name));
}

Chart::Chart(Tab *tab, const int type, const char *name) {
  _pimpl = std::shared_ptr<ChartImpl>(new ChartImpl(tab->_pimpl.get(), type, name));
}

void Chart::updateX(int *arr_x, size_t x_size) {
  _pimpl->updateX(arr_x, x_size);
}

void Chart::updateX(float *arr_x, size_t x_size) {
  _pimpl->updateX(arr_x, x_size);
}

void Chart::updateX(String *arr_x, size_t x_size) {
  _pimpl->updateX(arr_x, x_size);
}

void Chart::updateY(int *arr_y, size_t y_size) {
  _pimpl->updateY(arr_y, y_size);
}

void Chart::updateY(float *arr_y, size_t y_size) {
  _pimpl->updateY(arr_y, y_size);
}

} // End of namespace ESPDash