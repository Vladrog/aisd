#pragma once
#include <iostream>
#include "List.h"
using namespace std;

struct node
{
	bool red;
	int key;
	node* link[2];
};

class rbTree
{
public: 
	node* root;

	rbTree()
	{
		root = nullptr;
	}

	node* singleRotation(node* root, bool dir)
	{
		node* save;
		save = root->link[!dir];

		root->link[!dir] = save->link[dir];
		save->link[dir] = root;

		root->red = 1;
		save->red = 0;

		return save;
	}

	node* doubleRotation(node* root, int dir)
	{
		root->link[!dir] = singleRotation(root->link[!dir], !dir);
		return singleRotation(root, dir);
	}

	int is_red(node* node)
	{
		return (node != nullptr && node->red == 1);
	}

	node* makeNode(int key) // creating the node
	{
		node* newNode = new node;

		newNode->key = key;
		newNode->red = 1;
		newNode->link[0] = nullptr;
		newNode->link[1] = nullptr;

		return newNode;
	}

	int height() // counting the height of tree
	{
		return heightRec(root);
	}

	int heightRec(node* element) // recursive realisation of height function
	{
		int h1 = 0, h2 = 0;
		if (!element) return(0);
		if (element->link[0]) h1 = heightRec(element->link[0]);
		if (element->link[1]) h2 = heightRec(element->link[1]);
		if (h1 > h2) return h1 + 1;
		else return h2 + 1;
	}

	void print() // printing the tree in console
	{
		printRec(root, height(), 0);
	}

	void printRec(node* element, int level, bool direction) // recursive realisation of print function
	{
		if (element)
		{
			printRec(element->link[0], level - 1, 0); // printing the left tree
			for (int i = 0; i < level; i++) cout << "   "; // printing gaps
			if (is_red(element)) cout << element->key << "r";
			else cout << element->key << "b";
			if (direction) cout << "/" << endl; // printing element
			else cout << "\\" << endl;
			printRec(element->link[1], level - 1, 1); // printing the right tree
		}
	}

	int add(int key)
	{
		if (!root) // if its first element - just add it
		{
			this->root = makeNode(key);
			return 0;
		}
		else
		{
			node head = { 0 }; // temp root
			node* g, * t;     // grandfather and his father
			node* p, * q;     // father and iterator 
			int dir = 0, last;
			
			t = &head;
			g = p = nullptr;
			q = t->link[1] = this->root;

			for (; ; ) // searching position for adding
			{
				if (q == nullptr)  // position found - adding element
				{
					p->link[dir] = q = makeNode(key);
					if (q == nullptr)
						return 0;
				}
				else if (is_red(q->link[0]) && is_red(q->link[1])) // if children - red
				{ 
					q->red = 1; // inversion of this node and children colors
					q->link[0]->red = 0;
					q->link[1]->red = 0;
				}
		
				if (p && g)
				{
					if (is_red(q) && is_red(p)) // this node and his parent are red
					{
						int dir2 = t->link[1] == g; // choosing the direction of rotation

						if (q == p->link[last]) // if we need single rotation 
							t->link[dir2] = singleRotation(g, !last);
						else // double rotation
							t->link[dir2] = doubleRotation(g, !last);
					}
				}
				if (q->key == key) // this key is already found
				{
					break;
				}

				last = dir; // saving the last direction of searching
				dir = q->key < key; // changing the direction 

				if (g != nullptr) // level down
					t = g;
				g = p;
				p = q;
				q = q->link[dir];
			}

			this->root = head.link[1]; // refreshing the root of tree
		}
		
		this->root->red = 0; // painting the root in black
		return 1;
	}

	void remove(int key)
	{
		if (root)
		{
			node head = { 0 }; // temporary pointer to root
			node* q, * p, * g; // element, his parent and grandparent
			node* s; // brother
			node* f = nullptr;  // element, which we will delete
			int dir = 1; // start direction

			q = &head; // initialisation
			g = p = nullptr;
			q->link[1] = this->root;

			while (q->link[dir] != nullptr) // searching and deleting the element
			{
				int last = dir; // previous direction

				g = p, p = q; // changing the level
				q = q->link[dir];
				dir = q->key < key;

				if (q->key == key) // if element has been found
					f = q;

				if (!is_red(q) && !is_red(q->link[dir])) // if this element and his child are black
				{
					if (is_red(q->link[!dir])) // if brother of child is red
						p = p->link[last] = singleRotation(q, dir);
					else if (!is_red(q->link[!dir])) // if its black 
					{
						s = p->link[!last]; // brother of element
						if (s != nullptr)
						{
							if (!is_red(s->link[!last]) && !is_red(s->link[last])) // if children of brother are black
							{
								p->red = 0; // changing the colors
								s->red = 1;
								q->red = 1;
							}
							else
							{
								int dir2 = g->link[1] == p; // directiong from grandparent to parent

								if (is_red(s->link[last])) // if child of brother is red on the same direction
									g->link[dir2] = doubleRotation(p, last);
								else if (is_red(s->link[!last]))
									g->link[dir2] = singleRotation(p, last);

								q->red = g->link[dir2]->red = 1; // changing the colors
								g->link[dir2]->link[0]->red = 0;
								g->link[dir2]->link[1]->red = 0;
							}
						}
					}
				}
			}

			if (f != nullptr) // deleting the element
			{
				p->link[p->link[1] == q] = q->link[q->link[0] == nullptr];
				q->link[0] = q->link[1] = nullptr;
				delete q;
			}
			else throw logic_error("Element was not found");

			this->root = head.link[1]; // changing the pointers
			if (this->root != nullptr)
				this->root->red = 0;
		}
		else throw logic_error("Tree is empty");
	}

	bool contains(int key) // searching the element in tree
	{
		return containsRec(key, root);
	}

	bool containsRec(int key, node* element) // recursive realisation of contains function
	{
		if (element)
		{
			if (element->key == key) return true; // if element was found
			else
			{
				if (key < element->key) return containsRec(key, element->link[0]);
				else return containsRec(key, element->link[1]);
			}
		}
		else return false;
	}

	void keysPrint() // printing the keys of tree
	{
		if (root) // if tree is not empty
		{
			list* keys = new list;
			listFilling(root, keys);
			keys->print_to_console();
			delete keys;
		}
		else throw logic_error("Tree is empty");
	}

	void listFilling(node* element, list*& filledList) // filling the list by tree
	{
		if (element->link[0]) listFilling(element->link[0], filledList); // adding elements of left tree
		filledList->push_back(element->key); // adding element
		if (element->link[1]) listFilling(element->link[1], filledList); // adding element of right tree
	}

};