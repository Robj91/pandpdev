//this script will check if Dink is facing the sprites hardbox edge, and no more than 1 pixel from it.
//Uses provided hardbox values.
//returns '1' to calling script if true.
//returns '0' to calling script if false.

void quick_check(void)
{
    //Hard box boundary values are provided, so that makes things a little easier
 
    //First let's get the current position of the sprites hardbox boundaries, and save them away
    &save_x = sp_x(&arg1, -1);
    &save_y = sp_y(&arg1, -1);
    
    //current position of left boundary
    &val1 = sp_custom("LEFT-BOX", &arg1, -1);
    &val1 += &save_x; 
    sp_custom("LEFTBOX-POS", &arg1, &val1);
    
    //current position of top boundary
    &val1 = sp_custom("TOP-BOX", &arg1, -1);
    &val1 += &save_y; 
    sp_custom("TOPBOX-POS", &arg1, &val1);
    
    //current position of right boundary
    &val1 = sp_custom("RIGHT-BOX", &arg1, -1);
    &val1 += &save_x; 
    &val1 -= 1;
    sp_custom("RIGHTBOX-POS", &arg1, &val1);
   
    //current position of bottom boundary
    &val1 = sp_custom("BOTTOM-BOX", &arg1, -1);
    &val1 += &save_y; 
    &val1 -= 1;
    sp_custom("BOTTOMBOX-POS", &arg1, &val1);
   
    //check if dink is in the correct position and facing the sprites hardness
    &save_x = sp_custom("pushdir", &arg1, -1);
    if (&save_x == 2)
    {
     //Dink is facing south, 
   
     //assure he is above the sprites hard box
     &save_y = sp_y(1, -1);
     &val1 = sp_custom("TOPBOX-POS", &arg1, -1);
     
     if (&save_y < &val1)
     {
      //there should only be 1 pixel difference if DInk is standing against eh hardbox edge, let's make sure.
      &val1 -= &save_y;
      if (&val1 == 1)
      {
       //now make sure he is not too far to the right or left (could be right on the corner)
       &save_y = sp_x(1, -1);
       &val1 = sp_custom("LEFTBOX-POS", &arg1, -1);
       if (&save_y >= &val1)
       {
        &val1 = sp_custom("RIGHTBOX-POS", &arg1, -1);  
        if (&save_y <= &val1)
        {
         //Dink is in correct position.
         return(1);
        }
       }
      }
     }    
    }
    //OK you get the idea, I will not comment for the other directions.
    if (&save_x == 4)
    {
     &save_y = sp_x(1, -1);
     &val1 = sp_custom("RIGHTBOX-POS", &arg1, -1);
      
     if (&save_y > &val1)
     {
      &save_y -= &val1;
      if (&save_y == 1)
      {
       &save_y = sp_y(1, -1);
       &val1 = sp_custom("TOPBOX-POS", &arg1, -1);
       if (&save_y >= &val1)
       {
        &val1 = sp_custom("BOTTOMBOX-POS", &arg1, -1);  
        if (&save_y <= &val1)
        {
         return(1);
        }
       }
      }
     }   
    }
    if (&save_x == 6)
    {
     &save_y = sp_x(1, -1);
     &val1 = sp_custom("LEFTBOX-POS", &arg1, -1);
      
     if (&save_y < &val1)
     {
      &val1 -= &save_y;
      if (&val1 == 1)
      {
       &save_y = sp_y(1, -1);
       &val1 = sp_custom("TOPBOX-POS", &arg1, -1);
       if (&save_y >= &val1)
       {
        &val1 = sp_custom("BOTTOMBOX-POS", &arg1, -1);
        if (&save_y <= &val1)
        {
         return(1);
        }
       }
      }
     }   
    }
    if (&save_x == 8)
    {
     &save_y = sp_y(1, -1);
     &val1 = sp_custom("BOTTOMBOX-POS", &arg1, -1);
     
     if (&save_y > &val1)
     {
      &save_y -= &val1;
      if (&save_y == 1)
      {
       &save_y = sp_x(1, -1);
       &val1 = sp_custom("LEFTBOX-POS", &arg1, -1);
       if (&save_y >= &val1)
       {
        &val1 = sp_custom("RIGHTBOX-POS", &arg1, -1);  
        if (&save_y <= &val1)
        {
         return(1);
        }
       }
      }
     } 
    }

 return(0);
}