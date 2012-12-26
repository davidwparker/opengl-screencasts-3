#include "screencasts.h"

/*
 * initGlobals()
 * ------
 * Initializes the global variables.
 */
void initGlobals(void)
{
  /* WINDOW */
  windowHeight=DEF_WINDOW_HEIGHT;
  windowWidth=DEF_WINDOW_WIDTH;
  windowPosHeight=DEF_WINDOW_POS_H;
  windowPosWidth=DEF_WINDOW_POS_W;

  /* PROJECTION */
  dim=DEF_DIM;
  th=DEF_TH;
  ph=DEF_PH;
  fov=DEF_FOV;
  asp=DEF_ASP;
  ecX=DEF_ECX;
  ecY=DEF_ECY;
  ecZ=DEF_ECZ;
}

/*
 *  initSkybox
 *  ------
 *  initializes all of our textures for the skybox background
 */
void initSkybox(void)
{
  /*
    SKY_FRONT 0
    SKY_RIGHT 1
    SKY_LEFT 2
    SKY_BACK 3
    SKY_UP 4
    SKY_DOWN 5
   */
  skybox[SKY_FRONT] = loadTexBMP("txStormydays_front.bmp");
  skybox[SKY_RIGHT] = loadTexBMP("txStormydays_right.bmp");
  skybox[SKY_LEFT] = loadTexBMP("txStormydays_left.bmp");
  skybox[SKY_BACK] = loadTexBMP("txStormydays_back.bmp");
  skybox[SKY_UP] = loadTexBMP("txStormydays_up.bmp");
  skybox[SKY_DOWN] = loadTexBMP("txStormydays_down.bmp");
}


void windowKey(unsigned char key,int x,int y)
{
  /*  Exit on ESC */
  if (key == 27) exit(0);
  /*  Change field of view angle */
  else if (key == '-' && key>1) fov--;
  else if (key == '+' && key<179) fov++;

  redisplayAll();
}

void windowSpecial(int key,int x,int y)
{
  /*  Right/Left - rotate */
  if (key == GLUT_KEY_RIGHT) th += 5;
  else if (key == GLUT_KEY_LEFT) th -= 5;
  /*  Up/Down - elevation */
  else if (key == GLUT_KEY_UP) ph += 5;
  else if (key == GLUT_KEY_DOWN) ph -= 5;
  
  /*  Keep angles at +/- 360 degrees */
  th %= 360;
  ph %= 360;

  redisplayAll();
}

/*
 *  main()
 *  ----
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
  initGlobals();

  /* screencast specific variables */
  windowName = "OpenGL screenscasts 21: Skybox";
  screencastID = 21;
  
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(windowWidth,windowHeight);
  glutInitWindowPosition(windowPosWidth,windowPosHeight);
  glutCreateWindow(windowName);

  glutDisplayFunc(display);
  glutReshapeFunc(displayReshape);
  glutKeyboardFunc(windowKey);
  glutSpecialFunc(windowSpecial);

  initSkybox();

  redisplayAll();
  glutMainLoop();
  return 0;
}

