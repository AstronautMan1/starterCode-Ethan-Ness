/*
    @author Ethan Ness
    @author Peter Willemsen

    The implementation of the triangle class
*/

/*
    Includes section
*/
#include "triangle.h" // triangle class


/// @brief Intersect function for the triangle class which handles if a ray intersects the triangle using
///        Barycentric grid calculation
/// @param r The ray we are testing for intersection
/// @param tmin The tmin 
/// @param tmax The tmax
/// @return we return a boolean true or false in there was an intersection
bool Triangle::intersect(const ray &r, float tmin, float &tmax){

    // all the a through l calculations 
    double a = vertex_a[0] - vertex_b[0];
    double b = vertex_a[1] - vertex_b[1];
    double c = vertex_a[2] - vertex_b[2];

    double d = vertex_a[0] - vertex_c[0];
    double e = vertex_a[1] - vertex_c[1];
    double f = vertex_a[2] - vertex_c[2];

    double g = r.direction()[0];
    double h = r.direction()[1];
    double i = r.direction()[2];

    double j = vertex_a[0] - r.origin()[0];
    double k = vertex_a[1] - r.origin()[1];
    double l = vertex_a[2] - r.origin()[2];

    // all the a through l multiplied by and minus each other calculations
    double ei_minus_hf = e*i - h*f;
    double gf_minus_di = g*f - d*i;
    double dh_minus_eg = d*h - e*g;
    double ak_minus_jb = a*k - j*b;
    double jc_minus_al = j*c - a*l;
    double bl_minus_kc = b*l - k*c;

    double M = a * ei_minus_hf + b * gf_minus_di + c * (dh_minus_eg); // M calculation

    double beta = (j * ei_minus_hf + k * gf_minus_di + l * dh_minus_eg) / M; // betta calculation

    double gamma = (i * ak_minus_jb + h * jc_minus_al + g * bl_minus_kc) / M; // gamma calculation

    double t = -(f * ak_minus_jb + e * jc_minus_al + d * bl_minus_kc) / M; // t calculation

    if (std::abs(M) < 1e-8) return false; // if the determinant is near zero return false

    if(beta < 0.0 || beta > 1.0) return false; // if beta is less then 0 or greater then 1 return false

    if(gamma < 0.0 || (beta + gamma) > 1.0) return false; // if gamma is less then 0 or beta + gamma is greater then 1 return false

    if (t >= tmin && t <= tmax) { // if t is greater then or equal to tmin and t is less than or equal to tmax set t as the new tmax and return true
        tmax = (float)t;
        return true;
    }

    return false; // if nothing else return false

}