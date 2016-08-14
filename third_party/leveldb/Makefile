CC = g++
CXXFLAGS = -g
LDFLAGS = -lleveldb -lboost_system -lboost_filesystem `pkg-config --cflags --libs opencv`

db.o: db.cc
	$(CC) -c $(CXXFLAGS) db.cc

leveldb.o: leveldb.cc
	$(CC) -c $(CXXFLAGS) leveldb.cc

db_bench.o: db_bench.cc
	$(CC) -c $(CXXFLAGS) db_bench.cc

db_bench: db_bench.o db.o leveldb.o
	$(CC) -o db_bench db_bench.o db.o leveldb.o $(LDFLAGS)

all: db_bench


clean:
	rm -f *.o
	rm -f a.out
	rm -f db_bench

