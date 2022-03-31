#ifndef MATRIX_INCLUDED
#define MATRIX_INCLUDED
#include "../include/gsl/gsl_blas.h"
#include "../include/gsl/gsl_matrix.h"
#include "../include/gsl/gsl_vector.h"
#include "../header/vector.h"
#include "../include/GL/gl.h"
#include <math.h>

gsl_matrix *matrix_look_at(gsl_vector *,
                           gsl_vector *,
                           gsl_vector *);

gsl_matrix *matrix_perspective(double,
                               double,
                               double,
                               double);

void matrix_destroy(gsl_matrix *);

void matrix_get_float(gsl_matrix *,
                      float **matrixf,
                      int ,
                      int);

void matrix_print(gsl_matrix *,
                  int ,
                  int);

#endif
