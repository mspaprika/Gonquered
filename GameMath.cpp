#include "pch.h"
#include "GameMath.h"


const Play::Matrix2D& GetOrtho()
{
	static Play::Matrix2D s_ortho
	{
		{ 0.87f, 0.49f, 0.0f },
		{ 0.0f, 0.71f, 0.0f },
		{ -0.87f, 0.49f, 0.0f },
	};

	return s_ortho;
}

Play::Vector2f TransformOrtho(const Play::Vector3f& pos)
{
	return GetOrtho().Transform(pos).As2D();
}