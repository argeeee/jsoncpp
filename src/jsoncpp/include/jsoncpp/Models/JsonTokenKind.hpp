#pragma once

namespace JsonCpp::Models {

  enum class JsonTokenKind {
    EndOfFileToken,
    WhitespaceToken,
    UndefinedToken,
    NullToken,
    NumberToken,
    BooleanToken,
    StringToken,
    OpenSquareBracket,
    ClosedSquareBracket,
    OpenBrace,
    ClosedBrace,
    CommaToken,
    ColonToken,
  };

}

