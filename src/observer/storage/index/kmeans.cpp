#include "storage/index/kmeans.h"
#include "common/log/log.h"
#include "sql/parser/parse_defs.h"
#include <algorithm>
#include <cassert>
#include <cstring>
#include <limits>
#include <random>

Kmeans::Kmeans(int centroids, int n, int dim, DISTANCE_ALGO algorithm) : centroids_(centroids), n_(n), dim_(dim)
{
  centroids_   = std::min(centroids, n);
  converged_   = false;
  data_        = new float[n * dim];
  centers_     = new float[centroids_ * dim];
  assignment_  = new unsigned short[n];
  clusterSize_ = new int[centroids_];
  sumCenters_  = new float[centroids_ * dim];
  switch (algorithm) {
    case DISTANCE_ALGO::L2_DISTANCE: {
      calc_ = &l2_distance;
    } break;
    case DISTANCE_ALGO::COSINE_DISTANCE: {
      calc_ = &cosine_distance;
    } break;
    case DISTANCE_ALGO::INNER_PRODUCT: {
      calc_ = &inner_product;
    } break;
    default: {
      ASSERT(false, "");
    }
  }
}

void Kmeans::free()
{
  if (data_ != nullptr) {
    delete[] data_;
  }
  if (centers_ != nullptr) {
    delete[] centers_;
  }
  if (assignment_ != nullptr) {
    delete[] assignment_;
  }
  if (clusterSize_ != nullptr) {
    delete[] clusterSize_;
  }
  if (sumCenters_ != nullptr) {
    delete[] sumCenters_;
  }
}

void Kmeans::set_data(int index, const char *src)
{
  char *tar = reinterpret_cast<char *>(data_ + index * dim_);
  memcpy(tar, src, sizeof(float) * dim_);
}

void Kmeans::generate_index()
{
  initialize();
  run();
}

void Kmeans::initialize()
{
  // take the prefix vectors as inital centers
  memcpy(centers_, data_, sizeof(float) * centroids_ * dim_);
  // randomly generate the initial assignment
  for (int i = 0; i < n_; i++) {
    assignment_[i] = i % centroids_;
  }
  std::random_device rd;
  std::mt19937       engine(rd());
  std::shuffle(assignment_, assignment_ + n_, engine);
  // get statistics about the initial assignment
  memset(clusterSize_, 0, sizeof(int) * centroids_);
  memset(sumCenters_, 0, sizeof(float) * centroids_ * dim_);
  for (int i = 0; i < n_; i++) {
    auto centerIndex = assignment_[i];
    clusterSize_[centerIndex]++;
    float *vData = data_ + i * dim_;
    float *cData = sumCenters_ + centerIndex * dim_;
    addVector(vData, cData);
  }
}

void Kmeans::run()
{
  while (!converged_) {
    for (int i = 0; i < n_; i++) {
      int    closest     = 0;
      double closestDist = std::numeric_limits<double>::max();
      float *pdata       = data_ + i * dim_;
      for (int j = 0; j < centroids_; j++) {
        float *cdata  = centers_ + j * dim_;
        double curdis = calc_(pdata, cdata, dim_);
        if (curdis < closestDist) {
          closest     = j;
          closestDist = curdis;
        }
      }
      if (assignment_[i] != closest) {
        changeAssignment(i, closest);
      }
    }
    if (move_centers() < EPS) {
      converged_ = true;
    }
  }
}

void Kmeans::changeAssignment(int vectorIndex, int centerIndex)
{
  auto prevAssignment = assignment_[vectorIndex];
  assert(prevAssignment != centerIndex);
  clusterSize_[prevAssignment]--;
  clusterSize_[centerIndex]++;
  float *vData  = data_ + vectorIndex * dim_;
  float *pcData = sumCenters_ + prevAssignment * dim_;
  float *cData  = sumCenters_ + centerIndex * dim_;
  addVector(vData, cData);
  subVector(vData, pcData);
}

double Kmeans::move_centers()
{
  double furthestMovingDistance = 0;
  for (int i = 0; i < centroids_; i++) {
    int    size           = clusterSize_[i];
    double movingDistance = 0;
    if (size > 0) {
      for (int d = 0; d < dim_; d++) {
        int    dimOffset = i * dim_ + d;
        double dimAvg    = sumCenters_[dimOffset];
        dimAvg /= size;
        movingDistance += (dimAvg - centers_[dimOffset]) * (dimAvg - centers_[dimOffset]);
        centers_[dimOffset] = dimAvg;
      }
    }
    movingDistance         = sqrt(movingDistance);
    furthestMovingDistance = std::max(furthestMovingDistance, movingDistance);
  }
  return furthestMovingDistance;
}

const float *Kmeans::clusterCenter(int clusterIndex) const
{
  ASSERT(clusterIndex < centroids_, "");
  return centers_ + clusterIndex * dim_;
}

const int Kmeans::belongToCluster(int vectorIndex) const
{
    ASSERT(vectorIndex < n_, "");
    return static_cast<int>(assignment_[vectorIndex]);
}

double Kmeans::l2_distance(const float *lhs, const float *rhs, int dim)
{
  double product_sum = std::inner_product(
      lhs, lhs + dim, rhs, 0.0, std::plus<float>{}, [](float a, float b) { return (a - b) * (a - b); });
  return std::sqrt(product_sum);
}

double Kmeans::cosine_distance(const float *lhs, const float *rhs, int dim)
{
  double mag_left  = std::sqrt(std::accumulate(lhs, lhs + dim, 0.0, [](float sum, float i) { return sum + i * i; }));
  double mag_right = std::sqrt(std::accumulate(rhs, rhs + dim, 0.0, [](float sum, float i) { return sum + i * i; }));
  double inner_product = std::inner_product(lhs, lhs + dim, rhs, 0.0);
  double cos_distance  = 1.0 - inner_product / (mag_left * mag_right);
  return cos_distance;
}

double Kmeans::inner_product(const float *lhs, const float *rhs, int dim)
{
  double inner_product = std::inner_product(lhs, lhs + dim, rhs, 0.0);
  return inner_product;
}

void Kmeans::addVector(const float *vectorData, float *centerData)
{
  float *centerDataEnd = centerData + dim_;
  while (centerData < centerDataEnd) {
    *(centerData++) += *(vectorData++);
  }
}

void Kmeans::subVector(const float *vectorData, float *centerData)
{
  float *centerDataEnd = centerData + dim_;
  while (centerData < centerDataEnd) {
    *(centerData++) -= *(vectorData++);
  }
}