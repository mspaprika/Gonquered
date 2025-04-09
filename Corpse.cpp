#include "pch.h"
#include "GameMath.h"
#include "Corpse.h"



std::vector< Corpse* > vCorpses;

void AddCorpseToArray(Corpse* c)
{
	vCorpses.push_back(c);
}

void UpdateCorpses()
{
	for (Corpse* c : vCorpses)
	{
		if (c->frame < 40)
		{
			c->frame += 0.5f;
			c->spread += 0.1f;
		}
	}
}

void DrawCorpses()
{
	for (Corpse* c : vCorpses)
	{
		Play::Vector2f topOffset = { cos(c->rotationBottom) * (10 * c->spread), sin(c->rotationBottom) * (10 * c->spread) };

		Play::DrawSpriteRotated(GetGonkSpriteID(c->spriteColor, CORPSE_BOTTOM), TransformOrtho(c->pos3D), c->frame, c->rotationBottom, 1.0f);
		Play::DrawSpriteRotated(GetGonkSpriteID(c->spriteColor, CORPSE_TOP), TransformOrtho(c->pos3D) + topOffset, c->frame, c->rotationTop, 1.0f);
	}
}

void ClearCorpses()
{
	for (Corpse* c : vCorpses)
	{
		delete c;
	}
	vCorpses.clear();
}