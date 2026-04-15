#pragma once

#include "vec3.h"
#include "ray.h"

class BoundingBox{

    public:

        vec3 min;

        vec3 max;

        BoundingBox() {}

        BoundingBox(const vec3& minIn, const vec3& maxIn) : min(minIn), max(maxIn) {}

        bool hit(const ray& r, float tmin, float tmax) const {
            for (int a = 0; a < 3; ++a){
                float invD = 1.0f / r.direction()[a];
                float t0 = (min[a] - r.origin()[a]) * invD;
                float t1 = (max[a] - r.origin()[a]) * invD;

                if(invD < 0.0f) std::swap(t0, t1);
                tmin = t0 > tmin ? t0 : tmin;
                tmax = t1 < tmax ? t1 : tmax;
                if (tmax <= tmin) return false;

            }
            return true;
        }



        static BoundingBox mergeBoundingBoxes(const BoundingBox &b0, const BoundingBox &b1) {
            vec3 small(fmin(b0.min.x(), b1.min.x()),
                       fmin(b0.min.y(), b1.min.y()),
                       fmin(b0.min.z(), b1.min.z()));


            vec3 big(fmax(b0.max.x(), b1.max.x()),
                     fmax(b0.max.y(), b1.max.y()),
                     fmax(b0.max.z(), b1.max.z()));

            return BoundingBox(small, big);
        }

};