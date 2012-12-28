#include "screencasts.h"
/*  ID-used to keep screencasts separate  */
int screencastID = 0;

/*  WINDOW  */
char *windowName="OpenGL screenscasts XX: Placeholder";
int windowHeight=DEF_WINDOW_HEIGHT;
int windowWidth=DEF_WINDOW_WIDTH;
int windowPosHeight=DEF_WINDOW_POS_H;
int windowPosWidth=DEF_WINDOW_POS_W;

/*  PROJECTION  */
double asp=DEF_ASP;
double dim=DEF_DIM;
int th=DEF_TH;
int ph=DEF_PH;
int fov=DEF_FOV;

/*  FOG  */
GLint fogMode;
GLfloat density=DEF_DENS;
GLfloat fogColor[4]={0.5,0.5,0.5,1.0};
char *curFogMode="";

/*  CUBE RGB  */
int r=1;
int g=0;
int b=0;
