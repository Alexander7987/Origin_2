#pragma once

struct ListNode
{
public:
    ListNode(int value, ListNode* prev = nullptr, ListNode* next = nullptr);

public:
    int value;
    ListNode* prev;
    ListNode* next;
};