-----------------
--Push and Pull--
-----------------
Author: Robj
Special thanks to : Bluedy for mapping, title screen, and testing.
Compatibile with: All Versions. (FreeDink and 1.08 recommended)
FreeDink offers the best performance. 1.08 is fine too, with minor performance issues. Dink Smallwood HD is terrible, it's compatible, but just terrible.
Please credit if used.

----------------------------------------------

Contents of this README file:
Section 1: What is this Dmod?

Section 2: Implementation

Section 3: How to Use

Section 4: Updating from an older version of Push and Pull.

Section 5: Names of LOCAL variables used (make sure you don't have any globals with the same name in main.c or it will break them!)

Section 6: Things that are nice to know, but not essential.

-----------------------------------------------

**********************************
**SECTION 1 - What is this Dmod?**
**********************************

What is this Dmod? 
This is a demonstration Dmod for my Development file: Push and Pull.

Push and Pull is a rebuild of the push system, so Dink can push things smoothly, and move with the objects. Dink can also Pull objects as well now.

This project took me close to 2 months to complete, working for an hour+ most days, due to trial and error, or complete restarting when one method didn't work, and lots of debugging.
In it's current state, it works as intended. If you find any major (or minor) bugs that affect the gameplay please let me know via the DinkNetwork.

Featuring a new "sticky push" system, grab hold of an object by walking into and move it around.

If an object is not pushable, dinks push animation will not trigger anymore.

Optional other method that can be activated in "settings", in the "escape" menu (disables sticky push and enables hold 'z' to pull mode).

While there is A LOT of DinkC scripting involved to get this system working, I have made it as easy as possible to implement into your dmod.
Everything is streamlined and called with externals, you've just gotta do a few things first, and then you can start making your sprites moveable.


******************************
**SECTION 2 - Implementation**
******************************

Below you will find the steps to implement this sytem and use it.
It is recommended to watch the following youtube video tutorials to learn how to use this properly, with optional extras as well:
https://www.youtube.com/playlist?list=PL23KcNyjVv-CkWS2A32cXEXleuHUby04b

Implement this system - 4 simple steps.

If are using any older version of push and pull and simply wish top update to the latest version, please scroll down to SECTION 4, for a simple step-by-step guide on how to do this.

----------------------------
--STEP 1: Copy the scripts--
----------------------------
In the story folder of PushandPull you will find a folder named "Push and Pull Scripts".
Copy all the scripts from this folder into your dmod.


------------------------------------------------
--STEP 2: Edit Main.c--
------------------------------------------------
Scroll down until you find the "kill_this_task();" line, and paste these lines directly on the line ABOVE it:
    script_attach(1000);
    spawn("OnLoad");

Please also make sure these 2 lines are somewhere in your Main.c. These variables technically aren’t required and some skeletons don’t declare them by default:
make_global_int(“&save_x”, 0);
make_global_int(“&save_y”, 0);

If they are not in your main.c, add them, you can add them after all the other “make_global_int” lines.

----------------------------------
--STEP 3: Make a Sprite Moveable--
----------------------------------
Once all of the above is done, this is simple for most sprites.
Simply attach Sprite.c to any sprite in game, and it will become moveable. Without any change, it works as is, however, it is recommended to use it as a skeleton script, make copies and rename it for each sprite, and optimise the script specifically for that sprite (see script comments, and watch video tutorial linked earlier in this file). Using this script vanilla won't be as good as optimising it for your sprite, basically.
Be careful where you place your own scripting in relation to where the external lines are in sprite.c, for customised scripts. Just follow what the comments say in sprite.c, I've made it very clear where to place your scripting you want to add to each procedure.
For examples of custom scripts done properly see: heart.c(animated non-collectible, pushable heart),and Maze-R.c (Rock that activates a secret when moved to a certain spot on the screen) in the "Source (commented)" folder in PushandPull.


*************************
**SECTION 3: How to Use**
*************************
Use sprite.c as your "skeleton" moveable object script. 
Make a copy of it, and attach it to a sprite, that sprite will become moveable without any edits.
Then I would recommend you read through the comments and edit it however you wish.
If any, the one addition I suggest you do is to pass the hardbox values of your sprite (look near the bottom of the main procedure for the external line - it is explained there. That will improve performance a lot and REMOVE the possibility of a bug occuring).

If you would like Dink to still "push" against ALL objects (even unmoveable ones), simple open "onload.c" and remove the "push_active(0);" line. This will also allow you to work with a hybrid of the old push system and my push and pull system. Push procedures will work, and also the above sprite.c script will work (but don't try to mix them in one script, I'm not sure what that would produce).

In an attempt to not turn this into a behemoth of a readme doc, and due to laziness, I will again point you to my video tutorials I linked earlier on implemenatition and usage:
https://www.youtube.com/playlist?list=PL23KcNyjVv-CkWS2A32cXEXleuHUby04b

If you have already implemented and would just like to see the how to use, click the above link and watch part 2, 3 and 4.


Also, if they are unclear, there is also an in-game tutorial, which clearly explains the push and pull system in detail. You just need to solve the puzzles to find the tutorial section ;)


**************************************************************
**SECTION 4: Updating from an older version of Push and Pull**
**************************************************************

Simply look for the version that you have installed and follow the instructions from that section to update to the latest Push and Pull.

You only need to follow the instructions from the ONE section below that matches your version and you will be all up to date.

====================
==Update from 2.04==
====================
Update from Push and Pull version 2.04 to the LATEST version by replacing the scipt below:
- "phisend.d"
Copy it from the "story >> scripts" folder, from the LATEST version of Push and Pull , and paste it into your Dmods story folder and overwrite the old script.


====================
==Update from 2.03==
====================

Update from Push and Pull version 2.03 to the LATEST version by replacing the scipts below:
- "pulllim.d"
- "hyblim.d"
- "phisend.d"
- "escape.c"
Copy them from the "story >> scripts" folder, from the LATEST version of Push and Pull , and paste them your Dmods story folder and overwrite the old script.

NOTE: If you don't want to completely overwrite escape.c because you have your own modified version, just copy the relevant parts that have changed.
      The changes are to the following escape menu options: "Help" > "How to: Push and Pull Objects". Copy that part from escape.c and replace.
      OR just overwrite the whole script if you haven't made any changes you want to keep.


====================
==Update from 2.02==
====================
Update from Push and Pull version 2.02 to the LATEST version by replacing the scipts below:
- "vcheck.c"
- "pulllim.d"
- "hyblim.d"
- "phisend.d"
- "escape.c"
Copy them from the "story >> scripts" folder, from the LATEST version of Push and Pull , and paste them your Dmods story folder and overwrite the old script.

NOTE: If you don't want to completely overwrite escape.c because you have your own modified version, just copy the relevant parts that have changed.
      The changes are to the following escape menu options: "Help" > "How to: Push and Pull Objects". Copy that part from escape.c and replace.
      OR just overwrite the whole script if you haven't made any changes you want to keep.


====================
==Update from 2.01==
====================
I have made a separate video tutorial on how to update from an 2.01 to the latest version.
You can follow the instructions in this video to update from 2.01 to the LATEST version of Push and Pull.
Please watch follow the instructions in the video:
https://www.youtube.com/watch?v=UGQvMX6Tlb4


- The below note only applies if you had Version Checker installed in yor old Push and Pull version that you are updating from.

NOTE: In the video I forgot mention that the "but1" folder inside the graphics is no longer needed, and as such the corresponding load_sequence_now line in dink.ini which loads sequence 192 is not needed either. Leaving them in won't affect anything though. But feel free to remove them if you can be bothered or need an extra sequence slot.


====================
==Update from 1.xx==
====================
Version 1.xx of Push and Pull was scripted completely different and was very buggy.
If you want to update form a 1.xx version of Push and Pull to a 2.xx version, please start from scratch. Delete version 1.xx first by following the implementation instructions in the "readme readme readme.txt" file IN REVERSE, and then install the latest version.


***************************************************************************************************************************************
**SECTION 5: Names of LOCAL variables used (make sure you don't have any globals with the same name in main.c or it will break them!)**
***************************************************************************************************************************************
Below I have listed all the names of the LOCAL variables used in this system, so you can make sure you haven't got a global declared with the same name - Locals can not have a global with the same name, or they won't work, basically it will break this whole system, so check the list against your globals. If you are implementing this into a new dmod, don't worry about this, just make sure you don't declare any globals variables with the following names.
&crap, &txt, &val1, &val2, &hupsprite, &hybsprite, &pupsprite, &mco, &store


**************************************************************
**SECTION 6: Things that are nice to know, but not essential**
**************************************************************

==1==
Some scripts are compressed to *.d format, these are scirpts you don't need to touch, and compressing them improved performance in 1.08.
To see the commented *.c version of these scripts, look in the Source folder, which is inside the Story folder.

==2==
The scripting that makes this system possible was created by Robj. Bluedy also helped with mapping and testing.

==3==
I'm a firm believer in not using too many variables so I tried to use them sparingly. Unfortunately, a system like this is bound to use a few.
If you have 1 moveable sprite on a screen, it should always use less than 6 local variables at any time, sometimes just 2 or 3, sometimes none. 
Obviously if you have more than 1 pushable sprite on a screen, you can multiply the above estimate by the number of moveable sprites oyu have on the one screen.
It honestly doesn't use that many, and shouldn't affect your total local+global limit, unlesss you are overusing global variables in ways you shouldn't be.

==4==
What's with the Dink.ini lines we needed to add at the top of the dink.ini file?
We need to load Dink's push sequences into base sequence 520, which will then be overwritten further on in the dink.ini with the animation of dink's pig feeding (dink throwing seed).
This is because at a certain point in this system of scripts, a duplicate copy of push is loaded into 520, and 520 is used as dinks idle sequence. This is is necessary for detection of when the player stops while pulling, to make him static, and not walking on the spot.
Since this is the case, the sequence with the most frames (which is push) must be laoded first, then we can let it be overwritten with the pig feed sequence later. That prevents a glitch in 1.08 where some other sprites will appear as dink's push graphic.