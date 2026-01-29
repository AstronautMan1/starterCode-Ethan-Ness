#include "PerspectiveCamera.h"

void PerspectiveCamera::generateRay (int i, int j, ray &R){

    R.setOrigin(pos);

    
    float u = l + (r - l) * (i + 0.5f) / (float)nx;

    float v = t + (b - t) * (j + 0.5f) / (float)ny;

    vec3 direction = -W * focalLength + u * U + v * V;

    R.setDirection(direction);
}