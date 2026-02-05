/*
    @author Ethan Ness

    Implementation of the sphere class which implements the inherited pure virtual intersect function from the shape class

*/

/*
    include section
*/
#include "Sphere.h" // sphere class

/// @brief This handles the calculation for the intersect of a sphere it uses the quadratic 
///        equation to determine if the ray intersects the sphere shape if the discriminant
///        is greater than or equal to 0 there is an intersection if it is less then 0 there
///        is no intersection.
/// @param r a ray r passed in to see if that ray intersects the sphere
/// @return returns true if t1 or t2 is true which is greater than or equal to 0
///         which is calculated by taking -b - sqrt of the discriminant / a for t1
///         and -b + sqrt of the discriminant / a for t2 otherwise return false
bool Sphere::intersect(const ray& r){

    vec3 rayToSphere = r.origin() - center; // vector from the sphere center to the ray origin

    float a = dot(r.direction(), r.direction()); // a section of quadratic at^2 + bt + c = 0
    float b = 2.0f * dot(rayToSphere, r.direction()); // b section of quadratic at^2 + bt + c = 0
    float c = dot(rayToSphere, rayToSphere) - radius * radius; // c section of quadratic at^2 + bt + c = 0

    float discriminant = b * b - 4.0f * a * c; // discriminant = b^2 - 4ac

    if (discriminant < 0.0f){
        return false; // if discriminant is less than 0 it is not intersecting so return false
    }

    float sqrt_discriminant = std::sqrt(discriminant); // sqrt of discriminant

    float t1 = (-b - sqrt_discriminant) / (2.0f * a); // calculate t1 using quadratic formula

    float t2 = (-b + sqrt_discriminant) / (2.0f * a); // calculate t2 using quadratic formula

    if (t1 >= 0.0f){
        return true; // if t1 greater or equal to 0 it is intersecting the sphere so return true 
    }

    if (t2 >= 0.0f){
        return true; // if t2 greater or equal to 0 it is intersecting the sphere so return true
    }

    return false; // if nothing else happens just return false
}

/// @brief this is a getter to return the center
/// @return returns the center of the sphere
point3 Sphere::getCenter(){

    return center;

}

/// @brief This is a getter to return the radius
/// @return returns the radius of the sphere
float Sphere::getRadius(){

    return radius;
}

/// @brief seter for a new center for the sphere
/// @param newCenter the new center of the sphere we want to set
void Sphere::setCenter(point3 newCenter){

    center = newCenter;
}

/// @brief seter for a new radius for the sphere
/// @param newRadius the new radius of the sphere we want to set
void Sphere::setRadius(float newRadius){

    radius = newRadius;
}