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
	SECTION("�������� Empty, ���������� true � ������ ������")
	{
		CHECK(lst.Empty() == 1);
	}

	SECTION("�������� ���������� ����� PushBack � ������������ ���������� ��������� � ������ ����� Size")
	{
		lst.PushBack(54);
		lst.PushBack(78);
		CHECK(lst.Size() == 2);
	}
	
	SECTION("�������� ���������� ����� PushFront � ������������ ���������� ��������� � ������ ����� Size")
	{
		lst.PushFront(51);
		lst.PushFront(79);
		CHECK(lst.Size() == 2);
	}

	SECTION("�������� PopBack �� ������ ������")
	{
		lst.Clear();
		INFO("�������� PopBack �� ������ ������");
		std::cout << lst.PopBack();
	}

	SECTION("�������� PopFront �� ������ ������")
	{
		lst.Clear();
		INFO("�������� PopFront �� ������ ������");
		std::cout << lst.PopBack();
	}

	SECTION("�������� Clear")
	{
		lst.Clear();
		CHECK(lst.Size() == 0);
	}

	SECTION("�������� ������������� ������ �������: ��������� ������� �������");
	{
		lst.Clear();
		lst.PushFront(51);
		lst.PushFront(79);
		lst.PushBack(54);
		lst.PushBack(78);
		INFO("�������� ������������� ������ �������: ��������� ������� �������");
		CHECK(lst.Size() == 4);
		std::cout << lst.PopBack();
		CHECK(lst.Size() == 3);
	} 


}


int main(int argc, char* argv[]) {
	return Catch::Session().run(argc, argv);
}

