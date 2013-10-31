Hello, Bakge
============

In this tutorial we'll go through how to fork, clone build Bakge on Windows and Linux (we'll be using Ubuntu, but feel free to build on whatever flavor or distro tickles your fancy). Then we'll write create a simple "hello, world"-esque program using Bakge. If you experience any errors, let me know so I can fix them and update the tutorials!

Some important notes:

 - Bakge requires OpenGL version 2.1 or greater. To check your version on Linux, open a terminal and run ` $ glxinfo | grep version`. There isn't a quick and easy way to check your OpenGL version on Windows, so just run one of the unit tests. If you get an error, try updating your graphics drivers.
 - Bakge uses shaders for all rendering. Shaders, shaders, shaders. Immediate mode calls such as glVertex3f and glColor3f will likely not work when used in tandem with various Bakge graphics objects like the Pawn or Rectangle.
 - So far Bakge has only been built and tested on Ubuntu 12.x and Windows 7 (using Visual Studio 2010). If you can get your hands on older/different platforms (calling all virtual machine enthusiasts!), build and run the test suite and see if you can patch up any issues.
 - CSUB students: Bakge builds, but does not run on sleipnir. I'll see if I can get our system admin to install the latest Mesa GL implementation so we can test on it, but it's probably best if you run it on your personal machine anyways.

## Windows

What you'll need:

 - [CMake 2.6+](http://www.cmake.org/cmake/resources/software.html)
 - [git](http://git-scm.com/)
 - Visual Studio (I use 2010 but previous versions should work just fine)
 - Basic know-how for building a Visual Studio project with libraries.
 - A [GitHub](http://github.com) account

### 1) Fork Bakge

 - Log in to your GitHub account
 - Go to the [palistov/bakge](https://github.com/palistov/bakge) page
 - Click 'Fork' at the top right of the page.

### 2) Clone your fork to your local machine

 - Open Git Bash
 - `cd` into the directory where you will clone your repository
 - ` $ git clone https://github.com/your_username/bakge`
 - If you don't want to enter your password each time you push to your remove,
   read about [setting up SSH keys for GitHub](https://help.github.com/articles/generating-ssh-keys).
 - `cd bakge`

### 3) Build Bakge

 - Open CMake GUI
 - Set the 'Source' directory to the path of your repository.
 - Set the 'Build' directory. I suggest making it a subdirectory named 'build'.
 - Review the available options. Most of the time you won't need to configure anything
 - Click 'Configure' at the bottom.
 - Complete the first-time setup.
 - Wait for external libraries to download.
 - Make sure no options are highlighted red. If any are, click 'Configure'.
 - Once configuration is complete, click 'Generate'.
 - Open BAKGE.sln in Visual Studio.
 - Right-click the project 'bakge' and click 'Build'. Note we'll use a Debug configuration for the entirety of this tutorial.
 - Feel free to build and run any of the test programs.

### 4) Build the rest of the SDK

 - Open BAKGE.sln in Visual Studio.
 - Right click the project 'build_sdk' and click 'Build'.

### 5) Create your own project

 - Close BAKGE.sln and make a new project. We'll call ours 'HelloBakge' for now.
 - Copy the contents of the 'bakge/sdk' into the 'HelloBakge' project directory.
 - Configure your project to use 'bakge/sdk/include' as an additional include directory.
 - Create a new source file in your project called 'main.cpp'. Copy this code into it:

   ```cpp
   #include <bakge/Bakge.h>
   #pragma comment(lib, "lib/Debug/bakge.lib")

   int main(int argc, char* argv[])
   {
       if(bakge::Init(argc, argv) != BGE_SUCCESS) {
           return -1;
       }

       bakge::Log("Hello, Bakge!\n");

       bakge::Deinit();

       return 0;
   }
   ```

 - Build and run your program. Observe and fix any errors.
 - If you get a return code of -1, open 'bakge.log' (you might have to dig around in your directories for it).
 - If you're sure 'bakge.log' doesn't exist, you're likely getting a PhysicsFS error. Let me know about this!
 - If all is well, you should see a return code of 0. Open 'bakge.log' to see the log output.
