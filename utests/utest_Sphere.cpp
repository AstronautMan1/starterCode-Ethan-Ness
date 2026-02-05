/*
    @author Ethan Ness

    unit test for the sphere class

*/

/*
    Includes Section
*/
#include <catch2/catch_test_macros.hpp> // catch 2 unit rquirements
#include <catch2/matchers/catch_matchers_floating_point.hpp> // catch 2 unit rquirements
#include "Sphere.h" // sphere class
#include "ray.h" // ray class


TEST_CASE("basic sphere construction test"){

    Sphere s1(point3 (1,1,1), 10.0f);

    std::cout << "Sphere center is at: " << s1.getCenter() << std::endl;

    std::cout << "Sphere radius is: " << s1.getRadius() << std::endl;

    REQUIRE(s1.getCenter().x() == 1);
    REQUIRE(s1.getCenter().y() == 1);
    REQUIRE(s1.getCenter().z() == 1);

    REQUIRE(s1.getRadius() == 10.0f);

}

TEST_CASE("Intersect test") {

    Sphere s1(point3(1,1,1), 1.0f);

    ray r1(point3(0,0,0), point3(1,1,1));

    REQUIRE(s1.intersect(r1) == true);

    Sphere s2(point3(20,20,0), 1.0f);

    ray r2(point3(0,0,0), point3(1,1,1));

    REQUIRE(s2.intersect(r2) == false);

}
