bool state_motion = false;

/**
 * get_motion_flank
 */
bool get_motion(){
  if (digitalRead(motionPin)==HIGH){
    if(state_motion){
      return false;
    } else {
      state_motion = true;
      return true;
    }
  } else {
    state_motion = false;
    return false;
  }
}

//--------------------------------

int state_taster = 0; //times on per cycle_time

/**
 * get_button_time in ms
 */
int get_button(){
  if (digitalRead(tasterPin)==LOW){
    state_taster++;
    return 0;
  } else {
    int result = state_taster * cycle_time;
    state_taster = 0;
    return result;
  }
}

