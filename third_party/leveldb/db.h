#ifndef DB_H_
#define DB_H_

#include <string>

using std::string;

namespace db {

enum Mode{kRead, kWrite, kNew};

class Transaction;
class Iterator;

class DB {
  public:
    virtual ~DB() {}
    
    virtual bool Open(const string& source, Mode mode) = 0;
    virtual void Close() = 0;

    virtual bool Get(const string& key, string* value) = 0;
    virtual bool Put(const string& key, const string& value) = 0;
    virtual bool Delete(const string& key) = 0;

    virtual Transaction* NewTransaction() = 0;
    virtual Iterator* NewIterator() = 0;
};

class Transaction {
  public:
    virtual ~Transaction() {}
    virtual void Put(const string& key, const string& value) = 0;
    virtual void Delete(const string& key) = 0;
    virtual bool Commit() = 0;
};

class Iterator {
  public:
    virtual ~Iterator() {}

    virtual void SeekToFirst() = 0;
    virtual void Next() = 0;
    virtual string key() = 0;
    virtual string value() = 0;
    virtual bool Valid() = 0;
};

DB* GetDB(const string& backend);

}

#endif
