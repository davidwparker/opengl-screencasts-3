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

/*  Fog  */
#define DEF_DENS 0.3
