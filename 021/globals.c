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
double ecX=DEF_ECX;
double ecY=DEF_ECY;
double ecZ=DEF_ECZ;

/*  COLORS  */
float white[]={1,1,1,1};

/*  TEXTURES  */
int skybox[6];
