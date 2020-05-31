#pragma once

#include "..\Defs.h"
#include"Order.h"
#pragma once
class Cook
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding type (VIP, Normal, Vegan)
	int speed;		//dishes it can prepare in one clock tick (in one timestep)
	//ADDED
	int BreakDuration;				//Duration of Cook Break
	int NumberofServedOrders;		//Number of Orders Cook Served without taking a break
	bool injured;
	int CountOfTakenBreak;          // number of Timesteps taken in break
	bool isAvailable;				// State of Cook
	int RemainedDishes; // numbers of remained dishes a cook can still serve in this timestep
	int RestPeriod;
	int OriginalSpeed;
public:
	Cook();
	Cook(int cID, ORD_TYPE cType, int cSpeed, int cBreakDuration, int cOrdersBreak);
	virtual ~Cook();
	int GetID() const;
	ORD_TYPE GetType() const;
	//ADDED
	void setID(int);				//Setter for Cook ID
	void setType(ORD_TYPE);		//Setter for Cook type
	void setSpeed(int);				//Setter for Cook Speed
	void setBreak(int);				//Setter for Cook break
	void setAvailability(bool B);
	void setCountOfTakenBreak(int n);
	void setNumberOfServedOrders(int n);
	void setInjured();
	void setRecovered();
	void IncrementRestPeriod();
	int getSpeed() const;			//Getter for Cook Speed
	int getBreakDuration() const;	//Getter for Cook Break Duration
	void setRemainedDishes(int n);
	int getRemainedDishes();
	int getRestPeriod();
	int getNumberOfServedOrders();
	int getCountOfTakenBreak();
	void IncrementNumberOfServedOrders();
	void IncrementCountOfTakenBreak();
	bool isInjured();
	bool IsAvailable();

};
