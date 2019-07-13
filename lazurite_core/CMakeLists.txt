cmake_minimum_required(VERSION 3.14)

project(lazurite_core)

set(GLM_TEST_ENABLE OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare(external_glfw GIT_REPOSITORY https://github.com/glfw/glfw GIT_TAG 3.3)
FetchContent_Declare(external_assimp GIT_REPOSITORY https://github.com/assimp/assimp GIT_TAG v4.1.0)
FetchContent_Declare(external_glm GIT_REPOSITORY https://github.com/g-truc/glm GIT_TAG 0.9.9.5)
FetchContent_Declare(external_stb GIT_REPOSITORY https://github.com/nothings/stb)
FetchContent_MakeAvailable(external_glfw external_assimp external_glm external_stb)

set(LZ_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include") 
set(LZ_SRC_DIR "${PROJECT_SOURCE_DIR}/src")

set(
    LZ_CORE_HEADER_FILES
    ${LZ_INCLUDE_DIR}/gl_core_4_4.h
    ${LZ_INCLUDE_DIR}/Engine.h
    ${LZ_INCLUDE_DIR}/GameObject.h
    ${LZ_INCLUDE_DIR}/GameObject.h
    ${LZ_INCLUDE_DIR}/subsystem/Input.h
    ${LZ_INCLUDE_DIR}/rendering/Cubemap.h
    ${LZ_INCLUDE_DIR}/rendering/Material.h
    ${LZ_INCLUDE_DIR}/rendering/Mesh.h
    ${LZ_INCLUDE_DIR}/rendering/ShaderProgram.h
    ${LZ_INCLUDE_DIR}/rendering/Texture.h
    ${LZ_INCLUDE_DIR}/rendering/Vertex.h
    ${LZ_INCLUDE_DIR}/component/AComponent.h
    ${LZ_INCLUDE_DIR}/component/Camera.h
    ${LZ_INCLUDE_DIR}/component/Model.h
    ${LZ_INCLUDE_DIR}/component/Transform.h
	${LZ_INCLUDE_DIR}/utility/FileIO.h
)

set(
    LZ_CORE_SOURCE_FILES
    ${LZ_SRC_DIR}/gl_core_4_4.c
    ${LZ_SRC_DIR}/Engine.cpp
    ${LZ_SRC_DIR}/EntryPoint.cpp
    ${LZ_SRC_DIR}/GameObject.cpp
    ${LZ_SRC_DIR}/subsystem/Input.cpp
    ${LZ_SRC_DIR}/rendering/Cubemap.cpp
    ${LZ_SRC_DIR}/rendering/Material.cpp
    ${LZ_SRC_DIR}/rendering/Mesh.cpp
    ${LZ_SRC_DIR}/rendering/ShaderProgram.cpp
    ${LZ_SRC_DIR}/rendering/Texture.cpp
    ${LZ_SRC_DIR}/component/AComponent.cpp
    ${LZ_SRC_DIR}/component/Camera.cpp
    ${LZ_SRC_DIR}/component/Model.cpp
    ${LZ_SRC_DIR}/component/Transform.cpp
	${LZ_SRC_DIR}/utility/FileIO.cpp
)

add_executable(
	lazurite_core
	${LZ_CORE_SOURCE_FILES} 
	${LZ_CORE_HEADER_FILES}
)

target_include_directories(
	lazurite_core 
	PUBLIC 
	${LZ_INCLUDE_DIR} 
	${external_glfw_SOURCE_DIR}/include
	${external_assimp_SOURCE_DIR}/include
	${external_assimp_BINARY_DIR}/include
	${external_glm_SOURCE_DIR}
	${external_stb_SOURCE_DIR}
)

target_link_libraries(
	lazurite_core 
	external_glfw
	external_assimp
)