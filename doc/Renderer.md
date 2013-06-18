
Renderer
========

Renderers are classes which are used to draw objects type Drawable. They are bindable objects, due to the stateful of the OpenGL calls they make when used.

The engine class will have to manage drawing so that Bind and Unbind calls are minimized, and all objects in the scene or GUI are drawn with the proper renderer. Internally, Renderers will bind shaders, set up the viewport, perspective transform, color, properties and attributes (GL_DEPTH_TEST, GL_LIGHTING, etc) and more. When using Bakge, you should never have to directly call any functions from OpenGL or any external library used by Bakge.


Scene Rendering Process
=======================

Ideally, the use renderers from within the engine class should be:

![Rendering Process](http://www.cs.csubak.edu/~pholden/bakge/info_renderering.png)
  

