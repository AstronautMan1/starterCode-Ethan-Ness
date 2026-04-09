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

float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 500.0f, lastY = 500.0f;
bool firstMouse = true;

float sensitivity = 0.1f;

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if (firstMouse){
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;
}

int CheckGLErrors(const char *s)
{
    int errCount = 0;
    return errCount;
}

struct Vertex{
    glm::vec3 position;
    glm::vec3 normal;
};

Vertex getMidpoint(Vertex v1, Vertex v2, float radius){
    glm::vec3 mid = glm::normalize((v1.position + v2.position) * 0.5f) * radius;
    return {mid, glm::normalize(mid)};
}

void subDivide(Vertex v1, Vertex v2, Vertex v3, std::vector<float>& buffer, int depth, float radius){
    if (depth == 0){
        Vertex verts[3] = {v1, v2, v3};
        for(int i = 0; i < 3; ++i){
            buffer.push_back(verts[i].position.x);
            buffer.push_back(verts[i].position.y);
            buffer.push_back(verts[i].position.z);
            buffer.push_back(verts[i].normal.x);
            buffer.push_back(verts[i].normal.y);
            buffer.push_back(verts[i].normal.z);
        }
        return;
    }

    Vertex m1 = getMidpoint(v1, v2, radius);
    Vertex m2 = getMidpoint(v2, v3, radius);
    Vertex m3 = getMidpoint(v3, v1, radius);

    subDivide(v1, m1, m3, buffer, depth - 1, radius);
    subDivide(v2, m2, m1, buffer, depth - 1, radius);
    subDivide(v3, m3, m2, buffer, depth - 1, radius);
    subDivide(m1, m2, m3, buffer, depth - 1, radius);

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
/*
    // This is the base standard Triangle                                                                         
    std::vector< float > host_VertexBuffer
    {   -3.0f, -3.0f, 0.0f, 0.0f, 0.0f, 1.0f,   // V0                                    
        3.0f, -3.0f, 0.0f, 0.0f, 0.0f, 1.0f,    // V1                                    
        0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 1.0f     // V2 
    };       
*/

    std::vector<float> host_VertexBuffer;
    float r = 2.0f;
    int detail = 6;

    Vertex vTop = {{0, r, 0}, {0, 1, 0}};
    Vertex vBottom = {{0, -r, 0}, {0, -1, 0}};
    Vertex vLeft = {{-r, 0, 0}, {-1, 0, 0}};
    Vertex vRight = {{r, 0, 0}, {1, 0, 0}};
    Vertex vFront = {{0, 0, r}, {0, 0, 1}};
    Vertex vBack = {{0, 0, -r}, {0, 0, -1}};
    Vertex Triangle1V1 = {{-6.0f, -3.0f, -3.0f}, {0.0f, 0.0f, 1.0f}};
    Vertex Triangle1V2 = {{-3.0f, -3.0f, -3.0f}, {0.0f, 0.0f, 1.0f}};
    Vertex Triangle1V3 = {{-3.0f, 0.0f, -3.0f}, {0.0f, 0.0f, 1.0f}};

    Vertex Tri[] = {Triangle1V1, Triangle1V2, Triangle1V3};

    for(int i = 0; i < 3; ++i){
        host_VertexBuffer.push_back(Tri[i].position.x);
        host_VertexBuffer.push_back(Tri[i].position.y);
        host_VertexBuffer.push_back(Tri[i].position.z);
        host_VertexBuffer.push_back(Tri[i].normal.x);
        host_VertexBuffer.push_back(Tri[i].normal.y);
        host_VertexBuffer.push_back(Tri[i].normal.z);
    }

    subDivide(vTop, vLeft, vFront, host_VertexBuffer, detail, r);
    subDivide(vTop, vFront, vRight, host_VertexBuffer, detail, r);
    subDivide(vTop, vRight, vBack, host_VertexBuffer, detail, r);
    subDivide(vTop, vBack, vLeft, host_VertexBuffer, detail, r);

    subDivide(vBottom, vFront, vLeft, host_VertexBuffer, detail, r);
    subDivide(vBottom, vRight, vFront, host_VertexBuffer, detail, r);
    subDivide(vBottom, vBack, vRight, host_VertexBuffer, detail, r);
    subDivide(vBottom, vLeft, vBack, host_VertexBuffer, detail, r);

    int numVertices = host_VertexBuffer.size() / 6;

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
    shader.addShader("vertexShader_BlinnMultipleLights.glsl", sivelab::GLSLObject::VERTEX_SHADER);
    shader.addShader("fragmentShader_BlinnMultipleLights.glsl", sivelab::GLSLObject::FRAGMENT_SHADER);
    shader.createProgram();

    GLuint projMatrixID, viewMatrixID, modelMatrixID, normalMatrixID;
    projMatrixID = shader.createUniform("projMatrix");
    viewMatrixID = shader.createUniform("viewMatrix");
    modelMatrixID = shader.createUniform("modelMatrix");
    normalMatrixID = shader.createUniform("normalMatrix");

    glm::vec4 lightPositions[] = {
        glm::vec4(5.0f, 5.0f, 5.0f, 1.0f),
        glm::vec4(-5.0f, 5.0f, 5.0f, 1.0f),
        glm::vec4(0.0f, -5.0f, 2.0f, 1.0f)
    };

    glm::vec3 lightColors[] = {

        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f)
    };


    GLint lightPosWorldID = shader.createUniform("lightPosWorld"); // light position for lambertian and blinnphong
    GLint lightColID = shader.createUniform("lightColors");
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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        endFrameTime = glfwGetTime();
        timeDiff = endFrameTime - startFrameTime;
        startFrameTime = glfwGetTime();

        // Clear the window's buffer (or clear the screen to our
        // background color)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        m_W = -glm::normalize(front);
        m_U = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), m_W));
        m_V = glm::normalize(glm::cross(m_W, m_U));

        glm::mat4 M_view = glm::lookAt(m_pos, m_pos - m_W, m_V);

        /* Render your objects here */

        /* Movable Camera render*/

        shader.activate();

        glUniform4fv(lightPosWorldID, 3, glm::value_ptr(lightPositions[0]));
        glUniform3fv(lightColID, 3, glm::value_ptr(lightColors[0]));

        glm::mat4 modelTransform = glm::mat4(1.0);
        //modelTransform = glm::rotate(modelTransform, rotAngle , glm::vec3(0,1,0));
        //rotAngle += 0.001;
        //if(rotAngle > 2.0 * 3.14159) rotAngle = 0.0f;

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
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawArrays(GL_TRIANGLES, 0, numVertices);
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

        float speed = 2.5f;
        float moveRate = speed * (float)timeDiff;

        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
            m_pos += -m_W * moveRate;
        }
        else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
            m_pos -= m_U * moveRate;
        }
        else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
            m_pos += m_W * moveRate;
        }
        else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
            m_pos += m_U * moveRate;
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
