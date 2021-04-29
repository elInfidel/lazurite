cmake_minimum_required(VERSION 3.14)

project(lazurite_core)

find_package(OpenGL)

set(GLM_STATIC_LIBRARY_ENABLE  OFF CACHE BOOL "")
set(GLM_TEST_ENABLE OFF CACHE BOOL "")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")

include(FetchContent)
FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw GIT_TAG 3.3.2)
FetchContent_Declare(glm GIT_REPOSITORY https://github.com/g-truc/glm GIT_TAG 0.9.9.7)
FetchContent_Declare(json GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent GIT_TAG v3.7.3)
FetchContent_Declare(stb GIT_REPOSITORY https://github.com/nothings/stb)
FetchContent_MakeAvailable(glfw glm stb json)

set(LZ_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include") 
set(LZ_SRC_DIR "${PROJECT_SOURCE_DIR}/src")

if(APPLE) 
	set(CMAKE_CXX_FLAGS "-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")
endif()

set(
    LZ_CORE_HEADER_FILES
    ${LZ_INCLUDE_DIR}/gl_core_4_4.h
    ${LZ_INCLUDE_DIR}/Engine.h
	${LZ_INCLUDE_DIR}/Editor.h
    ${LZ_INCLUDE_DIR}/GameObject.h
	${LZ_INCLUDE_DIR}/GLTF.h
	${LZ_INCLUDE_DIR}/GLTFLoader.h
	${LZ_INCLUDE_DIR}/Scene.h

    ${LZ_INCLUDE_DIR}/subsystem/Input.h
	${LZ_INCLUDE_DIR}/subsystem/Metrics.h

    ${LZ_INCLUDE_DIR}/rendering/Cubemap.h
    ${LZ_INCLUDE_DIR}/rendering/Material.h
	${LZ_INCLUDE_DIR}/rendering/Mesh.h
    ${LZ_INCLUDE_DIR}/rendering/Primitive.h
    ${LZ_INCLUDE_DIR}/rendering/ShaderProgram.h
    ${LZ_INCLUDE_DIR}/rendering/Texture.h
    ${LZ_INCLUDE_DIR}/rendering/Vertex.h

    ${LZ_INCLUDE_DIR}/component/AComponent.h
    ${LZ_INCLUDE_DIR}/component/Camera.h
    
    ${LZ_INCLUDE_DIR}/component/Transform.h

	${LZ_INCLUDE_DIR}/utility/FileIO.h

	${LZ_INCLUDE_DIR}/imconfig.h
	${LZ_INCLUDE_DIR}/imgui.h
	${LZ_INCLUDE_DIR}/imgui_impl_glfw.h
	${LZ_INCLUDE_DIR}/imgui_impl_opengl3.h
	${LZ_INCLUDE_DIR}/imgui_internal.h
	${LZ_INCLUDE_DIR}/imstb_rectpack.h
	${LZ_INCLUDE_DIR}/imstb_textedit.h
	${LZ_INCLUDE_DIR}/imstb_truetype.h
)

set(
    LZ_CORE_SOURCE_FILES

    ${LZ_SRC_DIR}/gl_core_4_4.c
    ${LZ_SRC_DIR}/Engine.cpp
	${LZ_SRC_DIR}/Editor.cpp
    ${LZ_SRC_DIR}/EntryPoint.cpp
    ${LZ_SRC_DIR}/GameObject.cpp
	${LZ_SRC_DIR}/GLTFLoader.cpp
	${LZ_SRC_DIR}/GLTF.cpp
	${LZ_SRC_DIR}/Scene.cpp

    ${LZ_SRC_DIR}/subsystem/Input.cpp
	${LZ_SRC_DIR}/subsystem/Metrics.cpp

    ${LZ_SRC_DIR}/rendering/Cubemap.cpp
    ${LZ_SRC_DIR}/rendering/Material.cpp
	${LZ_SRC_DIR}/rendering/Mesh.cpp
    ${LZ_SRC_DIR}/rendering/Primitive.cpp
    ${LZ_SRC_DIR}/rendering/ShaderProgram.cpp
    ${LZ_SRC_DIR}/rendering/Texture.cpp

    ${LZ_SRC_DIR}/component/AComponent.cpp
    ${LZ_SRC_DIR}/component/Camera.cpp
    ${LZ_SRC_DIR}/component/Transform.cpp

	${LZ_SRC_DIR}/utility/FileIO.cpp

	${LZ_SRC_DIR}/imgui.cpp
	${LZ_SRC_DIR}/imgui_demo.cpp
	${LZ_SRC_DIR}/imgui_draw.cpp
	${LZ_SRC_DIR}/imgui_impl_glfw.cpp
	${LZ_SRC_DIR}/imgui_impl_opengl3.cpp
	${LZ_SRC_DIR}/imgui_widgets.cpp
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
	${glfw_SOURCE_DIR}/include
	${glm_SOURCE_DIR}
	${stb_SOURCE_DIR}
	${json_SOURCE_DIR}
)

target_link_libraries(
	lazurite_core
	glfw
	${OPENGL_gl_LIBRARY}
)