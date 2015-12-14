/**
 * Map between RTNETLINK message binary and Objects
 */
#include "message.h"

Nan::Persistent<v8::Function> Message::constructor;

NAN_MODULE_INIT(Message::Init) {
  v8::Local<v8::FunctionTemplate> function = Nan::New<v8::FunctionTemplate>(New);
  function->SetClassName(Nan::New("Message").ToLocalChecked());
  function->InstanceTemplate()->SetInternalFieldCount(1);

  // Nan::SetPrototypeMethod(function, "plusOne", PlusOne);

  constructor.Reset(Nan::GetFunction(function).ToLocalChecked());
  Nan::Set(target, Nan::New("Message").ToLocalChecked(), Nan::GetFunction(function).ToLocalChecked());
}


void Message::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.IsConstructCall()) {
    Message *message = new Message();
    message->Wrap(info.This());
    info.GetReturnValue().Set(info.This());

  } else {
    v8::Local<v8::Value> argv[] = {
      info[0]
    };

    v8::Local<v8::Function> cons = Nan::New(constructor);
    info.GetReturnValue().Set(cons->NewInstance(1, argv));
  }
}
