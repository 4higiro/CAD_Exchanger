Hello, I offer a solution to the task in three versions (containing additional points of the task).
In solutions v2 and v3, the dynamic link library is located in the "lib" folder. 
The "curves" folder contains the project files for compiling the dynamic link library.
When starting the application, you need to copy the lib/curves.dll file to the folder with the application executable file. All source files were compiled using Visual C++.<br>
v1 - without dll without openmp<br>
v2 - with dll without openmp<br>
v3 - with dll with openmp<br>
Initially, a version with a graphics module using OpenGL was intended, since I wanted to do a little more than was required, which is why elements of linear algebra remained in the source code, but I didn’t have time (I was dealing with new material).
<hr>
<h2>Curves</h2>
There are three types of curves in total, each of which exists in three-dimensional space (I added a linear operator on my own that allows you to apply linear transformations to curves, for example, rotate these curves. The linear operator is constant with respect to the parameter t, which means it can be applied before the differential operator).<br>
All curves implement a common interface that allows you to get the coordinates of a point on the curve and the coordinates of its first derivative. The constructors of all curves are hidden and the curve builder is responsible for creating the object, which allows you to create any curve in different ways (including with random parameters).
<hr>
