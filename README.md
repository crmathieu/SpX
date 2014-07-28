SpX
===

OG2 Launch code

To run: "make 1" for default, or "make 2" for coriolis

default.c and default.h are simulated from the reference frame of an observer standing on the Earth - i.e they do NOT take into account the Coriolis effect. This is handy for any boost stage trajectories.

For second stage trajectories (like trying to achieve orbit), coriolis.c and coriolis.h give the physical result.

There's a lot of duplicate code between default and coriolis so I need to clean them up. Please don't critique the code. I know it's messy. I wrote it as I went so it's not planned. Also it's not commented yet so you might get a bit lost, although it's mostly intuitive.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

The only thing I want to improve is smoother rotations. As it stands, the pitch-kick is a sudden chage in angle, as are all the course corrections (of which OG2 second stage has a lot - see the angles() function). 

Also I'll translate this to C++ at some point in time. Object-oriented programming would be much smoother for this kind of project.
