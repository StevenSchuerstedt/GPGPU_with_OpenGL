# CMakeList.txt: CMake-Projekt für "GPGPU_with_OpenGL". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.8)

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.

add_library(Shader "shader.cpp")

add_executable (GPGPU_with_OpenGL "GPGPU_with_OpenGL.cpp")

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.

target_link_libraries (GPGPU_with_OpenGL
glfw
libglew_static
Shader
)
