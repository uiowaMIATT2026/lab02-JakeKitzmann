Jacob Kitzmann
Partner: Partho Ghosh

### Assignment
Problem Statement: Write a program that registers two 2D images. 
The program will be used more than 1 million times to register pairs of images to be supplied in the future.

For this assignment, use two 2D images of circles.
img1.png: 30mm diameter centered at 50mm, 50mm img2.png: 60mm diameter centered at 200mm,200mm

Step 1: Write a EngineeringDesignPrinciples.md file that describes the approach you are taking. 
Step 2: Write the algorithm 
Step 3: Write a ExperimentalResults.md file that convinces 20 other people in your research 
area that your solution is trustworthy and appropriate.

### Initial Idea

Our goal is to register images together. We'll need to select and optimize some parameters.
The big one will be the metric. We want something fast, since registering two circles together
is a much simpler problem than full medical images. I'd select MSE initially, rather than something
more complex like Mattes MI.

Initially though, we'll need to create the images. I'm going to use MATLAB, since 
making a few circle images is a trivial problem there.