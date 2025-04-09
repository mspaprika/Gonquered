#pragma once

static constexpr int DISPLAY_WIDTH{ 1920 };
static constexpr int DISPLAY_HEIGHT{ 1028 };

constexpr float DELTA_TIME{ 1.0f / 60.0f };

const Play::Matrix2D& GetOrtho();
Play::Vector2f TransformOrtho( const Play::Vector3f& pos );
