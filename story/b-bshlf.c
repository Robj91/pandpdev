void main(void)
{
 sp_speed(&current_sprite, 1);
 sp_timing(&current_sprite, 0);	

 wait(1);

 //needed for talk procedure. Can't use global juggle var, causes a bug. If no talk procedure, can delete.
 int &val1; 

  sp_custom("que_fix", &current_sprite, 1);  

 sp_custom("setcollision", &current_sprite, 1);

 sp_custom("trimleft", &current_sprite, 15);
 sp_custom("trimtop", &current_sprite, 0);
 sp_custom("trimright", &current_sprite, 15);
 sp_custom("trimbottom", &current_sprite, 0);
 
 external("phisbo", "main", -92, -51, 82, 1); 
 
 goto stopex;
}


void touch(void)
{
 external("phisbo", "touch"); 
 goto stopex;
}

void talk(void)
{
 external("phisbo", "moveactive");
 if (&return <= 0)
 {
  //ADD ANY TALK STUFF HERE.
 }
 else
 {
  external("dsmove", "main");
 }
 goto stopex;
}

void hit(void)
{
 external("phisbo", "hit");
 goto stopex;
}

void stopex(void)
{
stopex:
 return;
}