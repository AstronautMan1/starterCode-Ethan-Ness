#include <cstdlib>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GLSL.h"

#include "SimpleCamera_Impl.h"

int CheckGLErrors(const char *s)
{
  int errCount = 0;
  return errCount;
}

int main(void)
{
  /* Initialize the library */
  if (!glfwInit()) {
    exit(-1);
  }
  // throw std::runtime_error("Error! initialization of glfw failed!");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  /* Create a windowed mode window and its OpenGL context */
  int winWidth = 1000;
  float aspectRatio = 1.0;// 16.0 / 9.0; // winWidth / (float)winHeight;
  int winHeight = winWidth / aspectRatio;

  GLFWwindow *window = glfwCreateWindow(winWidth, winHeight, "GLFW Example", NULL, NULL);
  if (!window) {
    std::cerr << "GLFW did not create a window!" << std::endl;

    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (err != GLEW_OK) {
    std::cerr << "GLEW Error! glewInit failed, exiting." << std::endl;
    exit(EXIT_FAILURE);
  }

  const GLubyte *renderer = glGetString(GL_RENDERER);
  const GLubyte *version = glGetString(GL_VERSION);
  std::cout << "Renderer: " << renderer << std::endl;
  std::cout << "OpenGL version supported: " << version << std::endl;

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glClearColor(0.08, 0.08, 0.1, 1.0);

  int fb_width, fb_height;
  glfwGetFramebufferSize(window, &fb_width, &fb_height);
  glViewport(0, 0, fb_width, fb_height);

  // Need to set a projection matrix that fits the aspect ratio set
  // by the window frame.
  //

  GLint major_version;
  glGetIntegerv(GL_MAJOR_VERSION, &major_version);
  std::cout << "GL_MAJOR_VERSION: " << major_version << std::endl;

  // Initialize all my data and get it on the GPU.
  // load the scene file...
  // get my shapes in the scene...

  GLuint m_triangleVBO[1], m_VAO;

  // load a triangle...
  // create a Vertex Array Buffer to hold our triangle data
  glGenBuffers(1, m_triangleVBO);
      
  glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO[0]);

  // this is the actual triangle data that will be copied to
  // the GPU memory
  std::vector<float> host_VertexBuffer{ -3.0f, -3.0f, 0.0f,// V0
                                        1.0, 0.08, 0.18,
                                        3.0f, -3.0f, 0.0f,// V1
                                        0.0, 0.95, 0.87,
                                        0.0f, 3.0f, 0.0f, // V2
                                        0.58, 0.0, 1.0};

  int numBytes = host_VertexBuffer.size() * sizeof(float);

  // copy the numBytes from host_VertexBuffer t the GPU and store in
  // the currently bound VBO
  glBufferData(GL_ARRAY_BUFFER, numBytes, host_VertexBuffer.data(), GL_STATIC_DRAW);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // once copied, we no longer need the data on the host
  host_VertexBuffer.clear();

  // VAO for the VBO
  // create a vertex array object that will map the attributes in
  // our vertex buffer to different location attributes for our
  // // shaders

  glGenVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);

  // VAO details here - we only have 1 attribute or location
  // (Position of the vertex)

  glEnableVertexAttribArray(0);  // enable attrib 0 - Vertex Position
  glEnableVertexAttribArray(1);  // enable attrib 1 - Vertex color

  glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO[0]);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const GLvoid *)12);  // Color
  glBindVertexArray(0);

  // Create a shader using my GLSLObject class
  sivelab::GLSLObject shader;
  shader.addShader( "vertexShader_withMatrices.glsl", sivelab::GLSLObject::VERTEX_SHADER );
  shader.addShader( "fragmentShader_barycentric.glsl", sivelab::GLSLObject::FRAGMENT_SHADER );
  shader.createProgram();

  GLuint projMatrixID, viewMatrixID, modelMatrixID;
  projMatrixID = shader.createUniform( "projMatrix" );
  viewMatrixID = shader.createUniform( "viewMatrix" );
  modelMatrixID = shader.createUniform( "modelMatrix" );

  glm::mat4 modelTransform = glm::mat4(1.0);
  // modelTransform = glm::translate(modelTransform, glm::vec3(0.0f, 1.0f, 0.0f));
  float rot = 0;
  modelTransform = glm::rotate(modelTransform, rot, glm::vec3(0, 1, 0));


  SimpleCamera_Impl cam;
  
  double timeDiff = 0.0, startFrameTime = 0.0, endFrameTime = 0.0;

  float rotAngle = 0.0f;

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    endFrameTime = glfwGetTime();
    timeDiff = endFrameTime - startFrameTime;
    startFrameTime = glfwGetTime();

    // Clear the window's buffer (or clear the screen to our
    // background color)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#if 0
    std::cout << "cam.getProjectionMatrix: \n"
              << '\t' << cam.getProjectionMatrix()[0][0] << ' ' << cam.getProjectionMatrix()[0][1] << ' ' << cam.getProjectionMatrix()[0][2] << ' ' << cam.getProjectionMatrix()[0][3] << '\n'
              << '\t' << cam.getProjectionMatrix()[1][0] << ' ' << cam.getProjectionMatrix()[1][1] << ' ' << cam.getProjectionMatrix()[1][2] << ' ' << cam.getProjectionMatrix()[1][3] << '\n'
              << '\t' << cam.getProjectionMatrix()[2][0] << ' ' << cam.getProjectionMatrix()[2][1] << ' ' << cam.getProjectionMatrix()[2][2] << ' ' << cam.getProjectionMatrix()[2][3] << '\n'
              << '\t' << cam.getProjectionMatrix()[3][0] << ' ' << cam.getProjectionMatrix()[3][1] << ' ' << cam.getProjectionMatrix()[3][2] << ' ' << cam.getProjectionMatrix()[3][3] << std::endl;

    std::cout << "cam.getViewMatrix: \n"
              << '\t' << cam.getViewMatrix()[0][0] << ' ' << cam.getViewMatrix()[0][1] << ' ' << cam.getViewMatrix()[0][2] << ' ' << cam.getViewMatrix()[0][3] << '\n'
              << '\t' << cam.getViewMatrix()[1][0] << ' ' << cam.getViewMatrix()[1][1] << ' ' << cam.getViewMatrix()[1][2] << ' ' << cam.getViewMatrix()[1][3] << '\n'
              << '\t' << cam.getViewMatrix()[2][0] << ' ' << cam.getViewMatrix()[2][1] << ' ' << cam.getViewMatrix()[2][2] << ' ' << cam.getViewMatrix()[2][3] << '\n'
              << '\t' << cam.getViewMatrix()[3][0] << ' ' << cam.getViewMatrix()[3][1] << ' ' << cam.getViewMatrix()[3][2] << ' ' << cam.getViewMatrix()[3][3] << std::endl;
#endif
 
    /* Render your objects here */
    shader.activate();

    modelTransform = glm::mat4(1.0);
    modelTransform = glm::rotate(modelTransform, rotAngle, glm::vec3(0, 1, 0));
    rotAngle += 0.05;
    if (rotAngle > 2.0*3.14159) rotAngle = 0.0f;

    // pass in the new camera matrix and the projection matrix    
    glUniformMatrix4fv(projMatrixID, 1, GL_FALSE, glm::value_ptr(cam.getProjectionMatrix()));
    glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, glm::value_ptr(cam.getViewMatrix()));
    glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(modelTransform));    
    
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    shader.deactivate();

    // Swap the front and back buffers
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cam.moveForward();
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cam.strafeLeft();
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cam.moveBackward();
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cam.strafeRight();
    }

    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
      std::cout << "fps: " << 1.0 / timeDiff << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, 1);
    }
  }

  glfwTerminate();
  return 0;
}
