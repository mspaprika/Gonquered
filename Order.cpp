#include "pch.h"
#include "Building.h"
#include "Gonk.h"
#include "Order.h"


std::vector< Order* > vOrders;
std::vector< Order* > vAllOrders;


void CreateOrder( int color, int gonks, Building* src, Building* trg )
{
	static int ID{ 0 };

	Order* order = new Order;
	order->id = ID++;
	order->player = color;
	order->warriors = gonks;
	order->source = src;
	order->dest = trg;

	vOrders.push_back( order );
}

void ExecuteOrder( Order* order )
{
	int batch{ 0 };
	int count{ -2 };
	int modulus{ 5 };

	for ( int i = 1; i <= order->warriors; i++ )
	{
		Gonk* gonk = new Gonk;
		gonk->order = order;
		gonk->spriteID = static_cast< Gonks >(gonk->order->source->owner);
		gonk->spriteDir = static_cast< GonkDir >(GetDirectionGonk( gonk->order->source->pos3D, gonk->order->dest->pos3D ));
		gonk->spawnTimer = ( batch == 0 ) ? 0.0f : gonk->spawnTimer * batch;

		Play::Vector3f vel = { gonk->order->dest->pos3D - gonk->order->source->pos3D };
		vel.Normalize();
		gonk->velocity = vel;

		gonk->pos3D = order->source->pos3D;
		gonk->offset = static_cast<float>(count);

		AddGonkToArray( gonk );
		count++;
		
		if ( !(i % modulus) && i != 0 ) 
		{
			batch++;
			count = -2;
		}
	}
}

void UpdateOrders()
{	
	for ( Order* order : vOrders )
	{
		ExecuteOrder( order );
		vAllOrders.push_back( order );
	}
	vOrders.clear();
}

void ClearOrders()
{
	for ( Order* order : vOrders )
	{
		delete order;
	}
	for ( Order* order : vAllOrders )
	{
		delete order;		
	}
	vOrders.clear();
	vAllOrders.clear();
}

void DeleteOrder( int ID )
{
	for ( int i =0; i < vAllOrders.size(); i++ )
	{
		Order* order = vAllOrders[ i ];
		if ( order->id == ID )
		{
			delete order;
			vAllOrders.erase( vAllOrders.begin() + i );
			break;
		}
	}
}

const std::vector< Order* >& GetOrdersArray()
{
	return vOrders;
}


