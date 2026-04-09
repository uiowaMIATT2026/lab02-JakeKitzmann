Jacob Kitzmann
Initial Lab Partner: Partho Ghosh

### AI/Web Use Disclosure
This is a test of knowledge up to this point of the semester. Absolutely no AI tools were used in this assignment.
Resources used:

- SimpleITK documentation https://github.com/SimpleITK/SimpleITK
- SimpleITKNotebooks https://github.com/InsightSoftwareConsortium/SimpleITK-Notebooks.git
- Pixi documentation https://pixi.prefix.dev/latest/
- ITK Documentation
  - Doxygen -> Transforms

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

