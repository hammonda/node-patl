#ifndef FACTORY_HPP_
#define FACTORY_HPP_

namespace nasync {
template <class T>
class HeapFactory {
public:
  inline static T* New () {
    return new T();
  }

  template <class Arg0>
  inline static T* New (Arg0 arg0) {
    return new T(arg0);
  }

  inline static void Delete (T* t) {
    delete t;
  }
};

template <class T>
class SingleValueFactory {
public:
  inline static T* New () {
    return &value;
  }

  inline static void Delete (T* t) {
  }

private:
  static T value;
};

template <class T> T SingleValueFactory<T>::value;
} /* namespace nasync */

#endif /* FACTORY_HPP_ */
