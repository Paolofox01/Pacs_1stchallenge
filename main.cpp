
#include "compute_min.h"
#include "json.hpp"
#include <fstream>
#include "parameters.h"
using json = nlohmann::json;
#include <string>



int main (int argc, char **argv) 
{
    //read the .json file to get the parameters

    std::ifstream f("parameters.json");
    json paras = json::parse(f);

    //put the initial conditions in a vector

    int dim = paras["init_cond"].value("dim", 0);
    Eigen::VectorXd init_cond(dim);
    init_cond <<  paras["init_cond"].value("first", 1e-7), paras["init_cond"].value("second", 1e-7);
    
    //read the function and the gradient from the file

    std::string funString = paras.value("fun","");
    std::string Grad1 = paras["dfun"].value("primo","");
    std::string Grad2 = paras["dfun"].value("secondo","");
    MuparserFun Fun(funString);
    MuparserGrad Grad(Grad1, Grad2);

    //put the data in a struct "parameters"

    parameters dati(Fun, Grad, init_cond, paras.value("tol_r", 1e-7), paras.value("tol_s", 1e-7), paras.value("init_alpha", 0.2), paras.value("max_it",100), paras.value("mu",0.2), paras.value("eta",0.9));

    //choose the method to calculate the minimum

    std::cout << "Choose a method to compute alpha_k:" << std::endl;
    std::cout << "1. Armijo"  << std::endl;
    std::cout << "2. Exponential"  << std::endl;
    std::cout << "3. Inverse"   << std::endl;
    std::cout << "Enter your choice (1-3): "  << std::endl;

    int choice;

    std::cin >> choice;

    if (choice == 3 || choice == 2)
    {
        std::cout << "Choose the scheme to implement:" << std::endl;
    std::cout << "1. Gradient method"  << std::endl;
    std::cout << "2. Momentum method"  << std::endl;
    std::cout << "3. Nesterov method"   << std::endl;
    std::cout << "Enter your choice (1-3): "  << std::endl;

        int choice2;

    std::cin >> choice2;

        choice = choice + 2 * (choice2-1);
    }

    

    //find the minimum with the corresponding method and print it

    if (choice == 1) {
            Eigen::VectorXd min = compute_min<method::Armijo>(dati);

            std::cout << "using the Armijo method the minimum is"   << std::endl;
            
            std::cout << min <<std::endl; }
    else if (choice == 2) {

            Eigen::VectorXd min = compute_min<method::base_Exponential>(dati);
           
            std::cout << "using the Exponential method with the Gradient scheme the minimum is"   << std::endl;
            
            std::cout << min <<std::endl;}
    else if (choice == 3) {
            Eigen::VectorXd min = compute_min<method::base_Inverse>(dati);
            
            std::cout << "using the Inverse method with the Gradient scheme the minimum is"   << std::endl;
            
            std::cout << min <<std::endl;}
    else if (choice == 4) {
            Eigen::VectorXd min = compute_min<method::Momentum_Exp>(dati);
            
            std::cout << "using the Exponential method with the Momentum scheme the minimum is"   << std::endl;
            
            std::cout << min <<std::endl;}
    else if (choice == 5) {
            Eigen::VectorXd min = compute_min<method::Momentum_Inv>(dati);

            std::cout << "using the Inverse method with the Momentum scheme the minimum is"   << std::endl;
            
            std::cout << min <<std::endl;}
    else if (choice == 6) {
            Eigen::VectorXd min = compute_min<method::Nesterov_Exp>(dati);

            std::cout << "using the Exponential method with the Nesterov scheme the minimum is"   << std::endl;
            
            std::cout << min <<std::endl;}
    else if (choice == 7) {
            Eigen::VectorXd min = compute_min<method::Nesterov_Inv>(dati);

            std::cout << "using the Inverse method with the Nesterov scheme the minimum is"   << std::endl;
            
            std::cout << min <<std::endl;}                
    else {
            std::cerr << "Invalid choice!" << std::endl;
    } 
    
    
    return 0;
}