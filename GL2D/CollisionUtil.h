#pragma once
#include "GLHeader.h"
#include "Shader.h"
#include "ImageUtil.h"
#include "TextUtil.h"
#include "RenderModeUtil.h"
#include <array>

class AABB {
private:
	glm::mat4 TranslateMatrix{ 1.0f }, RotateMatrix{ 1.0f }, ScaleMatrix{ 1.0f };
	unsigned int ModelLocation{}, TransparencyLocation{}, ObjectColorLocation{};

	GLfloat LeftX{}, LeftY{};
	GLfloat RightX{}, RightY{};

	GLfloat SizeX{};
	GLfloat SizeY{};

	GLfloat x{}, y{};

	bool ShowBound{};

	unsigned int Box{};

	Text text;

public:
	AABB() {
		Box = image.ImportImage("GL2D Res//boundbox.png");
		text.Init("Arial", FW_NORMAL);
		text.SetColor(1.0, 0.0, 0.0);
	}

	void ShowAABB(bool Flag) {
		ShowBound = Flag;
	}

	void Update(GLfloat X, GLfloat Y, GLfloat xScale, GLfloat yScale) {
		LeftX = X - xScale / 2;
		LeftY = Y - yScale / 2;
		RightX = X + xScale / 2;
		RightY = Y + yScale / 2;

		if (ShowBound) {
			InitTransform();

			ScaleMatrix = scale(ScaleMatrix, glm::vec3(xScale, yScale, 0.0));
			TranslateMatrix = translate(TranslateMatrix, glm::vec3(X, Y, 0.0));

			ProcessTransform();
			image.Draw(Box);

			text.SetAlign(Align::Left);
			text.Draw(LeftX - 0.02, LeftY - 0.02, 0.07, "[%.2f, %.2f]", LeftX, LeftY);
			text.SetAlign(Align::Default);
			text.Draw(RightX + 0.02, RightY + 0.02, 0.07, "[%.2f, %.2f]", RightX, RightY);
			text.SetAlign(Align::Middle);
			text.Draw(X, Y, 0.07, "[%.2f, %.2f]", X, Y);
		}
	}

	bool CheckCollisionAABB(AABB aabb) {
		if (RightX < aabb.LeftX || LeftX > aabb.RightX)
			return false;

		if (RightY < aabb.LeftY || LeftY > aabb.RightY) 
			return false;
		
		return true;
	}

	bool CheckCollisionDot(GLfloat X, GLfloat Y) {
		if ((LeftX <= X && X <= RightX) && (LeftY <= Y && Y <= RightY))
			return true;

		return false;
	}

	void InitTransform() {
		TranslateMatrix = glm::mat4(1.0f);
		RotateMatrix = glm::mat4(1.0f);
		ScaleMatrix = glm::mat4(1.0f);
	}

	void ProcessTransform() {
		renderMode.SetImageMode();

		TransparencyLocation = glGetUniformLocation(ImageShader, "transparency");
		glUniform1f(TransparencyLocation, 1.0);

		ModelLocation = glGetUniformLocation(ImageShader, "model");
		glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, value_ptr(RotateMatrix * TranslateMatrix * ScaleMatrix));
	}
};