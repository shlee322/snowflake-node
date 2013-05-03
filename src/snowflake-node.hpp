#ifndef MODULENAME_HPP
#define MODULENAME_HPP

#include <node.h>
#include "../snowflake-cpp/src/Snowflake.h"

class SnowflakeNode : public node::ObjectWrap {
public:
    static v8::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Handle<v8::Object> target);

protected:
    SnowflakeNode();

    static v8::Handle<v8::Value> New(const v8::Arguments& args);
    static v8::Handle<v8::Value> SetEpoch(const v8::Arguments& args);
    static v8::Handle<v8::Value> SetMachine(const v8::Arguments& args);
    static v8::Handle<v8::Value> Generate(const v8::Arguments& args);

    Snowflake *snowflake;
};

#endif