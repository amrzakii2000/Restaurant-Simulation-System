#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"

class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, vegan, VIP
	ORD_STATUS status;	//waiting, in-service, done
	int Distance;	//The distance (in meters) between the order location and the resturant 

	double totalMoney;	//Total order money

	int ArrTime, WaitTime, ServTime, FinishTime;	//arrival, service start, and finish times


	//
	// TODO: Add More Data Members As Needed

	int size;   //number of dishes
	double score;
	//

public:
	Order(int ID, ORD_TYPE r_Type, double money, int oSize, int oDistance, int arrTime);
	virtual ~Order();

	int GetID();

	ORD_TYPE GetType() const;

	void SetDistance(int d);
	int GetDistance() const;

	void setStatus(ORD_STATUS s);
	ORD_STATUS getStatus() const;


	//
	// TODO: Add More Member Functions As Needed
	//


	//ADDED
	Order(); // default constructor
	int getArrTime(); //Getter for Arrival time
	int getFinishTime(); //Getter for Finish Time
	int getServTime(); //Getter for Serv time
	int getWaitTime();
	int getOrderSize(); //Getter for Order size
	double getTotalMoney(); //Getter for total money
	void setScore();     //Calaculates Order score
	double getScore();			//Gets the priority Score of an order
	void setID(int id);			//Setter for Order ID
	void setOrderSize(int s);
	void setWaitTime(int wtime);
	void setArrTime(int atime);  //Sets the Order Arrival time
	void setServTime(int stime);  //Sets the Order Serve Time
	void setFinishTime(int ftime);  //Sets the Order Finish Time
	void UpdateMoney(double add);   //Adds extra money to the order
	void setType(ORD_TYPE type);		//Sets order type
	//bool operator<=(Order*O);			//Compares Orders according to Priority Score
	//bool operator>(Order* O);
};

#endif