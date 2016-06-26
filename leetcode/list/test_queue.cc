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

struct Queue {
  ListNode* head;
  ListNode* tail;
  int length;
  Queue(): head(NULL), tail(NULL), length(0) {}
};

void QueuePush(Queue* queue, int val) {
  ListNode* node = (ListNode*)malloc(sizeof(ListNode));
  node->val = val;
  node->next = NULL;

  if (queue->head == NULL) {
    queue->head = node;
    queue->tail = node;
  } else {
    // 队列非空
    queue->tail->next = node; 
    queue->tail = queue->tail->next;
  }

  queue->length++;
}

int QueueFront(Queue* queue) {
  assert(0 != queue->length);

  return queue->head->val;
}

void QueuePop(Queue* queue) {
  if (0 == queue->length) {
    return ;
  }

  ListNode* tmp = queue->head;
  queue->head = tmp->next;

  free(tmp);

  queue->length--;
}

int QueueLength(Queue* queue) {
  return queue->length;
}

int QueueEmpty(Queue* queue) {
  return 0 == queue->length;
}

void TestQueuePushAndPop() {
  Queue q;
  QueuePush(&q, 1);
  QueuePush(&q, 2);
  QueuePush(&q, 3);
  QueuePush(&q, 4);

  cout << QueueFront(&q) << endl;
  QueuePop(&q);
  cout << QueueFront(&q) << endl;
  QueuePop(&q);
  QueuePush(&q, 5);
  cout << QueueFront(&q) << endl;
  QueuePop(&q);
  cout << QueueFront(&q) << endl;
  QueuePop(&q);
  cout << QueueFront(&q) << endl;
  QueuePop(&q);

  QueuePush(&q, 6);
  cout << QueueFront(&q) << endl;
  QueuePop(&q);

  cout << QueueLength(&q) << endl;
}

int main() {
  cout << "TestQueuePushAndPop:" << endl;
  TestQueuePushAndPop();
  return 0;
}
