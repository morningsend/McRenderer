cmake_minimum_required(VERSION 2.8)
project(renderer CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -L/usr/local/lib -lSDL2_image -lSDL2 -std=c++11 -lm -lstdc++ -O3")

set(SOURCE_FILES 
        src/scene/Transform.cpp src/scene/Transform.hpp
        src/scene/Mesh.cpp src/scene/Mesh.hpp
        src/scene/Line.cpp src/scene/Line.hpp
        src/scene/Ray.cpp src/scene/Ray.hpp
        src/scene/Plane.cpp src/scene/Plane.hpp
        src/scene/Camera.cpp src/scene/Camera.hpp
        src/scene/Vertex.cpp src/scene/Vertex.hpp
        src/scene/TestModelH.h
        src/SDLauxiliary.hpp src/SDLauxiliary.cpp
        src/scene/Light.cpp src/scene/Light.hpp
        src/scene/Triangle.cpp src/scene/Triangle.hpp
        src/scene/Sphere.cpp src/scene/Sphere.hpp
        src/rendering/PathTracingRenderer.cpp src/rendering/PathTracingRenderer.hpp
        src/scene/SimpleScene.cpp src/scene/SimpleScene.hpp
        src/scene/BoundingBox.cpp src/scene/BoundingBox.hpp
        src/rendering/RenderTarget.cpp src/rendering/RenderTarget.hpp
        src/brdf/phong/PhongShader.cpp src/brdf/phong/PhongShader.hpp
        src/Exception.cpp src/Exception.hpp
        src/rendering/Renderer.cpp src/rendering/Renderer.hpp
        src/window/KeyboardEventHandler.cpp src/window/KeyboardEventHandler.hpp
        src/window/KeyboardEvent.cpp src/window/KeyboardEvent.hpp
        src/window/Window.cpp src/window/Window.hpp
        src/rendering/RenderTargetDrawFunction.cpp src/rendering/RenderTargetDrawFunction.hpp
        src/window/TestDrawFunction.cpp src/window/TestDrawFunction.hpp
        src/tree/KdTree.cpp src/tree/KdTree.hpp
        src/CameraKeyboardController.cpp src/CameraKeyboardController.hpp
        src/obj/ObjFileReader.cpp src/obj/ObjFileReader.hpp
        src/rendering/RayTracerConfig.cpp src/rendering/RayTracerConfig.hpp
        src/obj/MtlFileReader.cpp src/obj/MtlFileReader.hpp
        src/IOUtility.cpp src/IOUtility.hpp
        src/brdf/MicroFacetShader.cpp src/brdf/MicroFacetShader.hpp
        src/brdf/blinn/BlinnShader.cpp src/brdf/blinn/BlinnShader.hpp
        src/brdf/lambert/LamberShader.cpp src/brdf/lambert/LamberShader.hpp
        src/scene/Scene.cpp src/scene/Scene.hpp
        src/scene/AxisAlignedPlane.cpp src/scene/AxisAlignedPlane.hpp
        src/scene/RayIntersecting.hpp src/image/UvSampler1D.hpp
        src/image/UvSampler3D.hpp
        src/image/ConstantColourSampler.cpp src/image/ConstantColourSampler.hpp
        src/image/ConstantFloatSampler.cpp src/image/ConstantFloatSampler.hpp
        src/image/GrayScaleImageSampler.hpp src/image/GrayScaleImageSampler.cpp
        src/brdf/RGBImageSampler.cpp src/brdf/RGBImageSampler.hpp
        src/image/PngReader.cpp src/image/PngReader.hpp
        src/image/Image.cpp src/image/Image.hpp
        src/brdf/Material.hpp
        src/rendering/GaussianSampler.cpp src/rendering/GaussianSampler.hpp src/rendering/PathTracer.cpp src/rendering/PathTracer.hpp src/scene/SceneObject.hpp src/brdf/Brdf.hpp src/brdf/HemisphereSampler.cpp src/brdf/HemisphereSampler.hpp)

set(CATCH_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/lib/catch/")

set(TESTS_SOURCE_FILES ${SOURCE_FILES}
        tests/scene/RayTests.hpp
        tests/scene/MeshTests.hpp
        tests/obj/ObjFileReaderTests.hpp
        tests/obj/MtlFileReaderTests.hpp
        tests/scene/SphereTest.hpp)

add_library(Catch INTERFACE)

target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${CATCH_INCLUDE_DIR})
include_directories("${PROJECT_SOURCE_DIR}/lib/glm/")

find_package(SDL2_image REQUIRED)
find_package(sdl2 REQUIRED)

add_executable(renderer ${SOURCE_FILES} src/main.cpp )
add_executable(renderer_tests ${TESTS_SOURCE_FILES} tests/testMain.cpp)

target_link_libraries(renderer ${SDL2_LIBRARIES})
target_link_libraries(renderer ${SDL2_IMAGE_LIBRARY})
target_link_libraries(renderer_tests ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARY})
