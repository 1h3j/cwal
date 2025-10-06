#include <opencv2/opencv.hpp>
#include <filesystem>
#include <iostream>
#include <cstdlib>
#include <string>

#include "getopt.h"

#include "palette.hpp"


inline void showHelp(const char *program_name) {
  std::cout << "Usage: " << program_name << " image_path [options]\n"
    << "\nOptions:\n"
    << "  -n, --number NUM      Number of colors to use (default: 3)\n"
    << "  -j, --json            Output result as JSON (default: false)\n"
    << "  -h, --help            Show this help message\n";
}


int main(int argc, char** argv) {
  int         number_colors = 3;
  bool        use_json = false;
  std::string image_path;

  const char* const short_opts = "n:jh";
  const option long_opts[] = {
    {"number", required_argument, nullptr, 'n'},
    {"json",   no_argument,       nullptr, 'j'},
    {"help",   no_argument,       nullptr, 'h'},
    {nullptr,  0,                 nullptr, 0}
  };

  int opt;
  while ((opt = getopt_long(argc, argv, short_opts, long_opts, nullptr)) != -1) {
    switch (opt) {
      case 'n':
        number_colors = std::atoi(optarg);
        break;
      case 'j':
        use_json = true;
        break;
      case 'h':
        showHelp(argv[0]);
        break;
      default:
        showHelp(argv[0]);
        return 1;
    }
  }

  if (optind < argc) {
    image_path = argv[optind];
    if ( !std::filesystem::exists(image_path) ) {
      std::cerr << "Error: File does not exist.\n";
      return -1;
    }
  } else {
    std::cerr << "Error: image_path is required.\n";
    showHelp(argv[0]);
    return 1;
  }

  if (number_colors <= 0) {
    std::cerr << "Error: invalid number_of_colors.\n";
    return -1;
  }

  cv::Mat img = cv::imread(image_path);
  if (img.empty()) {
    std::cout << "Image not loaded\n";
    return -1;
  }

  cv::resize(img, img, cv::Size(255, 255), 0, 0, cv::INTER_AREA);
  cv::Mat centers = generatePalette(img, number_colors);

  // Too lazy to use JSON serializers
  // Meh, this is faster anyways
  if ( use_json ) {
    std::printf("{\"palette\":[");
    for (int i = 0; i < number_colors; ++i) {
      const float b = centers.at<float>(i, 0);
      const float g = centers.at<float>(i, 1);
      const float r = centers.at<float>(i, 2);
      std::printf((i == number_colors - 1) ? "\"#%02x%02x%02x\"" : "\"#%02x%02x%02x\",",
                  static_cast<uint8_t>(r * 255),
                  static_cast<uint8_t>(g * 255),
                  static_cast<uint8_t>(b * 255));
    }
    std::printf("]}\n");
  } else {
    for (int i = 0; i < number_colors; ++i) {
      const float b = centers.at<float>(i, 0);
      const float g = centers.at<float>(i, 1);
      const float r = centers.at<float>(i, 2);
      std::printf("%d:#%02x%02x%02x\n", i,
                  static_cast<uint8_t>(r * 255),
                  static_cast<uint8_t>(g * 255),
                  static_cast<uint8_t>(b * 255));
    }
  }

  return 0;
}
