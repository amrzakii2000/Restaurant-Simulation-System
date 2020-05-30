#include "CancellationEvent.h"
 
CancellationEvent::CancellationEvent(int eTime, int id): Event(eTime,id)
{
  
}
void CancellationEvent::Execute(Restaurant* pRest)
{
    Order* pOrd = pRest->getOrderbyID(OrderID,TYPE_NRM);
    if (pOrd)
        pRest->RemoveFromNormalList(pOrd);
}








