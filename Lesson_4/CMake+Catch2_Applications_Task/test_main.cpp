#include <iostream>
#include "factorial.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>


TEST_CASE("test factorial", "[factorial]") 
{
	CHECK(factorial(1) == 5);
	SECTION("positive numbers") {
		CHECK(factorial(1) == 1);
		CHECK(factorial(5) == 120);
		CHECK(factorial(10) == 3628800);
	}
}
int main(int argc, char* argv[]) {
	return Catch::Session().run(argc, argv);
	return 0;
}

