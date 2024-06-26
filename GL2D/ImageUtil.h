#pragma once
#include "GLHeader.h"
#include <string>
#include <map>

class ImageUtil {
private:
	GLuint VAO{};
	std::map<std::string, unsigned int> LoadedImageList;

public:
	void Init();
	void LoadImageFromList();
	unsigned int SetImage(std::string ImageName);
	GLfloat Aspect(int Width, int Height);
	void Render(unsigned int ImageVar);
};
extern ImageUtil imageUtil;