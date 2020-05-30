#include "Order.h"

Order::Order(int id, ORD_TYPE r_Type, double money, int osize, int oDistance, int arrTime)
{
	ID = (id > 0 && id < 1000) ? id : 0;	//1<ID<999
	type = r_Type;
	status = WAIT;
	Distance = oDistance;
	totalMoney = money > 0 ? money : 0;
	size = osize > 0 ? osize : 0;
	ArrTime = arrTime;
	WaitTime = 0;

	if (r_Type == TYPE_VIP)
	{
		score = 10 * (double)ArrTime + 8 * totalMoney - 3 * (double)size - 2 * (double)Distance;
	}
	else
		score = 0;
}

Order::~Order()
{
}

int Order::GetID()
{
	return ID;
}


ORD_TYPE Order::GetType() const
{
	return type;
}


void Order::SetDistance(int d)
{
	Distance = d > 0 ? d : 0;
}

int Order::GetDistance() const
{
	return Distance;
}


void Order::setStatus(ORD_STATUS s)
{
	status = s;
}

ORD_STATUS Order::getStatus() const
{
	return status;
}
Order::Order()
{
}
int Order::getArrTime()
{
	return ArrTime;
}
int Order::getFinishTime()
{
	return FinishTime;
}
int Order::getServTime()
{
	return ServTime;
}
int Order:: getWaitTime()
{
	return WaitTime;
}
int Order::getOrderSize()
{
	return size;
}
double Order::getTotalMoney()
{
	return totalMoney;
}
double Order::getScore()
{
	return score;
}
void Order::setScore()
{
	score = 10 * (double)ArrTime + 8 * totalMoney - 3 * (double)size - 2 * (double)Distance;
}
void Order::setID(int id)
{
	ID = (id > 0) ? id : 0;
}

void Order::setArrTime(int atime)  //Sets the Order Arrival time
{
	ArrTime = atime;
}

void Order::setWaitTime(int wtime)
{
	WaitTime = wtime;
}

void Order::setServTime(int stime)  //Sets the Order Serve Time
{
	ServTime = stime;
}

void Order::setFinishTime(int ftime)  //Sets the Order Finish Time
{
	FinishTime = ftime;
}

void Order::setOrderSize(int s)
{
	size = s >= 0 ? s : getOrderSize();
}

void Order::UpdateMoney(double add)   //Adds extra money to the order
{
	add = add > 0 ? add : 0;
	totalMoney += add;
}

void Order::setType(ORD_TYPE type)		//Sets order type
{
	this->type = type;
}

//bool Order::operator<=(Order* O)
//{
//	return score <= O->score;
//}
//
//bool Order::operator>(Order* O)
//{
//	return (ArrTime > O->ArrTime);
//}
