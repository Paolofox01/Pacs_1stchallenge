#ifndef ARMIJO_H
#define ARMIJO_H

#include <vector>
#include <iostream>
#include <functional>
#include <cmath>

#include "parameters.h"

#include <Eigen/Eigen>

//a function to modify alpha using the Armijo method
bool armijo (Eigen::VectorXd const & grad_x_k, Eigen::VectorXd const & x_k, MuparserFun & func, double & alpha);

#endif