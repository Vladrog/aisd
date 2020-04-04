#include <iostream>
#include <clocale>
#include <conio.h>
#include "rbTree.h"

int main()
{
	setlocale(LC_ALL, "rus");
	rbTree* newTree = new rbTree();
	int choose = 1, key;
	while (choose != 6)
	{
		system("cls");
		cout << "Выберите опцию" << endl;
		cout << "1) Добавить" << endl;
		cout << "2) Удалить" << endl;
		cout << "3) Вывести дерево" << endl;
		cout << "4) Поиск" << endl;
		cout << "5) Вывести ключи" << endl;
		cout << "6) Выйти" << endl << endl;
		cin >> choose;
		switch (choose)
		{
			case 1:
				cout << "Введите ключ" << endl;
				cin >> key;
				if (newTree->add(key) == 0) cout << "Добавлен корень" << endl;
				else cout << "Добавлен элемент" << endl;
				break;
			case 2:
				cout << "Введите ключ" << endl;
				cin >> key;
				newTree->remove(key);
				break;
			case 3:
				newTree->print();
				break;
			case 4: 
				cout << "Введите ключ" << endl;
				cin >> key;
				if (newTree->contains(key)) cout << "Найден" << endl;
				else cout << "Не найден" << endl;
				break;
			case 5:
				newTree->keysPrint();
				break;
			case 6: 
				cout << "Выходим..." << endl;
				break;
			default:
				cout << "Ошибка, повторите ввод" << endl;
				break;
		}
		_getch();
	}
	delete newTree;
}

