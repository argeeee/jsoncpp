#pragma once

#include "gtest/gtest.h"

#include "jsoncpp/UseCases/Parse.hpp"

class ParserTest : public ::testing::Test {
	protected:
	 std::shared_ptr<Parser> parser;
 
	 void SetUp() override {
		 // ignore
	 }
 };

TEST_F(ParserTest, ParsesNumberToken) {
	parser = make_shared<Parser>("123");
	auto expression = parser->Parse();
	ASSERT_EQ(expression->Kind(), JsonExpressionKind::Number);
	ASSERT_EQ(any_cast<long>(expression->Value()), 123);
}

TEST_F(ParserTest, ParsesStringToken) {
	parser = make_shared<Parser>("\"hello\"");
	auto expression = parser->Parse();
	ASSERT_EQ(expression->Kind(), JsonExpressionKind::String);
	ASSERT_EQ(any_cast<std::string>(expression->Value()), "hello");
}

TEST_F(ParserTest, ParsesBooleanTrue) {
	parser = make_shared<Parser>("true");
	auto expression = parser->Parse();
	ASSERT_EQ(expression->Kind(), JsonExpressionKind::Bool);
	ASSERT_EQ(any_cast<bool>(expression->Value()), true);
}

TEST_F(ParserTest, ParsesBooleanFalse) {
	parser = make_shared<Parser>("false");
	auto expression = parser->Parse();
	ASSERT_EQ(expression->Kind(), JsonExpressionKind::Bool);
	ASSERT_EQ(any_cast<bool>(expression->Value()), false);
}

TEST_F(ParserTest, ParsesNullToken) {
	parser = make_shared<Parser>("null");
	auto expression = parser->Parse();
	ASSERT_EQ(expression->Kind(), JsonExpressionKind::Null);
}

TEST_F(ParserTest, ParsesArray) {
	parser = make_shared<Parser>("[1, \"text\", true, null]");
	auto expression = parser->Parse();
	ASSERT_EQ(expression->Kind(), JsonExpressionKind::Array);
	auto elements = any_cast<std::vector<std::shared_ptr<JsonExpression>>>(expression->Value());
	ASSERT_EQ(elements.size(), 4);
	ASSERT_EQ(elements[0]->Kind(), JsonExpressionKind::Number);
	ASSERT_EQ(any_cast<long>(elements[0]->Value()), 1);
	ASSERT_EQ(elements[1]->Kind(), JsonExpressionKind::String);
	ASSERT_EQ(any_cast<std::string>(elements[1]->Value()), "text");
	ASSERT_EQ(elements[2]->Kind(), JsonExpressionKind::Bool);
	ASSERT_EQ(any_cast<bool>(elements[2]->Value()), true);
	ASSERT_EQ(elements[3]->Kind(), JsonExpressionKind::Null);
}

TEST_F(ParserTest, ParsesObject) {
	parser = make_shared<Parser>("{\"key\": 42, \"text\": \"hello\"}");
	auto expression = parser->Parse();
	ASSERT_EQ(expression->Kind(), JsonExpressionKind::Object);
	auto object = any_cast<std::unordered_map<std::string, std::shared_ptr<JsonExpression>>>(expression->Value());
	ASSERT_EQ(object.size(), 2);
	ASSERT_EQ(object["key"]->Kind(), JsonExpressionKind::Number);
	ASSERT_EQ(any_cast<long>(object["key"]->Value()), 42);
	ASSERT_EQ(object["text"]->Kind(), JsonExpressionKind::String);
	ASSERT_EQ(any_cast<std::string>(object["text"]->Value()), "hello");
}

TEST_F(ParserTest, ThrowsOnUnexpectedToken) {
	ASSERT_THROW(parser = make_shared<Parser>("@unexpected"), std::runtime_error);
}
