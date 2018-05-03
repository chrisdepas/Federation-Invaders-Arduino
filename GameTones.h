#ifndef __GAMETONES_H__
#define __GAMETONES_H__


/* Decreasing frequency with increasing length */
toneNote playerDeathTone[] = {
 toneNote(50, 1000), 
 toneNote(60, 900), 
 toneNote(70, 800), 
 toneNote(80, 700), 
 toneNote(90, 600), 
 toneNote(100, 500), 
 toneNote(110, 400), 
 toneNote(120, 300), 
 toneNote(130, 200), 
 toneNote(150, 100), 
 toneEnd()
};

toneNote playerShootTone[] = {
 toneNote(20, 500), 
 toneNote(20, 700), 
 toneNote(20, 450), 
 toneNote(20, 600), 
 toneEnd()
};
  
toneNote testTone[] = {
  toneNote(200, 262), 
  toneNote(200, 392), 
  toneNote(400, 440),
  toneNote(200, 262), 
  toneNote(200, 392), 
  toneNote(400, 440),
  
  toneNote(200, 220), 
  toneNote(200, 392), 
  toneNote(400, 440),
  toneNote(200, 220), 
  toneNote(200, 392), 
  toneNote(400, 440),
  
  toneNote(200, 294), 
  toneNote(200, 392), 
  toneNote(400, 440),
  toneNote(200, 294), 
  toneNote(200, 392), 
  toneNote(400, 440),
  
  toneNote(200, 262), 
  toneNote(200, 392), 
  toneNote(400, 440),
  toneNote(200, 262), 
  toneNote(200, 392), 
  toneNote(400, 440),
  
  toneEnd()
};

  
toneNote introTone[] = {
  toneNote(256, 554),
  toneNote(256, 370),
  toneNote(256, 554),
  toneNote(256, 370),
  toneNote(256, 523),
  toneNote(256, 415),
  tonePause(256),
  toneNote(256, 415),
  toneNote(256, 554),
  toneNote(256, 466),
  toneNote(256, 554),
  toneNote(256, 233),
  toneNote(256, 698),
  toneNote(256, 554),
  toneNote(256, 831),
  toneNote(256, 622),
  toneEnd()
};



#endif
