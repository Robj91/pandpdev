//Collision system Final calculations taking into account custom hardbox trim entries

void main(void)
{
 //&colsprite will store the sprite.
 int &colsprite = &save_y;
 
 return;
}

void lessthan(void)
{
lessthan:     
//Tracker 1
  &save_x = sp_custom("Tracker1", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("plimit2", &colsprite, -1);
   &save_y = sp_custom("TrackerLimit1-ret", &colsprite, -1);
   if (&save_y < &save_x)
    sp_custom("plimit2", &colsprite, &save_y);
  }
//Tracker 2
  &save_x = sp_custom("Tracker2", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("plimit2", &colsprite, -1);
   &save_y = sp_custom("TrackerLimit2-ret", &colsprite, -1);
   if (&save_y < &save_x)
    sp_custom("plimit2", &colsprite, &save_y);
  }
//Tracker 3
  &save_x = sp_custom("Tracker3", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("plimit2", &colsprite, -1);
   &save_y = sp_custom("TrackerLimit3-ret", &colsprite, -1);
   if (&save_y < &save_x)
    sp_custom("plimit2", &colsprite, &save_y);
  }
//Tracker 4
  &save_x = sp_custom("Tracker4", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("plimit2", &colsprite, -1);
   &save_y = sp_custom("TrackerLimit4-ret", &colsprite, -1);
   if (&save_y < &save_x)
    sp_custom("plimit2", &colsprite, &save_y);
  }
//Tracker 5
  &save_x = sp_custom("Tracker5", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("plimit2", &colsprite, -1);
   &save_y = sp_custom("TrackerLimit5-ret", &colsprite, -1);
   if (&save_y < &save_x)
    sp_custom("plimit2", &colsprite, &save_y);
  }
//Tracker 6
  &save_x = sp_custom("Tracker6", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("plimit2", &colsprite, -1);
   &save_y = sp_custom("TrackerLimit6-ret", &colsprite, -1);
   if (&save_y < &save_x)
    sp_custom("plimit2", &colsprite, &save_y);
  }
//Tracker 7
  &save_x = sp_custom("Tracker7", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("plimit2", &colsprite, -1);
   &save_y = sp_custom("TrackerLimit7-ret", &colsprite, -1);
   if (&save_y < &save_x)
    sp_custom("plimit2", &colsprite, &save_y);
  }
   
 goto plimit2recalc;
}

void greaterthan(void)
{
greaterthan:
//Tracker 1
  &save_x = sp_custom("Tracker1", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("plimit2", &colsprite, -1);
   &save_y = sp_custom("TrackerLimit1-ret", &colsprite, -1);
   if (&save_y > &save_x)
    sp_custom("plimit2", &colsprite, &save_y);
  }
//Tracker 2
  &save_x = sp_custom("Tracker2", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("plimit2", &colsprite, -1);
   &save_y = sp_custom("TrackerLimit2-ret", &colsprite, -1);
   if (&save_y > &save_x)
    sp_custom("plimit2", &colsprite, &save_y);
  }
//Tracker 3
  &save_x = sp_custom("Tracker3", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("plimit2", &colsprite, -1);
   &save_y = sp_custom("TrackerLimit3-ret", &colsprite, -1);
   if (&save_y > &save_x)
    sp_custom("plimit2", &colsprite, &save_y);
  }
//Tracker 4
  &save_x = sp_custom("Tracker4", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("plimit2", &colsprite, -1);
   &save_y = sp_custom("TrackerLimit4-ret", &colsprite, -1);
   if (&save_y > &save_x)
    sp_custom("plimit2", &colsprite, &save_y);
  }
//Tracker 5
  &save_x = sp_custom("Tracker5", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("plimit2", &colsprite, -1);
   &save_y = sp_custom("TrackerLimit5-ret", &colsprite, -1);
   if (&save_y > &save_x)
    sp_custom("plimit2", &colsprite, &save_y);
  }
//Tracker 6
  &save_x = sp_custom("Tracker6", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("plimit2", &colsprite, -1);
   &save_y = sp_custom("TrackerLimit6-ret", &colsprite, -1);
   if (&save_y > &save_x)
    sp_custom("plimit2", &colsprite, &save_y);
  }
//Tracker 7
  &save_x = sp_custom("Tracker7", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("plimit2", &colsprite, -1);
   &save_y = sp_custom("TrackerLimit7-ret", &colsprite, -1);
   if (&save_y > &save_x)
    sp_custom("plimit2", &colsprite, &save_y);
  }

 goto plimit2recalc;
}

void PHISlessthan(void)
{
PHISlessthan:
//TrackerPhis 1
  &save_x = sp_custom("TrackerPhis1", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("phislimit2", &colsprite, -1);
   &save_y = sp_custom("TrackerPhisLimit1-ret", &colsprite, -1);
   if (&save_y < &save_x)
    sp_custom("phislimit2", &colsprite, &save_y);
  }
//TrackerPhis 2
  &save_x = sp_custom("TrackerPhis2", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("phislimit2", &colsprite, -1);
   &save_y = sp_custom("TrackerPhisLimit2-ret", &colsprite, -1);
   if (&save_y < &save_x)
    sp_custom("phislimit2", &colsprite, &save_y);
  }
//TrackerPhis 3
  &save_x = sp_custom("TrackerPhis3", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("phislimit2", &colsprite, -1);
   &save_y = sp_custom("TrackerPhisLimit3-ret", &colsprite, -1);
   if (&save_y < &save_x)
    sp_custom("phislimit2", &colsprite, &save_y);
  }
//TrackerPhis 4
  &save_x = sp_custom("TrackerPhis4", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("phislimit2", &colsprite, -1);
   &save_y = sp_custom("TrackerPhisLimit4-ret", &colsprite, -1);
   if (&save_y < &save_x)
    sp_custom("phislimit2", &colsprite, &save_y);
  }
//TrackerPhis 5
  &save_x = sp_custom("TrackerPhis5", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("phislimit2", &colsprite, -1);
   &save_y = sp_custom("TrackerPhisLimit5-ret", &colsprite, -1);
   if (&save_y < &save_x)
    sp_custom("phislimit2", &colsprite, &save_y);
  }
//TrackerPhis 6
  &save_x = sp_custom("TrackerPhis6", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("phislimit2", &colsprite, -1);
   &save_y = sp_custom("TrackerPhisLimit6-ret", &colsprite, -1);
   if (&save_y < &save_x)
    sp_custom("phislimit2", &colsprite, &save_y);
  }
//TrackerPhis 7
  &save_x = sp_custom("TrackerPhis7", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("phislimit2", &colsprite, -1);
   &save_y = sp_custom("TrackerPhisLimit7-ret", &colsprite, -1);
   if (&save_y < &save_x)
    sp_custom("phislimit2", &colsprite, &save_y);
  }
  
 goto phislimit2recalc;
}

void PHISgreaterthan(void)
{
PHISgreaterthan:
//Tracker 1
  &save_x = sp_custom("TrackerPhis1", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("phislimit2", &colsprite, -1);
   &save_y = sp_custom("TrackerPhisLimit1-ret", &colsprite, -1);
   if (&save_y > &save_x)
    sp_custom("phislimit2", &colsprite, &save_y);
  }
//TrackerPhis 2
  &save_x = sp_custom("TrackerPhis2", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("phislimit2", &colsprite, -1);
   &save_y = sp_custom("TrackerPhisLimit2-ret", &colsprite, -1);
   if (&save_y > &save_x)
    sp_custom("phislimit2", &colsprite, &save_y);
  }
//TrackerPhis 3
  &save_x = sp_custom("TrackerPhis3", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("phislimit2", &colsprite, -1);
   &save_y = sp_custom("TrackerPhisLimit3-ret", &colsprite, -1);
   if (&save_y > &save_x)
    sp_custom("phislimit2", &colsprite, &save_y);
  }
//TrackerPhis 4
  &save_x = sp_custom("TrackerPhis4", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("phislimit2", &colsprite, -1);
   &save_y = sp_custom("TrackerPhisLimit4-ret", &colsprite, -1);
   if (&save_y > &save_x)
    sp_custom("phislimit2", &colsprite, &save_y);
  }
//TrackerPhis 5
  &save_x = sp_custom("TrackerPhis5", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("phislimit2", &colsprite, -1);
   &save_y = sp_custom("TrackerPhisLimit5-ret", &colsprite, -1);
   if (&save_y > &save_x)
    sp_custom("phislimit2", &colsprite, &save_y);
  }
//TrackerPhis 6
  &save_x = sp_custom("TrackerPhis6", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("phislimit2", &colsprite, -1);
   &save_y = sp_custom("TrackerPhisLimit6-ret", &colsprite, -1);
   if (&save_y > &save_x)
    sp_custom("phislimit2", &colsprite, &save_y);
  }
//TrackerPhis 7
  &save_x = sp_custom("TrackerPhis7", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("phislimit2", &colsprite, -1);
   &save_y = sp_custom("TrackerPhisLimit7-ret", &colsprite, -1);
   if (&save_y > &save_x)
    sp_custom("phislimit2", &colsprite, &save_y);
  }

 goto phislimit2recalc;
}

void plimit2recalc(void)
{
plimit2recalc:
 if (sp_custom("pulldir", &colsprite, -1) == 2)
 {
  &save_y = sp_custom("BOTTOM-BOX", &colsprite, -1);
  &save_x = sp_custom("trimbottom", &colsprite, -1);
  if (&save_x > 0)
   &save_y -= &save_x;    
  
  &save_x = sp_custom("plimit2", &colsprite, -1);
  &save_x -= &save_y; 
  &save_x += 1;
  sp_custom("plimit2", &colsprite, &save_x);
 }
 if (sp_custom("pulldir", &colsprite, -1) == 4)
 {
  &save_y = sp_custom("LEFT-BOX", &colsprite, -1);
  &save_x = sp_custom("trimleft", &colsprite, -1);
  if (&save_x > 0)
   &save_y += &save_x;    
  
  &save_x = sp_custom("plimit2", &colsprite, -1);
  &save_x -= &save_y; 
  sp_custom("plimit2", &colsprite, &save_x); 
 }
 if (sp_custom("pulldir", &colsprite, -1) == 6)
 {
  &save_y = sp_custom("RIGHT-BOX", &colsprite, -1);
  &save_x = sp_custom("trimright", &colsprite, -1);
  if (&save_x > 0)
   &save_y -= &save_x;  
  
  &save_x = sp_custom("plimit2", &colsprite, -1);
  &save_x -= &save_y; 
  &save_x += 1;
  sp_custom("plimit2", &colsprite, &save_x); 
 }
 if (sp_custom("pulldir", &colsprite, -1) == 8)
 {
  &save_y = sp_custom("TOP-BOX", &colsprite, -1);
  &save_x = sp_custom("trimtop", &colsprite, -1);
  if (&save_x > 0)
   &save_y += &save_x;   
  
  &save_x = sp_custom("plimit2", &colsprite, -1);
  &save_x -= &save_y; 
  sp_custom("plimit2", &colsprite, &save_x); 
 }
 return;
}

void phislimit2recalc(void)
{
phislimit2recalc:
 if (sp_custom("pushdir", &colsprite, -1) == 2)
 {
  &save_y = sp_custom("BOTTOM-BOX", &colsprite, -1);
  &save_x = sp_custom("trimbottom", &colsprite, -1);
  if (&save_x > 0)
   &save_y -= &save_x;  
  
  &save_x = sp_custom("phislimit2", &colsprite, -1);
  &save_x -= &save_y; 
  &save_x += 1;
  sp_custom("phislimit2", &colsprite, &save_x);
 }
 if (sp_custom("pushdir", &colsprite, -1) == 4)
 {
  &save_y = sp_custom("LEFT-BOX", &colsprite, -1);
  &save_x = sp_custom("trimleft", &colsprite, -1);
  if (&save_x > 0)
   &save_y += &save_x;    
  
  &save_x = sp_custom("phislimit2", &colsprite, -1);
  &save_x -= &save_y; 
  sp_custom("phislimit2", &colsprite, &save_x); 
 }
 if (sp_custom("pushdir", &colsprite, -1) == 6)
 {
  &save_y = sp_custom("RIGHT-BOX", &colsprite, -1);
  &save_x = sp_custom("trimright", &colsprite, -1);
  if (&save_x > 0)
   &save_y -= &save_x;
  
  &save_x = sp_custom("phislimit2", &colsprite, -1);
  &save_x -= &save_y; 
  &save_x += 1;
  sp_custom("phislimit2", &colsprite, &save_x); 
 }
 if (sp_custom("pushdir", &colsprite, -1) == 8)
 {
  &save_y = sp_custom("TOP-BOX", &colsprite, -1);
  &save_x = sp_custom("trimtop", &colsprite, -1);
  if (&save_x > 0)
   &save_y += &save_x;  
  
  &save_x = sp_custom("phislimit2", &colsprite, -1);
  &save_x -= &save_y; 
  sp_custom("phislimit2", &colsprite, &save_x); 
 }
 return;
}

void KillColFin(void)
{
 kill_this_task();
}