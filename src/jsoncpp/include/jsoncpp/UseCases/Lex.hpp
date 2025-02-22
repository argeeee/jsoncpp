#pragma once

#include <string>
#include <memory>
#include <any>
#include <exception>

#include "jsoncpp/Models/JsonKind.hpp"
#include "jsoncpp/Models/JsonToken.hpp"

namespace JsonCpp::UseCases {

  using namespace std;
  using namespace JsonCpp::Models;

  class Lexer {
   private:
    long _position = 0;
    string _text;

    char Current();
    void Next();
    any GetNumberValue(long start, long length, bool isFloat);

    shared_ptr<JsonToken> ReadWhitespaceToken();
    shared_ptr<JsonToken> ReadNumberToken();
    shared_ptr<JsonToken> ReadSingleCharacterToken(JsonKind kind);
    shared_ptr<JsonToken> ReadStringToken();
    shared_ptr<JsonToken> ReadIdentifierToken();

   public:
    Lexer(string text)
      : _text(text)
    {
    }

    shared_ptr<JsonToken> Lex();

   private:
    static bool IsDigit(char);
    static bool IsWhiteSpace(char);
  };
  
}

