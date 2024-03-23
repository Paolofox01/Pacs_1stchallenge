#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#include <vector>
#include <functional>
#include <Eigen/Eigen>
#include "muparser_fun.hpp"
#include "muparser_grad.hpp"

// a struct that contains the functions and all the parameters needed  
struct parameters {
MuparserFun func;
MuparserGrad grad;
Eigen::VectorXd init_cond;
double tol_r;
double tol_s;
double init_alpha;
unsigned int max_it;
double mu;
double eta;

};

#endif