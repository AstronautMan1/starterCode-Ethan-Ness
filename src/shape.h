/*
    @author Ethan Ness

    This is the shape interface class for making different classes
*/
#pragma once

/*
    includes section
*/
#include "ray.h" // ray class

/// @brief The shape interface which will be used for making different shapes
class Shape{

    public:

        Shape() {} // basic constructor

        virtual ~Shape() {} // basic deconstructor

        virtual bool intersect(const ray& r) = 0; // pure virtual intersect function

    private:

};