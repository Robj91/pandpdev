 //discovered something interesting - 
 //the hardbox value for the right and bottom hardbox are 1 less than actually written in Dink.ini, the left and top are exact.
 //E.G.. if dink is standing against a sprite's LEFT hardbox edge, he will be 1 LESS than the depth dot -= Dink.ini hardbox value.
 //      In the same sitation as above for the RIGHT hardbox edge, Dink's position is at the SAME location as depth dot -= Dink.ini hardbox value.
 //        Which means the location of the RIGHT hardbox is actually: Depth dot of sprite -= RIGHT dink.ini hardbox value -= 1.
 
 //AND.. if dink is standing against a sprite's TOP hardbox edge, he will be 1 LESS than the depth dot -= Dink.ini hardbox value.
 //      In the same sitation as above for the BOTTOM hardbox edge, Dink's position is at the SAME location as depth dot -= Dink.ini hardbox value.
 //        Which means the location of the BOTTOM hardbox is actually: Depth dot of sprite -= RIGHT dink.ini hardbox value -= 1.

//This script used to have a different purpose but I now use it for sticky push collision system
//This is now the combined HYBRID(Sticky Push) Collision main script.
//Some of these procedures aren't used anymore - they are incorporated directly into hyblim.c

void main(void)
{
 //we require 3 local variables.
 int &val1;
 int &val2;
 
 //&colsprite will store the sprite.
 int &colsprite = &save_y;
 return;
}

void hybCol(void)
{
 //PULL
 sp_custom("Tracker1", &colsprite, 0);
 sp_custom("Tracker2", &colsprite, 0);
 sp_custom("Tracker3", &colsprite, 0);
 sp_custom("Tracker4", &colsprite, 0);
 sp_custom("Tracker5", &colsprite, 0);
 sp_custom("Tracker6", &colsprite, 0); 
 sp_custom("Tracker7", &colsprite, 0);

 sp_custom("TrackerCounter", &colsprite, 0);
 
 &save_x = sp_x(&colsprite, -1);
 &save_y = sp_y(&colsprite, -1);
 //current position of left boundary
 &val1 = sp_custom("LEFT-BOX", &colsprite, -1);
 &val1 += &save_x; 
 &val2 = sp_custom("trimleft", &colsprite, -1);
 if (&val2 > 0)
  &val1 += &val2;
 sp_custom("LEFTBOX-POS", &colsprite, &val1);
 
 //current position of top boundary
 &val1 = sp_custom("TOP-BOX", &colsprite, -1);
 &val1 += &save_y; 
 &val2 = sp_custom("trimtop", &colsprite, -1);
 if (&val2 > 0)
  &val1 += &val2;
 sp_custom("TOPBOX-POS", &colsprite, &val1);
 
 //current position of right boundary
 &val1 = sp_custom("RIGHT-BOX", &colsprite, -1);
 &val1 += &save_x; 
 &val1 -= 1;
 &val2 = sp_custom("trimright", &colsprite, -1);
 if (&val2 > 0)
  &val1 -= &val2;
 sp_custom("RIGHTBOX-POS", &colsprite, &val1);

 //current position of bottom boundary
 &val1 = sp_custom("BOTTOM-BOX", &colsprite, -1);
 &val1 += &save_y; 
 &val1 -= 1;
 &val2 = sp_custom("trimbottom", &colsprite, -1);
 if (&val2 > 0)
  &val1 -= &val2;
 sp_custom("BOTTOMBOX-POS", &colsprite, &val1);

 //Vertical length of hardbox
 &save_y = sp_custom("TOPBOX-POS", &colsprite, -1);
 &val2 = sp_custom("BOTTOMBOX-POS", &colsprite, -1);
 &val2 -= &save_y;
 sp_custom("HBOX-VERT", &colsprite, &val2);
 
 //Horizontal length of hardbox
 &save_y = sp_custom("LEFTBOX-POS", &colsprite, -1);
 &val2 = sp_custom("RIGHTBOX-POS", &colsprite, -1);
 &val2 -= &save_y;
 sp_custom("HBOX-HORIZ", &colsprite, &val2);
 
 //let's set how many sprites to create along the hard box edge
 sp_custom("Trackermax", &colsprite, 6) 
 
 &val1 = sp_custom("pulldir", &colsprite, -1);
 //store dinks position
 if (&val1 == 6)
 {
  //Pulling from Right hard box boundary
  //set whether to use horizontal or vertical.
  sp_custom("HBOX-HorV", &colsprite, 1);
  //set where the first sprite should be created
  &save_x = sp_custom("RIGHTBOX-POS", &colsprite, -1);
  &save_y = sp_custom("TOPBOX-POS", &colsprite, -1);
 } 
 if (&val1 == 4)
 {
  //Pulling from Left hard box boundary
  //set whether to use horizontal or vertical.
  sp_custom("HBOX-HorV", &colsprite, 1);
  //set where the first sprite should be created
  &save_x = sp_custom("LEFTBOX-POS", &colsprite, -1);
  &save_y = sp_custom("TOPBOX-POS", &colsprite, -1);
 }
 if (&val1 == 8)
 {
  //Pulling from top hard box boundary
  //set whether to use horizontal or vertical.
  sp_custom("HBOX-HorV", &colsprite, 2);
  //set where the first sprite should be created
  &save_x = sp_custom("LEFTBOX-POS", &colsprite, -1);
  &save_y = sp_custom("TOPBOX-POS", &colsprite, -1);
 }
 if (&val1 == 2)
 {
  //Pulling from bottom hard box boundary
  //set whether to use horizontal or vertical.
  sp_custom("HBOX-HorV", &colsprite, 2);
  //set where the first sprite should be created
  &save_x = sp_custom("LEFTBOX-POS", &colsprite, -1);
  &save_y = sp_custom("BOTTOMBOX-POS", &colsprite, -1);
 } 
 
//PULL - Create collision tracker sprites that will find hardness that the hardbox will collide with
//TrackerCounter counts created sprites
//HBOX-HorV - 1 for Vertical, 2 for Horizontal
Trackers:
  &val1 = sp_custom("TrackerCounter", &colsprite, -1);
  &val1 += 1;
  &val2 = create_sprite(&save_x, &save_y, 0, 21, 1);
  sp_speed(&val2, 1000);
  sp_nodraw(&val2, 1);
  sp_nohit(&val2, 1);
  sp_que(&val2, 1000); 
    
  //make each tracker it's own custom key
  if (&val1 == 1)
  {
   sp_custom("Tracker1", &colsprite, &val2);
   sp_custom("Tracker1fix", &val2, &colsprite);
  }
  if (&val1 == 2)
  {
   sp_custom("Tracker2", &colsprite, &val2);
   sp_custom("Tracker2fix", &val2, &colsprite);
  }
  if (&val1 == 3)
  {
   sp_custom("Tracker3", &colsprite, &val2);
   sp_custom("Tracker3fix", &val2, &colsprite);
  }
  if (&val1 == 4)
  {
   sp_custom("Tracker4", &colsprite, &val2);
   sp_custom("Tracker4fix", &val2, &colsprite);
  }
  if (&val1 == 5)
  {
   sp_custom("Tracker5", &colsprite, &val2);
   sp_custom("Tracker5fix", &val2, &colsprite);
  }
  if (&val1 == 6)
  {
   sp_custom("Tracker6", &colsprite, &val2);
   sp_custom("Tracker6fix", &val2, &colsprite);
  }
  if (&val1 == 7)
  {
   sp_custom("Tracker7", &colsprite, &val2);
   sp_custom("Tracker7fix", &val2, &colsprite);
  }
  
  //store the sprite creation counter 
  sp_custom("TrackerCounter", &colsprite, &val1); 
  
  //get the max sprites we should be creating
  &val2 = sp_custom("Trackermax", &colsprite, -1);
   
  if (&val1 < &val2)
  {
   &val1 = sp_custom("HBOX-HorV", &colsprite, -1);
   if (&val1 == 1)
   {
    &val2 = sp_custom("HBOX-VERT", &colsprite, -1);
    &val2 /= 6;
    if (&val2 > 0)
     &save_y += &val2;
     
    if (&val2 == 0)
    {
     &val2 = sp_custom("HBOX-VERT", &colsprite, -1);
     &val2 = math_mod(&val2, 6);
     //Hardbox is less than 6 pixels long, set Trackermax to the number of pixels
     sp_custom("Trackermax", &colsprite, &val2);
     &save_y += 1;
    }    
   }
   if (&val1 == 2)
   {
    &val2 = sp_custom("HBOX-HORIZ", &colsprite, -1); 
    &val2 /= 6;
    if (&val2 > 0)
     &save_x += &val2;
    
    if (&val2 == 0)
    {
     &val2 = sp_custom("HBOX-VERT", &colsprite, -1);
     &val2 = math_mod(&val2, 6);
     //Hardbox is less than 6 pixels long, set Trackermax to the number of pixels
     sp_custom("Trackermax", &colsprite, &val1);
     &save_x += 1;
    } 
   }  
   goto Trackers;
  }
  if (&val1 == &val2)
  {
   //We have created 6 Trackers.
   //Let's see if there was a remaining gap we need to fil, and if so create a 7th tracker.
   &val1 = sp_custom("HBOX-HorV", &colsprite, -1);
   if (&val1 == 1)
   {
    &val2 = sp_custom("HBOX-VERT", &colsprite, -1);
    &val1 = math_mod(&val2, 6);
    if (&val1 > 0)
    {
     &save_y = sp_custom("BOTTOMBOX-POS", &colsprite, -1);
     goto Trackers;
    }
   }
   if (&val1 == 2)
   {
    &val2 = sp_custom("HBOX-HORIZ", &colsprite, -1);
    &val1 = math_mod(&val2, 6);
    if (&val1 > 0)
    {
     &save_x = sp_custom("RIGHTBOX-POS", &colsprite, -1);
     goto Trackers;
    }
   }     
  }

 //PUSH
 sp_custom("TrackerPhis1", &colsprite, 0);
 sp_custom("TrackerPhis2", &colsprite, 0);
 sp_custom("TrackerPhis3", &colsprite, 0);
 sp_custom("TrackerPhis4", &colsprite, 0);
 sp_custom("TrackerPhis5", &colsprite, 0);
 sp_custom("TrackerPhis6", &colsprite, 0); 
 sp_custom("TrackerPhis7", &colsprite, 0);

 sp_custom("TrackerPhisCounter", &colsprite, 0);
 
 &save_x = sp_x(&colsprite, -1);
 &save_y = sp_y(&colsprite, -1);
 //current position of left boundary
 &val1 = sp_custom("LEFT-BOX", &colsprite, -1);
 &val1 += &save_x; 
 &val2 = sp_custom("trimleft", &colsprite, -1);
 if (&val2 > 0)
  &val1 += &val2;
 sp_custom("LEFTBOX-POS", &colsprite, &val1);
 
 //current position of top boundary
 &val1 = sp_custom("TOP-BOX", &colsprite, -1);
 &val1 += &save_y; 
 &val2 = sp_custom("trimtop", &colsprite, -1);
 if (&val2 > 0)
  &val1 += &val2;
 sp_custom("TOPBOX-POS", &colsprite, &val1);
 
 //current position of right boundary
 &val1 = sp_custom("RIGHT-BOX", &colsprite, -1);
 &val1 += &save_x; 
 &val1 -= 1;
 &val2 = sp_custom("trimright", &colsprite, -1);
 if (&val2 > 0)
  &val1 -= &val2;
 sp_custom("RIGHTBOX-POS", &colsprite, &val1);

 //current position of bottom boundary
 &val1 = sp_custom("BOTTOM-BOX", &colsprite, -1);
 &val1 += &save_y; 
 &val1 -= 1;
 &val2 = sp_custom("trimbottom", &colsprite, -1);
 if (&val2 > 0)
  &val1 -= &val2;
 sp_custom("BOTTOMBOX-POS", &colsprite, &val1);

 //Vertical length of hardbox
 &save_y = sp_custom("TOPBOX-POS", &colsprite, -1);
 &val2 = sp_custom("BOTTOMBOX-POS", &colsprite, -1);
 &val2 -= &save_y;
 sp_custom("HBOX-VERT", &colsprite, &val2);
 
 //Horizontal length of hardbox
 &save_y = sp_custom("LEFTBOX-POS", &colsprite, -1);
 &val2 = sp_custom("RIGHTBOX-POS", &colsprite, -1);
 &val2 -= &save_y;
 sp_custom("HBOX-HORIZ", &colsprite, &val2);
 
 //let's set how many sprites to create along the hard box edge
 sp_custom("TrackerPhismax", &colsprite, 6)
 
 &val1 = sp_custom("pushdir", &colsprite, -1);
 //store dinks position
 if (&val1 == 4)
 {
  //Pushing from Right hard box boundary
  //set whether to use horizontal or vertical.
  sp_custom("HBOX-HorV", &colsprite, 1);
  //set where the first sprite should be created
  &save_x = sp_custom("LEFTBOX-POS", &colsprite, -1);
  &save_y = sp_custom("TOPBOX-POS", &colsprite, -1);
 }
 if (&val1 == 6)
 {
  //Pushing from Left hard box boundary
  //set whether to use horizontal or vertical.
  sp_custom("HBOX-HorV", &colsprite, 1);
  //set where the first sprite should be created
  &save_x = sp_custom("RIGHTBOX-POS", &colsprite, -1);
  &save_y = sp_custom("TOPBOX-POS", &colsprite, -1);
 }
  
 if (&val1 == 2)
 {
  //Pushing from top hard box boundary
  //set whether to use horizontal or vertical.
  sp_custom("HBOX-HorV", &colsprite, 2);
  //set where the first sprite should be created
  &save_x = sp_custom("LEFTBOX-POS", &colsprite, -1);
  &save_y = sp_custom("BOTTOMBOX-POS", &colsprite, -1);
 }
  
 if (&val1 == 8)
 {
  //Pushing from bottom hard box boundary
  //set whether to use horizontal or vertical.
  sp_custom("HBOX-HorV", &colsprite, 2);
  //set where the first sprite should be created
  &save_x = sp_custom("LEFTBOX-POS", &colsprite, -1);
  &save_y = sp_custom("TOPBOX-POS", &colsprite, -1);
 }

//Create tracker sprites which will find hardness that the hardbox will collide with
//TrackerPhisCounter counts created sprites
//HBOX-HorV - 1 for Vertical, 2 for Horizontal
TrackerPhiss:
  &val1 = sp_custom("TrackerPhisCounter", &colsprite, -1);
  &val1 += 1;
  &val2 = create_sprite(&save_x, &save_y, 0, 21, 1);
  sp_speed(&val2, 1000);
  sp_nodraw(&val2, 1);
  sp_nohit(&val2, 1);
    
  //make each TrackerPhis it's own custom key
  if (&val1 == 1)
  {
   sp_custom("TrackerPhis1", &colsprite, &val2);
   sp_custom("TrackerPhis1fix", &val2, &colsprite);
  }
  if (&val1 == 2)
  {
   sp_custom("TrackerPhis2", &colsprite, &val2);
   sp_custom("TrackerPhis2fix", &val2, &colsprite);
  }
  if (&val1 == 3)
  {
   sp_custom("TrackerPhis3", &colsprite, &val2);
   sp_custom("TrackerPhis3fix", &val2, &colsprite);
  }
  if (&val1 == 4)
  {
   sp_custom("TrackerPhis4", &colsprite, &val2);
   sp_custom("TrackerPhis4fix", &val2, &colsprite);
  }
  if (&val1 == 5)
  {
   sp_custom("TrackerPhis5", &colsprite, &val2);
   sp_custom("TrackerPhis5fix", &val2, &colsprite);
  }
  if (&val1 == 6)
  {
   sp_custom("TrackerPhis6", &colsprite, &val2);
   sp_custom("TrackerPhis6fix", &val2, &colsprite);
  }
  if (&val1 == 7)
  {
   sp_custom("TrackerPhis7", &colsprite, &val2);
   sp_custom("TrackerPhis7fix", &val2, &colsprite);
  }
  
  //store the sprite creation counter 
  sp_custom("TrackerPhisCounter", &colsprite, &val1); 
  
  //get the max sprites we should be creating
  &val2 = sp_custom("TrackerPhismax", &colsprite, -1);
   
  if (&val1 < &val2)
  {
   &val1 = sp_custom("HBOX-HorV", &colsprite, -1);
   if (&val1 == 1)
   {
    &val2 = sp_custom("HBOX-VERT", &colsprite, -1);
    &val2 /= 6;
    if (&val2 > 0)
     &save_y += &val2;
     
    if (&val2 == 0)
    {
     &val2 = sp_custom("HBOX-VERT", &colsprite, -1);
     &val2 = math_mod(&val2, 6);
     //Hardbox is less than 6 pixels long, set TrackerPhismax to the number of pixels
     sp_custom("TrackerPhismax", &colsprite, &val2);
     &save_y += 1;
    }    
   }
   if (&val1 == 2)
   {
    &val2 = sp_custom("HBOX-HORIZ", &colsprite, -1); 
    &val2 /= 6;
    if (&val2 > 0)
     &save_x += &val2;
    
    if (&val2 == 0)
    {
     &val2 = sp_custom("HBOX-VERT", &colsprite, -1);
     &val1 = math_mod(&val2, 6);
     //Hardbox is less than 6 pixels long, set TrackerPhismax to the number of pixels
     sp_custom("TrackerPhismax", &colsprite, &val1);
     &save_x += 1;
    } 
   }  
   goto TrackerPhiss;
  }
  if (&val1 == &val2)
  {
   //We have created 6 TrackerPhiss.
   //Let's see if there was a remaining gap we need to fill, and if so create a 7th TrackerPhis.
   &val1 = sp_custom("HBOX-HorV", &colsprite, -1);
   if (&val1 == 1)
   {
    &val2 = sp_custom("HBOX-VERT", &colsprite, -1);
    &val1 = math_mod(&val2, 6);
    if (&val1 > 0)
    {
     &save_y = sp_custom("BOTTOMBOX-POS", &colsprite, -1);
     goto TrackerPhiss;
    }
   }
   if (&val1 == 2)
   {
    &val2 = sp_custom("HBOX-HORIZ", &colsprite, -1);
    &val1 = math_mod(&val2, 6);
    if (&val1 > 0)
    {
     &save_x = sp_custom("RIGHTBOX-POS", &colsprite, -1);
     goto TrackerPhiss;
    }
   }     
  }

 return;
}

void store(void)
{
//PULL - Store the x or y of the created trackers before they move, depending on direction object will be moving
 &save_y = sp_custom("move-axis", &colsprite, -1);
 &save_x = sp_custom("Tracker1", &colsprite, -1);
 if (&save_x > 0)
 {
  if (&save_y == 2) 
   &save_x = sp_y(&save_x, -1);
   
  if (&save_y == 1)
   &save_x = sp_x(&save_x, -1);
   
  sp_custom("TrackerLimit1", &colsprite, &save_x);
 }
 
 &save_x = sp_custom("Tracker2", &colsprite, -1);
 if (&save_x > 0)
 {
  if (&save_y == 2) 
   &save_x = sp_y(&save_x, -1);
   
  if (&save_y == 1)
   &save_x = sp_x(&save_x, -1);
   
  sp_custom("TrackerLimit2", &colsprite, &save_x);
 }
 
 &save_x = sp_custom("Tracker3", &colsprite, -1);
 if (&save_x > 0)
 {
  if (&save_y == 2) 
   &save_x = sp_y(&save_x, -1);
   
  if (&save_y == 1)
   &save_x = sp_x(&save_x, -1);
   
  sp_custom("TrackerLimit3", &colsprite, &save_x);
 }
  
 &save_x = sp_custom("Tracker4", &colsprite, -1);
 if (&save_x > 0)
 {
  if (&save_y == 2) 
   &save_x = sp_y(&save_x, -1);
   
  if (&save_y == 1)
   &save_x = sp_x(&save_x, -1);
   
  sp_custom("TrackerLimit4", &colsprite, &save_x);
 }
  
 &save_x = sp_custom("Tracker5", &colsprite, -1);
 if (&save_x > 0)
 {
  if (&save_y == 2) 
   &save_x = sp_y(&save_x, -1);
   
  if (&save_y == 1)
   &save_x = sp_x(&save_x, -1);
   
  sp_custom("TrackerLimit5", &colsprite, &save_x);
 }
 
 &save_x = sp_custom("Tracker6", &colsprite, -1);
 if (&save_x > 0)
 {
  if (&save_y == 2) 
   &save_x = sp_y(&save_x, -1);
   
  if (&save_y == 1)
   &save_x = sp_x(&save_x, -1);
   
  sp_custom("TrackerLimit6", &colsprite, &save_x);
 }
 
  &save_x = sp_custom("Tracker7", &colsprite, -1);
 if (&save_x > 0)
 {
  if (&save_y == 2) 
   &save_x = sp_y(&save_x, -1);
   
  if (&save_y == 1)
   &save_x = sp_x(&save_x, -1);
   
  sp_custom("TrackerLimit7", &colsprite, &save_x);
 }

//PUSH - store the x or y of the tracker sprites before they move, depending on the direction the object will  be moving
 &save_y = sp_custom("move-axis", &colsprite, -1);
 &save_x = sp_custom("TrackerPhis1", &colsprite, -1);
 if (&save_x > 0)
 {
  if (&save_y == 2) 
   &save_x = sp_y(&save_x, -1);
   
  if (&save_y == 1)
   &save_x = sp_x(&save_x, -1);
   
  sp_custom("TrackerPhisLimit1", &colsprite, &save_x);
 }
 
 &save_x = sp_custom("TrackerPhis2", &colsprite, -1);
 if (&save_x > 0)
 {
  if (&save_y == 2) 
   &save_x = sp_y(&save_x, -1);
   
  if (&save_y == 1)
   &save_x = sp_x(&save_x, -1);
   
  sp_custom("TrackerPhisLimit2", &colsprite, &save_x);
 }
 
 &save_x = sp_custom("TrackerPhis3", &colsprite, -1);
 if (&save_x > 0)
 {
  if (&save_y == 2) 
   &save_x = sp_y(&save_x, -1);
   
  if (&save_y == 1)
   &save_x = sp_x(&save_x, -1);
   
  sp_custom("TrackerPhisLimit3", &colsprite, &save_x);
 }
  
 &save_x = sp_custom("TrackerPhis4", &colsprite, -1);
 if (&save_x > 0)
 {
  if (&save_y == 2) 
   &save_x = sp_y(&save_x, -1);
   
  if (&save_y == 1)
   &save_x = sp_x(&save_x, -1);
   
  sp_custom("TrackerPhisLimit4", &colsprite, &save_x);
 }
  
 &save_x = sp_custom("TrackerPhis5", &colsprite, -1);
 if (&save_x > 0)
 {
  if (&save_y == 2) 
   &save_x = sp_y(&save_x, -1);
   
  if (&save_y == 1)
   &save_x = sp_x(&save_x, -1);
   
  sp_custom("TrackerPhisLimit5", &colsprite, &save_x);
 }
 
 &save_x = sp_custom("TrackerPhis6", &colsprite, -1);
 if (&save_x > 0)
 {
  if (&save_y == 2) 
   &save_x = sp_y(&save_x, -1);
   
  if (&save_y == 1)
   &save_x = sp_x(&save_x, -1);
   
  sp_custom("TrackerPhisLimit6", &colsprite, &save_x);
 }
 
 &save_x = sp_custom("TrackerPhis7", &colsprite, -1);
 if (&save_x > 0)
 {
  if (&save_y == 2) 
   &save_x = sp_y(&save_x, -1);
   
  if (&save_y == 1)
   &save_x = sp_x(&save_x, -1);
   
  sp_custom("TrackerPhisLimit7", &colsprite, &save_x);
 }

 return;
}

void move(void)
{
//Move already created trackers in teh direction necessary to find hardness
 //&save_y = position. (Stored in phislim.c before poking this proc) 
 
 &val1 = sp_custom("pulldir", &colsprite, -1);
 &save_x = sp_custom("Tracker1", &colsprite, -1);
 if (&save_x > 0)
  move(&save_x, &val1, &save_y, 0); 
 
 &save_x = sp_custom("Tracker2", &colsprite, -1); 
 if (&save_x > 0)
  move(&save_x, &val1, &save_y, 0);
 
 &save_x = sp_custom("Tracker3", &colsprite, -1);
 if (&save_x > 0)
  move(&save_x, &val1, &save_y, 0);
 
 &save_x = sp_custom("Tracker4", &colsprite, -1);
 if (&save_x > 0)
  move(&save_x, &val1, &save_y, 0);

 &save_x = sp_custom("Tracker5", &colsprite, -1);
 if (&save_x > 0)
  move(&save_x, &val1, &save_y, 0);
 
 &save_x = sp_custom("Tracker6", &colsprite, -1);
 if (&save_x > 0)
  move(&save_x, &val1, &save_y, 0);
 
 &save_x = sp_custom("Tracker7", &colsprite, -1);
 if (&save_x > 0)
  move(&save_x, &val1, &save_y, 0);
 
 return;
}

void movephis(void)
{
//Move already created tracker sprites
 //&save_y = position. (Stored in phislim.c before poking this proc)

 &val1 = sp_custom("pushdir", &colsprite, -1);
 &save_x = sp_custom("TrackerPhis1", &colsprite, -1);
 if (&save_x > 0)
  move(&save_x, &val1, &save_y, 0); 
 
 &save_x = sp_custom("TrackerPhis2", &colsprite, -1); 
 if (&save_x > 0)
  move(&save_x, &val1, &save_y, 0);
 
 &save_x = sp_custom("TrackerPhis3", &colsprite, -1);
 if (&save_x > 0)
  move(&save_x, &val1, &save_y, 0);
 
 &save_x = sp_custom("TrackerPhis4", &colsprite, -1);
 if (&save_x > 0)
  move(&save_x, &val1, &save_y, 0);

 &save_x = sp_custom("TrackerPhis5", &colsprite, -1);
 if (&save_x > 0)
  move(&save_x, &val1, &save_y, 0);
 
 &save_x = sp_custom("TrackerPhis6", &colsprite, -1);
 if (&save_x > 0)
  move(&save_x, &val1, &save_y, 0);
 
 &save_x = sp_custom("TrackerPhis7", &colsprite, -1);
 if (&save_x > 0)
  move(&save_x, &val1, &save_y, 0);

 return;
}

void done(void)
{
//If trackers have found hardness, set custom keys to be able to identify this later
//Tracker1
 &save_x = sp_custom("Tracker1", &colsprite, -1);
 if (&save_x > 0)
 {
  &save_x = sp_custom("done", &save_x, -1);
  if (&save_x <= 0)
   &save_y = 0;
 }
//Tracker2
 &save_x = sp_custom("Tracker2", &colsprite, -1);
 if (&save_x > 0)
 {
  &save_x = sp_custom("done", &save_x, -1);
  if (&save_x <= 0)
   &save_y = 0;
 }
//Tracker3
 &save_x = sp_custom("Tracker3", &colsprite, -1);
 if (&save_x > 0)
 {
  &save_x = sp_custom("done", &save_x, -1);
  if (&save_x <= 0)
   &save_y = 0;
 }
//Tracker4
 &save_x = sp_custom("Tracker4", &colsprite, -1);
 if (&save_x > 0)
 {
  &save_x = sp_custom("done", &save_x, -1);
  if (&save_x <= 0)
   &save_y = 0;
 }
//Tracker5
 &save_x = sp_custom("Tracker5", &colsprite, -1);
 if (&save_x > 0)
 {
  &save_x = sp_custom("done", &save_x, -1);
  if (&save_x <= 0)
   &save_y = 0;
 }
//Tracker6
 &save_x = sp_custom("Tracker6", &colsprite, -1);
 if (&save_x > 0)
 {
  &save_x = sp_custom("done", &save_x, -1);
  if (&save_x <= 0)
   &save_y = 0;
 }
//Tracker7
 &save_x = sp_custom("Tracker7", &colsprite, -1);
 if (&save_x > 0)
 {
  &save_x = sp_custom("done", &save_x, -1);
  if (&save_x <= 0)
   &save_y = 0;
 }

//If the tracker sprites have found hardness, let the calling script know.
//TrackerPhis1
 &save_x = sp_custom("TrackerPhis1", &colsprite, -1);
 if (&save_x > 0)
 {
  &save_x = sp_custom("done", &save_x, -1);
  if (&save_x <= 0)
   &save_y = 0;
 }
//TrackerPhis2
 &save_x = sp_custom("TrackerPhis2", &colsprite, -1);
 if (&save_x > 0)
 {
  &save_x = sp_custom("done", &save_x, -1);
  if (&save_x <= 0)
   &save_y = 0;
 }
//TrackerPhis3
 &save_x = sp_custom("TrackerPhis3", &colsprite, -1);
 if (&save_x > 0)
 {
  &save_x = sp_custom("done", &save_x, -1);
  if (&save_x <= 0)
   &save_y = 0;
 }
//TrackerPhis4
 &save_x = sp_custom("TrackerPhis4", &colsprite, -1);
 if (&save_x > 0)
 {
  &save_x = sp_custom("done", &save_x, -1);
  if (&save_x <= 0)
   &save_y = 0;
 }
//TrackerPhis5
 &save_x = sp_custom("TrackerPhis5", &colsprite, -1);
 if (&save_x > 0)
 {
  &save_x = sp_custom("done", &save_x, -1);
  if (&save_x <= 0)
   &save_y = 0;
 }
//TrackerPhis6
 &save_x = sp_custom("TrackerPhis6", &colsprite, -1);
 if (&save_x > 0)
 {
  &save_x = sp_custom("done", &save_x, -1);
  if (&save_x <= 0)
   &save_y = 0;
 }
//TrackerPhis7
 &save_x = sp_custom("TrackerPhis7", &colsprite, -1);
 if (&save_x > 0)
 {
  &save_x = sp_custom("done", &save_x, -1);
  if (&save_x <= 0)
   &save_y = 0;
 }
 
 if (&save_y == 0)
  return(1);
 else
  return(0);
  
 return;
}

void kill(void)
{
//kill off collision tracker sprites
//Tracker1
 &save_x = sp_custom("Tracker1", &colsprite, -1);
 &save_y = sp_custom("Tracker1fix", &save_x, -1);
 if (&save_y == &colsprite)
  sp_active(&save_x, 0);
  
//Tracker2
 &save_x = sp_custom("Tracker2", &colsprite, -1);
 &save_y = sp_custom("Tracker2fix", &save_x, -1);
 if (&save_y == &colsprite)
  sp_active(&save_x, 0);
  
//Tracker3
 &save_x = sp_custom("Tracker3", &colsprite, -1);
 &save_y = sp_custom("Tracker3fix", &save_x, -1);
 if (&save_y == &colsprite)
  sp_active(&save_x, 0); 
  
//Tracker4
 &save_x = sp_custom("Tracker4", &colsprite, -1);
 &save_y = sp_custom("Tracker4fix", &save_x, -1);
 if (&save_y == &colsprite)
  sp_active(&save_x, 0);
  
//Tracker5
 &save_x = sp_custom("Tracker5", &colsprite, -1);
 &save_y = sp_custom("Tracker5fix", &save_x, -1);
 if (&save_y == &colsprite)
  sp_active(&save_x, 0);
  
//Tracker6
 &save_x = sp_custom("Tracker6", &colsprite, -1);
 &save_y = sp_custom("Tracker6fix", &save_x, -1);
 if (&save_y == &colsprite)
  sp_active(&save_x, 0);
  
//Tracker7
 &save_x = sp_custom("Tracker7", &colsprite, -1);
 &save_y = sp_custom("Tracker7fix", &save_x, -1);
 if (&save_y == &colsprite)
  sp_active(&save_x, 0);

//kill off collision TrackerPhis sprites
//TrackerPhis1
 &save_x = sp_custom("TrackerPhis1", &colsprite, -1);
 &save_y = sp_custom("TrackerPhis1fix", &save_x, -1);
 if (&save_y == &colsprite)
  sp_active(&save_x, 0);
   
//TrackerPhis2
 &save_x = sp_custom("TrackerPhis2", &colsprite, -1);
 &save_y = sp_custom("TrackerPhis2fix", &save_x, -1);
 if (&save_y == &colsprite)
  sp_active(&save_x, 0); 
  
//TrackerPhis3
 &save_x = sp_custom("TrackerPhis3", &colsprite, -1);
 &save_y = sp_custom("TrackerPhis3fix", &save_x, -1);
 if (&save_y == &colsprite)
  sp_active(&save_x, 0); 
  
//TrackerPhis4
 &save_x = sp_custom("TrackerPhis4", &colsprite, -1);
 &save_y = sp_custom("TrackerPhis4fix", &save_x, -1);
 if (&save_y == &colsprite)
  sp_active(&save_x, 0); 
  
//TrackerPhis5
 &save_x = sp_custom("TrackerPhis5", &colsprite, -1);
 &save_y = sp_custom("TrackerPhis5fix", &save_x, -1);
 if (&save_y == &colsprite)
  sp_active(&save_x, 0); 
  
//TrackerPhis6
 &save_x = sp_custom("TrackerPhis6", &colsprite, -1);
 &save_y = sp_custom("TrackerPhis6fix", &save_x, -1);
 if (&save_y == &colsprite)
  sp_active(&save_x, 0);
  
//TrackerPhis7
 &save_x = sp_custom("TrackerPhis7", &colsprite, -1);
 &save_y = sp_custom("TrackerPhis7fix", &save_x, -1);
 if (&save_y == &colsprite)
  sp_active(&save_x, 0); 

 return;
}

void KillColPull(void)
{
 kill_this_task();
}