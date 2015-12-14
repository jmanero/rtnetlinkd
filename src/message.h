/**
 * Map between RTNETLINK message binary and Objects
 */
#ifndef NODE_MESSAGE_H
#define NODE_MESSAGE_H

#include <nan.h>

class Message : public Nan::ObjectWrap {
  public:
    static NAN_MODULE_INIT(Init);

  private:
    explicit Message(double value = 0);
    ~Message();

    static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
    static Nan::Persistent<v8::Function> constructor;
};

#endif
