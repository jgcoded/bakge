Hello, Bakge
============

In this tutorial we'll go through how to fork, clone build Bakge on Windows and Linux (we'll be using Ubuntu, but feel free to build on whatever flavor or distro tickles your fancy). Then we'll write create a simple "hello, world"-esque program using Bakge.


## Windows

What you'll need:

 - [CMake 2.6+](http://www.cmake.org/cmake/resources/software.html)
 - [git](http://git-scm.com/)
 - Visual Studio (I use 2010 but previous versions should work just fine)
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
 - Click 'Configure' at the bottom. Complete the first-time setup.
 - Make sure no options are highlighted red. If any are, click 'Configure'.
 - Once configuration is complete, click 'Generate'.
 - Open BAKGE.sln in Visual Studio.
 - Right-click the project 'bakge' and click 'Build'.
 - Feel free to build and run any of the test programs.
