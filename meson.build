project(
  'color_palette',
  'cpp',
  version: '1.0',
  default_options: ['cpp_std=c++17']
)

opencv_dep = dependency('opencv4', required: true)

inc = include_directories('include')

executable(
  'color_palette',
  'src/main.cpp',
  include_directories: inc,
  dependencies: [opencv_dep],
  install: false
)
