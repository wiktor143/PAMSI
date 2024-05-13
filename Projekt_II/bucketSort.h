#ifndef BUCKET_SORT
#define BUCKET_SORT

#include"readFile.h"
void bucketSort(std::vector<Movie>& data, int length);
int findBucketIndex(float rating, int num_buckets);
void sortBucket(std::vector<Movie>& bucket);
int getBucketIndex(float rating, float maxRating);
float findMaxRating(const std::vector<Movie>& data);
#endif