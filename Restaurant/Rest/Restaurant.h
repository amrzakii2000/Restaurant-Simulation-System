#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include"..\Generic_DS\Node.h"
#include "..\Generic_DS\PriorityQueue.h"
#include "..\Generic_DS\LinkedList.h"
#include "..\Events\Event.h"
#include "..\Events\ArrivalEvent.h"
#include "..\Events\CancellationEvent.h"
#include "..\Events\PromotionEvent.h"
#include "Order.h"
#include <fstream>
#include <string>
#include <sstream>
// it is the maestro of the project


class Restaurant
{
private:
	GUI* pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file, it is Queue of pointers as we will use polymorphism (class Event is an abstract class)
	LinkedList<Order*> NormalOrdersList; // Queue of all Normal orders
	PriorityQueue<Order*> VipOrdersQ; // Priority Queue of all VIP orders
	PriorityQueue<Order*> UrgentOrdersQ;  //Priority Queue of Urgent Orders
	Queue<Order*> VeganOrdersQ; // Queue for vegan orders
	Queue<Order*> FinishedOrdersQ; // Queue for Finished Orders
	LinkedList<Order*> InServiceList; // List of Orders in service
	Queue<Cook*> NormalCooks; // Queue of Normal cooks
	Queue<Cook*> VeganCooks; // Queue of Vegan cooks
	Queue<Cook*> VipCooks; // Queue of VIP cooks
	LinkedList<Cook*>InServiceCooks; // List of cooks in Service
	LinkedList<Cook*>InBreakCooks; // List of cooks in break
	LinkedList<Cook*> RestingCooks; // Injured cooks receiving medication
	string FileName;
								//
								// TODO: Add More Data Members As Needed
								//
	int WaitNormalOrders;
	int WaitVipOrders;
	int WaitVeganOrders;
	int AvailableNormalCooks;
	int AvailableVipCooks;
	int AvailableVeganCooks;
	int NoNormalCooks;
	int NoVeganCooks;
	int NoVipCooks;
	int NoSRVNormal;
	int NoSRVVeg;
	int NoSRVvip;
	int BO; // number of orders that a cook must prepare before taking a break
	
	int AutoP; // Number of time steps after which an order is automatically promoted to to VIP
	float InjProp; // Probability a busy cook gets injured
	int RstPrd; // The rest Period in Case of injury
	int VIP_WT; // The number of ticks after which a VIP Order is considered urgent
	int Injured; //Number of Injured Cooks during the simulation
	int Urgent; // Number of Urgent Orders during the simulation
	int AutoPromoted; // Number of AutoPromoted Orders during the simulation
public:

	Restaurant();
	~Restaurant();

	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();

	void FillDrawingList();

	//
	// TODO: Add More Member Functions As Needed
	//

	void ReadInputFile();			// Function that reads the input from a text file
	void CookInService(int CurrentTS);
	
	void AssignOrder(Cook*& pCook, Order*& pOrd, int CurrentTS);
	void CooksInjured();
	void CheckBreak();
	void CookMedication();
	void ResetRemainedDishes();
	void RemoveFromNormalList(Order* pOrd);
	void AddtoQueue(Order* pOrder); //Adds and order to its waiting list
	Order* getOrderbyID(int oID, ORD_TYPE type);     //Returns the address of an order according to its type and ID
	void AutoPromotion(int timestep);                //promote the normal orders that waits more than N timesteps to VIP order automatically
	int VipToUrgent(int timestep);       // A fuction that change VIP orders that waited longer than VIP_WT ticks to be urgent orders
	void OutputFile();						       // A function that produces the output file of the simulation
	       

};

#endif