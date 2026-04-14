include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable (glfwExample
  glfwExample.cpp 
  GLSL.cpp GLSL.h
  SimpleCamera_Impl.h SimpleCamera_Impl.cpp
)

target_link_libraries (glfwExample PRIVATE GLEW::GLEW)
target_link_libraries (glfwExample PRIVATE glfw)

if(APPLE)
    target_link_libraries(glfwExample PRIVATE
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
else()
    target_link_libraries(glfwExample PRIVATE OpenGL::GL)
endif()

target_link_libraries (glfwExample PRIVATE PNG::PNG)
target_link_libraries (glfwExample PRIVATE ZLIB::ZLIB)


add_executable (glfwExample_zfight
  glfwExample_zfight.cpp 
  GLSL.cpp GLSL.h
  SimpleCamera_Impl.h SimpleCamera_Impl.cpp
)

target_link_libraries (glfwExample_zfight PRIVATE GLEW::GLEW)
target_link_libraries (glfwExample_zfight PRIVATE glfw)

if(APPLE)
    target_link_libraries(glfwExample_zfight PRIVATE
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
else()
    target_link_libraries(glfwExample_zfight PRIVATE OpenGL::GL)
endif()

target_link_libraries (glfwExample_zfight PRIVATE PNG::PNG)
target_link_libraries (glfwExample_zfight PRIVATE ZLIB::ZLIB)


add_executable (glfwExample_blend
  glfwExample_blend.cpp 
  GLSL.cpp GLSL.h
  SimpleCamera_Impl.h SimpleCamera_Impl.cpp
)

target_link_libraries (glfwExample_blend PRIVATE GLEW::GLEW)
target_link_libraries (glfwExample_blend PRIVATE glfw)

if(APPLE)
    target_link_libraries(glfwExample_blend PRIVATE
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
else()
    target_link_libraries(glfwExample_blend PRIVATE OpenGL::GL)
endif()

target_link_libraries (glfwExample_blend PRIVATE PNG::PNG)
target_link_libraries (glfwExample_blend PRIVATE ZLIB::ZLIB)



add_executable (glfwExample_texture
  glfwExample_texture.cpp 
  GLSL.cpp GLSL.h
  SimpleCamera_Impl.h SimpleCamera_Impl.cpp
)

target_link_libraries (glfwExample_texture PRIVATE GLEW::GLEW)
target_link_libraries (glfwExample_texture PRIVATE glfw)

if(APPLE)
    target_link_libraries(glfwExample_texture PRIVATE
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
else()
    target_link_libraries(glfwExample_texture PRIVATE OpenGL::GL)
endif()

target_link_libraries (glfwExample_texture PRIVATE PNG::PNG)
target_link_libraries (glfwExample_texture PRIVATE ZLIB::ZLIB)