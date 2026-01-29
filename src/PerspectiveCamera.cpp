#include "PerspectiveCamera.h"

void PerspectiveCamera::generateRay (int i, int j, ray &r){

    float u, v;

    u = l + (r- l) *  (i + 0.5) / (float)nx;
    v = b + (t - b) * (j + 0.5) / (float)ny;


    r.setDirection(-W * focalLength + U*u + V*v);

}