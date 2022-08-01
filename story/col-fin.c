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
  &save_x = sp_custom("PPTracker1", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("PPplimit2", &colsprite, -1);
   &save_y = sp_custom("PPTrackerLimit1-ret", &colsprite, -1);
   if (&save_y < &save_x)
    sp_custom("PPplimit2", &colsprite, &save_y);
  }
//Tracker 2
  &save_x = sp_custom("PPTracker2", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("PPplimit2", &colsprite, -1);
   &save_y = sp_custom("PPTrackerLimit2-ret", &colsprite, -1);
   if (&save_y < &save_x)
    sp_custom("PPplimit2", &colsprite, &save_y);
  }
//Tracker 3
  &save_x = sp_custom("PPTracker3", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("PPplimit2", &colsprite, -1);
   &save_y = sp_custom("PPTrackerLimit3-ret", &colsprite, -1);
   if (&save_y < &save_x)
    sp_custom("PPplimit2", &colsprite, &save_y);
  }
//Tracker 4
  &save_x = sp_custom("PPTracker4", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("PPplimit2", &colsprite, -1);
   &save_y = sp_custom("PPTrackerLimit4-ret", &colsprite, -1);
   if (&save_y < &save_x)
    sp_custom("PPplimit2", &colsprite, &save_y);
  }
//Tracker 5
  &save_x = sp_custom("PPTracker5", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("PPplimit2", &colsprite, -1);
   &save_y = sp_custom("PPTrackerLimit5-ret", &colsprite, -1);
   if (&save_y < &save_x)
    sp_custom("PPplimit2", &colsprite, &save_y);
  }
//Tracker 6
  &save_x = sp_custom("PPTracker6", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("PPplimit2", &colsprite, -1);
   &save_y = sp_custom("PPTrackerLimit6-ret", &colsprite, -1);
   if (&save_y < &save_x)
    sp_custom("PPplimit2", &colsprite, &save_y);
  }
//Tracker 7
  &save_x = sp_custom("PPTracker7", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("PPplimit2", &colsprite, -1);
   &save_y = sp_custom("PPTrackerLimit7-ret", &colsprite, -1);
   if (&save_y < &save_x)
    sp_custom("PPplimit2", &colsprite, &save_y);
  }
   
 goto plimit2recalc;
}

void greaterthan(void)
{
greaterthan:
//Tracker 1
  &save_x = sp_custom("PPTracker1", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("PPplimit2", &colsprite, -1);
   &save_y = sp_custom("PPTrackerLimit1-ret", &colsprite, -1);
   if (&save_y > &save_x)
    sp_custom("PPplimit2", &colsprite, &save_y);
  }
//Tracker 2
  &save_x = sp_custom("PPTracker2", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("PPplimit2", &colsprite, -1);
   &save_y = sp_custom("PPTrackerLimit2-ret", &colsprite, -1);
   if (&save_y > &save_x)
    sp_custom("PPplimit2", &colsprite, &save_y);
  }
//Tracker 3
  &save_x = sp_custom("PPTracker3", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("PPplimit2", &colsprite, -1);
   &save_y = sp_custom("PPTrackerLimit3-ret", &colsprite, -1);
   if (&save_y > &save_x)
    sp_custom("PPplimit2", &colsprite, &save_y);
  }
//Tracker 4
  &save_x = sp_custom("PPTracker4", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("PPplimit2", &colsprite, -1);
   &save_y = sp_custom("PPTrackerLimit4-ret", &colsprite, -1);
   if (&save_y > &save_x)
    sp_custom("PPplimit2", &colsprite, &save_y);
  }
//Tracker 5
  &save_x = sp_custom("PPTracker5", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("PPplimit2", &colsprite, -1);
   &save_y = sp_custom("PPTrackerLimit5-ret", &colsprite, -1);
   if (&save_y > &save_x)
    sp_custom("PPplimit2", &colsprite, &save_y);
  }
//Tracker 6
  &save_x = sp_custom("PPTracker6", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("PPplimit2", &colsprite, -1);
   &save_y = sp_custom("PPTrackerLimit6-ret", &colsprite, -1);
   if (&save_y > &save_x)
    sp_custom("PPplimit2", &colsprite, &save_y);
  }
//Tracker 7
  &save_x = sp_custom("PPTracker7", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("PPplimit2", &colsprite, -1);
   &save_y = sp_custom("PPTrackerLimit7-ret", &colsprite, -1);
   if (&save_y > &save_x)
    sp_custom("PPplimit2", &colsprite, &save_y);
  }

 goto plimit2recalc;
}

void PHISlessthan(void)
{
PHISlessthan:
//PPTrackerPhis 1
  &save_x = sp_custom("PPTrackerPhis1", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("PPphislimit2", &colsprite, -1);
   &save_y = sp_custom("PPTrackerPhisLimit1-ret", &colsprite, -1);
   if (&save_y < &save_x)
    sp_custom("PPphislimit2", &colsprite, &save_y);
  }
//PPTrackerPhis 2
  &save_x = sp_custom("PPTrackerPhis2", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("PPphislimit2", &colsprite, -1);
   &save_y = sp_custom("PPTrackerPhisLimit2-ret", &colsprite, -1);
   if (&save_y < &save_x)
    sp_custom("PPphislimit2", &colsprite, &save_y);
  }
//PPTrackerPhis 3
  &save_x = sp_custom("PPTrackerPhis3", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("PPphislimit2", &colsprite, -1);
   &save_y = sp_custom("PPTrackerPhisLimit3-ret", &colsprite, -1);
   if (&save_y < &save_x)
    sp_custom("PPphislimit2", &colsprite, &save_y);
  }
//PPTrackerPhis 4
  &save_x = sp_custom("PPTrackerPhis4", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("PPphislimit2", &colsprite, -1);
   &save_y = sp_custom("PPTrackerPhisLimit4-ret", &colsprite, -1);
   if (&save_y < &save_x)
    sp_custom("PPphislimit2", &colsprite, &save_y);
  }
//PPTrackerPhis 5
  &save_x = sp_custom("PPTrackerPhis5", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("PPphislimit2", &colsprite, -1);
   &save_y = sp_custom("PPTrackerPhisLimit5-ret", &colsprite, -1);
   if (&save_y < &save_x)
    sp_custom("PPphislimit2", &colsprite, &save_y);
  }
//PPTrackerPhis 6
  &save_x = sp_custom("PPTrackerPhis6", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("PPphislimit2", &colsprite, -1);
   &save_y = sp_custom("PPTrackerPhisLimit6-ret", &colsprite, -1);
   if (&save_y < &save_x)
    sp_custom("PPphislimit2", &colsprite, &save_y);
  }
//PPTrackerPhis 7
  &save_x = sp_custom("PPTrackerPhis7", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("PPphislimit2", &colsprite, -1);
   &save_y = sp_custom("PPTrackerPhisLimit7-ret", &colsprite, -1);
   if (&save_y < &save_x)
    sp_custom("PPphislimit2", &colsprite, &save_y);
  }
  
 goto phislimit2recalc;
}

void PHISgreaterthan(void)
{
PHISgreaterthan:
//Tracker 1
  &save_x = sp_custom("PPTrackerPhis1", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("PPphislimit2", &colsprite, -1);
   &save_y = sp_custom("PPTrackerPhisLimit1-ret", &colsprite, -1);
   if (&save_y > &save_x)
    sp_custom("PPphislimit2", &colsprite, &save_y);
  }
//PPTrackerPhis 2
  &save_x = sp_custom("PPTrackerPhis2", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("PPphislimit2", &colsprite, -1);
   &save_y = sp_custom("PPTrackerPhisLimit2-ret", &colsprite, -1);
   if (&save_y > &save_x)
    sp_custom("PPphislimit2", &colsprite, &save_y);
  }
//PPTrackerPhis 3
  &save_x = sp_custom("PPTrackerPhis3", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("PPphislimit2", &colsprite, -1);
   &save_y = sp_custom("PPTrackerPhisLimit3-ret", &colsprite, -1);
   if (&save_y > &save_x)
    sp_custom("PPphislimit2", &colsprite, &save_y);
  }
//PPTrackerPhis 4
  &save_x = sp_custom("PPTrackerPhis4", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("PPphislimit2", &colsprite, -1);
   &save_y = sp_custom("PPTrackerPhisLimit4-ret", &colsprite, -1);
   if (&save_y > &save_x)
    sp_custom("PPphislimit2", &colsprite, &save_y);
  }
//PPTrackerPhis 5
  &save_x = sp_custom("PPTrackerPhis5", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("PPphislimit2", &colsprite, -1);
   &save_y = sp_custom("PPTrackerPhisLimit5-ret", &colsprite, -1);
   if (&save_y > &save_x)
    sp_custom("PPphislimit2", &colsprite, &save_y);
  }
//PPTrackerPhis 6
  &save_x = sp_custom("PPTrackerPhis6", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("PPphislimit2", &colsprite, -1);
   &save_y = sp_custom("PPTrackerPhisLimit6-ret", &colsprite, -1);
   if (&save_y > &save_x)
    sp_custom("PPphislimit2", &colsprite, &save_y);
  }
//PPTrackerPhis 7
  &save_x = sp_custom("PPTrackerPhis7", &colsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("PPphislimit2", &colsprite, -1);
   &save_y = sp_custom("PPTrackerPhisLimit7-ret", &colsprite, -1);
   if (&save_y > &save_x)
    sp_custom("PPphislimit2", &colsprite, &save_y);
  }

 goto phislimit2recalc;
}

void plimit2recalc(void)
{
plimit2recalc:
 if (sp_custom("pulldir", &colsprite, -1) == 2)
 {
  &save_y = sp_custom("PPBOTTOM-BOX", &colsprite, -1);
  &save_x = sp_custom("trimbottom", &colsprite, -1);
  if (&save_x > 0)
   &save_y -= &save_x;    
  
  &save_x = sp_custom("PPplimit2", &colsprite, -1);
  &save_x -= &save_y; 
  &save_x += 1;
  sp_custom("PPplimit2", &colsprite, &save_x);
 }
 if (sp_custom("pulldir", &colsprite, -1) == 4)
 {
  &save_y = sp_custom("PPLEFT-BOX", &colsprite, -1);
  &save_x = sp_custom("trimleft", &colsprite, -1);
  if (&save_x > 0)
   &save_y += &save_x;    
  
  &save_x = sp_custom("PPplimit2", &colsprite, -1);
  &save_x -= &save_y; 
  sp_custom("PPplimit2", &colsprite, &save_x); 
 }
 if (sp_custom("pulldir", &colsprite, -1) == 6)
 {
  &save_y = sp_custom("PPRIGHT-BOX", &colsprite, -1);
  &save_x = sp_custom("trimright", &colsprite, -1);
  if (&save_x > 0)
   &save_y -= &save_x;  
  
  &save_x = sp_custom("PPplimit2", &colsprite, -1);
  &save_x -= &save_y; 
  &save_x += 1;
  sp_custom("PPplimit2", &colsprite, &save_x); 
 }
 if (sp_custom("pulldir", &colsprite, -1) == 8)
 {
  &save_y = sp_custom("PPTOP-BOX", &colsprite, -1);
  &save_x = sp_custom("trimtop", &colsprite, -1);
  if (&save_x > 0)
   &save_y += &save_x;   
  
  &save_x = sp_custom("PPplimit2", &colsprite, -1);
  &save_x -= &save_y; 
  sp_custom("PPplimit2", &colsprite, &save_x); 
 }
 return;
}

void phislimit2recalc(void)
{
phislimit2recalc:
 if (sp_custom("pushdir", &colsprite, -1) == 2)
 {
  &save_y = sp_custom("PPBOTTOM-BOX", &colsprite, -1);
  &save_x = sp_custom("trimbottom", &colsprite, -1);
  if (&save_x > 0)
   &save_y -= &save_x;  
  
  &save_x = sp_custom("PPphislimit2", &colsprite, -1);
  &save_x -= &save_y; 
  &save_x += 1;
  sp_custom("PPphislimit2", &colsprite, &save_x);
 }
 if (sp_custom("pushdir", &colsprite, -1) == 4)
 {
  &save_y = sp_custom("PPLEFT-BOX", &colsprite, -1);
  &save_x = sp_custom("trimleft", &colsprite, -1);
  if (&save_x > 0)
   &save_y += &save_x;    
  
  &save_x = sp_custom("PPphislimit2", &colsprite, -1);
  &save_x -= &save_y; 
  sp_custom("PPphislimit2", &colsprite, &save_x); 
 }
 if (sp_custom("pushdir", &colsprite, -1) == 6)
 {
  &save_y = sp_custom("PPRIGHT-BOX", &colsprite, -1);
  &save_x = sp_custom("trimright", &colsprite, -1);
  if (&save_x > 0)
   &save_y -= &save_x;
  
  &save_x = sp_custom("PPphislimit2", &colsprite, -1);
  &save_x -= &save_y; 
  &save_x += 1;
  sp_custom("PPphislimit2", &colsprite, &save_x); 
 }
 if (sp_custom("pushdir", &colsprite, -1) == 8)
 {
  &save_y = sp_custom("PPTOP-BOX", &colsprite, -1);
  &save_x = sp_custom("trimtop", &colsprite, -1);
  if (&save_x > 0)
   &save_y += &save_x;  
  
  &save_x = sp_custom("PPphislimit2", &colsprite, -1);
  &save_x -= &save_y; 
  sp_custom("PPphislimit2", &colsprite, &save_x); 
 }
 return;
}

void KillColFin(void)
{
 kill_this_task();
}