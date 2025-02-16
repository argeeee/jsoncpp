#pragma once

namespace JsonCpp::Models {

  enum class JsonKind {
		UndefinedToken,
		NullToken,
		NumberToken,
		BooleanToken,
		StringToken,
		ArrayToken,
		ObjectToken,

		WhitespaceToken,
		EndOfFileToken,
	};

}

