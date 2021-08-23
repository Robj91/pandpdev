//script for tutorial sections - disable text timeout, and outline hardboxes of sprites.

void txtskip(void)
{
  sp_kill(&arg1, 0);
 waitskip:
  wait_for_button();
  if (&result == 2)
   sp_active(&arg1, 0); 
  else
   goto waitskip;
 
 kill_this_task();
}

void tuttext(void)
{
  sp_kill(&arg1, 0);
  sp_kill(&arg2, 0);
 ttloop:
  wait_for_button();
  if (&result == 2)
  {
   sp_active(&arg1, 0); 
   sp_active(&arg2, 0); 
  }
  else
  {
   goto ttloop;
  }
 
 kill_this_task();
}
  
void hardbox(void)
{
 //&arg1 = hardleft, &arg2 = hardtop, &arg3 = hardright, &arg4 = hardbottom, &arg5 = sprite

 int &val1;
 int &val2;
 int &val3;
 int &val4;
 int &val5;

 &save_x = sp_x(&arg5, -1);
 &save_y = sp_y(&arg5, -1);

 //hardleft pos of current sprite
 &val1 = &save_x;
 &val1 += &arg1;
 sp_custom("hardleft", &arg5, &val1);

 //hardtop pos of current sprite
 &val1 = &save_y;
 &val1 += &arg2;
 sp_custom("hardtop", &arg5, &val1);

 //hardright pos of current sprite
 &val1 = &save_x;
 &val1 += &arg3;
 &val1 -= 1;
 sp_custom("hardright", &arg5, &val1);

 //hardbottom pos of current sprite
 &val1 = &save_y;
 &val1 += &arg4;
 &val1 -= 1;
 sp_custom("hardbottom", &arg5, &val1);
  
 //Halfway between left and right
 &val1 = sp_custom("hardright", &arg5, -1);
 &val2 = sp_custom("hardleft", &arg5, -1);
 &val1 -= &val2;
 &val1 /= 2;
 &val2 += &val1;
 sp_custom("XMID", &arg5, &val2);
 
 //Halfway between top and bottom
 &val1 = sp_custom("hardbottom", &arg5, -1);
 &val2 = sp_custom("hardtop", &arg5, -1);
 &val1 -= &val2;
 &val1 /= 2;
 &val2 += &val1;
 sp_custom("YMID", &arg5, &val2);
 
 &val1 = sp_custom("hardleft", &arg5, -1);
 &val2 = sp_custom("hardtop", &arg5, -1); 
 &val3 = sp_custom("hardright", &arg5, -1);
 &val4 = sp_custom("hardbottom", &arg5, -1);
 &val5 = sp_custom("XMID", &arg5, -1); 
 &save_y = sp_custom("YMID", &arg5, -1);

 //mark the hardbox with sparkles
 
    //left middle 
    &save_x = create_sprite(&val1, &save_y, 6, 165, 1);
    sp_seq(&save_x, 165);
    sp_que(&save_x, &val4);
    sp_custom("pspark", &arg5, &save_x);     
  
    //Top middle
    &save_x = create_sprite(&val5, &val2, 6, 165, 1);
    sp_seq(&save_x, 165);
    sp_que(&save_x, &val4);
    sp_custom("pspark2", &arg5, &save_x); 
  
    //Right middle
    &save_x = create_sprite(&val3, &save_y, 6, 165, 1);
    sp_seq(&save_x, 165);
    sp_que(&save_x, &val4);
    sp_custom("pspark3", &arg5, &save_x); 
  
    //bottom middle
    &save_x = create_sprite(&val5, &val4, 6, 165, 1);
    sp_seq(&save_x, 165);
    sp_que(&save_x, &val4);
    sp_custom("pspark4", &arg5, &save_x); 
  
    //top left corner
    &save_x = create_sprite(&val1, &val2, 6, 165, 1);
    sp_seq(&save_x, 165);
    sp_que(&save_x, &val4);
    sp_custom("pspark5", &arg5, &save_x);     
  
    //top right corner
    &save_x = create_sprite(&val3, &val2, 6, 165, 1);
    sp_seq(&save_x, 165);
    sp_que(&save_x, &val4);
    sp_custom("pspark6", &arg5, &save_x); 
  
    //bottom right corner
    &save_x = create_sprite(&val3, &val4, 6, 165, 1);
    sp_seq(&save_x, 165);
    sp_que(&save_x, &val4);
    sp_custom("pspark7", &arg5, &save_x); 
  
    //bottom left corner
    &save_x = create_sprite(&val1, &val4, 6, 165, 1);
    sp_seq(&save_x, 165);
    sp_que(&save_x, &val4);
    sp_custom("pspark8", &arg5, &save_x); 
    
 kill_this_task();
}

void boxmove(void)
{
 //&arg1 = hardleft, &arg2 = hardtop, &arg3 = hardright, &arg4 = hardbottom, &arg5 = sprite

 int &val1;
 int &val2;
 int &val3;
 int &val4;
 int &val5;

 &save_x = sp_x(&arg5, -1);
 &save_y = sp_y(&arg5, -1);

 //hardleft pos of current sprite
 &val1 = &save_x;
 &val1 += &arg1;
 sp_custom("hardleft", &arg5, &val1);

 //hardtop pos of current sprite
 &val1 = &save_y;
 &val1 += &arg2;
 sp_custom("hardtop", &arg5, &val1);

 //hardright pos of current sprite
 &val1 = &save_x;
 &val1 += &arg3;
 &val1 -= 1;
 sp_custom("hardright", &arg5, &val1);

 //hardbottom pos of current sprite
 &val1 = &save_y;
 &val1 += &arg4;
 &val1 -= 1;
 sp_custom("hardbottom", &arg5, &val1);
  
 //Halfway between left and right
 &val1 = sp_custom("hardright", &arg5, -1);
 &val2 = sp_custom("hardleft", &arg5, -1);
 &val1 -= &val2;
 &val1 /= 2;
 &val2 += &val1;
 sp_custom("XMID", &arg5, &val2);
 
 //Halfway between top and bottom
 &val1 = sp_custom("hardbottom", &arg5, -1);
 &val2 = sp_custom("hardtop", &arg5, -1);
 &val1 -= &val2;
 &val1 /= 2;
 &val2 += &val1;
 sp_custom("YMID", &arg5, &val2);
 
 &val1 = sp_custom("hardleft", &arg5, -1);
 &val2 = sp_custom("hardtop", &arg5, -1); 
 &val3 = sp_custom("hardright", &arg5, -1);
 &val4 = sp_custom("hardbottom", &arg5, -1);
 &val5 = sp_custom("XMID", &arg5, -1); 
 &save_y = sp_custom("YMID", &arg5, -1);

 //adjust the position of the already created sparkles from earlier
 
    //left middle 
    &save_x = sp_custom("pspark", &arg5, -1);
    sp_x(&save_x, &val1);
    sp_y(&save_x, &save_y);  
    sp_que(&save_x, &val4);
  
    //Top middle
    &save_x = sp_custom("pspark2", &arg5, -1);
    sp_x(&save_x, &val5);
    sp_y(&save_x, &val2); 
    sp_que(&save_x, &val4); 
  
    //Right middle
    &save_x = sp_custom("pspark3", &arg5, -1);
    sp_x(&save_x, &val3);
    sp_y(&save_x, &save_y);  
    sp_que(&save_x, &val4);
  
    //bottom middle
    &save_x = sp_custom("pspark4", &arg5, -1);
    sp_x(&save_x, &val5);
    sp_y(&save_x, &val4);  
    sp_que(&save_x, &val4);
  
    //top left corner
    &save_x = sp_custom("pspark5", &arg5, -1);
    sp_x(&save_x, &val1);
    sp_y(&save_x, &val2);     
    sp_que(&save_x, &val4);
  
    //top right corner
    &save_x = sp_custom("pspark6", &arg5, -1);
    sp_x(&save_x, &val3);
    sp_y(&save_x, &val2);  
    sp_que(&save_x, &val4);
  
    //bottom right corner
    &save_x = sp_custom("pspark7", &arg5, -1);
    sp_x(&save_x, &val3);
    sp_y(&save_x, &val4);  
    sp_que(&save_x, &val4);
  
    //bottom left corner
    &save_x = sp_custom("pspark8", &arg5, -1);
    sp_x(&save_x, &val1);
    sp_y(&save_x, &val4);   
    sp_que(&save_x, &val4);
    
 kill_this_task(); 
}

void boxkill(void)
{
 &save_x = sp_custom("pspark", &arg1, -1);
 &save_y = sp_custom("pspark2", &arg1, -1);
 sp_active(&save_x, 0);
 sp_active(&save_y, 0);
 
 &save_x = sp_custom("pspark3", &arg1, -1);
 &save_y = sp_custom("pspark4", &arg1, -1);
 sp_active(&save_x, 0);
 sp_active(&save_y, 0);

 &save_x = sp_custom("pspark5", &arg1, -1);
 &save_y = sp_custom("pspark6", &arg1, -1);
 sp_active(&save_x, 0);
 sp_active(&save_y, 0);

 &save_x = sp_custom("pspark7", &arg1, -1);
 &save_y = sp_custom("pspark8", &arg1, -1);
 sp_active(&save_x, 0);
 sp_active(&save_y, 0);
}