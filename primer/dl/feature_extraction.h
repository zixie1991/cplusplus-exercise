#ifndef FEATURE_EXTRACTION_H_
#define FEATURE_EXTRACTION_H_

#include <stdio.h>

class FeatureExtraction {
  public:
    void Extract() {
      printf("feature extraction extract\n");
    }

    void Similarity() {
      printf("feature extraction similarity\n");
    }
};

#ifdef __cplusplus
extern "C" {
#endif

FeatureExtraction* CreateFeatureExtraction();
void DestroyFeatureExtraction(FeatureExtraction* feature_extraction);


#ifdef __cplusplus
}
#endif

#endif
