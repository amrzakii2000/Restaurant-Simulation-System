#pragma once
#include "..\Events/Event.h"
#include "..\Rest/Order.h"
#include "..\Rest/Restaurant.h"
class CancellationEvent :
	public Event
{
	
public:
	CancellationEvent(int tstep, int ID);
	
    void  Execute(Restaurant* pRest);





};

