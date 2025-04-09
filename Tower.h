#pragma once


constexpr int kMaxTowers{ 2 };
constexpr float kFireInterval{ 1.0f };
constexpr float kMaxVisibilityRadius{ 400.0f };
constexpr float kMinVisibilityRadius{ 50.0f };

struct Gonk;

void ClearTowers();
void SetTowers();
void AddTowerToArray( int index );
const std::vector< int >& GetTowerArray();
int IsGonkVisible( Gonk* g );