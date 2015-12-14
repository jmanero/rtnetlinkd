/**
 * A generic asynchronous linux/rtnetlink interface
 */
#include "index.h"

/**
 * Open an RTNETLINK socket
 */
void Open(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (!info[0]->IsUint32()) Nan::ThrowTypeError("RTNETLINK identifier must be a UInt32");

  int32_t fd;
  struct sockaddr_nl address;

  if ((fd = socket(AF_NETLINK, SOCK_DGRAM, NETLINK_ROUTE)) < 0)
    Nan::ThrowError("Unable to open RTNETLINK socket");

  bzero(&address, sizeof(address));
  address.nl_family = AF_NETLINK;
  address.nl_pad = 0;
  address.nl_pid = info[0]->Uint32Value();
  address.nl_groups = 0;

  if(bind(fd, (struct sockaddr*) &address, sizeof(address)) < 0)
    Nan::ThrowError("Unable to bind RTNETLINK socket");

  info.GetReturnValue().Set(Nan::New(fd));
}

/**
 * Close an RTNETLINK socket
 */
void Close(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (!info[0]->IsInt32()) Nan::ThrowTypeError("RTNETLINK socket handle must be an Int32");

  if (close(info[0]->Int32Value()) < 0)
    Nan::ThrowError("Unable to close RTNETLINK socket");
}


/**
 * Send/receive an asynchronous request
 */
void Request(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (!info[0]->IsInt32()) Nan::ThrowTypeError("RTNETLINK socket handle must be an Int32");
  if (!node::Buffer::HasInstance(info[1])) Nan::ThrowTypeError("Request must be a buffer");
  if (!info[2]->IsFunction()) Nan::ThrowTypeError("Callback must be a function");

  v8::Local<v8::Object> request_buffer = info[1]->ToObject();

  Nan::AsyncQueueWorker(new RequestWorker(info[0]->Int32Value(),
                                          node::Buffer::Data(request_buffer),
                                          node::Buffer::Length(request_buffer),
                                          new Nan::Callback(info[2].As<v8::Function>())));
}

/**
 * Asynchronous Request Worker
 */
void RequestWorker::Execute () {
  std::cout << "I'm asynchronous 'n shit" << std::endl;

  // struct msghdr message;
  // struct sockaddr_nl address;
  //
  // bzero(&address, sizeof(address));
  // bzero(&message, sizeof(message));
  //
  // address.nl_family = AF_NETLINK;
  // address.nl_pad = 0;
  // address.nl_pid = 0;
  // address.nl_groups = 0;
  //
  // message.msg_name = &address;
  // message.msg_namelen = sizeof(address);
  //
  // // TODO Form request vector
  //
  // message.msg_control = 0;
  // message.msg_controllen = 0;
  // message.msg_flags = 0;
  //
  // if (sendmsg(handle, &message, sizeof(message)) < 0) {
  //   SetErrorMessage(strerror(errno));
  //   return;
  // }
  //
  // if ((int32_t)(response_length = recv(handle, response, 1024, 0)) < 0) {
  //   SetErrorMessage(strerror(errno));
  // }
}

void RequestWorker::HandleOKCallback() {
  Nan::HandleScope scope;

  char words[] = "That's just, like, your opinion, man.";

  v8::Local<v8::Value> argv[] = {
    Nan::Null(),
    Nan::NewBuffer(words, sizeof(words)).ToLocalChecked()
  };

  callback->Call(2, argv);
}

/**
 * Export Methods
 */
NAN_MODULE_INIT(IndexModule) {
  Nan::Set(target, Nan::New("open").ToLocalChecked(),
           Nan::GetFunction(Nan::New<v8::FunctionTemplate>(Open)).ToLocalChecked());
  Nan::Set(target, Nan::New("close").ToLocalChecked(),
           Nan::GetFunction(Nan::New<v8::FunctionTemplate>(Close)).ToLocalChecked());
  Nan::Set(target, Nan::New("request").ToLocalChecked(),
           Nan::GetFunction(Nan::New<v8::FunctionTemplate>(Request)).ToLocalChecked());

  // Expose constants to JS
  v8::Local<v8::Object> Constants = Nan::New<v8::Object>();
  Nan::Set(Constants, Nan::New("NEWLINK").ToLocalChecked(), Nan::New(RTM_NEWLINK));
  Nan::Set(Constants, Nan::New("DELLINK").ToLocalChecked(), Nan::New(RTM_DELLINK));
  Nan::Set(Constants, Nan::New("GETLINK").ToLocalChecked(), Nan::New(RTM_GETLINK));
  Nan::Set(Constants, Nan::New("NEWADDR").ToLocalChecked(), Nan::New(RTM_NEWADDR));
  Nan::Set(Constants, Nan::New("DELADDR").ToLocalChecked(), Nan::New(RTM_DELADDR));
  Nan::Set(Constants, Nan::New("GETADDR").ToLocalChecked(), Nan::New(RTM_GETADDR));
  Nan::Set(Constants, Nan::New("NEWROUTE").ToLocalChecked(), Nan::New(RTM_NEWROUTE));
  Nan::Set(Constants, Nan::New("DELROUTE").ToLocalChecked(), Nan::New(RTM_DELROUTE));
  Nan::Set(Constants, Nan::New("GETROUTE").ToLocalChecked(), Nan::New(RTM_GETROUTE));

  // Nan::Set(Constants, Nan::New("NEWADDR").ToLocalChecked(), Nan::New(RTM_NEWADDR));
  // Nan::Set(Constants, Nan::New("NEWADDR").ToLocalChecked(), Nan::New(RTM_NEWADDR));
  // Nan::Set(Constants, Nan::New("NEWADDR").ToLocalChecked(), Nan::New(RTM_NEWADDR));
  // Nan::Set(Constants, Nan::New("NEWADDR").ToLocalChecked(), Nan::New(RTM_NEWADDR));


  Nan::Set(target, Nan::New("Constants").ToLocalChecked(), Constants);
  Message::Init(target);
}

NODE_MODULE(Index, IndexModule)
