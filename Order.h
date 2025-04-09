#pragma once

struct Building;

struct Order
{
	int id{ 0 };
	int player{ -1 };
	Building* source{ nullptr };
	Building* dest{ nullptr };
	int warriors{ 0 };
};

void UpdateOrders();
void CreateOrder( int color, int gonks, Building* source, Building* target );
void ExecuteOrder( Order* order );
void ClearOrders();
void DeleteOrder( int ID );


const std::vector< Order* >& GetOrdersArray();
