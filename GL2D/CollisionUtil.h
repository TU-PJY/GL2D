#pragma once
#include "MATA_HEADER.h"

enum class Edge
{Left, Right, Top, Bottom};

enum class BoxRenderMode
{ Static, Default };

enum class RangeRenderMode
{ Static, Default };


class AABB {
private:
	glm::mat4 TranslateMatrix{ 1.0f }, ScaleMatrix{ 1.0f }, RotateMatrix{ 1.0f };
	unsigned int ModelLocation{}, TransparencyLocation{}, ObjectColorLocation{};
	unsigned int Box{};
	unsigned int BoxInside{};

	GLfloat LeftX{}, LeftY{};
	GLfloat RightX{}, RightY{};
	GLfloat CenterX{}, CenterY{};
	GLfloat OffsetX{}, OffsetY{};

	bool Collide{};

public:
	void Init();
	void Update(GLfloat X, GLfloat Y, GLfloat xScale, GLfloat yScale);
	void Render(BoxRenderMode Mode, GLfloat X, GLfloat Y, GLfloat xScale, GLfloat yScale);
	bool CheckCollisionAABB(const AABB& Other);
	bool CheckCollisionEdge(GLfloat X, Edge Edge);
	void InterpolateX(GLfloat& X);
	void InterpolateY(GLfloat& Y);
	bool CheckCollisionPoint(GLfloat X, GLfloat Y);

private:
	void InitTransform();
	void ProcessTransform();
};

class OBB {
private:
	glm::mat4 TranslateMatrix{ 1.0f }, RotateMatrix{ 1.0f }, ScaleMatrix{1.0f};
	unsigned int ModelLocation{}, TransparencyLocation{}, ObjectColorLocation{};
	unsigned int Box{};
	unsigned int BoxInside{};

	glm::vec2 Center{};
	glm::vec2 Offset{};
	glm::vec2 Axis[2]{};
	GLfloat Rotation{};

	bool Collide{};

public:
	void Init();
	void Update(GLfloat X, GLfloat Y, GLfloat xScale, GLfloat yScale, GLfloat rotation);
	void Render(BoxRenderMode Mode, GLfloat X, GLfloat Y, GLfloat xScale, GLfloat yScale, GLfloat Degree);
	bool CheckCollisionOBB(const OBB& Other);
	bool CheckCollisionPoint(const glm::vec2& Point);

private:
	bool OverlapOnAxis(const OBB& OBB1, const OBB& OBB2, const glm::vec2& Axis);
	void InitTransform();
	void ProcessTransform();
};

class Range {
private:
	glm::mat4 TranslateMatrix{ 1.0f }, ScaleMatrix{ 1.0f };
	unsigned int ModelLocation{}, TransparencyLocation{}, ObjectColorLocation{};
	unsigned int Circle{};
	unsigned int CircleInside{};

	GLfloat CenterX{}, CenterY{};
	GLfloat Radius{};

	bool Collide{};

public:
	void Init();
	void Update(GLfloat X, GLfloat Y, GLfloat Size);
	void Render(RangeRenderMode Mode, GLfloat X, GLfloat Y, GLfloat Size);
	bool CheckCollisionRange(const Range& Other);
	bool CheckCollisionPoint(GLfloat X, GLfloat Y);

private:
	GLfloat CalculateDistance(GLfloat x2, GLfloat y2);
	void InitTransform();
	void ProcessTransform();
};