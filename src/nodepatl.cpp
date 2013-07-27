#include <v8.h>
#include <node.h>

#include <Patl.h>

void RegisterAddon(v8::Handle<v8::Object> target) {
  v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(Patl::New);
  tpl->SetClassName(v8::String::NewSymbol("Patl"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  NODE_SET_PROTOTYPE_METHOD(tpl, "loadDictionary",
      Patl::LOAD_DICTIONARY_ASYNC::New);
  NODE_SET_PROTOTYPE_METHOD(tpl, "searchDictionary",
      Patl::SEARCH_DICTIONARY_ASYNC::New);

  target->Set(v8::String::NewSymbol("Patl"),
      v8::Persistent<v8::Function>::New(tpl->GetFunction()));
}

NODE_MODULE(nodepatl, RegisterAddon)
