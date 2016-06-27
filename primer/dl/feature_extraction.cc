#include "feature_extraction.h"

FeatureExtraction* CreateFeatureExtraction() {
  FeatureExtraction* feature_extraction = new FeatureExtraction();
  return feature_extraction;
}

void DestroyFeatureExtraction(FeatureExtraction* feature_extraction) {
  delete feature_extraction;
}
