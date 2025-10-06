// MIT License
// 
// Copyright (c) 2025 1h3j
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

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
