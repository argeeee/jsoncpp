#include "jsoncpp/UseCases/Lex.hpp"

namespace JsonCpp::UseCases {

	char Lexer::Current() {
		if (_position > _text.size())
			return '\0';
		return _text[_position];
	}

	void Lexer::Next() {
		_position++;
	}

	bool Lexer::IsDigit(char c) {
		return (c >= '0' && c <= '9');
	}

	bool Lexer::IsWhiteSpace(char c) {
		return c == ' ' || c == '\t' || c == '\r' || c == '\n';
	}

	any Lexer::GetNumberValue(long start, long length, bool isFloat) {
		if (isFloat) {
			return stod(_text.substr(start, length));
		}
		return stol(_text.substr(start, length));
	}

	shared_ptr<JsonToken> Lexer::ReadWhitespaceToken() {
		long start = _position;

		while (IsWhiteSpace(Current())) {
			Next();
		}

		long end = _position;

		return make_shared<JsonToken>(
			start,
			JsonTokenKind::WhitespaceToken,
			string_view(_text).substr(start, end - start)
		);
	}

	shared_ptr<JsonToken> Lexer::ReadNumberToken() {
		int start = _position;
		bool isFloat = false;

		while (IsDigit(Current())) {
			Next();
		}

		// Floating point number case
		if (Current() == '.') {
			isFloat = true;
			Next();

			while (IsDigit(Current())) {
				Next();
			}
		}

		int length = _position - start;

		return make_shared<JsonToken>(
			start,
			JsonTokenKind::NumberToken,
			string_view(_text).substr(start, length),
			GetNumberValue(start, length, isFloat)
		);
	}

	shared_ptr<JsonToken> Lexer::ReadSingleCharacterToken(JsonTokenKind kind) {
		long start = _position;
		_position++;
		long end = _position;

		return make_shared<JsonToken>(
			start,
			kind,
			string_view(_text).substr(start, end - start)
		);
	}

	shared_ptr<JsonToken> Lexer::ReadStringToken() {
		int start = _position;

		Next(); // Read '"'

		while (Current() != '"') {
			// TODO: to fix this implementation
			Next();
		}

		Next(); // Read '"'
		
		int length = _position - start;

		return make_shared<JsonToken>(
			start,
			JsonTokenKind::StringToken,
			string_view(_text).substr(start, length),
			_text.substr(start + 1, length - 2)
		);
	}
	
	shared_ptr<JsonToken> Lexer::ReadIdentifierToken() {
		long start = _position;
		int incrementAmount = 0;
		JsonTokenKind kind;
		any value;

		if (_text.compare(_position, 4, "true") == 0) {
			incrementAmount = 4;
			kind = JsonTokenKind::BooleanToken;
			value = true;
		}
		else if (_text.compare(_position, 5, "false") == 0) {
			incrementAmount = 5;
			kind = JsonTokenKind::BooleanToken;
			value = false;
		}
		else if (_text.compare(_position, 4, "null") == 0) {
			incrementAmount = 4;
			kind = JsonTokenKind::NullToken;
		}
		else if (_text.compare(_position, 9, "undefined") == 0) {
			incrementAmount = 9;
			kind = JsonTokenKind::UndefinedToken;
		}
		else {
			// TODO: better errors
			throw runtime_error("Unexpected identifier");
		}

		_position += incrementAmount;
		int length = _position - start;

		return make_shared<JsonToken>(
			start,
			kind,
			string_view(_text).substr(start, length),
			value
		);
	}
	
	shared_ptr<JsonToken> Lexer::Lex() {		
		if (IsWhiteSpace(Current())) {
			return ReadWhitespaceToken();
		}

		if (IsDigit(Current())) {
			return ReadNumberToken();
		}

		switch (Current()) {
		 	case '[':
				return ReadSingleCharacterToken(JsonTokenKind::OpenSquareBracket);
		 	case ']':
				return ReadSingleCharacterToken(JsonTokenKind::ClosedSquareBracket);
			case '{':
				return ReadSingleCharacterToken(JsonTokenKind::OpenBrace);
			case '}':
				return ReadSingleCharacterToken(JsonTokenKind::ClosedBrace);
			case ',':
				return ReadSingleCharacterToken(JsonTokenKind::CommaToken);
			case ':':
				return ReadSingleCharacterToken(JsonTokenKind::ColonToken);
			case '"':
				return ReadStringToken();
			case '\0':
				return make_shared<JsonToken>(_position, JsonTokenKind::EndOfFileToken, string_view("\0"));
			default: 
				return ReadIdentifierToken();
		}
	}

}