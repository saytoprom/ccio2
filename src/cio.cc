#include <iostream>
#include <stdlib.h>
#include <regex>
#include <string>
#include <node.h>
#include <map>

namespace cio {

using v8::FunctionCallbackInfo;
using v8::Exception;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::Array;
using v8::Number;
using v8::Boolean;
using v8::String;
using v8::Value;

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::regex;

map<string, int> typeMap;

void ReadLine(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  string str;
  char last;
  last = cin.peek();
  if(last == '\n')
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  getline(cin, str);
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, str.c_str()));
}

void Input(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  string str, type;
  double num;
  bool boolean;
  Local<String> jsType;
  Local<Array> jsArray;
  int len;
  const regex regPattern("^0+|0+\\.|\\.0+|0+\\.0+$");
  if(args.Length() < 1){
    cin>>str;
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, str.c_str()));
  } else {
    jsType = Local<String>::Cast(args[0]);
    String::Utf8Value utf8Value(jsType);
    type = string(*utf8Value);
    // cout<<typeMap[type]<<endl;
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
        boolean = true;
        cin>>str;
        if(str == "0" || str == "false")
          boolean = false;
        args.GetReturnValue().Set(Boolean::New(isolate, boolean));
        break;
      case 3:
        len = Local<Number>::Cast(args[1])->NumberValue();
        jsArray = Array::New(isolate);
        for(int i = 0; i < len; i++){
          cin>>str;
          if((Local<Boolean>::Cast(args[2]))->BooleanValue()){
            jsArray->Set(i, String::NewFromUtf8(isolate, str.c_str()));
            continue;
          }
          if(regex_match(str, regPattern)){
            num = 0;
            jsArray->Set(i, Number::New(isolate, num));
          } else {
            num = atof(str.c_str());
            if(num == 0.0)
              jsArray->Set(i, String::NewFromUtf8(isolate, str.c_str()));
            else
              jsArray->Set(i, Number::New(isolate, num));
          }
        }
        args.GetReturnValue().Set(jsArray);
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
  typeMap["Array"] = typeMap["array"] = typeCount++;
  NODE_SET_METHOD(exports, "input", Input);
  NODE_SET_METHOD(exports, "output", Output);
  NODE_SET_METHOD(exports, "readline", ReadLine);
}

NODE_MODULE(cio, init)

}  // namespace cio