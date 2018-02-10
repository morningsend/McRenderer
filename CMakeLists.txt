cmake_minimum_required(VERSION 2.8)
project(renderer CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

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
        src/rendering/RayTracer.cpp src/rendering/RayTracer.hpp
        src/scene/Scene.cpp src/scene/Scene.hpp
        src/tree/BoundingBox.cpp src/tree/BoundingBox.hpp
        src/rendering/RenderTarget.cpp src/rendering/RenderTarget.hpp 
        src/scene/Material.cpp src/scene/Material.hpp 
        src/scene/TextureSampler2D.cpp src/scene/TextureSampler2D.hpp 
        src/scene/TextureMap.cpp src/scene/TextureMap.hpp  
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
        src/rendering/RayTracerConfig.cpp src/rendering/RayTracerConfig.hpp)

set(CATCH_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/lib/catch/")

set(TESTS_SOURCE_FILES ${SOURCE_FILES} tests/scene/RayTests.hpp )

add_library(Catch INTERFACE)

target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

include_directories(${SDL2_INCLUDE_DIRS})
include_directories("${PROJECT_SOURCE_DIR}/lib/glm/")
include_directories(${CATCH_INCLUDE_DIR})

find_package(sdl2 REQUIRED)

add_executable(renderer ${SOURCE_FILES} src/main.cpp )
add_executable(renderer_tests ${TESTS_SOURCE_FILES} tests/testMain.cpp)

target_link_libraries(renderer ${SDL2_LIBRARIES})
target_link_libraries(renderer_tests ${SDL2_LIBRARIES})