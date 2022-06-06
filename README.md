
Here lies the framework provided for task1 of the 2020 courses ["Computer Graphics"](https://online.tugraz.at/tug_online/wbLv.wbShowLVDetail?pStpSpNr=228157&pSpracheNr=2&pMUISuche=FALSE) [1]
and ["Computer Graphics and Vision"](https://online.tugraz.at/tug_online/wbLv.wbShowLVDetail?pStpSpNr=228159&pSpracheNr=2&pMUISuche=FALSE) [1]
 at [Graz University of Technology](https://www.tugraz.at/home/) [3].

To build the framework, the following tools are needed

  * a C++ toolchain with C++17 support (e.g. GCC 8.x+, Visual Studio 2017)
  * [CMake 3.10+](https://cmake.org/) [5]

CMake scripts to generate a build system can be found in `build/cmake`. The CMake scripts can be controlled by two additional options `BUILD_TASK1A` and `BUILD_TASK1B` that enable/disable the generation of build files for the individual tasks (both options default to `ON`).

Compiled applications will be placed in a subdirectory `./bin/` within the CMake binary directory.

## Windows

For working on Windows, we recommend to use the [Visual Studio 2017](https://www.visualstudio.com/) [4] IDE (Community Edition is sufficient). Note that the framework requires Version 15.5 and up.

Open the CMake 3.10 GUI application and point the CMake source path to the location of your `build/cmake` directory. Set the second path to point to the location where you would like your Visual Studio project files to be placed, e.g., `build/vs2017`.

![CMake Screenshot](doc/images/cmake_win_1.png)

Press [Configure] and select the Visual Studio 2017 generator

![CMake Screenshot](doc/images/cmake_win_2.png)

At this point, you can optionally edit the configuration and afterwards press [Generate].

![CMake Screenshot](doc/images/cmake_win_3.png)

Finally, open the generated Visual Studio 2017 solution that should now be found in the build directory specified earlier. Do not forget to set the correct startup project:

![CMake Screenshot](doc/images/vs_set_startup_project_marked.png)

To set up the working directory and commandline arguments for launching your application from within the Visual Studio debugger, go to Project Properties > Debugging:

![CMake Screenshot](doc/images/vs_set_working_dir_marked.png)


## Ubuntu

The default compilers currently shipping with Ubuntu do not offer full support for some of the C++17 features needed by the framework. A more up-to-date C++ toolchain such as g++ 8.x must be installed:

```bash
sudo apt-get install gcc-8 g++-8
```

On older versions of Ubuntu (e.g. Ubuntu 16.04), g++ 8.x is not available from default distribution repositories. You may be able to get a working build from other sources such as, e.g., the [`ubuntu-toolchain-r/test`](https://launchpad.net/~ubuntu-toolchain-r/+archive/ubuntu/test) [6] repository:

```bash
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt-get install gcc-8 g++-8
```

Assuming you have installed [CMake 3.10](https://cmake.org/) [5] or newer as well as a suitable C++ toolchain, a build system can then be generated. First, switch into the directory where you want to the build files to be placed, for example:

```bash
cd /path/to/repository/build
mkdir blub
cd blub
```

Then, call cmake to generate the build system:

```bash
cmake -DCMAKE_C_COMPILER=gcc-8 -DCMAKE_CXX_COMPILER=g++-8 ../cmake/
```

The path to the `build/cmake` directory containing the CMake scripts (here `../cmake/`) has to be passed as the last argument to the `cmake` command. To use a compiler other than the system default, specify the `CMAKE_C_COMPILER` and `CMAKE_CXX_COMPILER` variables via the commandline as shown in the example above.

> Instead of using the commandline, you can install the `cmake-qt-gui` package to get a GUI application for managing the CMake generation process in essentially the same way as described in the Windows setup guide above. Use the "Specify native compilers" option in the generator selection dialogue to change the set of compilers to be used.

Once the build files have been generated, the project can be compiled using

```bash
make task1a
```


## pluto.tugraz.at

If you choose to work on [PLUTO](https://www.pluto.tugraz.at/) [7], suitable versions of CMake and GCC can be found in `/opt/cmake_3.12.2/` and `/opt/gcc820/`. Helper scripts are available to set up the environment to use these versions by default:

```bash
source /opt/gcc820/env-gcc-8.1.0.sh
source /opt/cmake_3.12.2/cmake-3.12.2-envs.sh
```

For convenience, the framework includes `setup_pluto.sh` to further simplify this process to:

```bash
source setup_pluto.sh
```

Once the default environment has been configured like this, you do *not* have to explicitly specify the compilers to CMake anymore. Note that you will have to reconfigure the environment on every login.

## Making a Submission

To make a submission, you need to create the ``submission'' branch and push it into your repository.
The following commands create a submission branch out the current branch's state and push it to remote. 

```bash
git checkout -b submission
git push origin submission
```
Now you will see the submission branch in your gitlab web interface. Double check whether it is your final state.
If you are not familiar with git, you'll find a lot of helpful tutorials online. For example this one has a nice 
visualization helping to understand the core concepts: https://learngitbranching.js.org/.

## Test system

If you push to the ``submission`` branch, the server will automatically run a simple test that verifies that your solution compiles. 
The result of this test can be seen in the web interface on the left side by clicking `"CI/CD"` and looking at the resulting pipelines. 
The pipelines will show the compile log and the "test" stage will produce an output image for the `x-wing` input case.



[1] https://online.tugraz.at/tug_online/wbLv.wbShowLVDetail?pStpSpNr=228157&pSpracheNr=2&pMUISuche=FALSE
[2] https://online.tugraz.at/tug_online/wbLv.wbShowLVDetail?pStpSpNr=228159&pSpracheNr=2&pMUISuche=FALSE
[3] https://www.tugraz.at/home/
[4] https://www.visualstudio.com/
[5] https://cmake.org/
[6] https://launchpad.net/~ubuntu-toolchain-r/+archive/ubuntu/test
[7] https://www.pluto.tugraz.at/
