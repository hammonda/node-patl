#ifndef METHOD_HPP_
#define METHOD_HPP_

#include <v8.h>
#include <uv.h>
#include <node.h>

#include <nasync/Args.hpp>
#include <nasync/Context.hpp>
#include <nasync/Factory.hpp>
#include <nasync/Signature.hpp>

namespace nasync {

template <class S, class Signature<S>::MethodPtr MethodPtr,
  template <class> class Factory = HeapFactory>
class Method {
public:
  typedef Context<S, MethodPtr, Signature<S>::ClassMethod> MethodContext;

  static v8::Handle<v8::Value> New (const v8::Arguments &args) {
    v8::HandleScope scope;
    if (args.Length() != 1 + MethodContext::MethodArgs::Size) {
      v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong number of arguments")));
      return scope.Close(v8::Undefined());
    }
    MethodContext *context = Factory<MethodContext>::New(args);
    uv_queue_work(uv_default_loop(), &context->req, Work, AfterWork);
    return scope.Close(v8::Undefined());
  }
private:
  Method() { }

  static void Work (uv_work_t *req) {
    static_cast<MethodContext*>(req->data)->work();
  }

  static void AfterWork (uv_work_t *req, int32_t status) {
    MethodContext *context = static_cast<MethodContext*>(req->data);
    v8::HandleScope scope;
    v8::Handle<v8::Value> argv[MethodContext::ReturnArgs::Size];
    context->call(v8::Context::GetCurrent()->Global(), argv);
    Factory<MethodContext>::Delete(context);
  }
};

} /* namespace nasync */

#endif /* METHOD_HPP_ */
