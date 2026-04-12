## Jacob Kitzmann - Lab 02

### Introduction
Medical image registration is a common preprocessing step for image analysis pipelines. A simple registration is required as the background for more complex Affine and non-rigid/elastic registration techniques. Further, its limited fixed parameter space allows lower computational complexity than higher-order registration transforms. The goal of this project is to create a system to register two digital phantoms (circles) together, creating a knowledge base and reproducible code for future use.

### Materials & Methods
I focused on using the lowest run-time parameters and metrics for registration, while keeping high accuracy in the final product. The final registration pipline was heavily based on the ITK Registration with Mean Squares tutorial [1]. The final pipeline included:

Registration Type - ITK Image Registration Version 4
Metric - Mean Square Error Version 4
Optimizer - Regular Step Gradient Descent Version 4
Learning Rate - 4
Minimum Step Size for Convergence - 0.001
Relaxation Factor - 0.5
Maximum Iterations - 200
Initial Fixed Image Transform - Identity
Registration Transform - Translation
Multi-Resolution Pyramid - None (one level at full resolution, not smoothed)

### Results
### Discussion
### References

[1] - https://examples.itk.org/src/registration/common/perform2dtranslationregistrationwithmeansquares/documentation
