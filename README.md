# Time Warp Gameplay Mechanic C++ Version[^1]
[^1]: This is a part of a templated game jam

## Controls Default:
- **Left Mouse: Shoot a sphere trace that freezes an object in time**
- **Right Mouse: Unfreezes all objects**
- **Scroll Wheel Down: Begins reversing time on *ALL* frozen objects. Incrementally increasing reversing speed the more you scroll.**
- **Scroll Wheel Up: Slows down and eventually freezes all reversing objects in time.**

## Info:
The mechanic in its current form functions using a combination of a custom time warp component and time warp interface on an object.
This method was used as it allows for the mechanics functionality to be changed and altered more easily. Ie for a character to be affected appropriately
the component's functionality may need to be expanded and the implementation of the interface on the character would need to be adjusted accordingly.

## C++ Version Notes:
I highly encourage you to use the C++ version for the game jam. If you are unfamiliar with source control of C++ projects in UE5
then there are a few steps to take after you download the files.

1. Generate VS files by right-clicking the .uproject file and selecting generate project files.
2. Once generated open up the VS file and do a build of the project.

If you do those two steps **before** opening up the .uproject then you shouldn't have any issues.
It is also worth noting that there are comments within the C++ code that help to explain the process of how the mechanic functions within C++.
Once again, you **do not** have to leave all of this as is. Feel free to alter any of the logic behind the mechanic.
What's important is the mechanic itself and how you use it in your game.
Its up to you and/or your team to decide if it is necessary or beneficial to change the logic of how the mechanic works.
