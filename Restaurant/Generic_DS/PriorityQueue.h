#pragma once
#include"../Generic_DS/Node.h"

template<class T>
class PriorityQueue
{
	Node<T>* frontptr;
	int count ;
public:
	PriorityQueue<T>(Node<T>*ptr = nullptr)
	{
		count = 0;
		frontptr = ptr;
	}
	int getSize() const
	{
		return count;
	}
	void enqueueSort(const T& item)
	{
		count++;
		Node<T>* newNode = new Node<T>(item);
		if (!frontptr || frontptr->getItem() <= item)
		{
			newNode->setNext(frontptr);
			frontptr = newNode;

			return;
		}
		else
		{
			Node<T>* prev = frontptr;
			Node<T>* after = frontptr->getNext();
			while (after)
			{
				if (after->getItem() <= item)
				{
					prev->setNext(newNode);
					newNode->setNext(after);
					return;
				}
				prev = after;
				after = after->getNext();
			}
			prev->setNext(newNode);
			newNode->setNext(nullptr);
		}
	}

	bool isEmpty()
	{
		if (!frontptr)
			return true;

		return false;
	}

	bool peek(T& item)
	{
		if (!frontptr)
			return false;
		item = frontptr->getItem();
		return true;
	}

	bool dequeue(T& item)
	{
		if (!frontptr)
			return false;

		item = frontptr->getItem();
		Node<T>* temp = frontptr;
		frontptr = frontptr->getNext();
		delete temp;
		count--;
		return true;
	}

	

	T* toArray(int& count)
	{
		count = 0;
		if (!frontptr)
			return nullptr;
		//counting the no. of items in the Queue
		Node<T>* p = frontptr;
		while (p)
		{
			count++;
			p = p->getNext();
		}


		T* Arr = new T[count];
		p = frontptr;
		for (int i = 0; i < count; i++)
		{
			Arr[i] = p->getItem();
			p = p->getNext();
		}
		return Arr;
	}
	~PriorityQueue<T>()
	{
		T item;
		while (dequeue(item));
	}

};

template <>
class PriorityQueue<Order*>
{
	Node<Order*>* frontptr;
	int count;
public:
	PriorityQueue(Node<Order*>*ptr = nullptr)
	{
		count = 0;
		frontptr = ptr;
	}
	int getSize() const
	{
		return count;
	}
	void enqueueSort(Order*& item)
	{
		count++;
		Node<Order*>* newNode = new Node<Order*>(item);
		if (!frontptr || frontptr->getItem()->getScore()<= item->getScore())
		{
			newNode->setNext(frontptr);
			frontptr = newNode;

			return;
		}
		else
		{
			Node<Order*>* prev = frontptr;
			Node<Order*>* after = frontptr->getNext();
			while (after)
			{
				if (after->getItem()->getScore()<= item->getScore())
				{
					prev->setNext(newNode);
					newNode->setNext(after);
					return;
				}
				prev = after;
				after = after->getNext();
			}
			prev->setNext(newNode);
			newNode->setNext(nullptr);
		}
	}

	bool isEmpty()
	{
		if (!frontptr)
			return true;

		return false;
	}

	bool peek(Order*& item)
	{
		if (!frontptr)
			return false;
		item = frontptr->getItem();
		return true;
	}

	bool dequeue(Order*& item)
	{
		if (!frontptr)
			return false;

		item = frontptr->getItem();
		Node<Order*>* temp = frontptr;
		frontptr = frontptr->getNext();
		delete temp;
		count--;
		return true;
	}

	bool Remove(Order* item)
	{
		if (!frontptr) return false;
		Node<Order*>* ptr = frontptr;
		if (frontptr && frontptr->getItem() == item)
		{
			Node<Order*>* NodeToDelete = frontptr;
			frontptr = frontptr->getNext();
			NodeToDelete->setNext(nullptr);
			count--;

			delete NodeToDelete;
			return true;
		}
		while (ptr && ptr->getNext())
		{
			if (ptr->getNext()->getItem() == item)
			{
				Node<Order*>* nodeToDelete = ptr->getNext();
				ptr->setNext(ptr->getNext()->getNext());
				nodeToDelete->setNext(nullptr);
				delete nodeToDelete;
				count--;
				return true;
			}
			ptr = ptr->getNext();
		}
		return false;
	}
	

	Order** toArray(int& count)
	{
		count = 0;
		if (!frontptr)
			return nullptr;
		//counting the no. of items in the Queue
		Node<Order*>* p = frontptr;
		while (p)
		{
			count++;
			p = p->getNext();
		}


		Order** Arr = new Order*[count];
		p = frontptr;
		for (int i = 0; i < count; i++)
		{
			Arr[i] = p->getItem();
			p = p->getNext();
		}
		return Arr;
	}
	~PriorityQueue<Order*>()
	{
		Order* item;
		while (dequeue(item));
	}

};

