#include "gtest/gtest.h"

#include "jsoncpp/UseCases/Lex.test.hpp"
#include "jsoncpp/UseCases/Parse.test.hpp"

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}