#include <iostream>
#include "mylist.h."
#include "RedBlackTree.h"
int main()
{
	Map<int, int> map;
	map.insert(2, 1);
	map.insert(4, 2);
	map.insert(3, 3);
	map.insert(1, 4);
	map.insert(7, 4);

	map.remove(4);
	auto keyList = map.get_colors();
	auto keyList2 = map.get_keys();
	cout << *keyList2 << endl;
	cout << *keyList << endl;
	return 0;
}

