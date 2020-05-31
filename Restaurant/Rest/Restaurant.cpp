#include <cstdlib>
#include <time.h>
#include <iostream>
#include<iomanip>
using namespace std;


#include"Restaurant.h"

Restaurant::Restaurant()
{
	WaitNormalOrders = 0;
	WaitVipOrders = 0;
	WaitVeganOrders = 0;
	NoSRVNormal=NoSRVVeg=NoSRVvip=0;
	Urgent = 0;
	Injured = 0;
	AutoPromoted = 0;
	pGUI = NULL;
}

void Restaurant::RunSimulation()
{
	srand(time(0));
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();

	ReadInputFile();
	Order* pOrd;
	Cook* pCook;
	int CurrentTimeStep = 1;
	while (!EventsQueue.isEmpty() || !InServiceList.isEmpty() || !NormalOrdersList.isEmpty() || !VeganOrdersQ.isEmpty() || !VipOrdersQ.isEmpty() || !UrgentOrdersQ.isEmpty()) // The program
	{
		Queue<string> ServedLast; 
		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step
		CookMedication();
		ResetRemainedDishes();
		CheckBreak();
		AutoPromotion(CurrentTimeStep);
		VipToUrgent(CurrentTimeStep);
		CooksInjured();
		CookInService(CurrentTimeStep);
		while (!UrgentOrdersQ.isEmpty())
		{
			if (!NormalCooks.isEmpty() || !VeganCooks.isEmpty() || !VipCooks.isEmpty() || !InBreakCooks.isEmpty() || !RestingCooks.isEmpty())
			{
				UrgentOrdersQ.dequeue(pOrd);
				InServiceList.InsertEnd(pOrd);
				if (!VipCooks.isEmpty())
				{
					VipCooks.dequeue(pCook);
					AvailableVipCooks--;
					AssignOrder(pCook, pOrd, CurrentTimeStep);
					ServedLast.enqueue("V" + to_string(pCook->GetID()) + "(V" + to_string(pOrd->GetID()) + ")");
					WaitVipOrders--;
					NoSRVvip++;
				}
				else if (!NormalCooks.isEmpty())
				{
					NormalCooks.dequeue(pCook);
					AvailableNormalCooks--;
					AssignOrder(pCook, pOrd, CurrentTimeStep);
					ServedLast.enqueue("N" + to_string(pCook->GetID()) + "(V" + to_string(pOrd->GetID()) + ")");
					WaitVipOrders--;
					NoSRVvip++;
				}
				else if (!VeganCooks.isEmpty())
				{
					VeganCooks.dequeue(pCook);
					AvailableVeganCooks--;
					AssignOrder(pCook, pOrd, CurrentTimeStep);
					ServedLast.enqueue("G" + to_string(pCook->GetID()) + "(V" + to_string(pOrd->GetID()) + ")");
					WaitVipOrders--;
					NoSRVvip++;
				}
				else if (!InBreakCooks.isEmpty())
				{
					InBreakCooks.removeFirst(pCook);
					AssignOrder(pCook, pOrd, CurrentTimeStep);
					ORD_TYPE type = pCook->GetType();
					string T;
					if (type == TYPE_NRM)
						T = "N";
					else if (type == TYPE_VGAN)
						T = "G";
					else if (type == TYPE_VIP)
						T = "V";
					ServedLast.enqueue(T + to_string(pCook->GetID()) + "(V" + to_string(pOrd->GetID()) + ")");
					WaitVipOrders--;
					NoSRVvip++;
				}
				else if (!RestingCooks.isEmpty())
				{
					RestingCooks.removeFirst(pCook);
					AssignOrder(pCook, pOrd, CurrentTimeStep);
					ORD_TYPE type = pCook->GetType();
					string T;
					if (type == TYPE_NRM)
						T = "N";
					else if (type == TYPE_VGAN)
						T = "G";
					else if (type == TYPE_VIP)
						T = "V";
					ServedLast.enqueue(T + to_string(pCook->GetID()) + "(V" + to_string(pOrd->GetID()) + ")");
					WaitVipOrders--;
					NoSRVvip++;
				}
			}
			else
				break;
		}
		while (!VipOrdersQ.isEmpty())
		{
			if (!VipCooks.isEmpty() || !NormalCooks.isEmpty() || !VeganCooks.isEmpty())
			{
				VipOrdersQ.dequeue(pOrd);
				InServiceList.InsertEnd(pOrd);
				if (!VipCooks.isEmpty())
				{
					VipCooks.dequeue(pCook);
					AvailableVipCooks--;
					AssignOrder(pCook, pOrd, CurrentTimeStep);
					ServedLast.enqueue("V" + to_string(pCook->GetID()) + "(V" + to_string(pOrd->GetID()) + ")");
					WaitVipOrders--;
					NoSRVvip++;
				}
				else if (!NormalCooks.isEmpty())
				{
					NormalCooks.dequeue(pCook);
					AvailableNormalCooks--;
					AssignOrder(pCook, pOrd, CurrentTimeStep);
					ServedLast.enqueue("N" + to_string(pCook->GetID()) + "(V" + to_string(pOrd->GetID()) + ")");
					WaitVipOrders--;
					NoSRVvip++;
				}
				else if (!VeganCooks.isEmpty())
				{
					VeganCooks.dequeue(pCook);
					AvailableVeganCooks--;
					AssignOrder(pCook, pOrd, CurrentTimeStep);
					ServedLast.enqueue("G" + to_string(pCook->GetID()) + "(V" + to_string(pOrd->GetID()) + ")");
					WaitVipOrders--;
					NoSRVvip++;
				}
			}
			else
				break;
		}
		while (!VeganOrdersQ.isEmpty())
		{
			if (!VeganCooks.isEmpty())
			{
				VeganOrdersQ.dequeue(pOrd);
				InServiceList.InsertEnd(pOrd);
				VeganCooks.dequeue(pCook);
				AvailableVeganCooks--;
				AssignOrder(pCook, pOrd, CurrentTimeStep);
				ServedLast.enqueue("G" + to_string(pCook->GetID()) + "(G" + to_string(pOrd->GetID()) + ")");
				WaitVeganOrders--;
				NoSRVVeg++;
			}
			else
				break;
		}
		while (!NormalOrdersList.isEmpty())
		{
			if (!NormalCooks.isEmpty() || !VipCooks.isEmpty())
			{
				NormalOrdersList.removeFirst(pOrd);
				InServiceList.InsertEnd(pOrd);
				if (!NormalCooks.isEmpty())
				{
					NormalCooks.dequeue(pCook);
					AvailableNormalCooks--;
					AssignOrder(pCook, pOrd, CurrentTimeStep);
					ServedLast.enqueue("N" + to_string(pCook->GetID()) + "(N" + to_string(pOrd->GetID()) + ")");
					WaitNormalOrders--;
					NoSRVNormal++;
				}
				else if (!VipCooks.isEmpty())
				{
					VipCooks.dequeue(pCook);
					AvailableVipCooks--;
					AssignOrder(pCook, pOrd, CurrentTimeStep);
					ServedLast.enqueue("V" + to_string(pCook->GetID()) + "(N" + to_string(pOrd->GetID()) + ")");
					WaitNormalOrders--;
					NoSRVNormal++;
				}
			}
			else
				break;
		}
		
		if (mode == MODE_INTR || mode == MODE_STEP) // interactive or step by step
		{
			FillDrawingList();
			string msg = "TimeStep: " + to_string(CurrentTimeStep) + "\nNo of Available Normal cooks: " + to_string(AvailableNormalCooks) + "    No of Available Vegan cooks: " + to_string(AvailableVeganCooks) + "    No of Available Vip cooks: " + to_string(AvailableVipCooks) + "\nNo of Waiting Normal Orders: " + to_string(WaitNormalOrders) + "     No of Waiting Vegan Orders: " + to_string(WaitVeganOrders) + "     No of Waiting Vip Orders: " + to_string(WaitVipOrders) + 
				"\nNo of Served Normal Orders: "+to_string(NoSRVNormal)+ "      No of Served Vegan Orders: " + to_string(NoSRVVeg)+ "      No of Served VIP Orders: " + to_string(NoSRVvip)+"\n";
			
			while (!ServedLast.isEmpty())
			{
				string str;
				ServedLast.dequeue(str);
				msg = msg + str + " ";
			}
			pGUI->PrintMessage(msg);
			pGUI->UpdateInterface();
			if (mode == MODE_INTR) // interactive
				pGUI->waitForClick();
			Sleep(1000);
			CurrentTimeStep++;	//advance timestep
			pGUI->ResetDrawingList();
		}
		else // silent mode
		{
			CurrentTimeStep++;
		}
	}
	OutputFile();
}





//////////////////////////////////  Event handling functions   /////////////////////////////

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event* pE;
	while (EventsQueue.peekFront(pE))	//as long as there are more events
	{
		if (pE->getEventTime() > CurrentTimeStep)	//no more events at current timestep
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}


Restaurant::~Restaurant()
{
	if (pGUI)
		delete pGUI;
}


void Restaurant::FillDrawingList()
{
	//This function should be implemented in phase1
	//It should add ALL orders and Cooks to the drawing list
	//It should get orders from orders lists/queues/stacks/whatever (same for Cooks)
	//To add orders it should call function  void GUI::AddToDrawingList(Order* pOrd);
	//To add Cooks it should call function  void GUI::AddToDrawingList(Cook* pCc);

	Order** arrOrders; // used as auxiliary array of orders
	Cook** arrCooks; // used as auxiliary array of cooks
	LinkedList<Order*> tempWaitingList; // used as auxiliary List for waiting orders
	LinkedList<Order*> tempWaitingList2; // used as auxiliary List for waiting orders
	int size;

	arrOrders = VipOrdersQ.toArray(size);
	for (int i = 0; i < size; i++)
		tempWaitingList.InsertSort(arrOrders[i]);  // In order to add it in the Drawing List Sorted

	arrOrders = tempWaitingList.toArray(size); // Vip Orders added sorted in arrTime
	for (int i = 0; i < size; i++)
		pGUI->AddToDrawingList(arrOrders[i]);

	arrOrders = UrgentOrdersQ.toArray(size);
	for (int i = 0; i < size; i++)
		tempWaitingList2.InsertSort(arrOrders[i]);  // In order to add it in the Drawing List Sorted

	arrOrders = tempWaitingList2.toArray(size); // Urgent Vip Orders added sorted in arrTime
	for (int i = 0; i < size; i++)
		pGUI->AddToDrawingList(arrOrders[i]);

	arrOrders = VeganOrdersQ.toArray(size); // Vegan Orders added sorted in arrTime
	for (int i = 0; i < size; i++)
		pGUI->AddToDrawingList(arrOrders[i]);

	arrOrders = NormalOrdersList.toArray(size); // Normal Orders added sorted in arrTime
	for (int i = 0; i < size; i++)
		pGUI->AddToDrawingList(arrOrders[i]);

	arrOrders = InServiceList.toArray(size); // In service Orders added sorted in assignment Time
	for (int i = 0; i < size; i++)
		pGUI->AddToDrawingList(arrOrders[i]);

	arrOrders = FinishedOrdersQ.toArray(size); // Finished Orders added sorted by finish time
	for (int i = 0; i < size; i++)
		pGUI->AddToDrawingList(arrOrders[i]);

	arrCooks = NormalCooks.toArray(size); //Normal cooks added sorted in Availability 
	for (int i = 0; i < size; i++)
		pGUI->AddToDrawingList(arrCooks[i]);

	arrCooks = VeganCooks.toArray(size); //Vegan cooks added sorted in Availability 
	for (int i = 0; i < size; i++)
		pGUI->AddToDrawingList(arrCooks[i]);

	arrCooks = VipCooks.toArray(size); //Vip cooks added sorted in Availability 
	for (int i = 0; i < size; i++)
		pGUI->AddToDrawingList(arrCooks[i]);

	arrCooks = InServiceCooks.toArray(size); //In service cooks added sorted in Assignment ( not available ) 
	for (int i = 0; i < size; i++)
		pGUI->AddToDrawingList(arrCooks[i]);

	arrCooks = InBreakCooks.toArray(size); //In break cooks added sorted in Availability ( Not available )
	for (int i = 0; i < size; i++)
		pGUI->AddToDrawingList(arrCooks[i]);

	arrCooks = RestingCooks.toArray(size); // Resting (injured) cooks added sorted in availability ( not available )
	for (int i = 0; i < size; i++)
		pGUI->AddToDrawingList(arrCooks[i]);
}



Order* Restaurant::getOrderbyID(int oID, ORD_TYPE type)
{
	Order** Orders;
	int count = 0;
	if (type == TYPE_NRM)
	{
		Orders = NormalOrdersList.toArray(count);
		for (int i = 0; i < count; i++)
		{
			if (Orders[i]->GetID() == oID)
				return Orders[i];
		}
	}
	else if (type == TYPE_VGAN)
	{
		Orders = VeganOrdersQ.toArray(count);
		for (int i = 0; i < count; i++)
		{
			if (Orders[i]->GetID() == oID)
				return Orders[i];
		}
	}
	else if (type == TYPE_VIP)
	{
		Orders = VipOrdersQ.toArray(count);
		for (int i = 0; i < count; i++)
		{
			if (Orders[i]->GetID() == oID)
				return Orders[i];
		}
	}
	return nullptr;
}



void Restaurant::ReadInputFile()
{
	
	pGUI->PrintMessage("Please Enter Input File Name: ");
	FileName = pGUI->GetString(); // read file nme from the user
	FileName = FileName + ".txt";

	ifstream File;
	File.open(FileName); // open input file

	string Line; // serves as a copy of each Line in the input file
	string n; // value read from input file

	int NumberEvents;
	int ID = 1;
	int SNmin, SNmax, SGmin, SGmax, SVmin, SVmax;
	int BNmin, BNmax, BGmin, BGmax, BVmin, BVmax;

	if (File.is_open())
	{
		pGUI->PrintMessage("File is opened successfully");
		for (int i = 1; i <= 6; i++) // While loop passes on First 5 Lines lines
		{
			getline(File, Line);
			istringstream ISS(Line); // associates a string object with a stream allowing you to read from the string
			switch (i) // switch on no. of Line
			{
			case 1: // Line 1 : no. of cooks for each type
			{
				for (int i = 1; i <= 3; i++) // Loops on elements, as we have 3 types of cooks
				{
					ISS >> n;
					int Value = stoi(n); //converts string read from file to integer
					if (i == 1) // Normal cooks
					{
						NoNormalCooks = Value;
						AvailableNormalCooks = Value;
					}

					else if (i == 2) // Vegan Cooks
					{
						NoVeganCooks = Value;
						AvailableVeganCooks = Value;
					}

					else if (i == 3) // VIP cooks
					{
						NoVipCooks = Value;
						AvailableVipCooks = Value;
					}
				}
				break;
			}
			case 2: // Line 2 : cooks speeds for each type
			{
				for (int i = 1; i <= 6; i++) // Loops on elements, as we have 3 types of cooks
				{
					ISS >> n;
					int speed = stoi(n); //converts string read from file to integer
					if (i == 1) // Min speed of normal cooks
						SNmin = speed;
					else if (i == 2) // Max speed of  normal cooks
						SNmax = speed;
					else if (i == 3) // Min speed of VG cooks
						SGmin = speed;
					else if (i == 4) // Max speed of  VG cooks
						SGmax = speed;
					else if (i == 5) // Min speed of  VIP cooks
						SVmin = speed;
					else if (i == 6) // Max speed of VIP cooks
						SVmax = speed;
				}
				break;
			}
			case 3: // Line 3: Break Durations
			{
				for (int i = 1; i <= 7; i++) // Loops on elements, as BO,BNmin,BNmax,BGmin,BGmax,BVmin,BVmax
				{
					ISS >> n;
					int Value = stoi(n);
					if (i == 1)
						BO = Value;
					else if (i == 2)
						BNmin = Value;
					else if (i == 3)
						BNmax = Value;
					else if (i == 4)
						BGmin = Value;
					else if (i == 5)
						BGmax = Value;
					else if (i == 6)
						BVmin = Value;
					else if (i == 7)
						BVmax = Value;
				}
				break;
			}
			case 4: // Line 4 : Injury Probability and Rest Period
			{
				for (int i = 1; i <= 2; i++)
				{
					ISS >> n;
					float Value = stof(n);
					if (i == 1)
						InjProp = Value;
					if (i == 2)
						RstPrd = Value;
				}
				break;
			}
			case 5: // Line 5 : Auto Promotion And VIP_Wait
			{
				for (int i = 1; i <= 2; i++)
				{
					ISS >> n;
					int Value = stoi(n);
					if (i == 1)
						AutoP = Value;
					if (i == 2)
						VIP_WT = Value;
				}
				break;
			}
			case 6: // Line 6 : no. of events in this file
			{
				ISS >> n;
				NumberEvents = stoi(n);
			}
			}
		}
		for (int i = 0; i < NoNormalCooks; i++) // Fill Normal cooks Queue
		{
			Cook* C = new Cook;
			C->setType(TYPE_NRM);
			C->setID(ID);
			C->setSpeed(SNmin + (rand() % (SNmax - SNmin + 1))); // Generate a random speed in range
			C->setAvailability(true);
			C->setBreak(BNmin + (rand() % (BNmax - BNmin + 1))); // generate random break Duration
			ID++;
			NormalCooks.enqueue(C);
		}
		for (int i = 0; i < NoVeganCooks; i++) // Fill Vegan cooks Queue
		{
			Cook* C = new Cook;
			C->setType(TYPE_VGAN);
			C->setID(ID);
			C->setSpeed(SGmin + (rand() % (SGmax - SGmin + 1))); // Generate a random speed in range
			C->setAvailability(true);
			C->setBreak(BGmin + (rand() % (BGmax - BGmin + 1))); // generate random break Duration
			ID++;
			VeganCooks.enqueue(C);
		}
		for (int i = 0; i < NoVipCooks; i++) // Fill VIP cooks Queue
		{
			Cook* C = new Cook;
			C->setType(TYPE_VIP);
			C->setID(ID);
			C->setSpeed(SVmin + (rand() % (SVmax - SVmin + 1))); // Generate a random speed in range
			C->setAvailability(true);
			C->setBreak(BVmin + (rand() % (BVmax - BVmin + 1))); // generate random break Duration
			ID++;
			VipCooks.enqueue(C);
		}
		for (int i = 0; i < NumberEvents; i++) // All Lines of Events
		{
			getline(File, Line);
			istringstream ISS(Line);
			ISS >> n;
			if (n == "R") // arrival event
			{
				ISS >> n;
				ORD_TYPE oType;
				if (n == "N") // Normal Order
					oType = TYPE_NRM;
				else if (n == "G") // Vegan Order
					oType = TYPE_VGAN;
				else if (n == "V") // VIP Order
					oType = TYPE_VIP;
				ISS >> n; // TS arrival time
				int eTime = stoi(n);
				ISS >> n; // ID
				int oID = stoi(n);
				ISS >> n; // Size
				int size = stoi(n);
				ISS >> n; // Money
				double money = stoi(n);
				ArrivalEvent* ArrEvent = new ArrivalEvent(eTime, oID, oType, money, size);
				EventsQueue.enqueue(ArrEvent);
			}
			else if (n == "X") // Cancelation event
			{
				ISS >> n;
				int eTime = stoi(n);
				ISS >> n;
				int oID = stoi(n);
				CancellationEvent* cancEvent = new CancellationEvent(eTime, oID);
				EventsQueue.enqueue(cancEvent);
			}
			else if (n == "P") // Promotion Event
			{
				ISS >> n;
				int eTime = stoi(n);
				ISS >> n;
				int oID = stoi(n);
				ISS >> n;
				int ExMony = stoi(n);
				PromotionEvent* promEvent = new PromotionEvent(eTime, oID, ExMony);
				EventsQueue.enqueue(promEvent);
			}
		}
		File.close();
	}
	else
	{
		pGUI->PrintMessage("Unable to open file");
		pGUI->waitForClick();
		exit;
	}
}

void Restaurant::CookInService(int CurrentTS)
{
	int n;
	Cook** CooksInServ = InServiceCooks.toArray(n);
	Order** OrdersInServ = InServiceList.toArray(n);
	for (int i = 0; i < n; i++)
	{
		int Size = OrdersInServ[i]->getOrderSize(); // number of dishes in the order
		int RemDish = CooksInServ[i]->getRemainedDishes(); // number of dishes the cook can serve
		ORD_TYPE TypeOrder = OrdersInServ[i]->GetType();
		ORD_TYPE TypeCook = CooksInServ[i]->GetType();
		if (Size > RemDish)
		{
			OrdersInServ[i]->setOrderSize(Size - RemDish);
			CooksInServ[i]->setRemainedDishes(0);
		}
		else
		{
			CooksInServ[i]->setRemainedDishes(RemDish - Size);
			CooksInServ[i]->setAvailability(true);
			CooksInServ[i]->IncrementNumberOfServedOrders();
			if (CooksInServ[i]->getCountOfTakenBreak() != 0) // he was in break and it was interrupted to serve urgent order
			{
				// remove the cook from the serving list and insert in break list
				InServiceCooks.Remove(CooksInServ[i]);
				InBreakCooks.InsertEnd(CooksInServ[i]);
				CooksInServ[i]->setNumberOfServedOrders(0);
			}
			else if (CooksInServ[i]->isInjured() && CooksInServ[i]->getRestPeriod() != 0) // he was recovering from injury and it was interrupted to serve urgent order
			{
				//remove from inservice and insert in Resting
				InServiceCooks.Remove(CooksInServ[i]);
				RestingCooks.InsertEnd(CooksInServ[i]);
			}
			else if (CooksInServ[i]->isInjured()) // the cook finished order and is injured
			{
				//remove from inservice and insert in Resting
				InServiceCooks.Remove(CooksInServ[i]);
				RestingCooks.InsertEnd(CooksInServ[i]);
			}
			else if (CooksInServ[i]->getNumberOfServedOrders() == BO) // The cook served the required numbers of orders to take a break
			{
				// remove the cook from the serving list and insert in break list
				InServiceCooks.Remove(CooksInServ[i]);
				InBreakCooks.InsertEnd(CooksInServ[i]);
				CooksInServ[i]->setNumberOfServedOrders(0);
			}
			else // still didn't serve the required number and not injured
			{
				// remove him from in service and insert in available cooks
				InServiceCooks.Remove(CooksInServ[i]);
				if (TypeCook == TYPE_NRM)
				{
					NormalCooks.enqueue(CooksInServ[i]);
					AvailableNormalCooks++;
				}
				else if (TypeCook == TYPE_VGAN)
				{
					VeganCooks.enqueue(CooksInServ[i]);
					AvailableVeganCooks++;
				}
				else
				{
					VipCooks.enqueue(CooksInServ[i]);
					AvailableVipCooks++;
				}
			}
			OrdersInServ[i]->setStatus(DONE);
			OrdersInServ[i]->setFinishTime(CurrentTS);
			// remove from in service and insert in finished list
			InServiceList.Remove(OrdersInServ[i]);
			FinishedOrdersQ.enqueue(OrdersInServ[i]);
		}
	}


}

void Restaurant::CooksInjured()
{
	Cook** CookSRV;
	int count = 0;
	float R = (float)rand() / (float)(RAND_MAX);
	if (R <= InjProp)
	{
		CookSRV = InServiceCooks.toArray(count);
		for (int i = 0; i < count; i++)
		{
			if (!(CookSRV[i]->isInjured()))
			{
				CookSRV[i]->setInjured();
				Injured++;
				break;
			}
		}
	}
}

void Restaurant::CookMedication()
{
	Cook** CooksRest;
	ORD_TYPE type;
	int count = 0;
	CooksRest = RestingCooks.toArray(count);
	for (int i = 0; i < count; i++)
	{
		if (CooksRest[i]->getRestPeriod() == RstPrd)
		{
			CooksRest[i]->setRecovered();
			type = CooksRest[i]->GetType();
			
			if (CooksRest[i]->getNumberOfServedOrders() == BO)
			{
				InBreakCooks.InsertEnd(CooksRest[i]);
				RestingCooks.Remove(CooksRest[i]);
			}
			else
			{
				if (type == TYPE_NRM)
				{
					AvailableNormalCooks++;
					NormalCooks.enqueue(CooksRest[i]);
				}
				else if (type == TYPE_VIP)
				{
					AvailableVipCooks++;
					VipCooks.enqueue(CooksRest[i]);
				}
				else
				{
					AvailableVeganCooks++;
					VeganCooks.enqueue(CooksRest[i]);
				}

				RestingCooks.Remove(CooksRest[i]);
			}
		}
		else
			CooksRest[i]->IncrementRestPeriod();
	}
}


void Restaurant::AssignOrder(Cook*& pCook, Order*& pOrd, int CurrentTS)
{
	ORD_TYPE TypeCook = pCook->GetType();
	pCook->setAvailability(false);
	InServiceCooks.InsertEnd(pCook);
	pOrd->setServTime(CurrentTS);
	pOrd->setWaitTime(CurrentTS - pOrd->getArrTime());
	pOrd->setStatus(SRV);
	int RemDish = pCook->getRemainedDishes();
	int Size = pOrd->getOrderSize();
	if (Size > RemDish)
	{
		pOrd->setOrderSize(Size - RemDish);
		pCook->setRemainedDishes(0);
	}
	else
	{
		pCook->setRemainedDishes(RemDish - Size);
		pCook->setAvailability(true);
		pCook->IncrementNumberOfServedOrders();
		if (pCook->getCountOfTakenBreak() != 0) // he was in break and it was interrupted to serve urgent order
		{
			// remove the cook from the serving list and insert in break list
			InServiceCooks.Remove(pCook);
			InBreakCooks.InsertEnd(pCook);
			pCook->setNumberOfServedOrders(0);
		}
		else if (pCook->isInjured() && pCook->getRestPeriod()!=0) // he was recovering from injury and it was interrupted to serve urgent order
		{
			//remove from inservice and insert in Resting
			InServiceCooks.Remove(pCook);
			RestingCooks.InsertEnd(pCook);
		}
		else if (pCook->isInjured()) // the cook finished order and is injured
		{
			//remove from inservice and insert in Resting
			InServiceCooks.Remove(pCook);
			RestingCooks.InsertEnd(pCook);
		}
		else if (pCook->getNumberOfServedOrders() == BO) // The cook served the required numbers of orders to take a break
		{
			// remove the cook from the serving list and insert in break list
			InServiceCooks.Remove(pCook);
			InBreakCooks.InsertEnd(pCook);
			pCook->setNumberOfServedOrders(0);
		}
		else // still didn't serve the required number and not injured
		{
			// remove him from in service and insert in available cooks
			InServiceCooks.Remove(pCook);
			if (TypeCook == TYPE_NRM)
			{
				NormalCooks.enqueue(pCook);
				AvailableNormalCooks++;
			}
			else if (TypeCook == TYPE_VGAN)
			{
				VeganCooks.enqueue(pCook);
				AvailableVeganCooks++;
			}
			else
			{
				VipCooks.enqueue(pCook);
				AvailableVipCooks++;
			}
		}
		pOrd->setStatus(DONE);
		pOrd->setFinishTime(CurrentTS);
		// remove from in service and insert in finished list
		InServiceList.Remove(pOrd);
		FinishedOrdersQ.enqueue(pOrd);
	}
}


void Restaurant::CheckBreak()
{
	int size;
	Cook** CookB = InBreakCooks.toArray(size);
	for (int i = 0; i < size; i++)
	{
		ORD_TYPE TypeCook = CookB[i]->GetType();
		if (CookB[i]->getCountOfTakenBreak() == CookB[i]->getBreakDuration())
		{
			// remove from break and insert in available cooks
			InBreakCooks.Remove(CookB[i]);
			CookB[i]->setCountOfTakenBreak(0);
			CookB[i]->setAvailability(true);
			if (TypeCook == TYPE_NRM)
			{
				NormalCooks.enqueue(CookB[i]);
				AvailableNormalCooks++;
			}
			else if (TypeCook == TYPE_VGAN)
			{
				VeganCooks.enqueue(CookB[i]);
				AvailableVeganCooks++;
			}
			else
			{
				VipCooks.enqueue(CookB[i]);
				AvailableVipCooks++;
			}
		}
		else
		{
			CookB[i]->IncrementCountOfTakenBreak();
		}

	}
}

void Restaurant::ResetRemainedDishes()
{
	int size;
	Cook** CookL;
	CookL = NormalCooks.toArray(size);
	for (int i = 0; i < size; i++)
		CookL[i]->setRemainedDishes(CookL[i]->getSpeed());

	CookL = VeganCooks.toArray(size);
	for (int i = 0; i < size; i++)
		CookL[i]->setRemainedDishes(CookL[i]->getSpeed());


	CookL = VipCooks.toArray(size);
	for (int i = 0; i < size; i++)
		CookL[i]->setRemainedDishes(CookL[i]->getSpeed());


	CookL = InServiceCooks.toArray(size);
	for (int i = 0; i < size; i++)
		CookL[i]->setRemainedDishes(CookL[i]->getSpeed());

	CookL = InBreakCooks.toArray(size);
	for (int i = 0; i < size; i++)
		CookL[i]->setRemainedDishes(CookL[i]->getSpeed());
}



void Restaurant::RemoveFromNormalList(Order* pOrd)
{
	NormalOrdersList.Remove(pOrd);
	WaitNormalOrders--;
}

void Restaurant::AddtoQueue(Order* pOrder)
{
	if (!pOrder)
		return;

	switch (pOrder->GetType())
	{
	case TYPE_VIP:
		VipOrdersQ.enqueueSort(pOrder);
		WaitVipOrders++;
		break;
	case TYPE_VGAN:
		VeganOrdersQ.enqueue(pOrder);
		WaitVeganOrders++;
		break;
	case TYPE_NRM:
		NormalOrdersList.InsertEnd(pOrder);
		WaitNormalOrders++;
		break;
	default:
		break;
	}
}


void Restaurant::AutoPromotion(int CurrentTimestep)
{
	if (NormalOrdersList.isEmpty())
		return;

	int n = 0;
	Order** NRMOrders = NormalOrdersList.toArray(n);
	for (int i = 0; i < n; i++)
	{
		if (CurrentTimestep - (NRMOrders[i]->getArrTime()) == AutoP)
		{
			Order* ToVIP = NRMOrders[i];
			ToVIP->setType(TYPE_VIP);
			VipOrdersQ.enqueueSort(ToVIP);
			NormalOrdersList.Remove(NRMOrders[i]);
			AutoPromoted++;
			WaitNormalOrders--;
			WaitVipOrders++;
			
		}
	}
}
int Restaurant::VipToUrgent(int CurrentTimestep)
{
	if (VipOrdersQ.isEmpty() && UrgentOrdersQ.isEmpty())
		return 0;
	Order** VipOrders;
	int NumofUrgent=0;  //Number of vip orders that considered to be Urgent order 
	int c;              //Number of VIP orders
	int n;             //Number of Urgent order before this current timestep
	UrgentOrdersQ.toArray(n);
	VipOrders=VipOrdersQ.toArray(c);
	for (int i = 0; i < c; i++)
	{
		if (CurrentTimestep - VipOrders[i]->getArrTime() == VIP_WT)
		{
			UrgentOrdersQ.enqueueSort(VipOrders[i]);
			VipOrdersQ.Remove(VipOrders[i]);
			NumofUrgent++;
			Urgent++;
		}
	}
	return n + NumofUrgent;
}



void Restaurant::OutputFile()
{
	
	ofstream out("Out_"+FileName+".txt");
	out << "FT\tID\tAT\tWT\tST\n";
	Order* Ord = nullptr;
	int total = FinishedOrdersQ.getSize();
	int Nrm = 0, Veg = 0, VIP = 0;
	int total_WT = 0, total_SRV = 0;
	int totalCooks = NoNormalCooks + NoVeganCooks + NoVipCooks;
	float AutoPercent ;

	while (!FinishedOrdersQ.isEmpty())
	{
		FinishedOrdersQ.dequeue(Ord);
		if (Ord->GetType() == TYPE_NRM)
			Nrm++;
		else if (Ord->GetType() == TYPE_VGAN)
			Veg++;
		else
			VIP++;

		int Finishtime = Ord->getFinishTime();
		int Arrtime = Ord->getArrTime();
		int ID = Ord->GetID();
		int Wait_time = Ord->getServTime() - Arrtime;
		int Servingtime = Finishtime - Ord->getServTime();
		total_WT += Wait_time;

		total_SRV += Servingtime;

		out << Finishtime << "\t" << ID << "\t" << Arrtime << "\t" << Wait_time << "\t" << Servingtime << "\n";
		delete Ord;
	}
	AutoPercent = Nrm == 0 ? 0 : ((float)AutoPromoted / (Nrm + AutoPromoted)) * 100;
	out << "Orders: " << total << " [Norm:" << Nrm << ", Veg:" << Veg << ", VIP:" << VIP << "]\n";
	out << "Cooks: " << totalCooks << " [Norm:" << NoNormalCooks << ", Veg:" << NoVeganCooks << ", VIP:" << NoVipCooks << ", Injured:" << Injured << "]\n";
	out << fixed << setprecision(2);
	out << "Avg Wait = " << (float)total_WT / total << " Avg Served = " << (float)total_SRV / total << endl;
	out << "Urgent Order: " << Urgent << ", Auto-Promoted: " <<AutoPercent<<"%"<< endl;

	out.close();
}


