{
  "targets": [
    {
      "target_name": "Index",
      "cflags": [ "-std=c++0x" ],
      "sources": [ "src/index.cc", "src/message.cc" ],
      "include_dirs" : [ "<!(node -e \"require('nan')\")" ]
    }
  ]
}
