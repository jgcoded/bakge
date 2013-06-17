Engine
======

Engine classes should focused on controlling interactions between various components like the renderers, scene manager and scene objects, event handlers, and more. Engines will house the main loop of the application, from which game world updates are polled, and render calls dispatched. A good example of Engine behavior is rendering the scene.


Legend
======

For following diagrams, the empty diamond arrow denotes a container containing the object pointed to.

![Box contains stuff](http://www.cs.csubak.edu/~pholden/bakge/info_contains.png)


Engine Structure
================

Typically an engine class will have the following components. Each component handles the "how" for its various purpose, while letting the engine determine the 5 W's: who, what, where, when and why.

![Engine Makeup](http://www.cs.csubak.edu/~pholden/bakge/engine_makeup.png)


Engine Types
============

Different types of engines can determine the W's different ways: A scripted engine will deploy events to a script language interpreter, which uses binded Bakge API to determine what to do. Or an engine could simply house its logic within the C++ class, making it a bit faster, but a bit less flexible. A combination of the two can be used also, if only some parts of the engine need frequent modification while others need a bit more speed.
