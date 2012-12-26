/*  Poor man's approximation of PI */
#define PI 3.1415926535898
/*  Macro for sin & cos in degrees */
#define Cos(th) cos(PI/180*(th))
#define Sin(th) sin(PI/180*(th))
/*  Determine number of elements in an array  */
#define Length(x) (sizeof (x) / sizeof *(x))

/*  Common #defines */
/*  Defaults for window sizing  */
#define DEF_WINDOW_HEIGHT 600
#define DEF_WINDOW_WIDTH 700
#define DEF_WINDOW_POS_H 150
#define DEF_WINDOW_POS_W 150

/*  Projection  */
#define DEF_ASP 1
#define DEF_DIM 25
#define DEF_TH 340
#define DEF_PH 30
#define DEF_FOV 25
#define DEF_ECX 0
#define DEF_ECY 0
#define DEF_ECZ 0

/*  Draw defaults  */
#define DEF_AXES 1
#define DEF_PARAMS 1
#define DEF_OVERLAY 0

/*  Skybox Textures  */
#define SKY_FRONT 0
#define SKY_RIGHT 1
#define SKY_LEFT 2
#define SKY_BACK 3
#define SKY_UP 4
#define SKY_DOWN 5

