#pragma once

#include "gtest/gtest.h"

#include "jsoncpp/UseCases/Lex.hpp"

using namespace JsonCpp::UseCases;

class LexerTest : public ::testing::Test {
 protected:
	std::shared_ptr<Lexer> lexer;

	void SetUp() override {
		// ignore
	}
};

TEST_F(LexerTest, ReadsWhitespaceToken) {
	lexer = std::make_shared<Lexer>("   \t\n");
	auto token = lexer->Lex();
	ASSERT_EQ(token->Kind(), JsonKind::WhitespaceToken);
	ASSERT_EQ(token->Text(), "   \t\n");
}

TEST_F(LexerTest, ReadsSingleDigitNumberToken) {
	lexer = std::make_shared<Lexer>("5");
	auto token = lexer->Lex();
	ASSERT_EQ(token->Kind(), JsonKind::NumberToken);
	ASSERT_EQ(std::any_cast<long>(token->Value()), 5);
}

TEST_F(LexerTest, ReadsMultiDigitNumberToken) {
	lexer = std::make_shared<Lexer>("12345");
	auto token = lexer->Lex();
	ASSERT_EQ(token->Kind(), JsonKind::NumberToken);
	ASSERT_EQ(std::any_cast<long>(token->Value()), 12345);
}

TEST_F(LexerTest, ReadsFloatNumberToken) {
	lexer = std::make_shared<Lexer>("12.34");
	auto token = lexer->Lex();
	ASSERT_EQ(token->Kind(), JsonKind::NumberToken);
	ASSERT_EQ(std::any_cast<double>(token->Value()), 12.34);
}

TEST_F(LexerTest, ReadsStringToken) {
	lexer = std::make_shared<Lexer>("\"hello\"");
	auto token = lexer->Lex();
	ASSERT_EQ(token->Kind(), JsonKind::StringToken);
	ASSERT_EQ(std::any_cast<std::string>(token->Value()), "hello");
}

TEST_F(LexerTest, ReadsBooleanTrueToken) {
	lexer = std::make_shared<Lexer>("true");
	auto token = lexer->Lex();
	ASSERT_EQ(token->Kind(), JsonKind::BooleanToken);
	ASSERT_EQ(std::any_cast<bool>(token->Value()), true);
}

TEST_F(LexerTest, ReadsBooleanFalseToken) {
	lexer = std::make_shared<Lexer>("false");
	auto token = lexer->Lex();
	ASSERT_EQ(token->Kind(), JsonKind::BooleanToken);
	ASSERT_EQ(std::any_cast<bool>(token->Value()), false);
}

TEST_F(LexerTest, ReadsNullToken) {
	lexer = std::make_shared<Lexer>("null");
	auto token = lexer->Lex();
	ASSERT_EQ(token->Kind(), JsonKind::NullToken);
}

TEST_F(LexerTest, ReadsUndefinedToken) {
	lexer = std::make_shared<Lexer>("undefined");
	auto token = lexer->Lex();
	ASSERT_EQ(token->Kind(), JsonKind::UndefinedToken);
}

TEST_F(LexerTest, ReadsSpecialCharacterTokens) {
	std::string input = "[]{},:";
	lexer = std::make_shared<Lexer>(input);
	
	ASSERT_EQ(lexer->Lex()->Kind(), JsonKind::OpenSquareBracket);
	ASSERT_EQ(lexer->Lex()->Kind(), JsonKind::ClosedSquareBracket);
	ASSERT_EQ(lexer->Lex()->Kind(), JsonKind::OpenBrace);
	ASSERT_EQ(lexer->Lex()->Kind(), JsonKind::ClosedBrace);
	ASSERT_EQ(lexer->Lex()->Kind(), JsonKind::CommaToken);
	ASSERT_EQ(lexer->Lex()->Kind(), JsonKind::ColonToken);
}

TEST_F(LexerTest, ReadsEndOfFileToken) {
	lexer = std::make_shared<Lexer>("");
	auto token = lexer->Lex();
	ASSERT_EQ(token->Kind(), JsonKind::EndOfFileToken);
}
