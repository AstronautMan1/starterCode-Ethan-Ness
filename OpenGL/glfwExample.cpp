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

#include "PerspectiveCamera.cpp"

int CheckGLErrors(const char *s)
{
    int errCount = 0;
    return errCount;
}

int main(void)
{
    /* Initialize the library */
    if (!glfwInit()) {
        exit (-1);
    }
    // throw std::runtime_error("Error! initialization of glfw failed!");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    PerspectiveCamera camera(vec3(0,0,5), vec3(1,0,0), vec3(0,1,0), vec3(0,0,1), 1.0f, 0.1f, 100.0f, 1000, 1000); // order of parameters (position, u, v, w, focal, image plane width, image plane length, image size x, image size y)

    /* Create a windowed mode window and its OpenGL context */
    //int winWidth = 1000;
    //int winWidth = camera.getNX();
    //float aspectRatio = 1.0; // 16.0 / 9.0; // winWidth / (float)winHeight;
    //int winHeight = winWidth / aspectRatio;
    
    //GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, "GLFW Example", NULL, NULL);
    GLFWwindow* window = glfwCreateWindow(camera.getNX(), camera.getNY(), "GLFW Example", NULL, NULL);
    if (!window) {
        std::cerr << "GLFW did not create a window!" << std::endl;
        
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    GLenum err=glewInit();
    if(err != GLEW_OK) {
        std::cerr <<"GLEW Error! glewInit failed, exiting."<< std::endl;
        exit(EXIT_FAILURE);
    }

    const GLubyte* renderer = glGetString (GL_RENDERER);
    const GLubyte* version = glGetString (GL_VERSION);
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported: " << version << std::endl;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.5, 0.5, 0.5, 1.0); //RGB and Alpha which is opaque 

    int fb_width, fb_height;
    glfwGetFramebufferSize(window, &fb_width, &fb_height);
    glViewport(0, 0, fb_width, fb_height);

    // Need to set a projection matrix that fits the aspect ratio set
    // by the window frame.
    //
    // The ortho parameters, in order: left, right, bottom, top, zNear, zFar
    //float halfWidth = 15.0 / 2.0;
    //float halfHeight = halfWidth / aspectRatio;
    //glm::mat4 projectionMatrix = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, -10.0f, 10.0f);

    // The ortho parameters, in order: left, right, bottom, top, zNear, zFar for the ortho matrix
    //float halfWidth = 15.0 / 2.0;
    //float halfHeight = halfWidth;

    //float left = -halfWidth;
    //float right = halfWidth;

    //float bottom = -halfHeight;
    //float top = halfHeight;

    //float near = 5.0f;
    //float far = -5.0f;

    //glm::mat4 M_ortho = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, near, far); // ortho

    //glm::mat4 M_ortho = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f); // perspective

    //float aspect = (float)camera.getNX() / (float)camera.getNY();

    glm::mat4 M_ortho = glm::perspective(glm::radians(45.0f),( (float)camera.getNX() / (float)camera.getNY() ),0.1f, 100.0f); // perspective

    //glm::vec3 m_pos(0,0,0), m_viewDir(0,0,-1);
    //glm::vec3 m_U(1,0,0), m_V(0,1,0), m_W(0,0,1);

    glm::vec3 m_pos(camera.getPos().x(),camera.getPos().y(),camera.getPos().z()), m_viewDir(0,0,-1);
    glm::vec3 m_U(camera.getU().x(),camera.getU().y(),camera.getU().z()), m_V(camera.getV().x(),camera.getV().y(),camera.getV().z()), m_W(camera.getW().x(),camera.getW().y(),camera.getW().z());

    double timeDiff = 0.0, startFrameTime = 0.0, endFrameTime = 0.0;



    GLint major_version;
    glGetIntegerv(GL_MAJOR_VERSION, &major_version);
    std::cout << "GL_MAJOR_VERSION: " << major_version << std::endl;

    //double timeDiff = 0.0, startFrameTime = 0.0, endFrameTime = 0.0;
    
    // get it on the GPU 
    // load scene file
    // get the shapes in the scene

    // load triangle
    // create a vertex array buffer to hold our triangle data

    // Scene images 

    /* VBO Vertex Buffer Object */

    GLuint m_triangleVBO[1], m_VAO; // triangle int array using the GLuint basically integer
    //sivelab::GLSLObject shader;

    // create a Vertex Array Buffer to hold our triangle data                                               
    glGenBuffers(1, m_triangleVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO[0]);

// this is the actual triangle data that will be copied to                                              
// the GPU memory                                                                                       
    std::vector< float > host_VertexBuffer
    {   -3.0f, -3.0f, 0.0f, 0.0f, 0.0f, 1.0f,   // V0                                    
        3.0f, -3.0f, 0.0f, 0.0f, 0.0f, 1.0f,    // V1                                    
        0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 1.0f     // V2 
    };       
                 

    int numBytes = host_VertexBuffer.size() * sizeof(float); // buffer works in bytes so this calculates the bytes of the vector of triangles 

    // buffer can only do one thing at a time
    // copy the numBytes from host_VertexBuffer t the GPU and store in                                      
    // the currently bound VBO                                                                              
    glBufferData(GL_ARRAY_BUFFER, numBytes, host_VertexBuffer.data(), GL_STATIC_DRAW); // bind buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind buffer

    // once copied, we no longer need the data on the host                                                  
    host_VertexBuffer.clear(); // clear the data from CPU or Host


    /* VAO or Vertex Array Objects For the objects because the GPU doesn't know the VBO you gave it*/

    // create a vertex array object that will map the attributes in                                         
    // our vertex buffer to different location attributes for our                                           
    // shaders                                                                                              
    glGenVertexArrays(1, &m_VAO); // make VAO
    glBindVertexArray(m_VAO); // bind VAO to say work on this one

    // VAO details here - we only have 1 attribute or location                                              
    // (Position of the vertex)                                                                             
    glEnableVertexAttribArray(0); // enable attributes in this case 1
    glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO[0]); // bind the VBO to the VAO

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0); // Sets the attributes
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    /* Shaders for triangle */

    // Create a shader using my GLSLObject class                                                            
    //sivelab::GLSLObject shader; // make shader
    //shader.addShader( "vertexShader_passthrough.glsl", sivelab::GLSLObject::VERTEX_SHADER ); // add the vertex shader (gets the triangle on screen or moving stuff)
    //shader.addShader( "fragmentShader_passthrough.glsl", sivelab::GLSLObject::FRAGMENT_SHADER ); // add the fragment shader (this is for all pixels in triangle color them)
    //shader.createProgram(); // then compile and link them

    /*We have to make a fragment and vertex shader in the build folder with names above*/


    /* Shaders for a Movable triangle*/

    sivelab::GLSLObject shader;
    shader.addShader("vertexShader_normal.glsl", sivelab::GLSLObject::VERTEX_SHADER);
    shader.addShader("fragmentShader_normal.glsl", sivelab::GLSLObject::FRAGMENT_SHADER);
    shader.createProgram();

    GLuint projMatrixID, viewMatrixID, modelMatrixID, normalMatrixID;
    projMatrixID = shader.createUniform("projMatrix");
    viewMatrixID = shader.createUniform("viewMatrix");
    modelMatrixID = shader.createUniform("modelMatrix");
    normalMatrixID = shader.createUniform("normalMatrix");

    GLint lightPosWorldID = shader.createUniform("lightPosWorld"); // light position for lambertian and blinnphong
    GLint diffuseComponentID = shader.createUniform("diffuseComponent"); // diffuse component for lambertian and blinnphong

    GLint cameraPosWorldID = shader.createUniform("cameraPosWorld");
    GLint specularComponentID = shader.createUniform("specularComponent");
    GLint shininessID = shader.createUniform("shininess");

    //glm::mat4 modelTransform = glm::mat4(1.0);
    //modelTransform = glm::rotate(modelTransform, 0.0f , glm::vec3(0,1,0));


    /*Render Triangle stage in while loop*/

    //GLint projMatrixID = shader.createUniform("projMatrix");

    /* Camera information */
    //glm::vec3 m_pos(0,0,0), m_viewDir(0,0,-1);
    //glm::vec3 m_U(1,0,0), m_V(0,1,0), m_W(0,0,1);

    //double timeDiff = 0.0, startFrameTime = 0.0, endFrameTime = 0.0;

    float rotAngle = 0.0f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        endFrameTime = glfwGetTime();
        timeDiff = endFrameTime - startFrameTime;
        startFrameTime = glfwGetTime();

        // Clear the window's buffer (or clear the screen to our
        // background color)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 M_view = glm::lookAt(m_pos, m_pos - m_W, m_V);

        /* Render your objects here */

        /* Movable Camera render*/

        shader.activate();

        glm::mat4 modelTransform = glm::mat4(1.0);
        modelTransform = glm::rotate(modelTransform, rotAngle , glm::vec3(0,1,0));
        rotAngle += 0.001;
        if(rotAngle > 2.0 * 3.14159) rotAngle = 0.0f;

        glm::mat4 normalMatrix = glm::transpose(glm::inverse(modelTransform));

        glUniformMatrix4fv(projMatrixID, 1, GL_FALSE, glm::value_ptr( M_ortho));
        glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, glm::value_ptr(M_view));
        glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(modelTransform));

        glUniformMatrix4fv(normalMatrixID, 1, GL_FALSE, glm::value_ptr(normalMatrix));
        glUniform4f(lightPosWorldID, 0.0f, 2.0f, 5.0f, 1.0f);
        glUniform3f(diffuseComponentID, 0.2f, 0.2f, 1.0f);

        glUniform3f(cameraPosWorldID, m_pos.x, m_pos.y, m_pos.z);
        glUniform3f(specularComponentID, 1.0f, 1.0f, 1.0f);
        glUniform1f(shininessID, 32.0f);

        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        shader.deactivate();

        
        /*Render Triangle stage in while loop*/
        /* Render your objects here */
        //shader.activate(); // activate shader
        //glBindVertexArray(m_VAO); // bind the vertex array
        //glDrawArrays(GL_TRIANGLES, 0, 3); // draw the arrays of triangles
        //glBindVertexArray(0); // unbind
        //shader.deactivate(); // deactivate shader
    

        // Swap the front and back buffers
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        float moveRatePerFrame = 0.05;

        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
            m_pos = m_pos + -m_W * moveRatePerFrame;
        }
        else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
            m_pos = m_pos - m_U * moveRatePerFrame;
        }
        else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
            m_pos = m_pos + m_W * moveRatePerFrame;
        }
        else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
            m_pos = m_pos + m_U * moveRatePerFrame;
        }

        if (glfwGetKey( window, GLFW_KEY_T ) == GLFW_PRESS) {
            std::cout << "fps: " << 1.0/timeDiff << std::endl;
        }
        if (glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, 1);
        }
    }
  
    glfwTerminate();
    return 0;
}
