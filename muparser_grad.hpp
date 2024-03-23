#include <muParser.h>
#include <Eigen/Eigen>
#include <memory>
#include <string>
#include "parameters.h"

class MuparserGrad
{
public:
  MuparserGrad(const MuparserGrad &m)
    : m_parser1(m.m_parser1), m_parser2(m.m_parser2)
  { m_var.resize(2);
    m_parser1.DefineVar("x", &(m_var[0]));
    m_parser1.DefineVar("y", &m_var[1]);
    m_parser2.DefineVar("x", &(m_var[0]));
    m_parser2.DefineVar("y", &m_var[1]);
  };

  MuparserGrad(const std::string &f, const std::string &s)
  {
    try
      {
        m_var.resize(2);
        m_parser1.DefineVar("x", &m_var[0]);
        m_parser1.DefineVar("y", &m_var[1]);
        m_parser2.DefineVar("x", &m_var[0]);
        m_parser2.DefineVar("y", &m_var[1]);
        m_parser1.SetExpr(f);
        m_parser2.SetExpr(s);
      }
    catch (mu::Parser::exception_type &e)
      {
        std::cerr << e.GetMsg() << std::endl;
      }
  };

  Eigen::VectorXd
  operator()(const Eigen::VectorXd &x)
  {
    m_var << x;
    Eigen::VectorXd z(2); 
    
    z << m_parser1.Eval(), m_parser2.Eval();
    return z;
  };

private:
  Eigen::VectorXd m_var;
  mu::Parser m_parser1;
  mu::Parser m_parser2;

};
