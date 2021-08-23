void main(void)
{
   //**PUSH AND PULL INVENTORY BUGFIX**//
   //Check if a sprite is currently being moved, and if so, set custom key to indicate inventory has been opened.
   &save_x = 0;
  inventoryloop:
   //get invisible shadow sprites, there is one for each moveable object currently being touched by dinked
   &save_x = get_next_sprite_with_this_brain(15, 0, &save_x);
   if (&save_x > 0)
   {
     //assure it's a shadow sprite actually attached to a moveable object by checking the "PP-Shadow" custom key.
     &save_y = sp_custom("PP-Parent", &save_x, -1);
     &save_y = sp_custom("PP-Shadow", &save_y, -1);
     if (&save_y == &save_x)
     { 
      //we have identified a moveable sprite, being touched by dink, now let's see if its being moved.
      &save_y = sp_custom("PP-Parent", &save_x, -1);
      &save_y = sp_custom("PPMoving", &save_y, -1);
      if (&save_y == 1)
      {
       //Found a sprite currently being moved - set the custom key.
       &save_y = sp_custom("PP-Parent", &save_x, -1);
       sp_custom("inventory", &save_y, 1);
      }
     }
     //increment and loop.
     &save_x += 1;
     goto inventoryloop;
   } 
   //**END PUSH AND PULL INVENTORY BUGFIX**//


 //normal inventory stuff. 
 playsound(21, 22052, 0, 0, 0); 
 show_inventory();

 kill_this_task();
}