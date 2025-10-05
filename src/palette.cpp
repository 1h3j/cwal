#include "palette.hpp"

cv::Mat generatePalette(cv::Mat image, int N) {
  cv::Mat data;
  image.convertTo(data, CV_32F);
  data = data.reshape(1, data.total());

  cv::Mat labels, centers;
  kmeans(data, N, labels,
         cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 10, 1.0),
         3, cv::KMEANS_PP_CENTERS, centers);
  return centers;
}
