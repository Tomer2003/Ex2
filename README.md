
### part 1

in this project, We designed the matrix class with a class that delegates the functions in the library of the so and in addition we added an exceptions for errors.
We implemented the rule of 5, and test the new methods.

- class class that delegates the functions - ClassMatrix
- exceptions for errors - MatrixExceptions

### part 2

in this project, we read the information from a BMPfile, saved it in a BMP-object and implemented 2 functions:

- Rotate the function 90 degrees clockwise
- transform a colorful photo into a black and white.

the way we read the information from the given BMP-file was:
first, we read and saved the information of the header and the DIB-header.
then we decided either to create an 8 bits BitMap or a 24 bits BitMap.
and then we read and saved the rest of the information like the color pallette (if it was an 8 bits photo) and the bitMap-array.

we rely on the way BMP-files look like and on the information from the headers(like where does the bitMap array begin).

if we had to save the information from another kind of file we would create a class that will be holding the information of the file and at the beginning only initialize the basic members which will give us the needed information for the rest of the file reading.

but generally, the way we would do that will be very similar to the way we did that in this project, we'll only have to change the position we start to read from in every part of the file and the number of bytes we read each time.