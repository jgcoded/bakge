Bakge
=====

Bakersfield Game Engine is a cross-platform framework for developing 2D and 3D graphical applications. Its goals are to 1) simplify programmatic approaches to game and engine development through its SDK, which provides a simple, natural-feeling class- and interface-centered API for writing games or game engines in C++ and 2) provide a game development kit (GDK) with a tool-chain and engine designed with a feature set robust enough to produce great content yet simple enough to be easily approached by developers new to Lua, Bakge or both.


A Simple Sample
===============

### C++

```cpp
int main(int argc, char* argv[])
{
    if(bakge::Init(argc, argv) == BGE_FAILURE)
        return -1;

    bakge::Window* Win = bakge::Window::Create(800, 600, 0);

    if(Win == NULL)
        return -1;

    glClearColor(1, 0, 0, 1);

    while(1) {
        bakge::Window::PollEvents();

        if(Win->IsOpen() == false)
            break;

        glClear(GL_COLOR_BUFFER_BIT);
        Win->SwapBuffers();
    }

    delete Win;

    bakge::Deinit();

    return 0;
}
```

### GDK & Lua
```lua
local c = nil
local p = nil

function bakge.onStart(argc, argv)
    c = bakge.graphics.shape.cube.create()
    p = bakge.graphics.pawn.create(0, 0, 0)
end

function bakge.onUpdate(dt)
    p:rotate(0, dt, 0)
end

function bakge.onRender()
    p:bind()
    c:draw()
    p:unbind()
end
```


Contribute
==========

To build and contribute to the source code of Bakge, you will need:

 - CMake version 2.6 or greater
 - C++ compiler (gcc, MSVC, clang)
 - git
