#pragma once
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <unordered_map>
#include <string_view>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "spdlog/spdlog.h"

#pragma warning(push, 0)
#include <ft2build.h>
#include FT_FREETYPE_H
#pragma warning(pop)

#include "DatEngine/Core/Logger.h"