Jacob Kitzmann
Initial Lab Partner: Partho Ghosh

### AI/Web Use Disclosure
This is a test of knowledge up to this point of the semester. Absolutely no AI tools were used in this assignment.
Resources used:

- SimpleITK documentation https://github.com/SimpleITK/SimpleITK
- SimpleITKNotebooks https://github.com/InsightSoftwareConsortium/SimpleITK-Notebooks.git
- Pixi documentation https://pixi.prefix.dev/latest/
- ITK Documentation
  - Doxygen -> Transforms (no actual page but args listed)
  - https://examples.itk.org/src/registration/common/perform2dtranslationregistrationwithmeansquares/documentation
  - ^^ the big one
- https://discourse.itk.org/t/to-v4-or-not-to-v4/7459

### Assignment
Problem Statement: Write a program that registers two 2D images. 
The program will be used more than 1 million times to register pairs of images to be supplied in the future.

For this assignment, use two 2D images of circles.
img1.png: 30mm diameter centered at 50mm, 50mm img2.png: 60mm diameter centered at 200mm,200mm

Step 1: Write a EngineeringDesignPrinciples.md file that describes the approach you are taking. 
Step 2: Write the algorithm 
Step 3: Write a ExperimentalResults.md file that convinces 20 other people in your research 
area that your solution is trustworthy and appropriate.

### Engineering Design principles

- Create test circle images using SimpleITK
  - pixi environment with lock file
  - 1 mm isotropic spacing
  - identity cosine matrix
  - Float32 data type
  - (0,0) origin
  - Use TransformPhysicalPointToIndex to calculate pixel coordinate of center of circle
  - For each pixel of the image, use TransformIndexToPhysicalPoint to calculate the Euclidean distance to our center point
  - If a point's Euclidean distance <= desired radius, we should make it a 1, otherwise we don't edit as default is zero
  - Output images as NIfTI to preserve metadata

- Registration
    - Mean Squared Error Metric
    - Full sampling (small images so high accuracy won't be expensive)
    - Similarity2D Transform 
    - Gradient Descent optimizer
      - LR TBD
    - Linear Interpolation for points
    - Linear Interpolation for resample filter once we get transform
    - Read images as Float32, as that's what the interpolator will want from my limited registration experience
    - Use v4 registration, as that is recommended in the beginner discourse
 
  ### Initial Results
 
    - <img width="781" height="412" alt="Screenshot 2026-04-10 at 8 47 37 AM" src="https://github.com/user-attachments/assets/59da589d-6249-4fe6-ae57-b9f12320794f" />

Well that didn't work. I skipped the last few steps of the tutorial, so that's the first place I'll look.

First thing I'll do is use a translation transform, and see if that keeps the circle from warping into the weird square shape.

Oh -- sick. The translation transform seems to have registered them perfectly. They look almost perfectly aligned in my check_circles.ipynb,
and have a RMSE of ~ 0.05.

### Registered images below.

<img width="1038" height="512" alt="Screenshot 2026-04-11 at 2 16 20 PM" src="https://github.com/user-attachments/assets/0c6b6e88-cfa6-41b8-b3d6-9ec3e9962a5b" />

### Difference image between images below.

<img width="466" height="365" alt="Screenshot 2026-04-11 at 2 18 02 PM" src="https://github.com/user-attachments/assets/1f4a75ed-0438-4219-bcd3-00584babad83" />


