#pragma once

#define GLEW_STATIC
#include <GL/glew.h>  // Include GLEW before other OpenGL headers
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <list>
#include <csignal>
#include <execinfo.h>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <dlfcn.h>
#include <algorithm>  // Add this line for the algorithm header

#include <ucontext.h>   
#include <sys/ucontext.h>  
#include <sstream>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SOIL/SOIL.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"