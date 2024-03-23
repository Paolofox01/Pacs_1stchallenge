#include "armijo.h"
 
bool armijo (Eigen::VectorXd const & grad_x_k, Eigen::VectorXd const & x_k, MuparserFun & func, double & alpha) {

    //choose sigma and compute the ( ||grad(x_k)||^2 ) *  sigma

    double const sig = 0.2;
    double sig_norm_grad2 = std::pow(grad_x_k.norm(), 2) * sig; 
        
    //halve alpha until the stopping condition is satisfied

    while ( func(x_k) - func(x_k - alpha * grad_x_k) < alpha * sig_norm_grad2 ) {
        alpha = alpha / 2;
    }  

    return true;
}