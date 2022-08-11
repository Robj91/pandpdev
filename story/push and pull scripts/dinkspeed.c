//All items/magic that affect Dinks speed in any way need to be added to this script. Read the comments below and copy herb boots example to add other items/magic.

void getspeed(void)
{
 //Anything in your dmod that affects Dinks speed needs to be added here, see herb boots below.

 ////////////////////
 //HERB BOOTS START//
 ////////////////////
 //enter compare magic/weapon line for speed buff item
 &save_x = compare_weapon("item-bt");
 if (&save_x > 0)
 {
  //return the sp_speed equivelant of set_dink_speed (can be found in the DinkC reference under the "set_dink_speed" function)
  return(6);
 }
 //////////////////
 //HERB BOOTS END//
 //////////////////

 //if all above condition checks returned 0, that means Dinks speed is normal (sp_speed equivelant of 3)
 return(3);
 
 kill_this_task();
}
