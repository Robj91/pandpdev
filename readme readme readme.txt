-----------------
--Push and Pull--
-----------------
Author: Robj
Special thanks to : Bluedy for mapping, title screen, and testing.

Please see the google doc for everything you need to know to implement push and pull in your dmod (or update from a previous verison of push and pull). Also includes tutorials on everything that you can configure withing the push and pull system using procedures, external functions, and setting “sp_custom” keys on move-able sprites:

https://docs.google.com/document/d/1IWCfk-2qVIgIfDJe4CrUAA57Jh1KV6zs4udo6OxCzlY/edit?usp=sharing 

**********************
**What is this Dmod?**
**********************

What is this Dmod? 
This is a demonstration Dmod for my Development file: Push and Pull.

Push and Pull is a rebuild of the push system, so Dink can push things smoothly, and move with the objects. Dink can also Pull objects as well now.

This project took me months to complete. If you find any major (or minor) bugs please let me know via the DinkNetwork.

Featuring a new "sticky push" system, grab hold of an object by walking into it and move it around.

While there is A LOT of DinkC scripting involved to get this system working, I have made it as easy as possible to implement into your dmod.
Everything is streamlined and called with “external” from one script.


***************************************************
**Things that are nice to know, but not essential**
***************************************************

==1==
To see the commented *.c versions of .d scripts(compressed for file size and a slight performance boost), look in the Source folder, which is inside the Story folder.

==2==
The scripting that makes this system possible was created by Robj. Bluedy also helped with mapping and testing.

==3==
I'm a firm believer in not using too many variables so I tried to use them sparingly. Unfortunately, a system like this is bound to use a few.
If you have 1 move-able sprite on a screen, it should always use less than 6 local variables at any time, sometimes just 2 or 3, sometimes none, depending on what Dink is currently doing. 
Obviously if you have more than 1 pushable sprite on a screen, you can multiply the above estimate by the number of moveable sprites you have on the one screen.
It honestly doesn't use that many, and shouldn't affect your total local+global limit, unlesss you are over-using global variables in ways you shouldn't be.