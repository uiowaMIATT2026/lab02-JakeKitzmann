## Jacob Kitzmann - Lab 02

### Introduction
Medical image registration is a common preprocessing step for image analysis pipelines. A simple registration is required as the background for more complex Affine and non-rigid/elastic registration techniques. Further, its limited fixed parameter space allows lower computational complexity than higher-order registration transforms. The goal of this project is to create a system to register two digital phantoms (circles) together, creating a knowledge base and reproducible code for future use.

### Materials & Methods
I focused on using the lowest run-time parameters and metrics for registration, while keeping high accuracy in the final product. The final registration pipline was heavily based on the ITK Registration with Mean Squares tutorial [1]. The final pipeline included:

-  Registration Type - ITK Image Registration Version 4
-  Metric - Mean Square Error Version 4
-  Optimizer - Regular Step Gradient Descent Version 4
-  Learning Rate - 4
-  Minimum Step Size for Convergence - 0.001
-  Relaxation Factor - 0.5
-  Maximum Iterations - 200
-  Initial Fixed Image Transform - Identity
-  Registration Transform - Translation
-  Multi-Resolution Pyramid - None (one level at full resolution, not smoothed)

### Results

<img width="743" height="341" alt="Screenshot 2026-04-12 at 12 19 28 PM" src="https://github.com/user-attachments/assets/9a1ed7fa-1f36-4517-8705-57ebde8d9363" />

I originally tried to use a Similarity2D transform. This was ineffective. I beieved that a Translation transform would not give me the scaling needed to map the lower radius circle to the higher radius circle. While this provided a small mean square error metric value, the registration was completely incorrect. 

<img width="938" height="443" alt="Screenshot 2026-04-12 at 12 21 18 PM" src="https://github.com/user-attachments/assets/5f4a757b-821f-40cb-9b3e-f31e7a294a6c" />

Switching to a translation trasform with identical methods otherwise, I was able to register the images together. The images mapped well onto each other, with a mean square error of about 0.003. The difference images between the registered first circle and the original second circle is shown below, it can be noted that the difference of intensity is virtually zero at every index location.

<img width="437" height="359" alt="Screenshot 2026-04-12 at 12 22 43 PM" src="https://github.com/user-attachments/assets/5880f949-a9b8-4a1f-86d3-ad7f3267f423" />


### Discussion
### References

[1] - https://examples.itk.org/src/registration/common/perform2dtranslationregistrationwithmeansquares/documentation
