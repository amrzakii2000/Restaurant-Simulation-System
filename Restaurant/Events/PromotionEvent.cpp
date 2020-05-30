#include"PromotionEvent.h"

PromotionEvent::PromotionEvent(int etime, int oID, double addMoney):Event(etime,oID)
{

	this->addMoney = addMoney;

}


void PromotionEvent::Execute(Restaurant* pRest)
{
	Order*pOrd=pRest->getOrderbyID(OrderID,TYPE_NRM);
	
	if (pOrd)
	{
		pOrd->UpdateMoney(addMoney);
		pOrd->setType(TYPE_VIP);
		pOrd->setScore();
		pRest->RemoveFromNormalList(pOrd);
		pRest->AddtoQueue(pOrd);
	}

}
