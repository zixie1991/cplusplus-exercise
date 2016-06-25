#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <list>
#include <forward_list>

using namespace std;

struct ListNode {
  int val;
  ListNode* next;
};

void ListInsert(ListNode** list, int val) {
  ListNode* node = (ListNode*)malloc(sizeof(ListNode));
  node->val = val;
  node->next = NULL;
  if (*list == NULL) {
    *list = node; 
    return ;
  }

  ListNode* ptr = *list;
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }

  ptr->next = node;
}

int ListLength(ListNode* list) {
  ListNode* ptr = list;
  int length = 0;

  while (ptr != NULL) {
    ptr = ptr->next;
    length++;
  }

  return length;
}

void ListRemoveFirstValue(ListNode** list, int val) {
  ListNode* ptr = *list;
  ListNode* ptr2 = *list;
  while (ptr != NULL && ptr->val != val) {
    ptr2 = ptr;
    ptr = ptr->next;
  }

  if (ptr == NULL) {
    return ;
  }

  if (ptr == *list) {
    *list = ptr->next;
  } else {
    ptr2->next = ptr->next; 
  }

  free(ptr);
}

void ListRemoveFirstNode(ListNode** list) {
  if (NULL == (*list)) {
    return ;
  }

  ListNode* ptr = *list;
  *list = (*list)->next;
  free(ptr);
}

ListNode* ListMiddleNode(ListNode* list) {
  if (list == NULL || list->next == NULL) {
    return list;
  }

  ListNode* ptr1 = list;
  ListNode* ptr2 = list;
  while (ptr2->next != NULL && ptr2->next->next != NULL) {
    ptr1 = ptr1->next;
    ptr2 = ptr2->next->next;
  }

  return ptr1;
}

void ListSort(ListNode** list) {
  // bubble sort
  int length = ListLength(*list);

  for (int i = 1; i < length; i++) {
    ListNode* ptr = *list;
    for (int j = 0; j < length - i; j++) {
      if (ptr->val > ptr->next->val) {
        int tmp = ptr->val;
        ptr->val = ptr->next->val;
        ptr->next->val = tmp;
      }
      
      ptr = ptr->next;
    }
  }
}

void ListReverse(ListNode** list) {
  if (NULL == (*list)) {
    return ;
  }

  ListNode* ptr = *list;
  *list = NULL;

  while (ptr != NULL) {
    ListNode* tmp = ptr;
    ptr = ptr->next;

    tmp->next = *list;
    *list = tmp;
  }
}

void ListPrint(ListNode* list) {
  ListNode* ptr = list;

  while (ptr != NULL) {
    cout << ptr->val << " ";
    ptr = ptr->next;
  }
  cout << endl;
}

void ListClear(ListNode** list) {
  ListNode* ptr = *list;
  while (ptr != NULL) {
    ListNode* tmp = ptr;
    ptr = ptr->next;

    free(tmp);
  }

  *list = NULL;
}

bool ListPalindrome(ListNode* list) {
  if (NULL == list || NULL == list->next) {
    return true;
  }

  ListNode* slow = list;
  ListNode* fast = list;

  // middle node
  while (fast->next && fast->next->next) {
    slow = slow->next;
    fast = fast->next->next;
  }

  // reverse half list
  ListNode* half = NULL;
  ListNode* ptr = slow->next;
  while (ptr) {
    ListNode* tmp = ptr;
    ptr = ptr->next;

    tmp->next = half;
    half = tmp;
  }

  // palindrome
  while (half && half->val == list->val) {
    half = half->next;
    list = list->next;
  }

  return half == NULL;
}

void TestListInsertAndPrint() {
  ListNode* list = NULL;
  ListInsert(&list, 1);
  ListInsert(&list, 3);
  ListInsert(&list, 2);
  ListInsert(&list, 4);

  cout << ListLength(list) << endl;
  ListPrint(list);

  ListClear(&list);
}

void TestListRemoveFirstValue() {
  ListNode* list = NULL;
  ListInsert(&list, 1);
  ListInsert(&list, 3);
  ListInsert(&list, 2);
  ListInsert(&list, 4);

  cout << ListLength(list) << endl;
  ListPrint(list);

  ListRemoveFirstValue(&list, 4);

  cout << ListLength(list) << endl;
  ListPrint(list);

  ListClear(&list);
}

void TestListSort() {
  ListNode* list = NULL;
  ListInsert(&list, 1);
  ListInsert(&list, 3);
  ListInsert(&list, 2);
  ListInsert(&list, 4);

  cout << ListLength(list) << endl;
  ListPrint(list);

  ListSort(&list);

  cout << ListLength(list) << endl;
  ListPrint(list);

  ListClear(&list);
}

void TestListReverse() {
  ListNode* list = NULL;
  ListInsert(&list, 1);
  ListInsert(&list, 3);
  ListInsert(&list, 2);
  ListInsert(&list, 4);

  cout << ListLength(list) << endl;
  ListPrint(list);

  ListReverse(&list);

  cout << ListLength(list) << endl;
  ListPrint(list);

  ListClear(&list);
}

void TestListRemoveFistNode() {
  ListNode* list = NULL;
  ListInsert(&list, 1);
  ListInsert(&list, 3);
  ListInsert(&list, 2);
  ListInsert(&list, 4);

  cout << ListLength(list) << endl;
  ListPrint(list);

  ListRemoveFirstNode(&list);

  cout << ListLength(list) << endl;
  ListPrint(list);

  ListClear(&list);
}

void TestListPalindrome() {
  ListNode* list = NULL;
  //ListInsert(&list, 1);
  //ListInsert(&list, 1);
  //ListInsert(&list, 3);
  //ListInsert(&list, 1);

  cout << ListPalindrome(list) << endl;
}

int main() {
  list<int> li_a;
  // c++11
  forward_list<int> li_b;
  cout << "TestListInsertAndPrint:" << endl;
  TestListInsertAndPrint();
  cout << "TestListRemoveFirstValue:" << endl;
  TestListRemoveFirstValue();
  cout << "TestListSort:" << endl;
  TestListSort();
  cout << "TestListReverse:" << endl;
  TestListReverse();
  cout << "TestListRemoveFirstNode:" << endl;
  TestListRemoveFistNode();
  cout << "TestListPalindrome:" << endl;
  TestListPalindrome();
  return 0;
}
