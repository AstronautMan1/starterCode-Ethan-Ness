#include "SimpleCamera_Impl.h"

// default camera
SimpleCamera_Impl::SimpleCamera_Impl() 
    : m_pos( glm::vec3(0.0f, 0.0f, 0.0f) ),
      m_viewDir( glm::vec3(0.0f, 0.0f, -1.0f) ),
      m_U(1.0f, 0.0f, 0.0f),
      m_V(0.0f, 1.0f, 0.0f),
      m_W(0.0f, 0.0f, 1.0f)
{}

SimpleCamera_Impl::SimpleCamera_Impl(const glm::vec3 &p,
                                     const glm::vec3 &v)
    : m_pos( p ),
      m_viewDir( v )
{ 
    m_viewDir = glm::normalize( m_viewDir );

    // Compute basis
    glm::vec3 tmpUp(0.0, 1.0, 0.0);

    m_W = -m_viewDir;
    m_W = glm::normalize( m_W );

    // !!! need to add check for co-linearity with W !!!

    m_U = glm::cross(tmpUp, m_W);
    m_U = glm::normalize(m_U);

    m_V = glm::cross(m_W, m_U);
    m_V = glm::normalize(m_V);
}
