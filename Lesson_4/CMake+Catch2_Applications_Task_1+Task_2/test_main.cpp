#pragma once

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include "struct_ListNode.h"
#include "class_List.h"
#include <Windows.h>
#include <iostream>


TEST_CASE("test list", "[list]")
{
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	List lst;
	SECTION("проверка Empty, возвращает true в данном случае")
	{
		CHECK(lst.Empty() == 1);
	}

	SECTION("проверка добавления через PushBack и правильность количества элементов в списке через Size")
	{
		lst.PushBack(54);
		lst.PushBack(78);
		CHECK(lst.Size() == 2);
	}
	
	SECTION("проверка добавления через PushFront и правильность количества элементов в списке через Size")
	{
		lst.PushFront(51);
		lst.PushFront(79);
		CHECK(lst.Size() == 2);
	}

	SECTION("проверка PopBack на пустом списке")
	{
		lst.Clear();
		INFO("проверка PopBack на пустом списке");
		std::cout << lst.PopBack();
	}

	SECTION("проверка PopFront на пустом списке")
	{
		lst.Clear();
		INFO("проверка PopFront на пустом списке");
		std::cout << lst.PopBack();
	}

	SECTION("проверка Clear")
	{
		lst.Clear();
		CHECK(lst.Size() == 0);
	}

	SECTION("сценарий использования списка сложнее: несколько вызовов функций");
	{
		lst.Clear();
		lst.PushFront(51);
		lst.PushFront(79);
		lst.PushBack(54);
		lst.PushBack(78);
		INFO("сценарий использования списка сложнее: несколько вызовов функций");
		CHECK(lst.Size() == 4);
		std::cout << lst.PopBack();
		CHECK(lst.Size() == 3);
	} 


}


int main(int argc, char* argv[]) {
	return Catch::Session().run(argc, argv);
}

