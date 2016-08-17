#ifndef LEVELDB_H_
#define LEVELDB_H_

#include "db.h"

#include <leveldb/db.h>
#include <leveldb/write_batch.h>

namespace db {

class LevelDBTransaction;
class LevelDBIterator;

class LevelDB: public DB {
  public:
    LevelDB();
    ~LevelDB();

    bool Open(const string& source, Mode mode);
    void Close();

    bool Get(const string& key, string* value);
    bool Put(const string& key, const string& value);
    bool Delete(const string& key);

    Transaction* NewTransaction();
    Iterator* NewIterator(); 

  private:
    leveldb::DB* db_;
};

class LevelDBTransaction: public Transaction {
  public:
    LevelDBTransaction(leveldb::DB* db);
    ~LevelDBTransaction();

    void Put(const string& key, const string& value);
    void Delete(const string& key);
    bool Commit();

  private:
    leveldb::DB* db_;
    leveldb::WriteBatch batch_;
};

class LevelDBIterator: public Iterator {
  public:
    LevelDBIterator(leveldb::Iterator* iter);
    ~LevelDBIterator();

    void SeekToFirst();
    void Next();
    string key();
    string value();
    bool Valid();

  private:
    leveldb::Iterator* iter_;
};

}

#endif
