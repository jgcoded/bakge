
Bindable
========

Bindable objects are stateful -- they must be bound before being used, and more often than not must be unbound to prevent unwanted behavior. Bind and unbind calls are quite frequent, and thus lend themselves very well to inlining in many cases.


Using Bindables
===============

The use of bindable objects is as follows. Not all Bindables REQUIRE unbinding, but some do.

![Using a Bindable](http://www.cs.csubak.edu/~pholden/bakge/bind_process.png)
