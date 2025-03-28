#include "hookapi.h"

struct XFL {
  uint64_t value;
  XFL(){
    this->value = 0;
  }
  XFL(uint64_t value){
    this->value = value;
  }
  XFL operator+(const XFL &other) const {
    return float_sum(value, other.value);
  }
  XFL operator+=(const XFL &other) {
    value = float_sum(value, other.value);
    return *this;
  }
  XFL operator-(const XFL &other) const {
    return float_sum(value, float_negate(other.value));
  }
  XFL operator-=(const XFL &other) {
    value = float_sum(value, float_negate(other.value));
    return *this;
  }
  XFL operator*(const XFL &other) const {
    return float_multiply(value, other.value);
  }
  XFL operator*=(const XFL &other) {
    value = float_multiply(value, other.value);
    return *this;
  }
  XFL operator/(const XFL &other) const {
    return float_divide(value, other.value);
  }
  XFL operator/=(const XFL &other) {
    value = float_divide(value, other.value);
    return *this;
  }

  uint64_t operator<(const XFL &other) const {
    return float_compare(value, other.value, COMPARE_LESS);
  }
  uint64_t operator<=(const XFL &other)  {
    return float_compare(value, other.value, COMPARE_LESS | COMPARE_EQUAL);
  }
  uint64_t operator>(const XFL &other) const {
    return float_compare(value, other.value, COMPARE_GREATER);
  }
  uint64_t operator>=(const XFL &other) const {
    return float_compare(value, other.value, COMPARE_GREATER | COMPARE_EQUAL);
  }
  uint64_t operator==(const XFL &other) const {
    return float_compare(value, other.value, COMPARE_EQUAL);
  }
  uint64_t operator!=(const XFL &other) const {
    return float_compare(value, other.value, COMPARE_LESS | COMPARE_GREATER);
  }
};
