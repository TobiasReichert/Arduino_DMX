void dmx_set(){ //float master, bool blink, int _r, int _g, int _b) {
  int temp_r;
  int temp_g;
  int temp_b;
  
  temp_r = r * master;
  temp_g = g * master;
  temp_b = b * master;
  
  //links
  DmxSimple.write(1, temp_r);
  DmxSimple.write(2, temp_g);
  DmxSimple.write(3, temp_b);

  //mitte
  DmxSimple.write(21, 255 * master * blink);
  DmxSimple.write(22, 255);
  DmxSimple.write(23, 255);
  DmxSimple.write(24, 255);

  //rechts
  DmxSimple.write(41, temp_r);
  DmxSimple.write(42, temp_g);
  DmxSimple.write(43, temp_b);
  DmxSimple.write(44, 255);

  //disko
  DmxSimple.write(61, 255);
  DmxSimple.write(62, temp_r);
  DmxSimple.write(63, temp_g);
  DmxSimple.write(64, temp_b);
}
