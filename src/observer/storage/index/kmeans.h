#ifndef KMEANS_H
#define KMEANS_H

#include "sql/parser/parse_defs.h"

class Kmeans
{
#define EPS (5e-2)
  using CmpFunc = std::function<double(const float *, const float *, int)>;

public:
  Kmeans(int centroids, int n, int dim, DISTANCE_ALGO algorithm);
  ~Kmeans() { free(); }
  void free();

  void set_data(int index, const char *src);
  void generate_index();

  bool converge() const { return converged_; }
  const float* clusterCenter(int clusterIndex) const;
  const int belongToCluster(int vectorIndex) const;

  static double l2_distance(const float *lhs, const float *rhs, int dim);
  static double cosine_distance(const float *lhs, const float *rhs, int dim);
  static double inner_product(const float *lhs, const float *rhs, int dim);

private:
  void   initialize();
  void   run();
  void   changeAssignment(int vectorIndex, int centerIndex);
  double move_centers();

  void addVector(const float *vectorData, float *centerData);
  void subVector(const float *vectorData, float *centerData);

  bool converged_;
  // number of clusters
  int centroids_;
  // tot number of vectors
  int n_;
  // dimension of each vector
  int dim_;
  // contiguous data of all vectors
  float *data_;
  // centers of each cluster
  float *centers_;
  // which cluster is each vector assgined to
  unsigned short *assignment_;
  // the number of vectors in each cluster
  int *clusterSize_;
  // sum of vectors in each cluster
  float *sumCenters_;
  // distance algorithm
  CmpFunc calc_;
};

#endif