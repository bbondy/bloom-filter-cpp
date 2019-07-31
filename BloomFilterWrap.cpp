/* Copyright (c) 2015 Brian R. Bondy. Distributed under the MPL2 license.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "BloomFilterWrap.h"

namespace BloomFilterWrap {

using v8::Context;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::Persistent;
using v8::String;
using v8::Boolean;
using v8::Value;
using v8::NewStringType;

#if V8_MAJOR_VERSION >= 7
#define CHECK_SET(X) X.Check()
#else
#define CHECK_SET(X) (void)X
#endif

Persistent<Function> BloomFilterWrap::constructor;

BloomFilterWrap::BloomFilterWrap(unsigned int bitsPerElement,
    unsigned int estimatedNumElements, HashFn hashFns[], int numHashFns)
  : BloomFilter(bitsPerElement, estimatedNumElements, hashFns, numHashFns) {
}

BloomFilterWrap::~BloomFilterWrap() {
}

void BloomFilterWrap::Init(Local<Object> exports) {
  Isolate* isolate = exports->GetIsolate();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "BloomFilter", NewStringType::kNormal).ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "add", BloomFilterWrap::Add);
  NODE_SET_PROTOTYPE_METHOD(tpl, "exists", BloomFilterWrap::Exists);

  constructor.Reset(isolate, tpl->GetFunction(
    isolate->GetCurrentContext()).ToLocalChecked());
  CHECK_SET(exports->Set(isolate->GetCurrentContext(), String::NewFromUtf8(isolate, "BloomFilter", NewStringType::kNormal).ToLocalChecked(),
  tpl->GetFunction(isolate->GetCurrentContext()).ToLocalChecked()));
}

void BloomFilterWrap::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.IsConstructCall()) {
    // Invoked as constructor: `new BloomFilter(...)`
    BloomFilterWrap* obj = new BloomFilterWrap();
    obj->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
  } else {
    // Invoked as plain function `BloomFilter(...)`, turn into construct call.
    const int argc = 1;
    Local<Value> argv[argc] = { args[0] };
    Local<Context> context = isolate->GetCurrentContext();
    Local<Function> cons = Local<Function>::New(isolate, constructor);
    Local<Object> result =
        cons->NewInstance(context, argc, argv).ToLocalChecked();
    args.GetReturnValue().Set(result);
  }
}

void BloomFilterWrap::Add(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  String::Utf8Value str(isolate, args[0]->ToString(isolate->GetCurrentContext())
      .FromMaybe(v8::Local<v8::String>()));
  const char * buffer = *str;

  BloomFilterWrap* obj = ObjectWrap::Unwrap<BloomFilterWrap>(args.Holder());
  obj->add(buffer);
}

void BloomFilterWrap::Exists(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  String::Utf8Value str(isolate, args[0]->ToString(isolate->GetCurrentContext())
      .FromMaybe(v8::Local<v8::String>()));
  const char * buffer = *str;

  BloomFilterWrap* obj = ObjectWrap::Unwrap<BloomFilterWrap>(args.Holder());
  bool exists = obj->exists(buffer);

  args.GetReturnValue().Set(Boolean::New(isolate, exists));
}


}  // namespace BloomFilterWrap
