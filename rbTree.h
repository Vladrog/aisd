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

	~rbTree()
	{
		clear(root);
		root = nullptr;
	}

	void clear(node* element) // recursive realisation of clearing the tree
	{
		if (element->link[0]) clear(element->link[0]);
		if (element->link[1]) clear(element->link[1]);
		delete element;
		element = nullptr;
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
		int heightLeft = 0, heightRight = 0;
		if (!element) return(0);
		if (element->link[0]) heightLeft = heightRec(element->link[0]);
		if (element->link[1]) heightRight = heightRec(element->link[1]);
		if (heightLeft > heightRight) return heightLeft + 1;
		else return heightRight + 1;
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

	int add(int inKey)
	{
		if (!root) // if its first element - just add it
		{
			this->root = makeNode(inKey);
			return 0;
		}
		else
		{
			node head = { 0 }; // temp root
			node* grand, * parentOfGrand;     // grandfather and his father
			node* parent, * element;     // father and iterator 
			int direction = 0, lastDirection;
			
			parentOfGrand = &head;
			grand = parent = nullptr;
			element = parentOfGrand->link[1] = this->root;

			for (; ; ) // searching position for adding
			{
				if (element == nullptr)  // position found - adding element
				{
					parent->link[direction] = element = makeNode(inKey);
					if (element == nullptr)
						return 0;
				}
				else if (is_red(element->link[0]) && is_red(element->link[1])) // if children - red
				{ 
					element->red = 1; // inversion of this node and children colors
					element->link[0]->red = 0;
					element->link[1]->red = 0;
				}
		
				if (parent && grand)
				{
					if (is_red(element) && is_red(parent)) // this node and his parent are red
					{
						int dir2 = parentOfGrand->link[1] == grand; // choosing the direction of rotation

						if (element == parent->link[lastDirection]) // if we need single rotation 
							parentOfGrand->link[dir2] = singleRotation(grand, !lastDirection);
						else // double rotation
							parentOfGrand->link[dir2] = doubleRotation(grand, !lastDirection);
					}
				}
				if (element->key == inKey) // this key is already found
				{
					break;
				}

				lastDirection = direction; // saving the last direction of searching
				direction = element->key < inKey; // changing the direction 

				if (grand != nullptr) // level down
					parentOfGrand = grand;
				grand = parent;
				parent = element;
				element = element->link[direction];
			}

			this->root = head.link[1]; // refreshing the root of tree
		}
		
		this->root->red = 0; // painting the root in black
		return 1;
	}

	void remove(int inKey)
	{
		if (root)
		{
			node head = { 0 }; // temporary pointer to root
			node* element, * parent, * grand; // element, his parent and grandparent
			node* brother; // brother
			node* deleted = nullptr;  // element, which we will delete
			int direction = 1; // start direction

			element = &head; // initialisation
			grand = parent = nullptr;
			element->link[1] = this->root;

			while (element->link[direction] != nullptr) // searching and deleting the element
			{
				int lastDirection = direction; // previous direction

				grand = parent, parent = element; // changing the level
				element = element->link[direction];
				direction = element->key < inKey;

				if (element->key == inKey) // if element has been found
					deleted = element;

				if (!is_red(element) && !is_red(element->link[direction])) // if this element and his child are black
				{
					if (is_red(element->link[!direction])) // if brother of child is red
						parent = parent->link[lastDirection] = singleRotation(element, direction);
					else if (!is_red(element->link[!direction])) // if its black 
					{
						brother = parent->link[!lastDirection]; // brother of element
						if (brother != nullptr)
						{
							if (!is_red(brother->link[!lastDirection]) && !is_red(brother->link[lastDirection])) // if children of brother are black
							{
								parent->red = 0; // changing the colors
								brother->red = 1;
								element->red = 1;
							}
							else
							{
								int direction2 = grand->link[1] == parent; // directiong from grandparent to parent

								if (is_red(brother->link[lastDirection])) // if child of brother is red on the same direction
									grand->link[direction2] = doubleRotation(parent, lastDirection);
								else if (is_red(brother->link[!lastDirection]))
									grand->link[direction2] = singleRotation(parent, lastDirection);

								element->red = grand->link[direction2]->red = 1; // changing the colors
								grand->link[direction2]->link[0]->red = 0;
								grand->link[direction2]->link[1]->red = 0;
							}
						}
					}
				}
			}

			if (deleted != nullptr) // deleting the element
			{
				parent->link[parent->link[1] == element] = element->link[element->link[0] == nullptr];
				element->link[0] = element->link[1] = nullptr;
				delete element;
			}
			else throw logic_error("Element was not found");

			this->root = head.link[1]; // changing the pointers
			if (this->root != nullptr)
				this->root->red = 0;
		}
		else throw logic_error("Tree is empty");
	}

	bool contains(int inKey) // searching the element in tree
	{
		return containsRec(inKey, root);
	}

	bool containsRec(int inKey, node* element) // recursive realisation of contains function
	{
		if (element)
		{
			if (element->key == inKey) return true; // if element was found
			else
			{
				if (inKey < element->key) return containsRec(inKey, element->link[0]);
				else return containsRec(inKey, element->link[1]);
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