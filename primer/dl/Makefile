CC = g++

libfeature_extraction.so: feature_extraction.cc
	$(CC) -shared -fPIC -o libfeature_extraction.so feature_extraction.cc

libface_detection.so: face_detection.cc
	$(CC) -shared -fPIC -o libface_detection.so face_detection.cc

libface_verification.so: face_verification.cc
	$(CC) -shared -fPIC -o libface_verification.so face_verification.cc

all: libfeature_extraction.so libface_detection.so libface_verification.so

clean:
	rm -rf *.o *.so a.out core
