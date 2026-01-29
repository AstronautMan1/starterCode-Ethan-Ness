#include "PerspectiveCamera.h"

void PerspectiveCamera::generateRay (int i, int j, ray &R){

    R.setOrigin(pos);

    
    float u = leftBound + (rightBound - leftBound) * (i + 0.5f) / (float)nx;

    float v = topBound + (bottomBound - topBound) * (j + 0.5f) / (float)ny;

    vec3 direction = -W * focalLength + u * U + v * V;

    R.setDirection(direction);
}