#pragma once
#include <iostream>
using namespace std;

struct listElement
{
	int key;
	listElement* next;
};

class list
{
private:
	listElement* head, * tail;

public:
	list() // constructor
	{
		head = nullptr;
		tail = nullptr;
	}

	~list() // destructor
	{
		if (head) // if list is not empty
		{
			listElement* buf;
			while (head != tail) // until there is one element
			{
				buf = head;
				head = head->next;
				delete buf;
			}
			delete head;
			head = nullptr;
			tail = nullptr;
		}
	}

	void push_back(int keyInput) // adding an element to the end of the list
	{
		listElement* newElement = new listElement;
		if (head) // if list is not empty
		{
			tail->next = newElement;
			newElement->next = nullptr;
			tail = newElement;
			newElement->key = keyInput;
		}
		else
		{
			head = newElement;
			tail = head;
			newElement->next = 0;
			newElement->key = keyInput;
		}
	}

	void push_front(int keyInput) // adding an element to the beginning of the list
	{
		listElement* newElement = new listElement;
		if (head) // if list is not empty
		{
			newElement->next = head;
			head = newElement;
			newElement->key = keyInput;
		}
		else
		{
			head = newElement;
			tail = head;
			newElement->next = 0;
			newElement->key = keyInput;
		}
	}

	void pop_back() // deleting last element
	{
		if (head) // if list is not empty 
		{
			listElement* cur = head;
			if (head != tail) // if there are more than one elements in the list
			{
				while (cur->next != tail) // while selected element is not penult
				{
					cur = cur->next;
				}
				delete cur->next;
				cur->next = nullptr;
				tail = cur;
			}
			else // if there is only one element in the list
			{
				delete cur;
				head = nullptr;
				tail = nullptr;
			}
		}
		else throw logic_error("List is empty");
	}

	void pop_front() // deleting the first element
	{
		if (head) // if list is not empty
		{
			listElement* cur = head;
			if (head != tail) // if there are more than one elements in the list
			{
				head = head->next;
				delete cur;
			}
			else // if there is only one element in the list
			{
				delete cur;
				head = nullptr;
				tail = nullptr;
			}
		}
		else throw logic_error("List is empty");
	}

	void insert(size_t index, int keyInput) // adding element behind indexed element
	{
		if (head) // if list is not empty
		{
			listElement* newElement = new listElement;
			listElement* cur = head;
			int i = 0;
			if (index == 0) // if indexed element is first element
			{
				newElement->next = head;
				head = newElement;
				newElement->key = keyInput;
			}
			else
			{
				while ((i != index - 1) && (cur != tail)) // while iterator is not behind indexed element and selected element is not last
				{
					cur = cur->next;
					i++;
				}
				if ((cur != tail) && (i == index - 1)) // if selected element is not last and iterator is behind indexed element
				{
					newElement->next = cur->next;
					cur->next = newElement;
					newElement->key = keyInput;
				}
				else throw invalid_argument("Invalid index");
			}
		}
		else throw logic_error("List is empty");
	}

	int at(size_t index)  // searching the element on indexed position
	{
		int keyAt;
		if (head) // if list is not empty
		{
			listElement* cur = head;
			int i = 0;
			while ((cur != tail) && (i != index)) // until element was found or end of the list was riched
			{
				cur = cur->next;
				i++;
			}
			if (i == index) // if element was found 
			{
				keyAt = cur->key;
			}
			else
			{
				throw invalid_argument("Invalid index");
			}
		}
		else throw logic_error("List is empty");
		return keyAt;
	}

	void remove(size_t index) //  deleting indexed element
	{
		if (head) // if list is not empty
		{
			listElement* cur = head;
			listElement* buf;
			int i = 0;
			if ((index == 0) && (head == tail)) // if there is only one element in list
			{
				delete head;
				head = nullptr;
				tail = nullptr;
			}
			else if ((index == 0) && (head != tail)) //  if indexed element is first element
			{
				head = head->next;
				delete cur;

			}
			else if ((index == this->get_size() - 1) && (head != tail)) // if indexed element is last element
			{
				while (cur->next != tail) // while selected element is not penult
				{
					cur = cur->next;
				}
				cur->next = nullptr;
				delete tail;
				tail = cur;
			}
			else
			{
				while ((i != index - 1) && (cur != tail)) // while iterator is not behind indexed element and selected element is not last
				{
					cur = cur->next;
					i++;
				}
				if ((cur != tail) && (i == index - 1)) // if selected element is not last and iterator is behind indexed element
				{
					buf = cur->next;
					cur->next = cur->next->next;
					delete buf;
				}
				else throw invalid_argument("Invalid index");
			}
		}
		else throw logic_error("List is empty");
	}

	size_t get_size() // counting the size of list
	{
		size_t size;
		listElement* cur = head;
		if (head) //  if list is not empty
		{
			size = 1;
			while (cur != tail) // until all elements counted
			{
				size++;
				cur = cur->next;
			}
		}
		else size = 0;
		return size;
	}

	void print_to_console() // printing all keys of elements in console
	{
		if (head) // if list is not empty
		{
			listElement* cur = head;
			while (cur != tail) //  until all elements printed
			{
				cout << cur->key << " | ";
				cur = cur->next;
			}
			cout << tail->key << endl;
		}
		else throw logic_error("List is empty");
	}

	void clear() // deleting all elements of the list
	{
		if (head) // if list is not empty
		{
			listElement* buf;
			while (head != tail) // until there is one element
			{
				buf = head;
				head = buf->next;
				buf->next = nullptr;
				delete buf;
			}
			delete head;
			head = nullptr;
			tail = nullptr;
		}
	}

	void set(size_t index, int keyInput) // changing the key in indexed element
	{
		if (head) // if list is not empty
		{
			listElement* cur = head;
			int i = 0;
			while ((cur != tail) && (i != index)) // until element was found or end of the list was riched
			{
				cur = cur->next;
				i++;
			}
			if (i == index) // if element was found
			{
				cur->key = keyInput;
			}
			else
			{
				throw invalid_argument("Invalid index");
			}
		}
		else throw logic_error("List is empty");
	}

	bool is_Empty() // checking if list is empty
	{
		if (head) return false;
		else return true;
	}

	void list_adding(list*& additive) // adding another list in the end of this
	{
		listElement* newElement;
		listElement* cur;
		if (additive->head) // if additive list is empty
		{
			cur = additive->head;
			if (head) // if main list is empty 
			{
				while (cur != additive->tail) // while current element is not last in additive list
				{
					newElement = new listElement; // copying element
					newElement->next = nullptr;
					tail->next = newElement;
					tail = newElement;
					newElement->key = cur->key;
					cur = cur->next;
				}
				newElement = new listElement; // copying last element
				newElement->next = nullptr;
				tail->next = newElement;
				tail = newElement;
				newElement->key = cur->key;
			}
			else
			{
				newElement = new listElement; //creating and copying first element
				head = newElement;
				head->next = nullptr;
				tail = head;
				head->key = cur->key;
				if (cur != additive->tail)
				{
					cur = cur->next;
					while (cur != additive->tail)
					{
						newElement = new listElement;
						newElement->next = nullptr;
						tail->next = newElement;
						tail = newElement;
						newElement->key = cur->key;
						cur = cur->next;
					}
					newElement = new listElement;
					newElement->next = nullptr;
					tail->next = newElement;
					tail = newElement;
					newElement->key = cur->key;
				}
			}
		}
	}
};