/*
    @author Ethan Ness

    This is the hit record class which handles keeping a record of objects hit with a front face, point of hit, normal, and t value
*/

#pragma once

/*
    includes section
*/
#include "vec3.h" // vec3 class
#include "ray.h" // ray class

/// @brief The hit record class 
class hit_record {

    public:

        void set_face_normal(const ray &r, const vec3 &outward_normal); // the normal of the face of the object where we hit with ray

        point3 getPoint() const {return point;} // getter for point

        vec3 getNormal() const {return normal;} // getter for normal

        double getT() const {return t;} // getter for T

        bool getFront_Face() const {return front_face;} // getter for front face

        void setPoint(point3 newPoint) {point = newPoint;} // setter for the point

        void setNormal(vec3 newNormal) {normal = newNormal;} // setter for the normal

        void setT(double newT) {t = newT;} // setter for the T value

        void setFront_Face(bool newFront_Face) {front_face = newFront_Face;} // setter for the front face

    private:

        point3 point; // point of impact of ray

        vec3 normal; // normal of the ray

        double t; // t of the object

        bool front_face; // did the ray hit the front or back of the object true if front

};