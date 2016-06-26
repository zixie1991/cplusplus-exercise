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

// 尾部插入值
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

// 列表长度
int ListLength(ListNode* list) {
  ListNode* ptr = list;
  int length = 0;

  while (ptr != NULL) {
    ptr = ptr->next;
    length++;
  }

  return length;
}

// 删除第一个等于val的节点
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

// 删除第一个节点
void ListRemoveFirstNode(ListNode** list) {
  if (NULL == (*list)) {
    return ;
  }

  ListNode* ptr = *list;
  *list = (*list)->next;
  free(ptr);
}

// 中间节点
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

// 排序
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

// 逆序
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

// 打印
void ListPrint(ListNode* list) {
  ListNode* ptr = list;

  while (ptr != NULL) {
    cout << ptr->val << " ";
    ptr = ptr->next;
  }
  cout << endl;
}

// 清空
void ListClear(ListNode** list) {
  ListNode* ptr = *list;
  while (ptr != NULL) {
    ListNode* tmp = ptr;
    ptr = ptr->next;

    free(tmp);
  }

  *list = NULL;
}

// 回文串
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

// 删除倒数第n个节点
ListNode* ListRemoveNthNodeFromEnd(ListNode** list, int n) {
  ListNode* slow = *list;
  ListNode* slow2 = slow;
  ListNode* fast = *list;

  // nth node
  for (int i = 1; fast && i < n; i++) {
    fast = fast->next;
  }

  // find nth node from end
  while (fast && fast->next) {
    slow2 = slow;
    slow = slow->next;
    fast = fast->next;
  }

  if (slow == (*list)) {
    *list = slow->next;
  } else {
    slow2->next = slow->next;
  }

  free(slow);

  return *list;
}

// 检查是否有环
bool ListHasCycle(ListNode* list) {
  if (NULL == list || NULL == list->next) {
    return false;
  }

  ListNode* slow = list;
  ListNode* fast = list;
  while (fast->next && fast->next->next) {
    slow = slow->next;
    fast = fast->next->next;

    if (slow == fast) {
      return true;
    }
  }

  return false;
}

// 找到进入环的第一个节点
ListNode* ListCycleBegin(ListNode* list) {
  if (NULL == list || NULL == list->next) {
    return NULL;
  }

  ListNode* slow = list;
  ListNode* fast = list;
  while (fast->next && fast->next->next) {
    slow = slow->next;
    fast = fast->next->next;

    if (slow == fast) {
      while (list != slow) {
        list = list->next;
        slow = slow->next;
      }

      return list;
    }
  }

  return NULL;
}

// 删除有序列表中包含重复值的节点
ListNode* ListRemoveDuplicatesFromSortedList(ListNode** list) {
  ListNode* ptr = *list;
  while (ptr && ptr->next) {
    if (ptr->val == ptr->next->val) {
      // rmeove duplicate node
      ListNode* tmp = ptr->next;
      ptr->next = ptr->next->next;
      free(tmp);
    } else {
      // next node
      ptr = ptr->next;
    }
  }

  return *list;
}

ListNode* ListMergeSortedList(ListNode* list1, ListNode* list2) {
  ListNode* list3 = (ListNode*)malloc(sizeof(ListNode));
  ListNode* ptr3 = list3;
  while (list1 && list2) {
    if (list1->val < list2->val) {
      ptr3->next = list1;
      ptr3 = ptr3->next;
      list1 = list1->next;
    } else {
      ptr3->next = list2;
      ptr3 = ptr3->next;
      list2 = list2->next;
    }
  }

  if (list1) {
    ptr3->next = list1;
  } else if (list2) {
    ptr3->next = list2;
  }

  return list3->next;
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

void TestListRemoveNthNodeFromEnd() {
  ListNode* list = NULL;
  ListInsert(&list, 1);
  ListInsert(&list, 1);
  ListInsert(&list, 3);
  ListInsert(&list, 1);

  cout << ListLength(list) << endl;
  ListPrint(list);

  ListRemoveNthNodeFromEnd(&list, 1);

  cout << ListLength(list) << endl;
  ListPrint(list);
}

void TestListMergeSortedList() {
  ListNode* list1 = NULL;
  ListInsert(&list1, 2);
  ListInsert(&list1, 3);

  ListNode* list2 = NULL;
  ListInsert(&list2, 1);
  ListInsert(&list2, 2);

  ListNode* list3 = ListMergeSortedList(list1, list2);

  cout << ListLength(list3) << endl;
  ListPrint(list3);
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
  cout << "TestListRemoveNthNodeFromEnd:" << endl;
  TestListRemoveNthNodeFromEnd();
  cout << "TestListMergeSortedList:" << endl;
  TestListMergeSortedList();
  return 0;
}
