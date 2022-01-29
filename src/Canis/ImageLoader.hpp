#pragma once
#include <string>
#include <SDL.h>
#include <GL/glew.h>

#include "GLTexture.hpp"
#include "picoPNG.h"
#include "IOManager.hpp"
#include "Debug.hpp"

namespace Canis
{

	class ImageLoader
	{
	public:
		static GLTexture loadPNG(std::string filePath);
	};
} // end of Canis namespace