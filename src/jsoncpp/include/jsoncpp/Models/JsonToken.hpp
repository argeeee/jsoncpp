#pragma once

#include <any>
#include <string_view>

#include "jsoncpp/Models/JsonKind.hpp"

namespace JsonCpp::Models {

  using namespace std;

  class JsonToken {
   private:
    long _position;
    JsonKind _kind;
    string_view _text;
    any _value;

   public:
    JsonToken(long position, JsonKind kind, string_view text, any value = any())
      : _position(position),
        _kind(kind),
        _text(text),
        _value(value)
    {
    }

    long Position() {
      return _position;
    }

    JsonKind Kind() {
      return _kind;
    }
    
    string_view Text() {
      return _text;
    }

    any Value() {
      return _value;
    }
  };

}

