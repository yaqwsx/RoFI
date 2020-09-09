# RoFI simulator

## Prerequisites

The development is currently in gazebo9. To install it, see
[the official documentation](http://gazebosim.org/tutorials?cat=install).
Be sure to install both `gazebo9` and `libgazebo9-dev` if you want to be able to
compile the project.

The used LwIP library requires `doxygen` for compilation.

### Ubuntu/Debian
For `gazebo9` on APT-based systems you can run:

```
apt install apt install gazebo9 libgazebo9-dev doxygen
```

## Compilation

Just run `make` in the simulation directory. It will create a build directory
and invoke CMake. The compiled binaries and Gazebo plugins are in the `build`
directory.

## How To Use It

The simulation consists of two parts. The server and the client (or clients.)

For usage help, run `make help`.

### Server

To use RoFI models and plugins, correct Gazebo paths have to be set up.
To ease this step, you can run `make run` which will set them
and runs gazebo server (with world defaulting to `empty.world`).
Alternatively you can run
`./setGazeboVariables.sh gazebo [GAZEBO_ARGS] <world_file>`.
If you want to see messages from gazebo, make sure to use `--verbose`.
For more details about arguments for gazebo run `gazebo -h`.

In Gazebo you can add models and control the simulation. Read more about the
Gazebo GUI in [the official
documentation](http://gazebosim.org/tutorials?tut=guided_b2&cat=).

### Clients

To connect to RoFI modules in the simulation, you should use a RoFI program
compiled with provided library.

The aim is to use one client for each module in the simulation.

#### To compile a program

You should link library `rofiHal` to your program and include the header
`rofi_hal.hpp` in your source file (it's located in directory `tools`).

Take a look at the examples in directory `examples` (and at `CMakeLists.txt`
in an example's directory).

### Examples and demos

To try an example, you have to run the server and the client.

To run the client of an example, run:

```
build/examples/<example_directory_name>/<example_name>
```

To run the server, if there is a file with `.world` extension, run:

```
./runGazebo.sh --verbose examples/<example_directory_name>/<world_name>
```

Otherwise run an empty server and then place a `universalModule` model into
the simulation. You can run an empty gazebo server by running `make run`.


## Development Guide

### Gazebo simulation

As the simulator is based on Gazebo, follow the [Gazebo
tutorials](http://gazebosim.org/tutorials). Especially, [the control plugin
tutorial](http://gazebosim.org/tutorials?tut=guided_i5) is a good starting point
for our purposes.

Another usefull tutorials:
- [Custom messages](http://gazebosim.org/tutorials?tut=custom_messages&cat=transport)
- [SDF format specification](http://sdformat.org/spec)