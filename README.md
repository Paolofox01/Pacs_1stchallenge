# PACS 2024 first challenge

This code allows the user to find the minimum of a function using different methods and schemes.
The choice is between the Armijo rule, Exponential decay and Inverse decay for alpha and gradient method, momentum method and nesterov method for the scheme to implement. The choice will be done after launching the program.

## json file
the function to minimize and the other parameters are stored in the parameters.json file and can therefore be changed by changing their value in the file. They contain:

"tol_r" --> tolerance on the residual

"tol_s" --> tolerance on the step
    
"max_it" --> maximum number of iterations
    
"init_cond" : 
    "dim"     --> number of variables
    "first"   --> starting value for the first variable
    "second"  --> starting value for the second varriable

the points will be stored in a vector of the Eigen library

"init_alpha" --> value of alpha_0, preferably in (0.1, 0.5)

"eta" --> value of eta, preferably in (0.8, 0.99)

"mu" --> value of mu, preferably in (0.01, 0.3)

"fun" --> the function to minimize

"dfun" --> the components of the gradient of fun

fun and dfun will be read thanks to the muparser library, the muparser_fun.hpp and muparser_grad.hpp files are built to store and compute the function and the gradient in the case of 2 variables, x and y.

## how to launch

To compile the program change in the makefile the paths to the libraries needed(eigen, json and muparser).
Then just write make in the terminal and then ./main.

I am aware of the warnings from the eigen library during compilation, I don't know the reason for them. If they bother you write -w in CXXFLAGS in the Makefile

