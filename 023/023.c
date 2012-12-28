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

  /* Star */
  int i;
  for (i=0; i<5; i++) {
    xyzPentLarge[i][0] = Sin(72*i);
    xyzPentLarge[i][1] = Cos(72*i);
    xyzPentLarge[i][2] = 0;
    //xyzPentSmall[i][0] = 0.35*Sin(72*i+36);
    xyzPentSmall[i][0] = 0.381967*Sin(72*i+36);
    xyzPentSmall[i][1] = 0.381967*Cos(72*i+36);
    //xyzPentSmall[i][1] = 0.35*Cos(72*i+36);
    xyzPentSmall[i][2] = 0;
  }
}

void windowKey(unsigned char key,int x,int y)
{
  /*  Exit on ESC */
  if (key == 27) exit(0);
  /*  Change modes */
  else if (key == '-' && mode>0) mode--;
  else if (key == '-' && mode<=0) mode=DEF_MODES-1;
  else if (key == '+' && mode<DEF_MODES-1) mode++;
  else if (key == '+' && mode>=DEF_MODES-1) mode=0;

  glutPostRedisplay();
}

void reshape(int w, int h)
{
  asp = (h>0) ? (double)w/h : 1;
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-asp*dim,asp*dim,-dim,+dim,-dim,+dim);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

/********
 * Tesselation callbacks
 ********/
/*
 * tessFatal
 * ------
 * Report Tessalation errors
 */
void tessFatal(GLenum err)
{
   fatal("Tessellation Fatal Error: %s\n",gluErrorString(err));
}

/*
 * tessCombine
 * ------
 * Generate vertex that combines vertices
 */
void tessCombine(double coords[3], double* data[4], float weight[4], double** result)
{
   *result = (double*) malloc(3 * sizeof(double));
   (*result)[0] = coords[0];
   (*result)[1] = coords[1];
   (*result)[2] = coords[2];
}

/*
 *  Tesselated star polygon
 */
void tesselatedStar(int star, int type, int hole, int rule)
{
   int i;
   //  Create new Tesselator
   GLUtesselator* tess = gluNewTess();
   //  Set polygon type (Line or Fill) and line width
   glPolygonMode(GL_FRONT_AND_BACK,type);
   if (type==GL_LINE) glLineWidth(3);

   //  Set winding rule
   gluTessProperty(tess,GLU_TESS_WINDING_RULE,rule);
   //  Set callbacks
   gluTessCallback(tess,GLU_TESS_BEGIN  ,glBegin);
   gluTessCallback(tess,GLU_TESS_END    ,glEnd);
   gluTessCallback(tess,GLU_TESS_VERTEX ,glVertex3dv);
   gluTessCallback(tess,GLU_TESS_COMBINE,tessCombine);
   gluTessCallback(tess,GLU_TESS_ERROR  ,tessFatal);

   //  Start polygon
   gluTessBeginPolygon(tess,NULL);
   //  Draw outside star
   if (star) {
      gluTessBeginContour(tess);
      for (i=0; i<5; i++)
         gluTessVertex(tess,xyzPentLarge[(2*i)%5],xyzPentLarge[(2*i)%5]);
      gluTessEndContour(tess);
   } else {
      //  Draw outside pentagon
      gluTessBeginContour(tess);
      for (i=0; i<5; i++)
         gluTessVertex(tess,xyzPentLarge[i],xyzPentLarge[i]);
      gluTessEndContour(tess);
      //  Draw inside pentagon
      gluTessBeginContour(tess);
      for (i=0; i<5; i++)
         gluTessVertex(tess,xyzPentSmall[i],xyzPentSmall[i]);
      gluTessEndContour(tess);
   }

   //  Draw diamond
   if (hole) {
      gluTessBeginContour(tess);
      for (i=0; i<5; i++)
         gluTessVertex(tess,xyzPentLarge[i],xyzPentLarge[i]);
      gluTessEndContour(tess);
   }

   //  End of polygon
   gluTessEndPolygon(tess);
   //  Delete tessalator
   gluDeleteTess(tess);

   //  Set polygon mode back to fill
   if (type==GL_LINE) glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}


/**
 *
 */
void drawLargePentagon(void)
{
  // Pentagon
  int i;
  glLineWidth(1);
  glColor3f(0,1,0); // green is cool
  glBegin(GL_LINE_LOOP);
  for (i=0; i<5; i++)
    glVertex3dv(xyzPentLarge[i]);
  glEnd();

  // Vertices
  glColor3f(1,1,1);
  for (i=0; i<5; i++) {
    glRasterPos3dv(xyzPentLarge[i]);
    print("%d",i);
  }
}

void drawSmallPentagon(void)
{
  // Pentagon
  int i;
  glLineWidth(1);
  glColor3f(0,0,1); // blue is cooler
  glBegin(GL_LINE_LOOP);
  for (i=0; i<5; i++)
    glVertex3dv(xyzPentSmall[i]);
  glEnd();

  // Vertices
  glColor3f(1,1,1);
  for (i=0; i<5; i++) {
    glRasterPos3dv(xyzPentSmall[i]);
    print("%d",i);
  }
}

void drawFilledOutline(void)
{
  int i;
  glBegin(GL_POLYGON);
  for (i=0; i<5; i++)
    glVertex3dv(xyzPentLarge[i]);
  glEnd();
}

void drawOutlineStar(void)
{
  int i;
  glLineWidth(3);
  glBegin(GL_LINE_LOOP);
  for (i=0; i<5; i++)
    glVertex3dv(xyzPentLarge[(2*i)%5]);
  glEnd();
}

void drawFilledStar(void)
{
  int i;
  glBegin(GL_POLYGON);
  for (i=0; i<5; i++)
    glVertex3dv(xyzPentLarge[(2*i)%5]);
  glEnd();
}

void drawFilledStarTri(void)
{
  int i;
  glBegin(GL_TRIANGLES);
  for (i=0; i<5; i++) {
    glVertex3dv(xyzPentSmall[(i+4)%5]);
    glVertex3dv(xyzPentLarge[i]);
    glVertex3dv(xyzPentSmall[i]);
  }
  glEnd();

  glColor3f(1,0.8,0);
  glBegin(GL_POLYGON);
  for (i=0; i<5; i++)
    glVertex3dv(xyzPentSmall[i]);
  glEnd();
}

void drawFilledStarQuad(void)
{
  int i;
  glBegin(GL_QUADS);
  for (i=0; i<5; i++) {
    glVertex2f(0,0);
    glVertex3dv(xyzPentSmall[(i+4)%5]);
    glVertex3dv(xyzPentLarge[i]);
    glVertex3dv(xyzPentSmall[i]);
  }
  glEnd();

  glColor3f(1,0.8,0);
  glLineWidth(3);
  for (i=0; i<5; i++) {
    glBegin(GL_LINE_LOOP);
    glVertex2f(0,0);
    glVertex3dv(xyzPentSmall[(i+4)%5]);
    glVertex3dv(xyzPentLarge[i]);
    glVertex3dv(xyzPentSmall[i]);
    glEnd();
  }
}

/*
 * display()
 * ------
 * Draw something
 */
void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  // Draw stuff here
  glColor3f(1,1,0);
  switch (mode) {
    // Outline
  case 0:
    break;
    //  Filled outline
  case 1:
    drawFilledOutline();
    break;
    //  Outline star
  case 2:
    drawOutlineStar();
    break;
    //  Filled star (INCORRECT)
  case 3:
    drawFilledStar();
    break;
    //  Filled star (Triangles + pentagon)
  case 4:
    drawFilledStarTri();
    break;
    //  Filled star (Quads)
  case 5:
    drawFilledStarQuad();
    break;
    //  Outline star (tesselation with positive winding rule)
  case 6:
    tesselatedStar(1,GL_LINE,0,GLU_TESS_WINDING_POSITIVE);
    break;
    //  Fill star (tesselation with positive winding rule)
  case 7:
    tesselatedStar(1,GL_FILL,0,GLU_TESS_WINDING_POSITIVE);
    break;
    //  Outline star (tesselation with odd winding rule)
  case 8:
    tesselatedStar(1,GL_LINE,0,GLU_TESS_WINDING_ODD);
    break;
    //  Fill star (tesselation with odd winding rule)
  case 9:
    tesselatedStar(1,GL_FILL,0,GLU_TESS_WINDING_ODD);
    break;
    //  Outline star with hole (tesselation with positive winding rule)
  case 10:
    tesselatedStar(1,GL_LINE,1,GLU_TESS_WINDING_POSITIVE);
    break;
    //  Fill star with hole (tesselation with positive winding rule)
  case 11:
    tesselatedStar(1,GL_FILL,1,GLU_TESS_WINDING_POSITIVE);
    break;
    //  Outline star with hole (tesselation with odd winding rule)
  case 12:
    tesselatedStar(1,GL_LINE,1,GLU_TESS_WINDING_ODD);
    break;
    //  Fill star with hole (tesselation with odd winding rule)
  case 13:
    tesselatedStar(1,GL_FILL,1,GLU_TESS_WINDING_ODD);
    break;
    //  Outline pentagon with hole (tesselation with odd winding rule)
  case 14:
    tesselatedStar(0,GL_LINE,1,GLU_TESS_WINDING_ODD);
    break;
    //  Fill pentagon with hole (tesselation with odd winding rule)
  case 15:
    tesselatedStar(0,GL_FILL,1,GLU_TESS_WINDING_ODD);
    break;
  default:
    break;
  }

  drawLargePentagon();
  drawSmallPentagon();

  // Display parameters
  glColor3f(1,1,1);
  printAt(5,5,"Mode=%d (%s)",mode,text[mode]);
  
  // Flush and swap
  glFlush();
  glutSwapBuffers();
}

/*
 *  main()
 *  ----
 *  Start up GLUT and tell it what to do
 */
int main(int argc, char **argv)
{
  initGlobals();

  /* screencast specific variables */
  windowName = "OpenGL screenscasts 23: Tesselation";
  screencastID = 23;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(windowWidth,windowHeight);
  glutInitWindowPosition(windowPosWidth,windowPosHeight);
  glutCreateWindow(windowName);

  glutDisplayFunc(display);
  glutIdleFunc(display);
  glutKeyboardFunc(windowKey);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}
