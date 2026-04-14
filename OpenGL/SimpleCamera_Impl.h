#pragma once

#include <iostream>

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

class SimpleCamera_Impl
{
public:
    SimpleCamera_Impl();
    SimpleCamera_Impl(const glm::vec3 &pos, const glm::vec3 &viewDir);

    void setPosition( const glm::vec3 &p ) { m_pos = p; }
    glm::vec3 getPosition() { return m_pos; }

    glm::vec3 getForward() { return -m_W; };
    glm::vec3 getRight() { return m_U; };
    glm::vec3 getUp() { return m_V; };

    glm::mat4 getProjectionMatrix() {
        // The ortho parameters, in order: left, right, bottom, top, zNear, zFar
        // square!
        float halfWidth = 15.0 / 2.0;
        float halfHeight = halfWidth;

        float left = -halfWidth;
        float right = halfWidth;

        float bottom = -halfHeight;
        float top = halfHeight;

        float near = 5.0f;
        float far = -5.0f;
        
        // return glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, near, far);
        return glm::perspective(3.14159f/4.0f, 1.0f, 0.1f, 100.0f);
    }
    
    glm::mat4 getViewMatrix() {
        return glm::lookAt( m_pos, m_pos - m_W, m_V );
    }

    void moveForward() 
    {
        m_pos = m_pos + getForward() * 0.08f;
    }

    void moveBackward() 
    {
        m_pos = m_pos - getForward() * 0.08f;
    }
    
    void strafeLeft() 
    {
        m_pos = m_pos - m_U * 0.05f;
    }

    void strafeRight() 
    {
        m_pos = m_pos + m_U * 0.05f;
    }
    
private:
    glm::vec3 m_pos, m_viewDir;
    glm::vec3 m_U, m_V, m_W;
};
