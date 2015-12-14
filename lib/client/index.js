/**
 * Stateful wrapper for native RTNetlink Interface
 */
var bindings = require('../../build/Release/Index');

var Wrapper = module.exports = {
  handle: null,
  Constants: bindings.Constants
};

Wrapper.open = function() {
  this.handle = bindings.open(process.pid);
};

Wrapper.close = function() {
  if (!this.handle) throw new ReferenceError('No handle for RTNETLINK');

  bindings.close(this.handle);
  this.handle = null;
};

Wrapper._request = function(request, callback) {
  if (!this.handle) throw new ReferenceError('No handle for RTNETLINK');
  // if (!(request instanceof Request))
  //   throw new TypeError('Request must be an instance of RTNetlink.Request');

  bindings.request(this.handle, request, callback);
};

/**
 * Don't expose prototype methods directly in the module root
 */
var Methods = {};
Object.setPrototypeOf(Methods, Wrapper);

Methods.show = function(id, callback) {
  if (id instanceof Function) {
    callback = id;
    id = null;
  }

  // this._send(new this.Requests.Show(id), callback)
};

Methods.add = function(id, options, callback) {

};

Methods.delete = function(id, options, callback) {

};

/**
 * Set prototype of a child module
 */
Wrapper.extend = function(child) {
  Object.setPrototypeOf(child, Methods);
  child.super = Methods;
};

// Wrapper.Request = require('./request');

// Wrapper.Address = require('./address');
// Wrapper.Link = require('./link');
// Wrapper.Route = require('./route');
