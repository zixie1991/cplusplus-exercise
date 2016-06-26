#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <iostream>

using namespace std;

struct ListNode {
  int val;
  ListNode* next;
};

struct Stack {
  ListNode* top;
  int length;
  Stack(): top(NULL), length(0) {}
};

bool StackEmpty(Stack* stack) {
  return 0 == stack->length;
}

int StackLength(Stack* stack) {
  return stack->length;
}

void StackPush(Stack* stack, int val) {
  ListNode* node = (ListNode*)malloc(sizeof(ListNode));
  node->val = val;
  node->next = stack->top;
  stack->top = node;

  stack->length++;
}

int StackTop(Stack* stack) {
  assert(0 != stack->length);

  return stack->top->val;
}

void StackPop(Stack* stack) {
  assert(0 != stack->length);

  ListNode* tmp = stack->top;
  stack->top = tmp->next;

  free(tmp);
  stack->length--;
}

void TestStackPushAndPop() {
  Stack s;
  StackPush(&s, 1);
  StackPush(&s, 2);
  StackPush(&s, 3);
  StackPush(&s, 4);

  cout << StackTop(&s) << endl;
  StackPop(&s);
  cout << StackTop(&s) << endl;
  StackPop(&s);
  cout << StackTop(&s) << endl;
  StackPop(&s);
  StackPush(&s, 5);
  cout << StackTop(&s) << endl;
  StackPop(&s);

  StackPush(&s, 6);
  cout << StackTop(&s) << endl;
  StackPop(&s);

  cout << StackLength(&s) << endl;
}

int main() {
  cout << "TestStackPushAndPop:" << endl;
  TestStackPushAndPop();
  return 0;
}
