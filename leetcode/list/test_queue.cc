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

const int MAX = 1000000;

struct SQueue {
  int s1[MAX]; // 入队栈
  int s2[MAX]; // 出队栈
  int top1;
  int top2;

  SQueue(): top1(0), top2(0) {}
};

void SQueuePush(SQueue* q, int val) {
  q->s1[q->top1++] = val;
}

int SQueueFront(SQueue* q) {
  if (q->top2 != 0) {
    return q->s2[q->top2 - 1];
  }

  assert(q->top1 != 0);
  while (q->top1) {
    q->s2[q->top2++] = q->s1[--q->top1];
  }

  return q->s2[q->top2 - 1];
}

int SQueuePop(SQueue* q) {
  if (q->top2 != 0) {
    return q->s2[--q->top2];
  }

  assert(q->top1 != 0);
  while (q->top1) {
    q->s2[q->top2++] = q->s1[--q->top1];
  }

  return q->s2[--q->top2];
}

int SQueueLength(SQueue* q) {
  return q->top1 + q->top2;
}

void TestSQueuePushAndPop() {
  SQueue q;
  SQueuePush(&q, 1);
  SQueuePush(&q, 2);
  SQueuePush(&q, 3);
  SQueuePush(&q, 4);

  cout << SQueueFront(&q) << endl;
  SQueuePop(&q);
  cout << SQueueFront(&q) << endl;
  SQueuePop(&q);
  SQueuePush(&q, 5);
  cout << SQueueFront(&q) << endl;
  SQueuePop(&q);
  cout << SQueueFront(&q) << endl;
  SQueuePop(&q);
  cout << SQueueFront(&q) << endl;
  SQueuePop(&q);

  SQueuePush(&q, 6);
  cout << SQueueFront(&q) << endl;
  SQueuePop(&q);

  cout << SQueueLength(&q) << endl;
}

int main() {
  cout << "TestQueuePushAndPop:" << endl;
  TestQueuePushAndPop();
  cout << "TestSQueuePushAndPop:" << endl;
  TestSQueuePushAndPop();
  return 0;
}
