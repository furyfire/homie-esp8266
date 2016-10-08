#include "HomieSetting.hpp"

using namespace HomieInternals;

std::vector<IHomieSetting*> IHomieSetting::settings;

template <class T>
HomieSetting<T>::HomieSetting(const char* name, const char* description)
: _name(name)
, _description(description)
, _required(true)
, _provided(false)
, _value()
, _validator([](T candidate) { return true; }) {
  IHomieSetting::settings.push_back(this);
}

template <class T>
T HomieSetting<T>::get() const {
  return _value;
}

template <class T>
bool HomieSetting<T>::wasProvided() const {
  return _provided;
}

template <class T>
HomieSetting<T>& HomieSetting<T>::setDefaultValue(T defaultValue) {
  _value = defaultValue;
  _required = false;
  return *this;
}

template <class T>
HomieSetting<T>& HomieSetting<T>::setValidator(std::function<bool(T candidate)> validator) {
  _validator = validator;
  return *this;
}

template <class T>
bool HomieSetting<T>::validate(T candidate) const {
  return _validator(candidate);
}

template <class T>
void HomieSetting<T>::set(T value) {
  _value = value;
  _provided = true;
}

template <class T>
bool HomieSetting<T>::isRequired() const {
  return _required;
}

template <class T>
const char* HomieSetting<T>::getName() const {
  return _name;
}

template <class T>
const char* HomieSetting<T>::getDescription() const {
  return _description;
}

template <class T>
bool HomieSetting<T>::isBool() const { return false; }

template <class T>
bool HomieSetting<T>::isUnsignedLong() const { return false; }

template <class T>
bool HomieSetting<T>::isLong() const { return false; }

template <class T>
bool HomieSetting<T>::isDouble() const { return false; }

template <class T>
bool HomieSetting<T>::isConstChar() const { return false; }

template<>
bool HomieSetting<bool>::isBool() const { return true; }

template<>
bool HomieSetting<unsigned long>::isUnsignedLong() const { return true; }

template<>
bool HomieSetting<long>::isLong() const { return true; }

template<>
bool HomieSetting<double>::isDouble() const { return true; }

template<>
bool HomieSetting<const char*>::isConstChar() const { return true; }

template class HomieSetting<bool>;  // Needed because otherwise undefined reference to
template class HomieSetting<unsigned long>;
template class HomieSetting<long>;
template class HomieSetting<double>;
template class HomieSetting<const char*>;