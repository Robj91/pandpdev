void main(void)
{
 &save_x = get_sprite_with_this_brain(20, 0);
 sp_custom("blu1", &save_x, &current_sprite); 
 
 int &val1;
 int &val2;
 int &val3;
 int &val4;
 int &crap;
 
 &val1 = editor_seq(11, -1);
 if (&val1 > 0)
 {
  &save_x = sp_x(&current_sprite, -1);
  &save_y = sp_y(&current_sprite, -1);
  &save_y -= 35;
  &save_x -= 7;
  if (&val1 == 1)
  {
   &crap = create_sprite(&save_x, &save_y, 0, 422, 5);
   sp_nohit(&crap, 1);
   &save_y = sp_y(&current_sprite, -1);
   &save_y += 1;
   sp_que(&crap, &save_y);
   sp_custom("redscroll", &current_sprite, &crap);   
  }
  if (&val1 == 2)
  {
   &crap = create_sprite(&save_x, &save_y, 0, 422, 8);
   sp_nohit(&crap, 1);
   &save_y = sp_y(&current_sprite, -1);
   &save_y += 1;
   sp_que(&crap, &save_y);
   sp_custom("greenscroll", &current_sprite, &crap);
  }
  if (&val1 == 3)
  {
   &crap = create_sprite(&save_x, &save_y, 0, 422, 6);
   sp_nohit(&crap, 1);
   &save_y = sp_y(&current_sprite, -1);
   &save_y += 1;
   sp_que(&crap, &save_y);
   sp_custom("yellowscroll", &current_sprite, &crap);
  }
  if (&val1 == 4)
  {
   &crap = create_sprite(&save_x, &save_y, 0, 422, 7);
   sp_nohit(&crap, 1);
   &save_y = sp_y(&current_sprite, -1);
   &save_y += 1;
   sp_que(&crap, &save_y);
   sp_custom("purplescroll", &current_sprite, &crap);
  }
 } 
 
 &val1 = editor_seq(9, -1);
 if (&val1 == 1)
 {
 }
}

void talk(void)
{
 &save_x = editor_seq(9, -1);
 if (&save_x == 1)
 {
  return;
 }

 &val1 = get_item("item-rsu");
 &val2 = get_item("item-gsu");
 &val3 = get_item("item-ysu");
 &val4 = get_item("item-psu");
 &save_x = editor_seq(11, -1);
 if (&save_x == 0)
 {
  if (&val1 == 0)
  {
   if (&val2 == 0)
   {
    if (&val3 == 0)
    {
     if (&val4 == 0)
     {
      say("This is strage. Looks like something belongs here though..", 1);
      return;
     }
    }
   }
  }
 }
 
  &save_y = sp_y(&current_sprite, -1);
  &save_x = sp_x(&current_sprite, -1);
  &save_y -= 35;
  &save_x -= 7;
  &crap = editor_seq(11, -1);
  freeze(1);
  choice_start();
  (&val1 > 0) (&crap == 0) "Place down the red scroll"
  (&crap == 1) "Remove the red scroll"
  (&val2 > 0) (&crap == 0) "Place down the green scroll"
  (&crap == 2) "Remove the green scroll"
  (&val3 > 0) (&crap == 0) "Place down the yellow scroll"
  (&crap == 3) "Remove the yellow scroll"
  (&val4 > 0) (&crap == 0) "Place down the purple scroll"
  (&crap == 4) "Remove the purple scroll"
  "leave"
  choice_end();
 
  if (&result == 1)
  {
   &crap = create_sprite(&save_x, &save_y, 0, 422, 5);
   sp_nohit(&crap, 1);
   &save_y = sp_y(&current_sprite, -1);
   &save_y += 1;
   sp_que(&crap, &save_y);
   sp_custom("redscroll", &current_sprite, &crap);
   
   kill_this_item("item-rsu");
   
   //use editor seq to remember the red scroll has been placed
   editor_seq(11, 1);
  }
  if (&result == 2)
  {
   &crap = sp_custom("redscroll", &current_sprite, -1);
   sp_active(&crap, 0);

   add_item("item-rsu", 438, 14);
   Playsound(10,22050,0,0,0);

   //use editor seq to remember the red scroll has been placed
   editor_seq(11, 0);
  }
  
  if (&result == 3)
  {
   &crap = create_sprite(&save_x, &save_y, 0, 422, 8);
   sp_nohit(&crap, 1);
   &save_y = sp_y(&current_sprite, -1);
   &save_y += 1;
   sp_que(&crap, &save_y);
   sp_custom("greenscroll", &current_sprite, &crap);

   kill_this_item("item-gsu");

   editor_seq(11, 2);
  }
  if (&result == 4)
  {
   &crap = sp_custom("greenscroll", &current_sprite, -1);
   sp_active(&crap, 0);

   add_item("item-gsu", 438, 17);
   Playsound(10,22050,0,0,0);

   //use editor seq to remember the red scroll has been placed
   editor_seq(11, 0);
  }  
  
  if (&result == 5)
  {
   &crap = create_sprite(&save_x, &save_y, 0, 422, 6);
   sp_nohit(&crap, 1);
   &save_y = sp_y(&current_sprite, -1);
   &save_y += 1;
   sp_que(&crap, &save_y);
   sp_custom("yellowscroll", &current_sprite, &crap);

   kill_this_item("item-ysu");

   editor_seq(11, 3);
  }
  if (&result == 6)
  {
   &crap = sp_custom("yellowscroll", &current_sprite, -1);
   sp_active(&crap, 0);

   add_item("item-ysu", 438, 15);
   Playsound(10,22050,0,0,0);

   //use editor seq to remember the red scroll has been placed
   editor_seq(11, 0);
  }   
  
  if (&result == 7)
  {
   &crap = create_sprite(&save_x, &save_y, 0, 422, 7);
   sp_nohit(&crap, 1);
   &save_y = sp_y(&current_sprite, -1);
   &save_y += 1;
   sp_que(&crap, &save_y);
   sp_custom("purplescroll", &current_sprite, &crap);

   kill_this_item("item-psu");

   editor_seq(11, 4);
  }
  if (&result == 8)
  {
   &crap = sp_custom("purplescroll", &current_sprite, -1);
   sp_active(&crap, 0);

   add_item("item-psu", 438, 16);
   Playsound(10,22050,0,0,0);

   //use editor seq to remember the red scroll has been placed
   editor_seq(11, 0);
  } 
  
 &crap = get_sprite_with_this_brain(20, 0);
 &crap = is_script_attached(&crap);
 if (&crap > 0)
 {
  run_script_by_number(&crap, "puzzle");
 }
 unfreeze(1);
}