#include "struct_ListNode.h"
#include "class_List.h"
#include <iostream>

ListNode::ListNode(int value, ListNode* prev, ListNode* next)
    {
    this->value = value;
    this->prev = prev;
    this->next = next;
        if (prev != nullptr) prev->next = this;
        if (next != nullptr) next->prev = this;
    }