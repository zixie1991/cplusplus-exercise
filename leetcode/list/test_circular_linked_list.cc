#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

struct ListNode {
  int val;
  ListNode* next;
};

void CircularListInsert(ListNode** list, int val) {
  ListNode* node = (ListNode*)malloc(sizeof(ListNode));
  node->val = val;
  node->next = *list;

  if (NULL == (*list)) {
    *list = node;
    (*list)->next = *list;
    return ;
  }

  ListNode* ptr = *list;
  while (ptr->next != (*list)) {
    ptr = ptr->next;
  }

  ptr->next = node;
  node->next = *list;
}

void CircularListPrint(ListNode* list) {
  ListNode* ptr = list;
  if (NULL == list) {
    cout << endl;
  }

  while (ptr->next != list) {
    cout << ptr->val << " ";
    ptr = ptr->next;
  }
  cout << ptr->val << endl;
}

int CircularListLength(ListNode* list) {
  if (NULL == list) {
    return 0;
  }

  ListNode* ptr = list;
  int length = 0;
  while (ptr->next != list) {
    length++;
    ptr = ptr->next;
  }
  length++;

  return length;
}

void TestCircularListInsertAndPrint() {
  ListNode* list = NULL;
  CircularListInsert(&list, 1);
  CircularListInsert(&list, 3);
  CircularListInsert(&list, 2);
  CircularListInsert(&list, 4);

  cout << CircularListLength(list) << endl;
  CircularListPrint(list);
}

void TestJosephus() {
  // 约瑟夫环
  ListNode* list = NULL;
  int n = 10;
  int m = 4;
  int k = 1;
  for (int i = 1; i <= n; i++) {
    CircularListInsert(&list, i);
  }

  ListNode* ptr = list;
  ListNode* ptr2 = list;
  while (--n) {
    for (int s = m - 1; s--; ptr2 = ptr, ptr = ptr->next);
    ptr2->next = ptr->next;
    free(ptr); 
    ptr = ptr2->next;
  }

  cout << ptr->val << endl;
}

int main() {
  cout << "TestCircularListInsertAndPrint:" << endl;
  TestCircularListInsertAndPrint();
  cout << "TestJosephus:" << endl;
  TestJosephus();
  return 0;
}
