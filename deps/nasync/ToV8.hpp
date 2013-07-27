#ifndef TO_V8_HPP
#define TO_V8_HPP

#include <stddef.h>
#include <stdint.h>
#include <string>

#include <v8.h>

#include <boost/mpl/and.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/mpl/set.hpp>
#include <boost/utility/enable_if.hpp>

namespace nasync {

typedef boost::mpl::set<float, double, uint64_t, int64_t> V8_FLOATS;
typedef boost::mpl::set<uint8_t, uint16_t, uint32_t> V8_UINTS;
typedef boost::mpl::set<int8_t, int16_t, int32_t> V8_INTS;

typedef v8::Handle<v8::Value> ValueHandle;

#define TOV8_FUNCTION_OVERLOAD_FROM_SET(SET,CONSTRUCTOR) \
template <class T> \
static inline typename boost::enable_if< \
  typename boost::mpl::has_key<SET,T>::type, \
  ValueHandle >::type ToV8 (T t) { \
  return CONSTRUCTOR(t); \
}; \
/**/

TOV8_FUNCTION_OVERLOAD_FROM_SET(V8_FLOATS, v8::Number::New)
TOV8_FUNCTION_OVERLOAD_FROM_SET(V8_UINTS, v8::Integer::NewFromUnsigned)
TOV8_FUNCTION_OVERLOAD_FROM_SET(V8_INTS, v8::Integer::New)

static inline ValueHandle ToV8 (ValueHandle value) {
  return value;
};

static inline ValueHandle ToV8 (bool value) {
  return v8::Boolean::New(value);
};

static inline ValueHandle ToV8 (const char* value) {
  return value != NULL ? v8::String::New(value) :
      static_cast<ValueHandle>(v8::Undefined());
};

static inline ValueHandle ToV8 (const std::string& value) {
  return value.size() != 0 ? ToV8(value.c_str()) :
      static_cast<ValueHandle>(v8::Undefined());
};

template <template <class, class> class C, class T, class A>
static inline ValueHandle ToV8 (const C<T, A>& container) {
  uint32_t size = container.size();
  v8::Local<v8::Array> array = v8::Array::New(size);
  for (uint32_t i = 0; i < size; ++i) {
    array->Set(i, ToV8(container[i]));
  }
  return array;
};
} /* namespace nasync */
#endif
