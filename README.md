# The Automatic Vasospasm Detection Application

## Introduction
The Automatic Vasospasm Detection Application (or Algorithm, depending on the
usage), AVDA, is an application to objectively detect the presence of vasospasms
based on comparisons of parameters extracted from transcranial doppler audio.

## Setup
AVDA is intended to be compiled on machines running Linux, though it could
likely be adapter for other environments. It must be downloaded from GitHub.com
and compiled locally. To do this, navigate to the directory in which AVDA should
be placed, then execute the following commands

	git clone https://github.com/sawbg/avda
	cd avda
	make

Sucessfully cloning, compilation, and execution of AVDA requires up-to-date
versions of the following executables:

* git
* make
* gcc (4.9)
* arecord

## FAQ

* **Why was this project developed?** This project was developed as a course 
project by two gradute students at the University of Alabama at Birmingham
School of Engineering, Nicholas Nolan and Andrew Wisner.

* **Is AVDA an active project?** Though it is not planned to develop AVDA
further in the near future, it is hoped that the algorithm discovered and
implemented can be used and built upon by researchers to fully automate the
detection of vasospasms.

* **AVDA is returning unusually low or high parameters. Why might this be?** In
  development, this occured when the mic-in volume was set too high. It is
likely in this senario that clipping is happening or that the signal (or a
strong enough signal) has no been received.

* **How will AVDA be affected by the machine uprising?** The University
  supercomputer, Cheaha, has assured us that AVDA will not be needed after the
uprising occures.

* **What about more specific questions?** Questions relating to AVDA not
covered in this FAQ may be sent to the AVDA team via awisner94@gmail.com.
