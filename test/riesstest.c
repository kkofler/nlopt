#include <math.h>
#include <nlopt.h>
#include <stdio.h>

#define s 1e8

double myfunc(unsigned n, const double *x, double *grad, void *my_func_data)
{
    if (grad) {
        grad[0] = -s;
        //if (grad[0] < -1000.) grad[0] = -1000.;
    }
    return -s*x[0];
}

int main(void) {
  nlopt_opt opt = nlopt_create(NLOPT_LD_SLSQP, 1);
  nlopt_set_lower_bounds1(opt, -1.);
  nlopt_set_upper_bounds1(opt, 1.);
  nlopt_set_min_objective(opt, myfunc, NULL);
  nlopt_set_xtol_abs1(opt, 1e-10);
  nlopt_set_xtol_rel(opt, 1e-10);
  nlopt_set_ftol_abs(opt, 1e-10);
  nlopt_set_ftol_rel(opt, 1e-10);
  double x[] = {0.};
  double minf;
  int status = 0;
  if (nlopt_optimize(opt, x, &minf) < 0) {
    printf("nlopt failed!\n");
    status = 1;
  }
  else {
    printf("found minimum at f(%g) = %0.10g\n", x[0], minf);
  }
  nlopt_destroy(opt);
  return status;
}
