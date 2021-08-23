//this script conducts the necessary checks to determine if Dink should start pushing a sprite
//detects and runs on all move-able sprites he is touching. 

//This script is spawned by the first move-able sprite he touches on a screen. 
//only 1 instance of this script will run at a time.

//This script cannot contain any waits or there's a possibility of push and pull breaking.

void main(void)
{
 //just in case - make it die on screen change.
 script_attach(0);
 int &hybsprite = &save_y;
}

void validate(void)
{
 //save this script number as a custom key attached to the sprite
 sp_custom("PP-pup", &save_y, &current_script);
 
 //save the players directional sequence in a custom key so we can assure it hasn't changed later on.
 &save_x = sp_pseq(1, -1);
 sp_custom("pseq-origin", &hybsprite, &save_x);
 &save_y = math_mod(&save_x, 2);
 //check if seq is correct for pushing and pulling, and save result in custom key 
 if (&save_x > 70)
 {
  if (&save_x < 80)
  {
   if (&save_y == 0)
   {
    //Here we have determined that Dink's seq is between 70 and 80, and an even number (we don't want diags)
    sp_custom("CanPush", &hybsprite, 1);
   }
   else
   {
    //dink is facing a diagonal direction, no point continuing, he can't push diagonal
    goto pupend;
   }
  }
 } 
 
 &save_x = sp_custom("CanPush", &hybsprite, 1);
 if (&save_x <= 0)
 {
  //no point continuing if Dink can't push  
  goto pupend; 
 }  

 //store dinks direction.
 &save_x = sp_dir(1, -1);
 sp_custom("pushdir", &hybsprite, &save_x);

 //work out the pulldir - it will be opposite the pushdir
 &save_x = sp_custom("pushdir", &hybsprite, -1);
 if (&save_x == 2) 
  sp_custom("pulldir", &hybsprite, 8);
  
 if (&save_x == 4)
  sp_custom("pulldir", &hybsprite, 6); 
  
 if (&save_x == 6)
  sp_custom("pulldir", &hybsprite, 4);
  
 if (&save_x == 8)
  sp_custom("pulldir", &hybsprite, 2);
 
 //and set the move-axis custom key. 1 = x axis. 2 = y axis.
 if (&save_x == 2)
  sp_custom("move-axis", &hybsprite, 2);
 
 if (&save_x == 4)
  sp_custom("move-axis", &hybsprite, 1);  
 
 if (&save_x == 6)
  sp_custom("move-axis", &hybsprite, 1);  
  
 if (&save_x == 8)
  sp_custom("move-axis", &hybsprite, 2);
  
 //set whether will be pushing in a positive or negative direction. (Adding or reducing X or Y value as we push)
 if (&save_x == 2)
  sp_custom("PushPosNeg", &hybsprite, 2);
 
 if (&save_x == 4)
  sp_custom("PushPosNeg", &hybsprite, 1);  
 
 if (&save_x == 6)
  sp_custom("PushPosNeg", &hybsprite, 2);  
  
 if (&save_x == 8)
  sp_custom("PushPosNeg", &hybsprite, 1);   

 //set whether will be pulling in a positive or negative direction. (Adding or reducing X or Y value as we push)
 &save_x = sp_custom("pulldir", &hybsprite, -1);
 if (&save_x == 2)
  sp_custom("PullPosNeg", &hybsprite, 2);
 
 if (&save_x == 4)
  sp_custom("PullPosNeg", &hybsprite, 1);  
 
 if (&save_x == 6)
  sp_custom("PullPosNeg", &hybsprite, 2);  
  
 if (&save_x == 8)
  sp_custom("PullPosNeg", &hybsprite, 1);  
 
 //store dinks coordinates
 &save_x = sp_x(1, -1);
 &save_y = sp_y(1, -1);
 sp_custom("dinkox", &hybsprite, &save_x);
 sp_custom("dinkoy", &hybsprite, &save_y);

 //store hybsprite's coordinates
 &save_x = sp_x(&hybsprite, -1);
 &save_y = sp_y(&hybsprite, -1);
 sp_custom("spriteox", &hybsprite, &save_x);
 sp_custom("spriteoy", &hybsprite, &save_y);
 
 &save_x = sp_custom("HBOX", &hybsprite, -1);
 if (&save_x > 0)
 {
  external("phispush", "quick_check", &hybsprite);
  if (&return == 0)
  {   
   goto pupend;
  }
 }
}

void pupend(void)
{
pupend:
 return(1);
}