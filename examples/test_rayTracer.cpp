#include "framebuffer.h"
#include "ray.h"
#include "vec3.h"
#include "camera.h"
#include "PerspectiveCamera.h"


#include <iostream>


vec3 directionToColor(const vec3 &direction){

    vec3 normalized = unit_vector(direction);

    vec3 colorOfRay = (normalized + vec3(1.0f,1.0f,1.0f) ) * 0.5f;

    return colorOfRay;

}


void rayTester(){

    Framebuffer fb(800,800);

    vec3 position(0,0,-1);
    vec3 U(1,0,0);
    vec3 V(0,1,0);
    vec3 W(0,0,1);
    float focal = 1.0f;
    float planeWidth = 0.25f;
    float planeHeight = 0.25f;

    PerspectiveCamera pc(position, U, V, W, focal, planeWidth, planeHeight, fb.getWidth(), fb.getHeight());

    for(int x(0); x < fb.getWidth(); ++x){
        for(int y(0); y < fb.getHeight(); ++y){

            ray R;

            pc.generateRay(x,y,R);

            vec3 color = directionToColor(R.direction());

            fb.setPixelColor(x, y, color);
        }
    }

    fb.exportToPNG("raytracetester.png");

}

int main(){

    rayTester();
    return 0;
}