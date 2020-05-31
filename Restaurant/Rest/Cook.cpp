#include "Cook.h"

Cook::Cook()
{
	NumberofServedOrders = 0;
	CountOfTakenBreak = 0;
	isAvailable = true;
	injured = false;
}
Cook::Cook(int cID, ORD_TYPE cType, int cSpeed, int cBreakDuration, int cOrdersBreak)
{
	ID = cID > 0 ? cID : 0;
	type = cType;
	speed = cSpeed > 0 ? cSpeed : 0;
	BreakDuration = cBreakDuration > 0 ? cBreakDuration : 0;
	NumberofServedOrders = 0;
	CountOfTakenBreak = 0;
	isAvailable = true;
	injured = false;
}


Cook::~Cook()
{
}


int Cook::GetID() const
{
	return ID;
}


ORD_TYPE Cook::GetType() const
{
	return type;
}


void Cook::setID(int id)
{
	ID = id;
}

void Cook::setType(ORD_TYPE t)
{
	type = t;
}


void Cook::setSpeed(int cSpeed)
{
	speed = cSpeed > 0 ? cSpeed : 0;
	RemainedDishes = speed;
	OriginalSpeed = speed;
}
int Cook::getSpeed() const
{
	return speed;
}

void Cook::setBreak(int cBreak)
{
	BreakDuration = cBreak > 0 ? cBreak : 0;
}


void Cook::setAvailability(bool B)
{
	isAvailable = B;
}

void Cook::setCountOfTakenBreak(int n)
{
	CountOfTakenBreak = n;
}

void Cook::setNumberOfServedOrders(int n)
{
	NumberofServedOrders = n;
}

int Cook::getBreakDuration() const
{
	return BreakDuration;
}

void Cook::setRemainedDishes(int n)
{
	RemainedDishes = n >= 0 ? n : 0;
}

int Cook::getRemainedDishes()
{
	return RemainedDishes;
}

int Cook::getNumberOfServedOrders()
{
	return NumberofServedOrders;
}

int Cook::getCountOfTakenBreak()
{
	return CountOfTakenBreak;
}

void Cook::IncrementNumberOfServedOrders()
{
	NumberofServedOrders++;
}

void Cook::IncrementCountOfTakenBreak()
{
	CountOfTakenBreak++;
}
void Cook::IncrementRestPeriod()
{
	RestPeriod++;
}



int Cook::getRestPeriod()
{
	return RestPeriod;
}

void Cook::setInjured()
{
	injured = true;
	speed==1?speed:speed/=2;
	RestPeriod = 0;
}
void Cook::setRecovered()
{
	injured = false;
	speed = OriginalSpeed;
}
bool Cook::isInjured()
{
	return injured;
}

bool Cook::IsAvailable()
{
	return isAvailable;
}