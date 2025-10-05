#include <opencv2/opencv.hpp>
#include <filesystem>
#include <iostream>
#include <string>

#include "palette.hpp"

int main(int argc, char** argv) {
  std::string fileName;
  int K = 3;

  // Parse Argument //
  if ( argc >= 2 ) {
    fileName = argv[1]; 

    if ( !std::filesystem::exists(fileName) ) {
      std::cout << "File does not exist..\n";
      return -1;
    }

    if ( argc == 3 ) {
      K = std::atoi( argv[2] );
      if ( K <= 0 ) {
        std::cout << "Invalid number_of_colors\n";
        return -1;
      }
    }
  } else {
    std::cout << "Usage: " << argv[0] << " image_path (number_of_colors default:3)\n";
    return -1;
  }

  cv::Mat img = cv::imread(fileName);
  if (img.empty()) {
    std::cout << "Image not loaded\n";
    return -1;
  }

  cv::resize(img, img, cv::Size(255, 255), 0, 0, cv::INTER_AREA);
  cv::Mat centers = generatePalette(img, K);

  for (int i = 0; i < K; ++i) {
    float b = centers.at<float>(i, 0);
    float g = centers.at<float>(i, 1);
    float r = centers.at<float>(i, 2);
    std::printf("%d:#%02x%02x%02x\n", i,
                static_cast<uint8_t>(r * 255),
                static_cast<uint8_t>(g * 255),
                static_cast<uint8_t>(b * 255));
  }
  return 0;
}
