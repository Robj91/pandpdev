void main(void)
{
 sp_speed(&current_sprite, 1);
 sp_timing(&current_sprite, 0);	

 int &val1;
 int &val2;
 int &val3;
 int &val4;
 int &val5;
 int &val6;
 int &val7;

 wait(1);

 sp_custom("setcollision", &current_sprite, 2);

 sp_custom("trimleft", &current_sprite, 10);
 sp_custom("trimtop", &current_sprite, 10);
 sp_custom("trimright", &current_sprite, 10);
 sp_custom("trimbottom", &current_sprite, 10);
 
 external("phisbo", "main", -21, -35, 23, 9); 
 
 goto stopex;
}


void touch(void)
{
 &save_x = sp_custom("initiated", &current_sprite, -1);
 if (&save_x > 0)
 {
  sp_touch_damage(&current_sprite, 0);
  wait(&save_x);
  sp_custom("initiated", &current_sprite, 0);
 }
 external("phisbo", "touch"); 
 wait(200);
 external("phisbo", "touchreset");
 
 goto stopex;
}

void MoveDetectDuring(void)
{
 //DinkHD lags when using external, and messes up push/pull loop, making it unbearably slow
 //so we can't use it external in movedetectduring at all for DinkHD.
 //hence this DinkHD specific script

 &val3 = -21;
 &val4 = -35;
 &val5 = 23;
 &val6 = 9;
  
 goto boxmove;
 boxmovecont: 
 
 goto stopex;
}

void MoveDetectAfter(void)
{
 goto stopex;
}

void pull(void)
{
 //call the pull procedure from phisbo
 external("phisbo", "pkey");

 goto stopex;
}

void talk(void)
{
 external("phisbo", "talk");
 &val7 = sp_custom("talkreturn", &current_sprite, -1);

 if (&val7 == 2)
 {
 }
 if (&val7 == 1)
 {
  say("A moveable rock with collision activated for all versions + all hardbox edges trimmed by 10.", 1);
 } 

 external("phisbo", "touchreset");
 goto stopex;
}

void hit(void)
{
 external("phisbo", "hit");

 external("phisbo", "touchreset");
 goto stopex;
}

void boxmove(void)
{
boxmove:
 //&arg1 = hardleft, &arg2 = hardtop, &arg3 = hardright, &arg4 = hardbottom, &current_sprite = sprite

 &save_x = sp_x(&current_sprite, -1);
 &save_y = sp_y(&current_sprite, -1);

 //hardleft pos of current sprite
 &val1 = &save_x;
 &val1 += &val3;
 sp_custom("hardleft", &current_sprite, &val1);

 //hardtop pos of current sprite
 &val1 = &save_y;
 &val1 += &val4;
 sp_custom("hardtop", &current_sprite, &val1);

 //hardright pos of current sprite
 &val1 = &save_x;
 &val1 += &val5;
 &val1 -= 1;
 sp_custom("hardright", &current_sprite, &val1);

 //hardbottom pos of current sprite
 &val1 = &save_y;
 &val1 += &val6;
 &val1 -= 1;
 sp_custom("hardbottom", &current_sprite, &val1);
  
 //Halfway between left and right
 &val1 = sp_custom("hardright", &current_sprite, -1);
 &val2 = sp_custom("hardleft", &current_sprite, -1);
 &val1 -= &val2;
 &val1 /= 2;
 &val2 += &val1;
 sp_custom("XMID", &current_sprite, &val2);
 
 //Halfway between top and bottom
 &val1 = sp_custom("hardbottom", &current_sprite, -1);
 &val2 = sp_custom("hardtop", &current_sprite, -1);
 &val1 -= &val2;
 &val1 /= 2;
 &val2 += &val1;
 sp_custom("YMID", &current_sprite, &val2);
 
 &val1 = sp_custom("hardleft", &current_sprite, -1);
 &val2 = sp_custom("hardtop", &current_sprite, -1); 
 &val3 = sp_custom("hardright", &current_sprite, -1);
 &val4 = sp_custom("hardbottom", &current_sprite, -1);
 &val5 = sp_custom("XMID", &current_sprite, -1); 
 &save_y = sp_custom("YMID", &current_sprite, -1);

 //adjust the position of the already created sparkles from earlier
 
    //left middle 
    &save_x = sp_custom("pspark", &current_sprite, -1);
    sp_x(&save_x, &val1);
    sp_y(&save_x, &save_y);  
    sp_que(&save_x, &val4);
  
    //Top middle
    &save_x = sp_custom("pspark2", &current_sprite, -1);
    sp_x(&save_x, &val5);
    sp_y(&save_x, &val2); 
    sp_que(&save_x, &val4); 
  
    //Right middle
    &save_x = sp_custom("pspark3", &current_sprite, -1);
    sp_x(&save_x, &val3);
    sp_y(&save_x, &save_y);  
    sp_que(&save_x, &val4);
  
    //bottom middle
    &save_x = sp_custom("pspark4", &current_sprite, -1);
    sp_x(&save_x, &val5);
    sp_y(&save_x, &val4);  
    sp_que(&save_x, &val4);
  
    //top left corner
    &save_x = sp_custom("pspark5", &current_sprite, -1);
    sp_x(&save_x, &val1);
    sp_y(&save_x, &val2);     
    sp_que(&save_x, &val4);
  
    //top right corner
    &save_x = sp_custom("pspark6", &current_sprite, -1);
    sp_x(&save_x, &val3);
    sp_y(&save_x, &val2);  
    sp_que(&save_x, &val4);
  
    //bottom right corner
    &save_x = sp_custom("pspark7", &current_sprite, -1);
    sp_x(&save_x, &val3);
    sp_y(&save_x, &val4);  
    sp_que(&save_x, &val4);
  
    //bottom left corner
    &save_x = sp_custom("pspark8", &current_sprite, -1);
    sp_x(&save_x, &val1);
    sp_y(&save_x, &val4);   
    sp_que(&save_x, &val4);
    
 goto boxmovecont;
}

void stopex(void)
{
stopex:
 return;
}