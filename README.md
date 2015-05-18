Discrete Parameter-less Population Pyramid
==

To compile you will need C++11.  We use gcc version 4.8.3 for our complilation.

Our build system uses Makefiles to build.  You can compile the release version
by changing directory to Release and calling "make".

All of the source code is available in the 'src' directory.

To run an experiment, call the executable with command line arguments for configuration.
This will run the default test configuration:

Release/DP3 config/default.cfg

The command line accepts any number of configuration files and configuration flags given
in the form "-key value" where key is the name of the option to change and value is the
value to change it to.  Arguments override in last given order.  For example:

Release/DP3 config/default.cfg -problem ValueMax

This line will use the default configuration and optimize on the ValueMax problem

Also, see main.cpp for implementation related details.
