// my files

// itk
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>

// C++
#include <iostream>

int main(int argc, const char * argv[]) {

  using PixelType = double;
  constexpr unsigned int Dimension = 2;
  using ImageType = itk::Image<PixelType, Dimension>;

  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <fixed image> <moving image>" << std::endl;
    return EXIT_FAILURE;
  }

  auto fixedImage = itk::ReadImage<ImageType>(argv[1]);
  auto movingImage = itk::ReadImage<ImageType>(argv[2]);

  std::cout << "Images Read" << std::endl;


  return EXIT_SUCCESS;
}