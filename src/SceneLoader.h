#pragma once

#include "ISceneLoader.h"
#include "SceneContainer.h"
#include "shape.h"
#include "BlinnPhongShader.h"
#include "LambertianShader.h"
#include "MirrorShader.h"
#include <iostream>

class SceneLoader : public ISceneLoader {
private:
  SceneContainer &m_targetScene; // Reference to the external scene

public:
  // The caller provides the scene to be filled
  SceneLoader(SceneContainer &sceneToPopulate)
      : m_targetScene(sceneToPopulate), numShaders(0), numTextures(0) {}

  void reserveCameras(size_t count) override {
    // makes sure the vector has enough space
    m_targetScene.cameras.reserve(count);
  }

  void reserveLights(size_t count) override {
    m_targetScene.lights.reserve(count);
  }
  void reserveShapes(size_t count) override {
    m_targetScene.shapes.reserve(count);
  }
  void reserveShaders(size_t count) override { numShaders = count; }
  void reserveTextures(size_t count) override { numTextures = count; }

  void setSceneParams(const SceneParams &sparams) override {
    std::cout << "Setting scene params." << std::endl;
  }

  void addCamera(const std::string &name, const std::string &type,
                 const ISceneLoader::vec &pos, const ISceneLoader::vec &viewDir,
                 float focalLength, float imagePlaneWidth) override {
    std::cout << "Creating camera: " << name << ", type:" << type << std::endl;

    vec3 position(pos.x,pos.y,pos.z);
    vec3 lookDir(viewDir.x,viewDir.y,viewDir.z);

    vec3 W = unit_vector(-lookDir);

    vec3 worldUp(0,1,0);
    if (std::abs(dot(W,worldUp)) > 0.99f) worldUp = vec3(1,0,0);

    vec3 U = unit_vector(cross(worldUp, W));
    vec3 V = cross(W,U);

    float aspectRatio = 16.0f/9.0f;
    float planeWidth = imagePlaneWidth;
    float planeHeight = planeWidth / aspectRatio;

    auto pc = std::make_shared<PerspectiveCamera>(position, U, V, W, focalLength, planeWidth, planeHeight, 1920, 1080);

    m_targetScene.camera = pc;

    /*
    auto cam = std::make_shared<Camera>();
    cam->type = type;
    m_targetScene.cameras.push_back(cam);
    */
  }
  void addPointLight(const ISceneLoader::vec &pos,
                     const ISceneLoader::vec &intensity) override {
    std::cout << "Creating point light." << std::endl;


    point3 lightpos(pos.x,pos.y,pos.z);
    vec3 lightIntensity(intensity.x, intensity.y, intensity.z);

    auto light = std::make_shared<Light>(lightpos, lightIntensity, "point light");

    //auto light = std::make_shared<Light>();
    //light->type = "Point Light";

    m_targetScene.lights.push_back(light);
  }
  void addAreaLight(const ISceneLoader::vec &pos,
                    const ISceneLoader::vec &color,
                    const ISceneLoader::vec &normal, float width,
                    float length) override {
    std::cout << "Creating area light." << std::endl;
  }
  void addShader(const ISceneLoader::ShaderDesc &shaderDesc) override {
    std::cout << "Creating shader: type=" << shaderDesc.type << std::endl;
    // I place my shaders on an unordered map often
    std::shared_ptr<shader> newShader;

    if(shaderDesc.type == "Lambertian"){
        vec3 LColor(shaderDesc.diffuse.data.x,shaderDesc.diffuse.data.y, shaderDesc.diffuse.data.z);
        newShader = std::make_shared<LambertianShader>(LColor);
    }
    else if(shaderDesc.type == "BlinnPhong"){
        vec3 BColor(shaderDesc.diffuse.data.x,shaderDesc.diffuse.data.y, shaderDesc.diffuse.data.z);
        float SpecStrength = (shaderDesc.specular.data.x + shaderDesc.specular.data.y + shaderDesc.specular.data.z) / 3;
        newShader = std::make_shared<BlinnPhongShader>(BColor, shaderDesc.phongExp, SpecStrength);
    }
    else if(shaderDesc.type == "Mirror"){
        newShader = std::make_shared<MirrorShader>(vec3(1,1,1), 1.0f);
    }

    if(newShader){
        std::cout << "Debuging storing shader with the key: [" << shaderDesc.name << "]" << std::endl;
        mapShader[shaderDesc.name] = newShader;
    }

  }
  void addShape(const ISceneLoader::ShapeDesc &shapeDesc) override {

    std::cout << "Creating shape: type=" << shapeDesc.type << std::endl;
    std::cout << "Debug: shape is looking for key: [" << shapeDesc.shaderNameReference << "]" << std::endl;

    auto it = mapShader.find(shapeDesc.shaderNameReference);
    std::shared_ptr<shader> shapeShader = (it != mapShader.end()) ? it->second : nullptr;

    if (!shapeShader){
        std::cout << "Warning shader" << shapeDesc.shaderNameReference << "not found using fallback" << std::endl;
        shapeShader = std::make_shared<LambertianShader>(vec3(1,0,1));
    }

    std::shared_ptr<Shape> s = nullptr;
    if(shapeDesc.type == "sphere"){
        vec3 center(shapeDesc.center.x, shapeDesc.center.y, shapeDesc.center.z);
        s = std::make_shared<Sphere>(center, shapeDesc.radius, shapeShader);
    }
    else if(shapeDesc.type == "triangle"){
        vec3 vertex1(shapeDesc.v0.x, shapeDesc.v0.y, shapeDesc.v0.z);
        vec3 vertex2(shapeDesc.v1.x, shapeDesc.v1.y, shapeDesc.v1.z);
        vec3 vertex3(shapeDesc.v2.x, shapeDesc.v2.y, shapeDesc.v2.z);

        s = std::make_shared<Triangle>(vertex1, vertex2, vertex3, shapeShader);

    }
    if (s){
        m_targetScene.shapes.push_back(s);
        m_targetScene.world.add(s);
    }
  }
  void addTexture(const std::string &type, const std::string &name,
                  const std::string &sourceFile) override {
    std::cout << "Creating texture: type=" << type << ", name=" << name
              << ", sourceFile=" << sourceFile << std::endl;
  }

public:
  int numShaders;
  int numTextures;

  std::map<std::string, std::shared_ptr<shader>> mapShader;
};