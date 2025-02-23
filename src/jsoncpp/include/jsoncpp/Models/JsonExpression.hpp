#pragma once

#include <any>
#include <string_view>

#include "jsoncpp/Models/JsonTokenKind.hpp"
#include "jsoncpp/Models/JsonExpressionKind.hpp"

namespace JsonCpp::Models {

  using namespace std;

  class JsonExpression {
   private:
     JsonExpressionKind _kind;
    any _value;

   public:
     JsonExpression(JsonExpressionKind kind, any value)
      : _kind(kind), _value(value)
    {
    }

    JsonExpressionKind Kind() {
      return _kind;
    }

    any& Value() {
      return _value;
    }
  };

}

