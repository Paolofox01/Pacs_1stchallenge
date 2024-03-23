#ifndef COMPUTEMIN_H
#define COMPUTEMIN_H

#include <vector>
#include "iostream"
#include "parameters.h"
#include "armijo.h"
#include <Eigen/Eigen>

// enumerator of the different methods
enum method { Armijo , 
                    base_Exponential, 
                    base_Inverse,
                    Momentum_Exp,
                    Momentum_Inv,
                    Nesterov_Exp,
                    Nesterov_Inv };


//function to compute the minimum

template <method metodo> Eigen::VectorXd compute_min(parameters const & pars)  {
    
    //we use two vectors (x_new and x_old) to to save the present and the past value of x_k

    Eigen::VectorXd x_new = pars.init_cond;
    Eigen::VectorXd x_old;

    //dim is the number of variables of the function

    int dim = x_new.size();

    //step will contain the difference between x_k and x_(k-1)

    Eigen::VectorXd step = Eigen::VectorXd::Zero(dim);

    //k is the number of iterations done
    
    unsigned int k=0;
    
    //we get our functions from the parameters

    MuparserFun fun = pars.func;
    MuparserGrad grad = pars.grad; 
    
    //start the iterations with our stopping conditions

    do {
        
        //alpha will contain the value of alpha_k computed with the chosen method
        double alpha = pars.init_alpha;

        x_old=x_new;

        //find alpha, x_new and update the other variables, for the nesterov method it is better to use smaller values of alpha, like 0.05
        if constexpr (metodo == method::base_Exponential || metodo == method::Momentum_Exp || metodo == method::Nesterov_Exp ) {

        alpha = alpha * exp( - static_cast<double>(k) * pars.mu);


    } else if constexpr (metodo == method::base_Inverse || metodo == method::Momentum_Inv || metodo == method::Nesterov_Inv) {

        alpha = alpha / ( 1 + ( static_cast<double>(k) * pars.mu ) );
       

    }  else {

        armijo( grad(x_new), x_new, fun, alpha);
        
    }

    
    if constexpr (metodo == method::Momentum_Exp || metodo == method::Momentum_Inv) {
        
        x_new = x_old - alpha * grad(x_old) + pars.eta * step;
    
        step = x_new - x_old;
    
        ++k;
    
    } else if constexpr (metodo == method::Nesterov_Exp || metodo == method::Nesterov_Inv) {
    
    x_new = x_old + pars.eta * step - alpha * grad(x_old + pars.eta * step);
    
    step = x_new - x_old;
    
        ++k;

    
    } else {   
    
        x_new = x_old - alpha * grad(x_old);

        step = x_new - x_old;
    
        ++k; }


    } while(k < pars.max_it && step.norm() > pars.tol_s && grad(x_new).norm() > pars.tol_r );

    std::cout << "The process finished in "  << k  << " iterations"   << std::endl;
    

    //return the minimum
    return x_new;
}



#endif