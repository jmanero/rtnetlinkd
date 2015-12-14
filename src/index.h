/**
 * A generic asynchronous linux/rtnetlink interface
 */
#ifndef NODE_INDEX_H
#define NODE_INDEX_H

#include <nan.h>

#include <asm/types.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <sys/socket.h>

#include <cstdint>
#include <errno.h>
#include <iostream>
#include <unistd.h>

#include "message.h"

void Open(const Nan::FunctionCallbackInfo<v8::Value>& info);
void Close(const Nan::FunctionCallbackInfo<v8::Value>& info);
void Request(const Nan::FunctionCallbackInfo<v8::Value>& info);

/**
 * Asynchronous Request Worker
 */
class RequestWorker : public Nan::AsyncWorker {
  public:
    RequestWorker(int handle, char *request, size_t request_length, Nan::Callback *callback)
      : AsyncWorker(callback),
        handle(handle),
        request(request),
        request_length(request_length) {}

    virtual ~RequestWorker() {}
    void Execute();
    void HandleOKCallback();

  private:
    int32_t handle;

    char *request;
    size_t request_length;

    char *response;
    size_t response_length;
};


#endif
