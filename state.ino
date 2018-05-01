#define s_off 0
#define s_on 1
#define s_permanent_off 2
#define s_permanent_on 3
#define s_fade_off 4
#define s_blink 5

int blink_count = 0;

/**
  * Statemachine
  */
void statemachine(){

  int button_time = get_button();

  switch(state) {
    case s_off: 
      master = 0;
      if(get_motion()){
        state = s_on;
      } else if(get_button()){
        state = s_on;
      }
      break;
      
    case s_on: 
      master = 1;
      if(get_motion()){
        state = s_blink;
      } else if(button_time >= 1000){
        state = s_permanent_off;
      } else if(button_time){
        state = s_fade_off;
      }
      break;
      
    case s_permanent_off:
      master = 0;
      if(button_time >= 1000){
        state = s_permanent_on;
      } else if(button_time){
        state = s_on;
      } 
      break;

    case s_permanent_on: 
      master = 1;
      if(button_time >= 1000){
        state = s_permanent_off;
      } else if(button_time){
        state = s_fade_off;
      } 
      break;

    case s_fade_off: 
      master -= 0.01;
      if(master < 0.01){
        master = 0;
        state = s_off; 
      }
      break;

    case s_blink: 
      if(blink_count % 2 == 0){
        blink = !blink;
      }
    
      blink_count++;
    
      if(blink_count > 8){
        blink = true;
        state = s_on;
        blink_count = 0;
      }
      break;


      
    default: 
      printf("state ist irgendwas\n"); 
      break;
  }
}

