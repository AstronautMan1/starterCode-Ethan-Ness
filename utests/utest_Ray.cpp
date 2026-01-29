#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "ray.h"
#include "vec3.h"

TEST_CASE("Ray Constructor and origin/direction return"){

    vec3 origin(0,0,0);
    vec3 direction(1,1,1);
    ray madeRay(origin, direction);

    std::cout << "Test of Ray Constructor and Origin/Direction Return" << std::endl;
    std::cout << std::string(30, '-') << std::endl;
    std::cout << madeRay.direction() << std::endl;
    std::cout << madeRay.origin() << std::endl;

    vec3 madeRayReturnDirection = madeRay.direction();

    vec3 madeRayReturnOrigin = madeRay.origin();

    REQUIRE(madeRayReturnDirection.x() == direction.x());
    REQUIRE(madeRayReturnDirection.y() == direction.y());
    REQUIRE(madeRayReturnDirection.z() == direction.z());
    REQUIRE(madeRayReturnOrigin.x() == origin.x());
    REQUIRE(madeRayReturnOrigin.y() == origin.y());
    REQUIRE(madeRayReturnOrigin.z() == origin.z());

}

TEST_CASE("Ray testing at function"){

    vec3 origin(1,1,1);
    vec3 direction(2,2,2);

    ray madeRay(origin, direction);

    double test1 = 0;
    double test2 = 1;
    double test3 = 32;
    double test4 = -22;

    vec3 test1Result = madeRay.at(test1);
    vec3 test2Result = madeRay.at(test2);
    vec3 test3Result = madeRay.at(test3);
    vec3 test4Result = madeRay.at(test4);

    std::cout << "Output of Ray Testing of the at() function" << std::endl;
    std::cout << std::string(30, '-') << std::endl;
    std::cout << test1Result << std::endl;
    std::cout << test2Result << std::endl;
    std::cout << test3Result << std::endl;
    std::cout << test4Result << std::endl;

    REQUIRE(test1Result.x() == madeRay.at(test1).x());
    REQUIRE(test1Result.y() == madeRay.at(test1).y());
    REQUIRE(test1Result.z() == madeRay.at(test1).z());

    REQUIRE(test2Result.x() == madeRay.at(test2).x());
    REQUIRE(test2Result.y() == madeRay.at(test2).y());
    REQUIRE(test2Result.z() == madeRay.at(test2).z());

    REQUIRE(test3Result.x() == madeRay.at(test3).x());
    REQUIRE(test3Result.y() == madeRay.at(test3).y());
    REQUIRE(test3Result.z() == madeRay.at(test3).z());

    REQUIRE(test4Result.x() == madeRay.at(test4).x());
    REQUIRE(test4Result.y() == madeRay.at(test4).y());
    REQUIRE(test4Result.z() == madeRay.at(test4).z());

}
