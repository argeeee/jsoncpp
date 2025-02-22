#pragma once

namespace JsonCpp::Models {

  enum class JsonKind {
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
		
		ArrayExpression,
		ObjectExpression,
	};

}

