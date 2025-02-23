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
  ASSERT_EQ(token->Kind(), JsonTokenKind::WhitespaceToken);
  ASSERT_EQ(token->Text(), "   \t\n");
}

TEST_F(LexerTest, ReadsSingleDigitNumberToken) {
  lexer = std::make_shared<Lexer>("5");
  auto token = lexer->Lex();
  ASSERT_EQ(token->Kind(), JsonTokenKind::NumberToken);
  ASSERT_EQ(std::any_cast<long>(token->Value()), 5);
}

TEST_F(LexerTest, ReadsMultiDigitNumberToken) {
  lexer = std::make_shared<Lexer>("12345");
  auto token = lexer->Lex();
  ASSERT_EQ(token->Kind(), JsonTokenKind::NumberToken);
  ASSERT_EQ(std::any_cast<long>(token->Value()), 12345);
}

TEST_F(LexerTest, ReadsFloatNumberToken) {
  lexer = std::make_shared<Lexer>("12.34");
  auto token = lexer->Lex();
  ASSERT_EQ(token->Kind(), JsonTokenKind::NumberToken);
  ASSERT_EQ(std::any_cast<double>(token->Value()), 12.34);
}

TEST_F(LexerTest, ReadsStringToken) {
  lexer = std::make_shared<Lexer>("\"hello\"");
  auto token = lexer->Lex();
  ASSERT_EQ(token->Kind(), JsonTokenKind::StringToken);
  ASSERT_EQ(std::any_cast<std::string>(token->Value()), "hello");
}

TEST_F(LexerTest, ReadsBooleanTrueToken) {
  lexer = std::make_shared<Lexer>("true");
  auto token = lexer->Lex();
  ASSERT_EQ(token->Kind(), JsonTokenKind::BooleanToken);
  ASSERT_EQ(std::any_cast<bool>(token->Value()), true);
}

TEST_F(LexerTest, ReadsBooleanFalseToken) {
  lexer = std::make_shared<Lexer>("false");
  auto token = lexer->Lex();
  ASSERT_EQ(token->Kind(), JsonTokenKind::BooleanToken);
  ASSERT_EQ(std::any_cast<bool>(token->Value()), false);
}

TEST_F(LexerTest, ReadsNullToken) {
  lexer = std::make_shared<Lexer>("null");
  auto token = lexer->Lex();
  ASSERT_EQ(token->Kind(), JsonTokenKind::NullToken);
}

TEST_F(LexerTest, ReadsUndefinedToken) {
  lexer = std::make_shared<Lexer>("undefined");
  auto token = lexer->Lex();
  ASSERT_EQ(token->Kind(), JsonTokenKind::UndefinedToken);
}

TEST_F(LexerTest, ReadsSpecialCharacterTokens) {
  std::string input = "[]{},:";
  lexer = std::make_shared<Lexer>(input);
  
  ASSERT_EQ(lexer->Lex()->Kind(), JsonTokenKind::OpenSquareBracket);
  ASSERT_EQ(lexer->Lex()->Kind(), JsonTokenKind::ClosedSquareBracket);
  ASSERT_EQ(lexer->Lex()->Kind(), JsonTokenKind::OpenBrace);
  ASSERT_EQ(lexer->Lex()->Kind(), JsonTokenKind::ClosedBrace);
  ASSERT_EQ(lexer->Lex()->Kind(), JsonTokenKind::CommaToken);
  ASSERT_EQ(lexer->Lex()->Kind(), JsonTokenKind::ColonToken);
}

TEST_F(LexerTest, ReadsEndOfFileToken) {
  lexer = std::make_shared<Lexer>("");
  auto token = lexer->Lex();
  ASSERT_EQ(token->Kind(), JsonTokenKind::EndOfFileToken);
}
