#pragma once
//ADDED Amr and Dina
#include "..\Generic_DS/Node.h"
#include "..\Rest/Cook.h"
#include"../Rest/Order.h"
template <class T>
class LinkedList
{
	Node <T>* Head;
	int count;
public:
	LinkedList()
	{
		count = 0;
		Head = nullptr;
	}
	Node<T>* getHead() const
	{
		return Head;
	}
	void PrintList()
	{
		Node<T>* p = Head;

		while (p)
		{
			cout << p->getItem();
			cout << " ";
			p = p->getNext();
		}
	}
	
	void DeleteAll()
	{
		count = 0;
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}
	~LinkedList()
	{
		DeleteAll();
	}

	bool isEmpty()
	{
		return Head == nullptr;
	}

	void Insert(T Item)
	{
		count++;
		Node <T>* newNode = new Node<T>(Item);
		newNode->setNext(Head);
		Head = newNode;
	}

	void InsertSort(const T& item)
	{
		count++;
		Node<T>* newNode = new Node<T>(item);
		if (!Head || Head->getItem() > item)
		{
			newNode->setNext(Head);
			Head = newNode;

			return;
		}
		else
		{
			Node<T>* prev = Head;
			Node<T>* after = Head->getNext();
			while (after)
			{
				if (after->getItem() > item)
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

	bool InsertEnd(T item)
	{
		count++;
		Node<T>* ptr = Head;
		Node<T>* nNode = new Node<T>;
		nNode->setItem(item);
		nNode->setNext(NULL);
		if (!ptr)
		{
			Head = nNode;
			return true;
		}
		while (ptr->getNext())
			ptr = ptr->getNext();
		ptr->setNext(nNode);
		return true;
	}

	bool Remove(T item)
	{
		if (!Head) return false;
		Node<T>* ptr = Head;
		if (Head && Head->getItem() == item)
		{
			Node<T>* NodeToDelete = Head;
			Head = Head->getNext();
			NodeToDelete->setNext(nullptr);
			count--;

			delete NodeToDelete;
			return true;
		}
		while (ptr && ptr->getNext())
		{
			if (ptr->getNext()->getItem() == item)
			{
				Node<T>* nodeToDelete = ptr->getNext();
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
	bool removeFirst(T& item)
	{
		Node<T>* temp = Head;
		if (!temp)
		{
			item = nullptr;
			return false;
		}
		Head = Head->getNext();
		item = temp->getItem();
		delete temp;
		count--;

		return true;
	}

	T* toArray(int& count)
	{
		count = 0;

		if (!Head)
			return nullptr;
		//counting the no. of items in the Queue
		Node<T>* p = Head;
		while (p)
		{
			count++;
			p = p->getNext();
		}


		T* Arr = new T[count];
		p = Head;
		for (int i = 0; i < count; i++)
		{
			Arr[i] = p->getItem();
			p = p->getNext();
		}
		return Arr;
	}


};

template <>
class LinkedList<Order*> // Class Template specialization
{
	Node <Order*>* Head;
	int count;
public:
	LinkedList()
	{
		count = 0;
		Head = nullptr;
	}
	Node<Order*>* getHead() const
	{
		return Head;
	}
	/*void PrintList()
	{
		Node<Order*>* p = Head;

		while (p)
		{
			cout << p->getItem();
			cout << " ";
			p = p->getNext();
		}
	}*/
	int getSize() const
	{
		return count;
	}
	void DeleteAll()
	{
		Node<Order*>* P = Head;
		count = 0;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}
	~LinkedList()
	{
		DeleteAll();
	}

	bool isEmpty()
	{
		return Head == nullptr;
	}

	void Insert(Order* Item)
	{
		count++;
		Node <Order*>* newNode = new Node<Order*>(Item);
		newNode->setNext(Head);
		Head = newNode;
	}

	void InsertSort(Order*& item)
	{
		count++;
		Node<Order*>* newNode = new Node<Order*>(item);
		if (!Head || Head->getItem()->getArrTime() > item->getArrTime())
		{
			newNode->setNext(Head);
			Head = newNode;

			return;
		}
		else
		{
			Node<Order*>* prev = Head;
			Node<Order*>* after = Head->getNext();
			while (after)
			{
				if (after->getItem()->getArrTime() > item->getArrTime())
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

	bool InsertEnd(Order* item)
	{
		count++;
		Node<Order*>* ptr = Head;
		Node<Order*>* nNode = new Node<Order*>;
		nNode->setItem(item);
		nNode->setNext(NULL);
		if (!ptr)
		{
			Head = nNode;
			return true;
		}
		while (ptr->getNext())
			ptr = ptr->getNext();
		ptr->setNext(nNode);
		return true;
	}

	bool Remove(Order* item)
	{
		if (!Head) return false;
		Node<Order*>* ptr = Head;
		if (Head && Head->getItem() == item)
		{
			Node<Order*>* NodeToDelete = Head;
			Head = Head->getNext();
			NodeToDelete->setNext(nullptr);
			delete NodeToDelete;
			count--;
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
	bool removeFirst(Order*& item)
	{
		
		Node<Order*>* temp = Head;
		if (!temp)
		{
			item = nullptr;
			return false;
		}
		Head = Head->getNext();
		item = temp->getItem();
		delete temp;
		count--;
		return true;
	}

	Order** toArray(int& count)
	{
		count = 0;

		if (!Head)
			return nullptr;
		//counting the no. of items in the Queue
		Node<Order*>* p = Head;
		while (p)
		{
			count++;
			p = p->getNext();
		}


		Order** Arr = new Order * [count];
		p = Head;
		for (int i = 0; i < count; i++)
		{
			Arr[i] = p->getItem();
			p = p->getNext();
		}
		return Arr;
	}


};


