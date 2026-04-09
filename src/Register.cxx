// itk
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include "itkSimilarity2DTransform.h"
#include "itkRegularStepGradientDescentOptimizerv4.h"
#include "itkMeanSquaresImageToImageMetricv4.h"
#include "itkImageRegistrationMethodv4.h"

// C++
#include <iostream>

int main(int argc, const char * argv[]) {

  using PixelType = double;
  constexpr unsigned int Dimension = 2;
  using ImageType = itk::Image<PixelType, Dimension>;

  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " <fixed image path> <moving image path> <output path>" << std::endl;
    return EXIT_FAILURE;
  }

  auto fixedImage = itk::ReadImage<ImageType>(argv[1]);
  auto movingImage = itk::ReadImage<ImageType>(argv[2]);

  // transform -- diverging from the tutorial because we need Similarity2D
  using TransformType = itk::Similarity2DTransform<PixelType>;
  auto initialTransform = TransformType::New();

  using OptimizerType = itk::RegularStepGradientDescentOptimizerv4<double>;
  auto optimizer = OptimizerType::New();
  optimizer->SetLearningRate(4);
  optimizer->SetMinimumStepLength(0.001);
  optimizer->SetRelaxationFactor(0.5);
  optimizer->SetNumberOfIterations(200);

  using MetricType = itk::MeanSquaresImageToImageMetricv4<ImageType, ImageType>;
  auto metric = MetricType::New();

  // add metric, optimizer, and transform into registration
  using RegistrationType = itk::ImageRegistrationMethodv4<ImageType, ImageType>;
  auto registration = RegistrationType::New();
  registration->SetInitialTransform(initialTransform);
  registration->SetMetric(metric);
  registration->SetOptimizer(optimizer);
  registration->SetFixedImage(fixedImage);
  registration->SetMovingImage(movingImage);

  // identity initial transform because our images are close to begin with
  auto identityTransform = TransformType::New();
  identityTransform->SetIdentity();
  registration->SetFixedInitialTransform(identityTransform);

  // not using multi-scale resolution so one level to the pyramid
  // I have a limited understanding of this part but have used it in
  // registration with SimpleITK
  constexpr unsigned int numberOfLevels = 1;
  registration->SetNumberOfLevels(numberOfLevels);

  // not shrinking
  RegistrationType::ShrinkFactorsArrayType shrinkFactorsPerLevel;
  shrinkFactorsPerLevel.SetSize(1);
  shrinkFactorsPerLevel[0] = 1;
  registration->SetShrinkFactorsPerLevel(shrinkFactorsPerLevel);

  // not smoothing
  RegistrationType::SmoothingSigmasArrayType smoothingSigmasPerLevel;
  smoothingSigmasPerLevel.SetSize(1);
  smoothingSigmasPerLevel[0] = 0;
  registration->SetSmoothingSigmasPerLevel(smoothingSigmasPerLevel);

  // run the registartion optimization
  try
  {
    registration->Update();
    std::cout << "Optimizer stop condition: " << registration->GetOptimizer()->GetStopConditionDescription()
              << std::endl;
  }
  catch (const itk::ExceptionObject & err)
  {
    std::cerr << "ExceptionObject caught !" << std::endl;
    std::cerr << err << std::endl;
    return EXIT_FAILURE;
  }

  // get transfrom from registration object
  auto transform = registration->GetTransform();
  auto finalParameters = transform->GetParameters();

  // adjusted this to incorporate more than just translation
  std::cout << "Final Parameters: " << std::endl;
  std::cout << finalParameters << std::endl;

  auto numberOfIterations = optimizer->GetCurrentIteration();
  auto bestValue = optimizer->GetValue();

  std::cout << " Iterations    = " << numberOfIterations << std::endl;
  std::cout << " Metric value  = " << bestValue << std::endl;

  // apply transformation to moving image
  using ResampleFilterType = itk::ResampleImageFilter<ImageType, ImageType>;
  auto resampler = ResampleFilterType::New();
  resampler->SetInput(movingImage);
  resampler->SetTransform(transform);
  resampler->SetUseReferenceImage(true);
  resampler->SetReferenceImage(fixedImage);
  resampler->SetDefaultPixelValue(100);

  // don't need to cast here because I chose to output as Float32
  itk::WriteImage(resampler->GetOutput(), argv[3]);
  return EXIT_SUCCESS;
}