#include <iostream>
#include <memory>

#include <boost/smart_ptr.hpp>

using namespace std;

class Item {
  public:
    Item(int idx=0):
      idx_(idx)
    {
      cout << "Item(), idx=" << idx_ << endl;
    }

    ~Item() {
      cout << "~Item(), idx=" << idx_ << endl;
    }

    void Print() {
      cout << "print, idx=" << idx_ << endl;
    }

    int idx_;
};


void TestAutoPtr() {
  std::auto_ptr<Item> item(new Item(1));
  if (item.get()) {
    item->Print();
    item.get()->idx_++;
    item->Print();
  } 

  if (item.get()) {
    //std::auto_ptr<Item> item2 = item; // item2夺走了item对单个对象的管理权, item悬空
    //item2->Print();
    //item->Print(); // error, item没有管理任何对象, 崩溃
  }

  if (item.get()) {
    //item.release(); // 归还所有权, 但并没有释放管理的对象, 会导致内存泄露
    // 正确做法
    item.reset(); // 释放内存管理的对象
  }
}

void TestScopedPtr() {
  boost::scoped_ptr<Item> item(new Item(10));
  if (item.get()) {
    item->Print();
    item.get()->idx_++;
    item->Print();

  }

  if (item.get()) {
    //boost::scoped_ptr<Item> item2 = item; // error, 未重载operator=
  }

  if (item.get()) {
    //item.release(); // boost没有提供relase()接口
    item.reset();
  }
}

void TestSharedPtr() {
  boost::shared_ptr<Item> item(new Item(20));
  if (item.get()) {
    item->Print();
    item.get()->idx_++;
    item->Print();
  }

  if (item.get()) {
    boost::shared_ptr<Item> item2 = item;
    item2->Print();
    item->Print();
    cout << "item use count: " << item.use_count() << endl;
  }
  cout << "item use count: " << item.use_count() << endl;

  if (item.get()) {
    // 只对item进行引用，未改变item的引用计数
    boost::weak_ptr<Item> item2 = item;
    cout << "item use count: " << item.use_count() << endl;
    cout << "item2 use count: " << item2.use_count() << endl;
  }
  cout << "item use count: " << item.use_count() << endl;

  if (item.get()) {
    item.reset();
  }
  cout << "item use count: " << item.use_count() << endl;
}

void TestScopedArray() {
  //boost::scoped_array<Item> items(new Item(5)); // error, 这样是在坑自己
  boost::scoped_array<Item> items(new Item[5]);

  if (items.get()) {
    items[0].Print();
    items[0].idx_++;
    items[0].Print();
    //items[0].release(); // release接口
    //boost::scoped_array<Item> items2 = items; // 没有重载operator=
  }
}

void TestSharedArray() {
  boost::shared_array<Item> items(new Item[5]);
  if (items.get()) {
    items[0].Print();
    items.get()[0].idx_++;
    items[0].Print();
  }

  if (items.get()) {
    boost::shared_array<Item> items2 = items;
    cout << "items use count: " << items.use_count() << endl;
    cout << "items2 use count: " << items2.use_count() << endl;
  }

  cout << "items use count: " << items.use_count() << endl;

  if (items.get()) {
    items.reset();
  }

  cout << "items use count: " << items.use_count() << endl;
}

int main() {
  //TestAutoPtr();
  //TestScopedPtr();
  TestSharedPtr();
  //TestScopedArray();
  //TestSharedArray();
  return 0;
}
