#include "pch.h"


#define IMGL3W_IMPL
#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#define IMGUI_API __declspec(dllexport)
#include "glad/glad.h"
#include "backends/imgui_impl_opengl3.cpp"
#include "backends/imgui_impl_glfw.cpp"
