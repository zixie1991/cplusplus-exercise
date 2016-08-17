#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <iostream>
#include <queue>
#include <stack>

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

template <typename T>
class QStack {
  public:
    void Push(T val) {
      // 选择q1, q2中非空的入队
      if (q1_.empty()) {
        // q1空
        q2_.push(val);
      } else {
        // q1非空, q2空
        q1_.push(val);
      }
    }

    void Pop() {
      if (q1_.empty() && q2_.empty()) {
        return ;
      }

      // q1, q2一个空，一个非空
      if (q1_.empty()) {
        // q2非空
        while (q2_.size() > 1) {
          T v = q2_.front();
          q2_.pop();
          q1_.push(v);
        }

        // 出栈
        q2_.pop();
      } else {
        // q1非空
        while (q1_.size() > 1) {
          T v = q1_.front();
          q1_.pop();
          q2_.push(v);
        }
        
        // 出栈
        q1_.pop();
      }
    }

    T Top() {
      assert(!q1_.empty() || !q2_.empty());
      T ret;

      // q1, q2一个空，一个非空
      if (q1_.empty()) {
        // q2非空
        while (q2_.size() > 1) {
          T v = q2_.front();
          q2_.pop();
          q1_.push(v);
        }

        // 栈顶
        ret = q2_.front();
        q2_.pop();
        q1_.push(ret);
      } else {
        // q1非空
        while (q1_.size() > 1) {
          T v = q1_.front();
          q1_.pop();
          q2_.push(v);
        }
        
        // 栈顶
        ret = q1_.front();
        q1_.pop();
        q2_.push(ret);
      }

      return ret;
    }

    int Size() {
      return q1_.size() + q2_.size();
    }

    bool Empty() {
      return q1_.empty() && q2_.empty();
      return data_.size();
    }

  private:
    queue<T> q1_;
    queue<T> q2_;
};

class StackWithMin {
  public:
    void Push(int val) {
      data_.push(val);

      if (min_.empty() || val < min_.top()) {
        min_.push(val);
      } else {
        min_.push(min_.top());
      }
    }

    void Pop() {
      data_.pop();
      min_.pop();
    }

    int Top() {
      return data_.top();
    }

    int Min() {
      return min_.top();
    }

    bool Empty() {
      return data_.empty();
    }

    int size() {
      return data_.size();
    }

  private:
    stack<int> min_;
    stack<int> data_;
};

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

void TestQStackPushAndPop() {
  QStack<int> s;
  s.Push(1);
  s.Push(2);
  s.Push(3);
  s.Push(4);

  cout << s.Top() << endl;
  s.Pop();
  cout << s.Top() << endl;
  s.Pop();
  cout << s.Top() << endl;
  s.Pop();
  s.Push(5);
  cout << s.Top() << endl;
  s.Pop();

  s.Push(6);
  cout << s.Top() << endl;
  s.Pop();

  cout << s.Size() << endl;
}

int main() {
  cout << "TestStackPushAndPop:" << endl;
  TestStackPushAndPop();
  cout << "TestQStackPushAndPop:" << endl;
  TestQStackPushAndPop();
  return 0;
}
