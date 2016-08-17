#include "leveldb.h"

#include <iostream>

using std::cerr;
using std::endl;

namespace db {

LevelDB::LevelDB():
  db_(NULL)
{
}

LevelDB::~LevelDB() {
  Close();
}

bool LevelDB::Open(const string& source, Mode mode) {
  leveldb::Options options;
  options.block_size = 65536;
  options.write_buffer_size = 268435456;
  options.max_open_files = 100;
  options.error_if_exists = mode == kNew;
  options.create_if_missing = mode != kRead;
  leveldb::Status status = leveldb::DB::Open(options, source, &db_);
  if (!status.ok()) {
    cerr << "Failed to open leveldb " << source << " " << status.ToString() << endl;
  }

  return status.ok();
}

void LevelDB::Close() {
  if (!db_) {
    delete db_;
    db_ = NULL;
  }
}

bool LevelDB::Get(const string& key, string* value) {
  leveldb::Status status = db_->Get(leveldb::ReadOptions(), key, value);
  return status.ok();
}

bool LevelDB::Put(const string& key, const string& value) {
  leveldb::Status status = db_->Put(leveldb::WriteOptions(), key, value);
  return status.ok();
}

bool LevelDB::Delete(const string& key) {
  leveldb::Status status = db_->Delete(leveldb::WriteOptions(), key);
  return status.ok();
}

Transaction* LevelDB::NewTransaction() {
  return new LevelDBTransaction(db_);
}

Iterator* LevelDB::NewIterator() {
  return new LevelDBIterator(db_->NewIterator(leveldb::ReadOptions()));
}

LevelDBTransaction::LevelDBTransaction(leveldb::DB* db):
  db_(db)
{
}

LevelDBTransaction::~LevelDBTransaction() {
}

void LevelDBTransaction::Put(const string& key, const string& value) {
  batch_.Put(key, value);
}

void LevelDBTransaction::Delete(const string& key) {
  batch_.Delete(key);
}

bool LevelDBTransaction::Commit() {
  leveldb::Status status = db_->Write(leveldb::WriteOptions(), &batch_);

  return status.ok();
}

LevelDBIterator::LevelDBIterator(leveldb::Iterator* iter):
  iter_(iter)
{
}

LevelDBIterator::~LevelDBIterator() {
}

void LevelDBIterator::SeekToFirst() {
  iter_->SeekToFirst();
}

void LevelDBIterator::Next() {
  iter_->Next();
}

string LevelDBIterator::key() {
  return iter_->value().ToString();
}

string LevelDBIterator::value() {
  return iter_->value().ToString();
}

bool LevelDBIterator::Valid() {
  return iter_->Valid();
}

}
