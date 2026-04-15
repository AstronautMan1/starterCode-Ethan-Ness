# 
# Adds the src directory to the include search
# path. ${CMAKE_SOURCE_DIR} is prefixed to allow the files in the
# utest directory to correctly include the relative reference to the
# src files.
#
include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(test_pngWrite
  test_pngWrite.cpp
)
target_link_libraries(test_pngWrite cs4212-util)
target_link_libraries(test_pngWrite ${Boost_PROGRAM_OPTIONS_LIBRARIES})
target_link_libraries(test_pngWrite PNG::PNG)
target_link_libraries(test_pngWrite ZLIB::ZLIB)

add_executable(test_readPNGFile
  test_readPNGFile.cpp
)
target_link_libraries(test_readPNGFile cs4212-util)
target_link_libraries(test_readPNGFile ${Boost_PROGRAM_OPTIONS_LIBRARIES})
target_link_libraries(test_readPNGFile PNG::PNG)
target_link_libraries(test_readPNGFile ZLIB::ZLIB)

add_executable(test_framebuffer
  test_framebuffer.cpp
)
target_link_libraries(test_framebuffer cs4212-util)
target_link_libraries(test_framebuffer PNG::PNG)
target_link_libraries(test_framebuffer ZLIB::ZLIB)

add_executable(test_rayTracer
  test_rayTracer.cpp
)
target_link_libraries(test_rayTracer cs4212-util)
target_link_libraries(test_rayTracer PNG::PNG)
target_link_libraries(test_rayTracer ZLIB::ZLIB)

add_executable(test_sphereImage
  test_sphereImage.cpp
)
target_link_libraries(test_sphereImage cs4212-util)
target_link_libraries(test_sphereImage PNG::PNG)
target_link_libraries(test_sphereImage ZLIB::ZLIB)

add_executable(test_triangleImage
  test_triangleImage.cpp
)
target_link_libraries(test_triangleImage cs4212-util)
target_link_libraries(test_triangleImage PNG::PNG)
target_link_libraries(test_triangleImage ZLIB::ZLIB)

add_executable(test_multipleShapesImage
  test_multipleShapes.cpp
)
target_link_libraries(test_multipleShapesImage cs4212-util)
target_link_libraries(test_multipleShapesImage PNG::PNG)
target_link_libraries(test_multipleShapesImage ZLIB::ZLIB)

add_executable(test_multipleTriangleImage
  test_multipleTriangles.cpp
)
target_link_libraries(test_multipleTriangleImage cs4212-util)
target_link_libraries(test_multipleTriangleImage PNG::PNG)
target_link_libraries(test_multipleTriangleImage ZLIB::ZLIB)

add_executable(test_LambertianImage
  test_LambertianTest.cpp
)
target_link_libraries(test_LambertianImage cs4212-util)
target_link_libraries(test_LambertianImage PNG::PNG)
target_link_libraries(test_LambertianImage ZLIB::ZLIB)

add_executable(test_BlinnPhongImage
  test_BlinnPhongTest.cpp
)
target_link_libraries(test_BlinnPhongImage cs4212-util)
target_link_libraries(test_BlinnPhongImage PNG::PNG)
target_link_libraries(test_BlinnPhongImage ZLIB::ZLIB)

add_executable(test_LambertianAntiAliasing
  test_AntiAliasingTest.cpp
)
target_link_libraries(test_LambertianAntiAliasing cs4212-util)
target_link_libraries(test_LambertianAntiAliasing PNG::PNG)
target_link_libraries(test_LambertianAntiAliasing ZLIB::ZLIB)

add_executable(test_MirrorShader
  test_MirrorShader.cpp
)
target_link_libraries(test_MirrorShader cs4212-util)
target_link_libraries(test_MirrorShader PNG::PNG)
target_link_libraries(test_MirrorShader ZLIB::ZLIB)

add_executable(test_graphicsArguments
  test_graphicsArgs.cpp
)
target_link_libraries(test_graphicsArguments cs4212-util)
target_link_libraries(test_graphicsArguments PNG::PNG)
target_link_libraries(test_graphicsArguments ZLIB::ZLIB)

add_executable(test_diffuseInter
  test_diffuseInter.cpp
)
target_link_libraries(test_diffuseInter cs4212-util)
target_link_libraries(test_diffuseInter PNG::PNG)
target_link_libraries(test_diffuseInter ZLIB::ZLIB)

add_executable(test_sceneloader
  test_sceneloader.cpp
)
target_link_libraries(test_sceneloader cs4212-util)
target_link_libraries(test_sceneloader PNG::PNG)
target_link_libraries(test_sceneloader ZLIB::ZLIB)

add_executable(test_diffuseInterBVH
  test_diffuseInterBVH.cpp
)
target_link_libraries(test_diffuseInterBVH cs4212-util)
target_link_libraries(test_diffuseInterBVH PNG::PNG)
target_link_libraries(test_diffuseInterBVH ZLIB::ZLIB)