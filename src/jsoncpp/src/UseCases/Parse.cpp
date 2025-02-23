#include <unordered_map>

#include "jsoncpp/UseCases/Parse.hpp"

namespace JsonCpp::UseCases {

  Parser::Parser(string text) {
    ReadTokens(text);
  }

  void Parser::ReadTokens(const string& text) {
    Lexer lexer = Lexer(text);

    shared_ptr<JsonToken> currToken = lexer.Lex();

    while (currToken->Kind() != JsonTokenKind::EndOfFileToken) {
      if (currToken->Kind() != JsonTokenKind::WhitespaceToken) {
        _tokens.push_back(currToken);
      }
      currToken = lexer.Lex();
    }

    _tokens.push_back(currToken);
  }

  JsonExpressionKind Parser::KindFromToken(JsonTokenKind kind) {
    switch (kind) {
      case JsonTokenKind::NumberToken:
        return JsonExpressionKind::Number;
      case JsonTokenKind::BooleanToken:
      return JsonExpressionKind::Bool;
      case JsonTokenKind::UndefinedToken:
        return JsonExpressionKind::Undefined;
      case JsonTokenKind::NullToken:
        return JsonExpressionKind::Null;
      case JsonTokenKind::StringToken:
        return JsonExpressionKind::String;
      default: {
        // TODO: better errors
        throw runtime_error("Unexpected json token when parsing");
      }
    }
  }

  shared_ptr<JsonToken> Parser::Current() {
    return Lookup(0);
  }

  shared_ptr<JsonToken> Parser::Lookup(int offset) {
    long position = _position + offset;
    if (position > _tokens.size())
      return _tokens[_tokens.size() - 1];
    return _tokens[position];
  }

  shared_ptr<JsonToken> Parser::MatchToken(JsonTokenKind kind) {
    auto currentToken = Current();
    
    Next();

    if (currentToken->Kind() != kind) {
      throw runtime_error("Unecpected token");
    }

    return currentToken;
  }

  void Parser::Next() {
    _position++;
  }

  shared_ptr<JsonExpression> Parser::ParseExpression() {
    switch (Current()->Kind()) {
      case JsonTokenKind::NumberToken:
      case JsonTokenKind::BooleanToken:
      case JsonTokenKind::UndefinedToken:
      case JsonTokenKind::NullToken:
      case JsonTokenKind::StringToken:
        return ParsePrimaryExpression();
      case JsonTokenKind::OpenSquareBracket:
        return ParseArrayExpression();
      case JsonTokenKind::OpenBrace:
        return ParseObjectExpression();
      default:
        // TODO: better errors
        throw runtime_error("Unecpected expression");
    }
  }

  shared_ptr<JsonExpression> Parser::ParsePrimaryExpression() {
    auto currentToken = Current();
    
    Next();
    
    return make_shared<JsonExpression>(
      KindFromToken(currentToken->Kind()),
      currentToken->Value()
    );
  }

  shared_ptr<JsonExpression> Parser::ParseArrayExpression() {
    vector<shared_ptr<JsonExpression>> arrayElements;

    MatchToken(JsonTokenKind::OpenSquareBracket);

    while (true) {
      auto value = ParseExpression();
      arrayElements.push_back(value);

      if (Current()->Kind() == JsonTokenKind::CommaToken) {
        MatchToken(JsonTokenKind::CommaToken);
        continue;
      }

      MatchToken(JsonTokenKind::ClosedSquareBracket);
      break;
    }

    return make_shared<JsonExpression>(
      JsonExpressionKind::Array,
      arrayElements
    );
  }

  shared_ptr<JsonExpression> Parser::ParseObjectExpression() {
    unordered_map<string, shared_ptr<JsonExpression>> object;

    MatchToken(JsonTokenKind::OpenBrace);

    while (true) {
      auto key = MatchToken(JsonTokenKind::StringToken);
      MatchToken(JsonTokenKind::ColonToken);
      auto value = ParseExpression();

      object.insert({
        any_cast<string>(key->Value()),
        value 
      });

      if (Current()->Kind() == JsonTokenKind::CommaToken) {
        MatchToken(JsonTokenKind::CommaToken);
        continue;
      }

      MatchToken(JsonTokenKind::ClosedBrace);
      break;
    }

    return make_shared<JsonExpression>(
      JsonExpressionKind::Object,
      object
    );
  }

  shared_ptr<JsonExpression> Parser::Parse() {
    auto expression = ParseExpression();
    MatchToken(JsonTokenKind::EndOfFileToken);
    return expression;
  }

}