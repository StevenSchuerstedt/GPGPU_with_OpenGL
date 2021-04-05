# CMakeList.txt: CMake-Projektdatei der obersten Ebene. Führen Sie hier die globale Konfiguration aus,
# und schließen Sie Unterprojekte ein.
#
cmake_minimum_required (VERSION 3.8)

project ("GPGPU_with_OpenGL")


# Schließen Sie Unterprojekte ein.
add_subdirectory ("glfw")
add_subdirectory ("glew")
add_subdirectory ("GPGPU_with_OpenGL")

target_include_directories (GPGPU_with_OpenGL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include)
target_include_directories (GPGPU_with_OpenGL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glew/include)
