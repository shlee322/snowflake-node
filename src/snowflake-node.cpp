#include <node.h>
#include "snowflake-node.hpp"

using namespace v8;

Persistent<FunctionTemplate> SnowflakeNode::constructor;

void SnowflakeNode::Init(Handle<Object> target) {
    HandleScope scope;

    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    Local<String> name = String::NewSymbol("snowflake");

    constructor = Persistent<FunctionTemplate>::New(tpl);
    constructor->InstanceTemplate()->SetInternalFieldCount(1);
    constructor->SetClassName(name);

    NODE_SET_PROTOTYPE_METHOD(constructor, "setEpoch", SetEpoch);
    NODE_SET_PROTOTYPE_METHOD(constructor, "setMachine", SetMachine);
    NODE_SET_PROTOTYPE_METHOD(constructor, "generate", Generate);

    target->Set(name, constructor->GetFunction());
}

SnowflakeNode::SnowflakeNode() : ObjectWrap()
{
    this->snowflake = new Snowflake();
}


Handle<Value> SnowflakeNode::New(const Arguments& args) {
    HandleScope scope;

    if (!args.IsConstructCall()) {
        return ThrowException(Exception::TypeError(
            String::New("Use the new operator to create instances of this object."))
        );
    }

    SnowflakeNode* obj = new SnowflakeNode();
    obj->Wrap(args.This());

    return args.This();
}

Handle<Value> SnowflakeNode::SetEpoch(const Arguments& args) {
    HandleScope scope;

    SnowflakeNode* obj = ObjectWrap::Unwrap<SnowflakeNode>(args.This());

    char stringValue[17];
    int64_t value;

    args[0]->ToString()->WriteAscii(stringValue);
    sscanf(stringValue, "%llx", &value);

    obj->snowflake->setEpoch(value);

    return scope.Close(Boolean::New(true));
}

Handle<Value> SnowflakeNode::SetMachine(const Arguments& args) {
    HandleScope scope;

    SnowflakeNode* obj = ObjectWrap::Unwrap<SnowflakeNode>(args.This());
    obj->snowflake->setMachine(args[0]->ToInteger()->Value());

    return scope.Close(Boolean::New(true));
}


Handle<Value> SnowflakeNode::Generate(const Arguments& args) {
    HandleScope scope;

    SnowflakeNode* obj = ObjectWrap::Unwrap<SnowflakeNode>(args.This());
    int64_t value = obj->snowflake->generate();

    char stringValue[17];
    sprintf(stringValue, "%llx", value);

    return scope.Close(String::New(stringValue));
}

void RegisterModule(v8::Handle<v8::Object> target) {
    SnowflakeNode::Init(target);
}

NODE_MODULE(SnowflakeNode, RegisterModule);