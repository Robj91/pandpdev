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
 sp_custom("PPTracker1", &colsprite, 0);
 sp_custom("PPTracker2", &colsprite, 0);
 sp_custom("PPTracker3", &colsprite, 0);
 sp_custom("PPTracker4", &colsprite, 0);
 sp_custom("PPTracker5", &colsprite, 0);
 sp_custom("PPTracker6", &colsprite, 0); 
 sp_custom("PPTracker7", &colsprite, 0);

 sp_custom("PPTrackerCounter", &colsprite, 0);
 
 &save_x = sp_x(&colsprite, -1);
 &save_y = sp_y(&colsprite, -1);
 //current position of left boundary
 &val1 = sp_custom("PPLEFT-BOX", &colsprite, -1);
 &val1 += &save_x; 
 &val2 = sp_custom("trimleft", &colsprite, -1);
 if (&val2 > 0)
  &val1 += &val2;
 sp_custom("PPLEFTBOX-POS", &colsprite, &val1);
 
 //current position of top boundary
 &val1 = sp_custom("PPTOP-BOX", &colsprite, -1);
 &val1 += &save_y; 
 &val2 = sp_custom("trimtop", &colsprite, -1);
 if (&val2 > 0)
  &val1 += &val2;
 sp_custom("PPTOPBOX-POS", &colsprite, &val1);
 
 //current position of right boundary
 &val1 = sp_custom("PPRIGHT-BOX", &colsprite, -1);
 &val1 += &save_x; 
 &val1 -= 1;
 &val2 = sp_custom("trimright", &colsprite, -1);
 if (&val2 > 0)
  &val1 -= &val2;
 sp_custom("PPRIGHTBOX-POS", &colsprite, &val1);

 //current position of bottom boundary
 &val1 = sp_custom("PPBOTTOM-BOX", &colsprite, -1);
 &val1 += &save_y; 
 &val1 -= 1;
 &val2 = sp_custom("trimbottom", &colsprite, -1);
 if (&val2 > 0)
  &val1 -= &val2;
 sp_custom("PPBOTTOMBOX-POS", &colsprite, &val1);

 //Vertical length of hardbox
 &save_y = sp_custom("PPTOPBOX-POS", &colsprite, -1);
 &val2 = sp_custom("PPBOTTOMBOX-POS", &colsprite, -1);
 &val2 -= &save_y;
 sp_custom("PPHBOX-VERT", &colsprite, &val2);
 
 //Horizontal length of hardbox
 &save_y = sp_custom("PPLEFTBOX-POS", &colsprite, -1);
 &val2 = sp_custom("PPRIGHTBOX-POS", &colsprite, -1);
 &val2 -= &save_y;
 sp_custom("PPHBOX-HORIZ", &colsprite, &val2);
 
 //let's set how many sprites to create along the hard box edge
 sp_custom("PPTrackermax", &colsprite, 6) 
 
 &val1 = sp_custom("pulldir", &colsprite, -1);
 //store dinks position
 if (&val1 == 6)
 {
  //Pulling from Right hard box boundary
  //set whether to use horizontal or vertical.
  sp_custom("PPHBOX-HorV", &colsprite, 1);
  //set where the first sprite should be created
  &save_x = sp_custom("PPRIGHTBOX-POS", &colsprite, -1);
  &save_y = sp_custom("PPTOPBOX-POS", &colsprite, -1);
 } 
 if (&val1 == 4)
 {
  //Pulling from Left hard box boundary
  //set whether to use horizontal or vertical.
  sp_custom("PPHBOX-HorV", &colsprite, 1);
  //set where the first sprite should be created
  &save_x = sp_custom("PPLEFTBOX-POS", &colsprite, -1);
  &save_y = sp_custom("PPTOPBOX-POS", &colsprite, -1);
 }
 if (&val1 == 8)
 {
  //Pulling from top hard box boundary
  //set whether to use horizontal or vertical.
  sp_custom("PPHBOX-HorV", &colsprite, 2);
  //set where the first sprite should be created
  &save_x = sp_custom("PPLEFTBOX-POS", &colsprite, -1);
  &save_y = sp_custom("PPTOPBOX-POS", &colsprite, -1);
 }
 if (&val1 == 2)
 {
  //Pulling from bottom hard box boundary
  //set whether to use horizontal or vertical.
  sp_custom("PPHBOX-HorV", &colsprite, 2);
  //set where the first sprite should be created
  &save_x = sp_custom("PPLEFTBOX-POS", &colsprite, -1);
  &save_y = sp_custom("PPBOTTOMBOX-POS", &colsprite, -1);
 } 
 
//PULL - Create collision tracker sprites that will find hardness that the hardbox will collide with
//PPTrackerCounter counts created sprites
//PPHBOX-HorV - 1 for Vertical, 2 for Horizontal
Trackers:
  &val1 = sp_custom("PPTrackerCounter", &colsprite, -1);
  &val1 += 1;
  &val2 = create_sprite(&save_x, &save_y, 0, 21, 1);
  sp_speed(&val2, 1000);
  sp_nodraw(&val2, 1);
  sp_nohit(&val2, 1);
  sp_que(&val2, 1000); 
    
  //make each tracker it's own custom key
  if (&val1 == 1)
  {
   sp_custom("PPTracker1", &colsprite, &val2);
   sp_custom("PPTracker1fix", &val2, &colsprite);
  }
  if (&val1 == 2)
  {
   sp_custom("PPTracker2", &colsprite, &val2);
   sp_custom("PPTracker2fix", &val2, &colsprite);
  }
  if (&val1 == 3)
  {
   sp_custom("PPTracker3", &colsprite, &val2);
   sp_custom("PPTracker3fix", &val2, &colsprite);
  }
  if (&val1 == 4)
  {
   sp_custom("PPTracker4", &colsprite, &val2);
   sp_custom("PPTracker4fix", &val2, &colsprite);
  }
  if (&val1 == 5)
  {
   sp_custom("PPTracker5", &colsprite, &val2);
   sp_custom("PPTracker5fix", &val2, &colsprite);
  }
  if (&val1 == 6)
  {
   sp_custom("PPTracker6", &colsprite, &val2);
   sp_custom("PPTracker6fix", &val2, &colsprite);
  }
  if (&val1 == 7)
  {
   sp_custom("PPTracker7", &colsprite, &val2);
   sp_custom("PPTracker7fix", &val2, &colsprite);
  }
  
  //store the sprite creation counter 
  sp_custom("PPTrackerCounter", &colsprite, &val1); 
  
  //get the max sprites we should be creating
  &val2 = sp_custom("PPTrackermax", &colsprite, -1);
   
  if (&val1 < &val2)
  {
   &val1 = sp_custom("PPHBOX-HorV", &colsprite, -1);
   if (&val1 == 1)
   {
    &val2 = sp_custom("PPHBOX-VERT", &colsprite, -1);
    &val2 /= 6;
    if (&val2 > 0)
     &save_y += &val2;
     
    if (&val2 == 0)
    {
     &val2 = sp_custom("PPHBOX-VERT", &colsprite, -1);
     &val2 = math_mod(&val2, 6);
     //Hardbox is less than 6 pixels long, set PPTrackermax to the number of pixels
     sp_custom("PPTrackermax", &colsprite, &val2);
     &save_y += 1;
    }    
   }
   if (&val1 == 2)
   {
    &val2 = sp_custom("PPHBOX-HORIZ", &colsprite, -1); 
    &val2 /= 6;
    if (&val2 > 0)
     &save_x += &val2;
    
    if (&val2 == 0)
    {
     &val2 = sp_custom("PPHBOX-VERT", &colsprite, -1);
     &val2 = math_mod(&val2, 6);
     //Hardbox is less than 6 pixels long, set PPTrackermax to the number of pixels
     sp_custom("PPTrackermax", &colsprite, &val1);
     &save_x += 1;
    } 
   }  
   goto Trackers;
  }
  if (&val1 == &val2)
  {
   //We have created 6 Trackers.
   //Let's see if there was a remaining gap we need to fil, and if so create a 7th tracker.
   &val1 = sp_custom("PPHBOX-HorV", &colsprite, -1);
   if (&val1 == 1)
   {
    &val2 = sp_custom("PPHBOX-VERT", &colsprite, -1);
    &val1 = math_mod(&val2, 6);
    if (&val1 > 0)
    {
     &save_y = sp_custom("PPBOTTOMBOX-POS", &colsprite, -1);
     goto Trackers;
    }
   }
   if (&val1 == 2)
   {
    &val2 = sp_custom("PPHBOX-HORIZ", &colsprite, -1);
    &val1 = math_mod(&val2, 6);
    if (&val1 > 0)
    {
     &save_x = sp_custom("PPRIGHTBOX-POS", &colsprite, -1);
     goto Trackers;
    }
   }     
  }

 //PUSH
 sp_custom("PPTrackerPhis1", &colsprite, 0);
 sp_custom("PPTrackerPhis2", &colsprite, 0);
 sp_custom("PPTrackerPhis3", &colsprite, 0);
 sp_custom("PPTrackerPhis4", &colsprite, 0);
 sp_custom("PPTrackerPhis5", &colsprite, 0);
 sp_custom("PPTrackerPhis6", &colsprite, 0); 
 sp_custom("PPTrackerPhis7", &colsprite, 0);

 sp_custom("PPTrackerPhisCounter", &colsprite, 0);
 
 &save_x = sp_x(&colsprite, -1);
 &save_y = sp_y(&colsprite, -1);
 //current position of left boundary
 &val1 = sp_custom("PPLEFT-BOX", &colsprite, -1);
 &val1 += &save_x; 
 &val2 = sp_custom("trimleft", &colsprite, -1);
 if (&val2 > 0)
  &val1 += &val2;
 sp_custom("PPLEFTBOX-POS", &colsprite, &val1);
 
 //current position of top boundary
 &val1 = sp_custom("PPTOP-BOX", &colsprite, -1);
 &val1 += &save_y; 
 &val2 = sp_custom("trimtop", &colsprite, -1);
 if (&val2 > 0)
  &val1 += &val2;
 sp_custom("PPTOPBOX-POS", &colsprite, &val1);
 
 //current position of right boundary
 &val1 = sp_custom("PPRIGHT-BOX", &colsprite, -1);
 &val1 += &save_x; 
 &val1 -= 1;
 &val2 = sp_custom("trimright", &colsprite, -1);
 if (&val2 > 0)
  &val1 -= &val2;
 sp_custom("PPRIGHTBOX-POS", &colsprite, &val1);

 //current position of bottom boundary
 &val1 = sp_custom("PPBOTTOM-BOX", &colsprite, -1);
 &val1 += &save_y; 
 &val1 -= 1;
 &val2 = sp_custom("trimbottom", &colsprite, -1);
 if (&val2 > 0)
  &val1 -= &val2;
 sp_custom("PPBOTTOMBOX-POS", &colsprite, &val1);

 //Vertical length of hardbox
 &save_y = sp_custom("PPTOPBOX-POS", &colsprite, -1);
 &val2 = sp_custom("PPBOTTOMBOX-POS", &colsprite, -1);
 &val2 -= &save_y;
 sp_custom("PPHBOX-VERT", &colsprite, &val2);
 
 //Horizontal length of hardbox
 &save_y = sp_custom("PPLEFTBOX-POS", &colsprite, -1);
 &val2 = sp_custom("PPRIGHTBOX-POS", &colsprite, -1);
 &val2 -= &save_y;
 sp_custom("PPHBOX-HORIZ", &colsprite, &val2);
 
 //let's set how many sprites to create along the hard box edge
 sp_custom("PPTrackerPhismax", &colsprite, 6)
 
 &val1 = sp_custom("pushdir", &colsprite, -1);
 //store dinks position
 if (&val1 == 4)
 {
  //Pushing from Right hard box boundary
  //set whether to use horizontal or vertical.
  sp_custom("PPHBOX-HorV", &colsprite, 1);
  //set where the first sprite should be created
  &save_x = sp_custom("PPLEFTBOX-POS", &colsprite, -1);
  &save_y = sp_custom("PPTOPBOX-POS", &colsprite, -1);
 }
 if (&val1 == 6)
 {
  //Pushing from Left hard box boundary
  //set whether to use horizontal or vertical.
  sp_custom("PPHBOX-HorV", &colsprite, 1);
  //set where the first sprite should be created
  &save_x = sp_custom("PPRIGHTBOX-POS", &colsprite, -1);
  &save_y = sp_custom("PPTOPBOX-POS", &colsprite, -1);
 }
  
 if (&val1 == 2)
 {
  //Pushing from top hard box boundary
  //set whether to use horizontal or vertical.
  sp_custom("PPHBOX-HorV", &colsprite, 2);
  //set where the first sprite should be created
  &save_x = sp_custom("PPLEFTBOX-POS", &colsprite, -1);
  &save_y = sp_custom("PPBOTTOMBOX-POS", &colsprite, -1);
 }
  
 if (&val1 == 8)
 {
  //Pushing from bottom hard box boundary
  //set whether to use horizontal or vertical.
  sp_custom("PPHBOX-HorV", &colsprite, 2);
  //set where the first sprite should be created
  &save_x = sp_custom("PPLEFTBOX-POS", &colsprite, -1);
  &save_y = sp_custom("PPTOPBOX-POS", &colsprite, -1);
 }

//Create tracker sprites which will find hardness that the hardbox will collide with
//PPTrackerPhisCounter counts created sprites
//PPHBOX-HorV - 1 for Vertical, 2 for Horizontal
PPTrackerPhiss:
  &val1 = sp_custom("PPTrackerPhisCounter", &colsprite, -1);
  &val1 += 1;
  &val2 = create_sprite(&save_x, &save_y, 0, 21, 1);
  sp_speed(&val2, 1000);
  sp_nodraw(&val2, 1);
  sp_nohit(&val2, 1);
    
  //make each PPTrackerPhis it's own custom key
  if (&val1 == 1)
  {
   sp_custom("PPTrackerPhis1", &colsprite, &val2);
   sp_custom("PPTrackerPhis1fix", &val2, &colsprite);
  }
  if (&val1 == 2)
  {
   sp_custom("PPTrackerPhis2", &colsprite, &val2);
   sp_custom("PPTrackerPhis2fix", &val2, &colsprite);
  }
  if (&val1 == 3)
  {
   sp_custom("PPTrackerPhis3", &colsprite, &val2);
   sp_custom("PPTrackerPhis3fix", &val2, &colsprite);
  }
  if (&val1 == 4)
  {
   sp_custom("PPTrackerPhis4", &colsprite, &val2);
   sp_custom("PPTrackerPhis4fix", &val2, &colsprite);
  }
  if (&val1 == 5)
  {
   sp_custom("PPTrackerPhis5", &colsprite, &val2);
   sp_custom("PPTrackerPhis5fix", &val2, &colsprite);
  }
  if (&val1 == 6)
  {
   sp_custom("PPTrackerPhis6", &colsprite, &val2);
   sp_custom("PPTrackerPhis6fix", &val2, &colsprite);
  }
  if (&val1 == 7)
  {
   sp_custom("PPTrackerPhis7", &colsprite, &val2);
   sp_custom("PPTrackerPhis7fix", &val2, &colsprite);
  }
  
  //store the sprite creation counter 
  sp_custom("PPTrackerPhisCounter", &colsprite, &val1); 
  
  //get the max sprites we should be creating
  &val2 = sp_custom("PPTrackerPhismax", &colsprite, -1);
   
  if (&val1 < &val2)
  {
   &val1 = sp_custom("PPHBOX-HorV", &colsprite, -1);
   if (&val1 == 1)
   {
    &val2 = sp_custom("PPHBOX-VERT", &colsprite, -1);
    &val2 /= 6;
    if (&val2 > 0)
     &save_y += &val2;
     
    if (&val2 == 0)
    {
     &val2 = sp_custom("PPHBOX-VERT", &colsprite, -1);
     &val2 = math_mod(&val2, 6);
     //Hardbox is less than 6 pixels long, set PPTrackerPhismax to the number of pixels
     sp_custom("PPTrackerPhismax", &colsprite, &val2);
     &save_y += 1;
    }    
   }
   if (&val1 == 2)
   {
    &val2 = sp_custom("PPHBOX-HORIZ", &colsprite, -1); 
    &val2 /= 6;
    if (&val2 > 0)
     &save_x += &val2;
    
    if (&val2 == 0)
    {
     &val2 = sp_custom("PPHBOX-VERT", &colsprite, -1);
     &val1 = math_mod(&val2, 6);
     //Hardbox is less than 6 pixels long, set PPTrackerPhismax to the number of pixels
     sp_custom("PPTrackerPhismax", &colsprite, &val1);
     &save_x += 1;
    } 
   }  
   goto PPTrackerPhiss;
  }
  if (&val1 == &val2)
  {
   //We have created 6 PPTrackerPhiss.
   //Let's see if there was a remaining gap we need to fill, and if so create a 7th PPTrackerPhis.
   &val1 = sp_custom("PPHBOX-HorV", &colsprite, -1);
   if (&val1 == 1)
   {
    &val2 = sp_custom("PPHBOX-VERT", &colsprite, -1);
    &val1 = math_mod(&val2, 6);
    if (&val1 > 0)
    {
     &save_y = sp_custom("PPBOTTOMBOX-POS", &colsprite, -1);
     goto PPTrackerPhiss;
    }
   }
   if (&val1 == 2)
   {
    &val2 = sp_custom("PPHBOX-HORIZ", &colsprite, -1);
    &val1 = math_mod(&val2, 6);
    if (&val1 > 0)
    {
     &save_x = sp_custom("PPRIGHTBOX-POS", &colsprite, -1);
     goto PPTrackerPhiss;
    }
   }     
  }

 return;
}

void KillColPull(void)
{
 kill_this_task();
}