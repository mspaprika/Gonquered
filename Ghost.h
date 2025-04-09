#pragma once


constexpr int kGhostLifetime{ 90 };

struct Ghost
{
	Play::Vector3f velocity{ 0.0f, 0.0f, 0.0f };
	Play::Point3D pos3D{ 0, 0, 0 };
	float frame{ 0.0f };
};


void DeleteGhosts();
void UpdateGhosts();
void AddGhostToArray( Ghost* g );
void DrawGhosts();
void ClearGhosts();