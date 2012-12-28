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

/*  TESSELATION  */
int mode=DEF_MODE;
double xyzPentLarge[5][3];
double xyzPentSmall[5][3];
char* text[16] = {"Just the Outline",
		"Filled-in Outline",
		"Star Outline",
		"Incorrect Filled-in Star",
		"Triangles and Pentagon",
		"Quads",
		"Tesselation Outline (Positive)",
		"Tesselation Fill (Positive)",
                "Tesselation Outline (Odd)",
		"Tesselation Fill (Odd)",
                "Tesselation Outline with Hole (Positive)",
		"Tesselation Fill with Hole (Positive)",
                "Tesselation Outline with Hole (Odd)",
		"Tesselation Fill with Hole (Odd)",
                "No Star Tesselation Outline with Hole (Odd)",
		"No Star Tesselation Fill with Hole (Odd)"};
