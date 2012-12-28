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

  /* FOG */
  fogMode=GL_EXP;
  curFogMode="GL_EXP";
}

/*
 * cube()
 * ------
 * Draw a cube of rotation ph, th with color RGB
 */
void cube(void) {
  glRotatef(ph, 1.0, 0.0, 0.0);
  glRotatef(th, 0.0, 1.0, 0.0);
  glColor3f(r, g, b);
  glutSolidCube(2);
}


void windowKey(unsigned char key,int x,int y)
{
  /*  Exit on ESC */
  if (key == 27) exit(0);
  else if (key == '1') {
    if (density >= 1.0) density = 1.0;
    else density += 0.05;
  }
  else if (key == '2') {
    if (density <= 0.0) density = 0.0;
    else density -= 0.05;
  }
  else if (key == 'r') r = 1.0-r;
  else if (key == 'g') g = 1.0-g;
  else if (key == 'b') b = 1.0-b;
  else if (key == 'f') {
    // change fog modes
    if (fogMode == GL_EXP) {
      fogMode = GL_EXP2;
      curFogMode = "GL_EXP2";
    }
    else if (fogMode == GL_EXP2) {
      fogMode = GL_LINEAR;
      curFogMode = "GL_LINEAR";
    }
    else if (fogMode == GL_LINEAR) {
      fogMode = GL_EXP;
      curFogMode = "GL_EXP";
    }
  }

  glutSwapBuffers();
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

  glutSwapBuffers();
}

/*
 * display()
 * ------
 * Setup fog and draw cube
 */
void display(void) {
  glClearColor(0.0,0.0,0.0,1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  // More on Fog at the Red Book:
  // http://www.glprogramming.com/red/chapter06.html#name3
  // glFog{if}v(TARGET, MODE)
  // TARGET = GL_FOG_MODE
  // MODE = GL_EXP, GL_EXP2, GL_LINEAR
  glEnable(GL_FOG);
  glFogi(GL_FOG_MODE, fogMode);
  // TARGET = GL_FOG_DENSITY, GL_FOG_START, GL_FOG_END
  // VALUE = 1,0,1 (default)
  glFogf(GL_FOG_DENSITY, density);
  //  glFogf(GL_FOG_START, 2.0);
  //  glFogf(GL_FOG_END, 3.0);
  cube();
  //  glDisable(GL_FOG);
  //  cube();

  // Print the current settings
  glColor3f(1,1,1);
  printAt(5,45, "R=%s, G=%s, B=%s", (r>0)?"On":"Off",(g>0)?"On":"Off",(b>0)?"On":"Off");
  printAt(5,25, "Fog Mode= %s", curFogMode);
  printAt(5,05, "Density= %f", density);

  // Flush and swap
  glFlush();
  glutSwapBuffers();
}

void reshape(int w, int h) {
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

/*
 *  main()
 *  ----
 *  Start up GLUT and tell it what to do
 */
int main(int argc, char **argv) {
  initGlobals();

  /* screencast specific variables */
  windowName = "OpenGL screenscasts 22: Fog";
  screencastID = 22;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(windowWidth,windowHeight);
  glutInitWindowPosition(windowPosWidth,windowPosHeight);
  glutCreateWindow(windowName);

  glEnable(GL_FOG);
  glFogfv(GL_FOG_COLOR, fogColor);
  glHint(GL_FOG_HINT, GL_DONT_CARE);

  glutDisplayFunc(display);
  glutIdleFunc(display);
  glutKeyboardFunc(windowKey);
  glutSpecialFunc(windowSpecial);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}
