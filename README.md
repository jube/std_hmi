# Proposal for Human-Machine Interface in the Standard Library

This is a proposal for what I would like to see in the C++ standard library regarding [human-machine interface](https://en.wikipedia.org/wiki/User_interface) (HMI). This is not a formal proposal but rather a proof of concept for something simple yet powerful that could be in the standard. If the idea gains attraction, it could be improved and become something more serious.

## Reminder

In [N3791: Lightweight Drawing Library - Objectives, Requirements, Strategies](https://isocpp.org/files/papers/n3791.html), the ISO C++ Committee gives some requirements for the starting point of a possible "lightweight drawing library":

> - Existing successful library already in wide use.
> - Modern C++, modulo naming conventions and C++11/14 features. (Dependencies hidden from users are exempt from this requirement.)
> - Extendible by third-parties. An initial library TS completed in a short time frame will likely be quite limited. That will be much more acceptable if the library is extendible by third parties.
> - Copyright or other intellectual property holders willing to meet ISO intellectual property requirements. It will also be helpful if the original developers get involved in SG work.
> - Meets Beman's challenge: "Display Hello C++ World in a window and allow the user to drag that text around inside the window with a program that is only slightly more complex that the traditional hello world program."
> - Meets Herb's challenge: "Learn the library basics and build an interesting app in four hours or less."
> - Other challenges or requirements may evolve, as long as they don't eliminate all candidates.

## Outline

The proposal contains two parts.

- a small vector and matrix library that lives in a `<geometry>` header: [design for geometry](docs/geometry.md)
- a window class with window events and a very simple renderer that lives in a `<window>` header: [design for window](docs/window.md)

Obviously `<window>` depends on `<geometry>`.

## Work in progress

For now, the implementation lives in a `hmi` namespace. This can be changed, as well as any other names (bikeshedding is allowed at the beginning, but with some arguments).

Some things are still missing, in the design or in the implementation. But the proposal can already [pass the Beman's challenge](examples/beman_s_challenge.cc). The most important missing part is the creation of any context for graphics libraries (software, Direct3D, OpenGL, Vulkan, etc).

## Implementation

The implementation relies on SDL and OpenGL ES 2 (for the renderer) and is distributed under the MIT license. Any contribution is welcomed.
