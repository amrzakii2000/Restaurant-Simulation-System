#pragma once
#include"..\Events/Event.h"
#include"..\Rest/Order.h"
#include"..\Rest/Restaurant.h"
class PromotionEvent:public Event
{
	Order*PromotedOrder; //Address of Promoted Order
	ORD_TYPE OrderType; //Prompoted Order Type
	double addMoney; //Extra Money
public:
	PromotionEvent(int etime, int oID,double addMoney=0);
	virtual void Execute(Restaurant* pRest);	//override execute function

};

