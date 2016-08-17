#include "db.h"

#include "leveldb.h"

namespace db {

DB* GetDB(const string& backend) {
  if (backend == "leveldb") {
    return new LevelDB();
  }

  return NULL;
}

}
