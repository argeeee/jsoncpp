#pragma once

#include <vector>
#include <memory>

#include "jsoncpp/Models/JsonTokenKind.hpp"
#include "jsoncpp/Models/JsonToken.hpp"
#include "jsoncpp/Models/JsonExpressionKind.hpp"
#include "jsoncpp/Models/JsonExpression.hpp"
#include "jsoncpp/UseCases/Lex.hpp"

namespace JsonCpp::UseCases {

  using namespace std;
  using namespace JsonCpp::Models;

  class Parser {
   private:
    long _position = 0;
    vector<shared_ptr<JsonToken>> _tokens;

    void ReadTokens(const string& text);

    shared_ptr<JsonToken> Current();
    shared_ptr<JsonToken> Lookup(int offset);
    shared_ptr<JsonToken> MatchToken(JsonTokenKind kind);
    void Next();

    shared_ptr<JsonExpression> ParseExpression();
    shared_ptr<JsonExpression> ParsePrimaryExpression();
    shared_ptr<JsonExpression> ParseArrayExpression();
    shared_ptr<JsonExpression> ParseObjectExpression();

   public:
    Parser(string text);

    shared_ptr<JsonExpression> Parse();
  
   private:
    static JsonExpressionKind KindFromToken(JsonTokenKind kind);
  };


}

