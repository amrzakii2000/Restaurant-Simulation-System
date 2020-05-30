#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"


ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType):Event(eTime, oID)
{
	OrdType = oType;
}

ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE otype, double money, int size) : Event(eTime,oID)
{
	OrdType = otype;
	OrdMoney = money;
	OrdSize = size;
	OrdDistance = 0;
}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create an order and fills its data 
	// Then adds it to normal, vegan, or VIP order lists that you will create in phase1

	
	
	///For the sake of demo, this function will just create an order and add it to DemoQueue
	///Remove the next code lines in phases 1&2
	Order* pOrd = new Order(OrderID,OrdType,OrdMoney,OrdSize,OrdDistance,EventTime);
	pRest->AddtoQueue(pOrd);
}
