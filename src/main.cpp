#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
  Mat img = imread("image.jpg");
  if (img.empty()) {
    cout << "Image not loaded\n";
    return -1;
  }

  resize(img, img, Size(255, 255), 0, 0, INTER_AREA);

  cout << "Loaded\n";

  Mat data;
  img.convertTo(data, CV_32F);
  data = data.reshape(1, data.total());  // Flatten to Nx3

  int K = 6;
  Mat labels, centers;
  kmeans(data, K, labels,
         TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 1.0),
         3, KMEANS_PP_CENTERS, centers);

  Mat palette(100, 100 * K, CV_8UC3);
  for (int i = 0; i < K; ++i) {
    float b = centers.at<float>(i, 0);
    float g = centers.at<float>(i, 1);
    float r = centers.at<float>(i, 2);
    Rect roi(i * 100, 0, 100, 100);
    rectangle(palette, roi, Scalar(b, g, r), FILLED);
  }
  imshow("Palette", palette);
  waitKey(0);
  return 0;
}
