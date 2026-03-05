#pragma once

#include <memory>
#include <vector>
#include <iostream>
#include "Light.h"
#include "shape.h"
#include "PerspectiveCamera.h"
#include "hitList.h"

/*
class Light {
public:
  std::string type;
};

class Shape {
public:
  std::string type;
};

class Camera {
public:
  std::string type;
};

*/
class SceneContainer {
  friend class SceneLoader; // this will allow the scene loader to
                            // manipulate the Scene

private:

  std::vector<std::shared_ptr<Camera>> cameras;

public:
  SceneContainer() = default;
  std::vector<std::shared_ptr<Light>> lights;
  std::shared_ptr<PerspectiveCamera> camera;
  hitList world;
  vec3 backgroundColor = vec3(0.5,0.5,0.5);
  std::vector<std::shared_ptr<Shape>> shapes;
};