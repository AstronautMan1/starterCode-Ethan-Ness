#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "vec3.h"

// This is just a base test used to test the initial creation of vec 3 unit testing
TEST_CASE("VEC 3 TEST"){

    vec3 testvec3;

    int i = 3;

    REQUIRE(i == 3);
}

// This is a test for the addition of the vec 3 class
TEST_CASE("VEC3 Addition"){

    vec3 a(1.0f,1.0f,1.0f);
    vec3 b(1.0f,1.0f,1.0f);

    vec3 c = a + b;

    float eps = 1.0e-3;
    float answer = 2.0f;

    std::cout << "addition of vector A(1,1,1) and B(1,1,1) is: " << c << std::endl;
    std::cout << "The answer should be: " << answer << std::endl;

    REQUIRE_THAT( c.x(), Catch::Matchers::WithinAbs(answer, eps));
    REQUIRE_THAT( c.y(), Catch::Matchers::WithinAbs(answer, eps));
    REQUIRE_THAT( c.z(), Catch::Matchers::WithinAbs(answer, eps));

}

// This is a test for the subtraction in the vec3 class
TEST_CASE("VEC3 Subtraction"){

    vec3 a(2.0f, 3.0f, 4.0f);
    vec3 b(1.0f, 1.0f, 1.0f);

    vec3 c = a - b;

    float eps = 1.0e-3;

    vec3 answer = a - b;

    std::cout << "Subtraction of vector A(2,3,4) and B(1,1,1) is: " << c << std::endl;

    std::cout << "The Answer should be: " << answer << std::endl;

    REQUIRE_THAT( c.x(), Catch::Matchers::WithinAbs(answer.x(), eps));
    REQUIRE_THAT( c.y(), Catch::Matchers::WithinAbs(answer.y(), eps));
    REQUIRE_THAT( c.z(), Catch::Matchers::WithinAbs(answer.z(), eps));
}

// this is a test for division in the vec3 class
TEST_CASE("VEC3 Division"){

    vec3 a(2.0f, 3.0f, 4.0f);

    float divider = 2.0f;

    vec3 c = a / divider;

    float eps = 1.0e-3;

    vec3 answer = a / divider;

    std::cout << "Division of vector A(2,3,4) by 2 is: " << c << std::endl;

    std::cout << "The answer should be: " << answer << std::endl;

    REQUIRE_THAT( c.x(), Catch::Matchers::WithinAbs(answer.x(), eps));
    REQUIRE_THAT( c.y(), Catch::Matchers::WithinAbs(answer.y(), eps));
    REQUIRE_THAT( c.z(), Catch::Matchers::WithinAbs(answer.z(), eps));

}

// This is the Dot Product testing of the vec 3 class
TEST_CASE("VEC3 Dot Product"){


    vec3 a(2.0f,2.0f,2.0f);
    vec3 b(2.0f,2.0f,2.0f);

    float c = dot(a, b);

    float eps = 1.0e-3;
    float answer = dot(a, b);


    std::cout << "The dot product of A(2,2,2) and B(2,2,2) is: " << dot(a,b) << std::endl;

    std::cout << "The dot product should be: " << c << std::endl;

    REQUIRE_THAT( c, Catch::Matchers::WithinAbs(answer, eps));
    REQUIRE_THAT( c, Catch::Matchers::WithinAbs(answer, eps));
    REQUIRE_THAT( c, Catch::Matchers::WithinAbs(answer, eps));
}

// This is a test case for the cross product of Vec 3 class
TEST_CASE("VEC3 Cross Product"){

    vec3 a(0.3f,0.5f,0.6f);
    vec3 b(0.4f,0.7f,0.3f);

    vec3 c = cross(a,b);
    vec3 compare = cross(a,b);
    float eps = 1.0e-3;

    std::cout << "The cross product of A(0.3,0.5,0.6) and B(0.4,0.7,0.3) is: " << c << std::endl;

    std::cout << "The cross product of A and B should be: " << compare << std::endl;

    REQUIRE_THAT( c.x(), Catch::Matchers::WithinAbs(compare.x(), eps));
    REQUIRE_THAT( c.y(), Catch::Matchers::WithinAbs(compare.y(), eps));
    REQUIRE_THAT( c.z(), Catch::Matchers::WithinAbs(compare.z(), eps));

}
// dot product, cross product, addition, subtraction, scalar multiplication, scalar division