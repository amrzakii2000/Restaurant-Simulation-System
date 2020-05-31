This project information credits goes to the staff of faculty of Engineering - Cairo Uiversity - Computer engineering department 
as this is an academic project
=======================================

Orders Information :
=
Orders:
The following information is available for each order:

-	Arrival Time Stamp: When the order was made.

-	Order Type: There are 3 types of orders: VIP, Vegan orders and Normal orders.

●	VIP orders must be served first before vegan and normal orders.

●	For VIP orders, there is a priority equation depending on order size, price, arrival time..etc for deciding which of the available VIP orders to serve first.

 VIP orders with higher priority must be serviced first.

  Urgent Orders :
 VIP orders that waited longer than VIP_WT ticks to be served are considered urgent orders and must be served even using cooks that are in break or in rest. 
The value of VIP_WT is read from the input file

●	Vegan orders are the orders that needs to be prepared by specialized cooks using all plant-based ingredients. 

●	Normal orders are the orders that neither VIP nor vegan.
-	Order Size: the number of dishes for this order (in dishes).
-	Order Price: the total order price the customer should pay.
	For Normal orders ONLY, 
	The customer can promote it to become VIP order by paying more money
	The customer can cancel the order as long as it is not assigned to a cook yet
	If a NORMAL order waits more than N timesteps from its arrival time without being assigned to a cook, 
it will be automatically promoted to be a VIP order. (N is read from the input file)  

=======================================
Cooks Information :
=
-	Cook specialization: There are 3 types: VIP cooks, vegan cooks and Normal cooks.

●	VIP cooks are cooks with higher cooking abilities so they are best for doing high profile orders.

●	Vegan cooks are cooks that tolerates making all vegetable food. 

●	Normal cooks are the cooks that neither VIP nor vegan.

-	Break Duration: Each cook takes a break after serving n consecutive orders. 

-	Cook speed: the number of dishes it can prepare in one timestep

-Cook speed/break time:
=
 cooks of the same type may have different speeds and different break times. 
In the input file you will get a minimum and a maximum values for the speed of each cook type.  a random speed is generated for each cook between min. and max. values.
The same applies for cooks break times

-Cooks Health Emergency Problems: "applicable for busy cooks only"
=
Busy cooks can get injured (with knives or heat) during cooking. If this happens for a cook:
o	His speed should be decreased to its half until he finishes the order he is working on
o	Then he should wait for a rest period to have the necessary medication.
o	After rest period, he can join the available cooks again.

=======================================
Service Criteria :
=
To determine the next order to serve (if a cook is available), the following Service Criteria should be applied for all the arrived un-serviced orders at each time step: 

1)	First, Serve VIP orders by ANY available type of cooks, but there is a priority based on the cook’s type over the others to prepare VIP orders: First use VIP Cooks THEN Normal Cooks THEN Vegan Cooks. This means that we don’t use Normal cook unless all VIP cooks are busy, and don’t use Vegan cooks unless all other types are busy.

2)	Second, Serve Vegan orders using available Vegan cooks ONLY. If all vegan cooks are busy, wait until one is free.

3)	Third, Serve Normal orders using any type of cooks EXCEPT vegan cooks, but First use the available Normal cooks THEN VIP cooks (if all Normal are busy).

4)	If an order cannot be served at the current time step, it should wait for the next time step to be checked if it can be serviced or not. If not, it should wait again.

Notes: If the orders of a specific type cannot be serviced in the current time step, try to service the other types (e.g. if Vegan orders cannot be serviced in the current time step, this does NOT mean not to service the Normal orders)

=======================================
GUI Information:
=
-The upper left section : has the arrived waiting orders (Normal orders are in red, Vegan Orders are in blue and VIP in pink) sorted by arrival time

-The lower right section : contains the orders that are assigned to cooks and are being served sorted by serving timestep

- The lower left corner: contains the IDs of finished orders

-The upper right corner: contains cooks IDs sorted by availability.




--------------------------------------------------------



You have to create an input file containing information about orders and cooks
=
- Please follow the following input Format :
The Input File Format


Line 1	
N	G	V
the number of cooks of different types (Normal, veGan, VIP)

Line 2	
SN_min	SN_max 	SG_min	SG_max	SV_min	SV_max
The speed range (min & max) of each cook type

Line 3	
BO	BN_min	BN_max	BG_min	BG_max	BV_min	BV_max
BO: the number of orders a cook must prepare before taking a break
Then the break range (mix & max) of each cook type

Line 4	
InjProp	RstPrd
The probability a busy cook gets injured and the rest period respectively

Line 5	
AutoP		VIP_WT
AutoP: the number of ticks after which an order is automatically promoted to VIP
VIP_WT: the number of ticks after which a VIP order is considered urgent

Line 6	
M: the number of events in this file

Next M Lines	Each line represents and event. An event can be:

●	Arrival of a new order. Denoted by letter R, or

●	Cancellation of an existing order. Denoted by letter X, or

●	Promotion of an order to be a VIP order. Denoted by letter P.

The lines of all events are sorted by the event time (TS) in ascending order.

Information about events format :
=

•	Arrival event line have the following info

	R(letter R in the beginning of its line) means an arrival event

	TYP is the order type (N: normal, G: vegan, V: VIP).

	TS is the event timestep. (order arrival time)

	ID is a unique sequence number that identifies each order.

	SIZE is the number of dishes of the order

	MONY is the total order money. 

•	Cancellation event line have the following info

	X(Letter X) means an order cancellation event

	TS is the event timestep.

	ID is the id of the order to be canceled. This ID must be of a Normal order.

•	Promotion event line have the following info

	P(Letter P) means an order promotion event occurring

	TS is the event timestep.

	ID is the id of the order to be promoted to be VIP. It must be of a Normal order.

	ExMony if the extra money the customer paid for promotion.

The project has six sample input files and their output 
(Notice : that the output might differ each time as some numbers are generated randomly during the simulation)
====

The program has three modes:
=
- Interactive mode : the user decides to move to the next time step by a mouse click
- Step by Step mode: the simulation runs by itself and every timestep takes one second
- Silent Mode: Only the output file is generated without any interface

=======================================
