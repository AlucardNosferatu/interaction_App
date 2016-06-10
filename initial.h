#ifndef INITIAL
#define INITIAL

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <QVector>

/* Parameter Declarations */
const int N_CHANNEL = 6;
const int N_FRENQUENCY = 500;
static float mav0[N_CHANNEL] = {0.00001454F, 0.00000490F, 0.00006819F, 0.00000523F,
                         0.00000531F, 0.00000475F};
static float threshold = 0.00000001467707833514250F;

/* Function Declarations */
void re_initial(float x[N_FRENQUENCY][N_CHANNEL]);

#endif // INITIAL
