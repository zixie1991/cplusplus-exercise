#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

struct DoubleListNode {
  int val;
  DoubleListNode* prev;
  DoubleListNode* next;
};

void DoubleListInsert(DoubleListNode** list, int val) {
  DoubleListNode* node = (DoubleListNode*)malloc(sizeof(DoubleListNode));
  node->val = val;
  node->prev = NULL;
  node->next = NULL;

  if (NULL == (*list)) {
    *list = node;
    return ;
  }

  DoubleListNode* ptr = *list;
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }

  ptr->next = node;
  node->prev = ptr;
}

int DoubleListLength(DoubleListNode* list) {
  int length = 0;
  while (list != NULL) {
    list = list->next;
    length++;
  }

  return length;
}

void DoubleListPrint(DoubleListNode* list) {
  DoubleListNode* ptr = list;

  while (ptr != NULL) {
    cout << ptr->val << " ";
    ptr = ptr->next;
  }
  cout << endl;
}

void DoubleListClear(DoubleListNode** list) {
  DoubleListNode* ptr = *list;
  while (ptr != NULL) {
    DoubleListNode* tmp = ptr;
    ptr = ptr->next;

    free(tmp);
  }

  *list = NULL;
}

void DoubleListRemoveFirstValue(DoubleListNode** list, int val) {
  DoubleListNode* ptr = *list;

  while (ptr != NULL && ptr->val != val) {
    ptr = ptr->next;
  }

  if (ptr == NULL) {
    return ;
  }

  if (ptr == (*list)) {
    *list = ptr->next; 
    (*list)->prev = NULL;
  } else if (ptr->next == NULL) {
    ptr->prev->next = NULL;
  } else {
    ptr->next->prev = ptr->prev;
    ptr->prev->next = ptr->next;
  }

  free(ptr);
}

void TestDoubleListInsertAndPrint() {
  DoubleListNode* list = NULL;
  DoubleListInsert(&list, 1);
  DoubleListInsert(&list, 3);
  DoubleListInsert(&list, 2);
  DoubleListInsert(&list, 4);

  cout << DoubleListLength(list) << endl;
  DoubleListPrint(list);

  DoubleListClear(&list);
}

void TestDoubleListRemoveFirstValue() {
  DoubleListNode* list = NULL;
  DoubleListInsert(&list, 1);
  DoubleListInsert(&list, 3);
  DoubleListInsert(&list, 2);
  DoubleListInsert(&list, 4);

  cout << DoubleListLength(list) << endl;
  DoubleListPrint(list);

  DoubleListRemoveFirstValue(&list, 4);

  cout << DoubleListLength(list) << endl;
  DoubleListPrint(list);

  DoubleListClear(&list);
}

int main() {
  cout << "TestDoubleListInsertAndPrint:" << endl;
  TestDoubleListInsertAndPrint();
  cout << "TestDoubleListRemoveFirstValue:" << endl;
  TestDoubleListRemoveFirstValue();
  return 0;
}
