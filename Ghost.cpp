#include "pch.h"
#include "GameMath.h"
#include "Gonk.h"
#include "Ghost.h"


std::vector< Ghost* > vGhosts;
const char* ghostGonkSpr{ "GhostGonk" };

void UpdateGhosts()
{
	for (Ghost* g : vGhosts)
	{
		g->pos3D += g->velocity;
		g->frame++;
	}
	DeleteGhosts();
}

void DeleteGhosts()
{
	for (int i = 0; i < vGhosts.size(); i++)
	{
		Ghost* ghost = vGhosts[i];
		if (ghost->frame > kGhostLifetime)
		{
			Ghost* ghost2 = vGhosts[vGhosts.size() - 1];
			vGhosts[i] = ghost2;
			vGhosts.pop_back();
			delete ghost;
			i--;
		}
	}
}

void DrawGhosts()
{
	for (Ghost* g : vGhosts)
	{
		float opacity{ 1.0f };

		if (g->frame > kGhostLifetime / 2)
		{
			opacity -= static_cast<float>(g->frame - (kGhostLifetime / 2)) / 100.0f * 2.0f;
		}
		Play::DrawSpriteRotated(ghostGonkSpr, TransformOrtho(g->pos3D), 0, 0.0f, 0.2f, opacity);
	}
}

void AddGhostToArray(Ghost* g)
{
	vGhosts.push_back(g);
}

void ClearGhosts()
{
	for (Ghost* g : vGhosts)
	{
		delete g;
	}
	vGhosts.clear();
}

