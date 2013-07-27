#ifndef CONTEXT_HPP_
#define CONTEXT_HPP_

#include <uv.h>
#include <v8.h>

#include <nasync/Signature.hpp>

namespace nasync {

template <class S, class Signature<S>::MethodPtr MethodPtr, bool ClassMethod >
class Context;

template <class S, class Signature<S>::MethodPtr MethodPtr >
class Context<S, MethodPtr, false > {
public:
  typedef typename Signature<S>::MethodArgs MethodArgs;
  typedef typename Signature<S>::ReturnArgs ReturnArgs;

  Context (const v8::Arguments &args)
    : methodArgs (args),
      returnArgs (),
      callback (v8::Persistent<v8::Function>::
          New(v8::Local<v8::Function>::Cast(args[MethodArgs::Size]))) {
    req.data = static_cast<void*>(this);
  }

  virtual ~Context () {
    callback.Dispose();
    callback.Clear();
  }

  inline void work () {
    (*MethodPtr)(this->methodArgs, this->returnArgs);
  }

  inline void call (v8::Local<v8::Object> context, v8::Handle<v8::Value> *argv) {
    returnArgs.toV8(argv);
    callback->Call(context, ReturnArgs::Size, argv);
  }

  uv_work_t req;
protected:
  const MethodArgs methodArgs;
  ReturnArgs returnArgs;
  v8::Persistent<v8::Function> callback;
};

template <class S, class Signature<S>::MethodPtr MethodPtr >
class Context<S, MethodPtr, true> : public Context<S, MethodPtr, false > {
public:
  typedef typename Signature<S>::ClassType ClassType;

  Context (const v8::Arguments &args)
    : Context<S, MethodPtr, false >(args),
      __class (node::ObjectWrap::Unwrap<ClassType>(args.This())) {
  }
  inline void work () {
    (__class->*MethodPtr)(this->methodArgs, this->returnArgs);
  }
private:
  ClassType *__class;
};

}

#endif /* CONTEXT_HPP_ */
