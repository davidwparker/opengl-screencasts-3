#ifndef SCREENCASTS
#define SCREENCASTS

/*  Standard headers  */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <time.h>

/*  OpenGL and friends  */
#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/*  Includes  */
#include "common.h"  /* common is just defines */

/*  COMMON  */
#include "print.h"   /* print convenience */

/*  GLOBALS (externs required here)  */
/*  Don't forget to initialize globals!  */
extern int screencastID;

/*  Window info  */
extern char *windowName;
extern int windowWidth;
extern int windowHeight;
extern int windowPosWidth;
extern int windowPosHeight;

/*  View  */
extern double asp;/* aspect ratio */
extern double dim;/* dimension of orthogonal box */
extern int th;    /* azimuth of view angle */
extern int ph;    /* elevation of view angle */
extern int fov;   /* field of view for perspective */

/*  Fog  */
extern GLint fogMode;
extern GLfloat density;
extern GLfloat fogColor[4];
extern char *curFogMode;

/*  Cube RGB  */
extern int r;
extern int g;
extern int b;

#endif
