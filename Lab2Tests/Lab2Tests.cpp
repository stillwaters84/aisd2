#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab2Map/RedBlackTree.h"

//Лаба2Дерево - 2 папки
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab2Tests
{
	TEST_CLASS(insert_tests)
	{
	public:
		
		TEST_METHOD(insert_int)
		{
			Map<int, int> map;
			map.insert(2, 1);
			map.insert(4, 2);
			map.insert(3, 3);
			map.insert(1, 4);
			map.insert(7, 4);
			auto valueList = map.get_keys();
			auto first = valueList->first;
			int check_key[5] = { 1,2,3,4,7 }; //IN-ORDER TRAVEL
			for (int i = 0; i < valueList->size; i++) {
				Assert::AreEqual(first->number, check_key[i]);
				first = first->next;
			}
		}

		TEST_METHOD(insert_int_color)
		{
			Map<int, int> map;
			map.insert(2, 1);
			map.insert(4, 2);
			map.insert(3, 3);
			map.insert(1, 4);
			map.insert(7, 4);
			bool check_color[5] = { 1,0,0,0,1 };
			bool color[5];
			auto color_list = map.get_colors();
			auto first = color_list->first;
			for (int i = 0; i < 5; i++) {
				color[i] = first->number;
				Assert::AreEqual(check_color[i], color[i]);
				first = first->next;
			}
		}
		TEST_METHOD(insert_int_char)
		{
			Map<int, char> map;
			map.insert(2, 'a');
			map.insert(4, 'b');
			map.insert(3, 'c');
			map.insert(1, 'g');
			map.insert(7, 'e');
			auto keyList = map.get_values();
			auto first = keyList->first;
			char check_value[5] = { 'g','a','c','b','e' }; //IN-ORDER TRAVEL
			for (int i = 0; i < keyList->size; i++) {
				Assert::AreEqual(first->number, check_value[i]);
				first = first->next;
			}
		}

		TEST_METHOD(insert_char_string)
		{
			Map<char, string> map;
			map.insert('f', "oof");
			map.insert('b', "wow");
			map.insert('l', "dam");
			map.insert('a', "heh");
			map.insert('g', "lol");
			auto keyList = map.get_values();
			auto first = keyList->first;
			string check_value[5] = { "heh","wow","oof","lol","dam" }; //IN-ORDER TRAVEL
			for (int i = 0; i < keyList->size; i++) {
				Assert::AreEqual(first->number, check_value[i]);
				first = first->next;
			}
		}


	};

	TEST_CLASS(remove_tests)
	{
	public:

		TEST_METHOD(remove_int_char)
		{
			Map<int, char> map;
			map.insert(2, 'b');
			map.insert(4, 'd');
			map.insert(3, 'c');
			map.insert(1, 'a');
			map.insert(7, 'e');

			map.remove(3);
			auto valueList = map.get_values();
			auto first = valueList->first;
			char check_key[4] = { 'a','b','d','e' }; //IN-ORDER TRAVEL
			for (int i = 0; i < valueList->size; i++) {
				Assert::AreEqual(first->number, check_key[i]);
				first = first->next;
			}

			try {
				map.remove(99);
			}
			catch (const std::out_of_range & error) {
				Assert::AreEqual(error.what(), "There's no this element");
			}
		}

		TEST_METHOD(remove_char_color)
		{
			Map<int, char> map;
			map.insert(2, 'b');
			map.insert(4, 'd');
			map.insert(3, 'c');
			map.insert(1, 'a');
			map.insert(7, 'e');

			map.remove(4);
			bool check_color[4] = { 1,0,0,1 };
			bool color[4];
			auto color_list = map.get_colors();
			auto first = color_list->first;
			for (int i = 0; i < 4; i++) {
				color[i] = first->number;
				Assert::AreEqual(check_color[i], color[i]);
				first = first->next;
			}

		}
		TEST_METHOD(remove_char_string)
		{
			Map<char, string> map;
			map.insert('f', "oof");
			map.insert('b', "wow");
			map.insert('l', "dam");
			map.insert('a', "heh");
			map.insert('g', "heh");

			map.remove('l');
			auto keyList = map.get_values();
			auto first = keyList->first;
			string check_value[4] = { "heh","wow","oof","heh" }; //IN-ORDER TRAVEL
			for (int i = 0; i < keyList->size; i++) {
				Assert::AreEqual(first->number, check_value[i]);
				first = first->next;
			}

			try {
				map.remove('z');
			}
			catch (const std::out_of_range & error) {
				Assert::AreEqual(error.what(), "There's no this element");
			}
		}


	};

	TEST_CLASS(find_tests)
	{
	public:

		TEST_METHOD(find_int)
		{
			Map<int, int> map;
			map.insert(2, 1);
			map.insert(4, 2);
			map.insert(3, 3);
			map.insert(1, 4);
			map.insert(7, 5);

			auto check1 = map.FindNode(7);
			Assert::AreEqual(5, check1->value);

			try {
				map.FindNode(88);
			}
			catch (const std::out_of_range & error) {
				Assert::AreEqual(error.what(), "There's no this element");
			}
		}

		TEST_METHOD(find_char)
		{
			Map<char, string> map;
			map.insert('a', "oof");
			map.insert('b', "heh");
			map.insert('c', "wow");
			map.insert('d', "lol");
			map.insert('e', "dam");
			string sample1 = "lol";
			auto check1 = map.FindNode('d');
			Assert::AreEqual(sample1, check1->value);

			try {
				map.FindNode('z');
			}
			catch (const std::out_of_range & error) {
				Assert::AreEqual(error.what(), "There's no this element");
			}
		}
	};

	TEST_CLASS(other_tests)
	{
	public:

		TEST_METHOD(clear_int)
		{
			Map<int, int> map;
			map.insert(2, 1);
			map.insert(4, 2);
			map.insert(3, 3);
			map.insert(1, 4);
			map.insert(7, 5);

			map.Clear();
			Assert::IsNull(map.root);

			try {
				map.FindNode(4);
			}
			catch (const std::out_of_range & error) {
				Assert::AreEqual(error.what(), "There's no this element");
			}
		}

		TEST_METHOD(get_keys_int)
		{
			Map<int, int> map;
			map.insert(2, 1);
			map.insert(4, 2);
			map.insert(3, 3);
			map.insert(1, 4);
			map.insert(7, 5);

			auto keyList = map.get_keys();
			auto first = keyList->first;
			int check_key[5] = { 1,2,3,4,7 }; //IN-ORDER TRAVEL
			for (int i = 0; i < keyList->size; i++) {
				Assert::AreEqual(first->number, check_key[i]);
				first = first->next;
			}

			Map<int, int> emptymap;
			try {
				emptymap.get_keys();
			}
			catch (const std::out_of_range & error) {
				Assert::AreEqual(error.what(), "List is empty");
			}
		}

		TEST_METHOD(get_values_int)
		{
			Map<int, int> map;
			map.insert(2, 1);
			map.insert(4, 2);
			map.insert(3, 3);
			map.insert(1, 4);
			map.insert(7, 5);

			auto valueList = map.get_values();
			auto first = valueList->first;
			int check_key[5] = { 4,1,3,2,5 }; //IN-ORDER TRAVEL
			for (int i = 0; i < valueList->size; i++) {
				Assert::AreEqual(first->number, check_key[i]);
				first = first->next;
			}

			Map<int, int> emptymap;
			try {
				emptymap.get_values();
			}
			catch (const std::out_of_range & error) {
				Assert::AreEqual(error.what(), "List is empty");
			}
		}
	};
}
