#include <iostream>
#include <string>
#include <node.h>
#include <map>

namespace cio {

using v8::FunctionCallbackInfo;
using v8::Exception;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::Number;
using v8::Boolean;
using v8::String;
using v8::Value;

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::map;

map<string, int> typeMap;

void Input(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  string str, type;
  double num;
  bool boolean;
  Local<String> jsType;
  if(args.Length() < 1){
    cin>>str;
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, str.c_str()));
  } else {
    jsType = Local<String>::Cast(args[0]);
    String::Utf8Value utf8Value(jsType);
    type = string(*utf8Value);
    cout<<typeMap[type]<<endl;
    switch(typeMap[type]){
      case 0:
        cin>>num;
        args.GetReturnValue().Set(Number::New(isolate, num));
        break;
      case 1:
        cin>>str;
        args.GetReturnValue().Set(String::NewFromUtf8(isolate, str.c_str()));
        break;
      case 2:
        cin>>boolean;
        args.GetReturnValue().Set(Boolean::New(isolate, boolean));
        break;
      default:
        break;
    }
  }
}

void Output(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  if(args.Length() < 1){
    // isolate->ThrowException(Exception::TypeError(
    //     String::NewFromUtf8(isolate, "Wrong number of arguments")));
    cout<<endl;
    return;
  }
  cout<<string(*String::Utf8Value(Local<String>::Cast(args[0])));
  if(args.Length() > 1 && !(Local<Boolean>::Cast(args[1]))->BooleanValue())
    return;
  cout<<endl;
}

void init(Local<Object> exports) {
  int typeCount = 0;
  typeMap["Number"] = typeMap["number"] = typeCount++;
  typeMap["String"] = typeMap["string"] = typeCount++;
  typeMap["Boolean"] = typeMap["boolean"] = typeCount++;
  NODE_SET_METHOD(exports, "input", Input);
  NODE_SET_METHOD(exports, "output", Output);
}

NODE_MODULE(cio, init)

}  // namespace cio