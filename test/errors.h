#ifndef PO_NUMERICAL_ERRORS_H
#define PO_NUMERICAL_ERRORS_H

#include <cmath>
#include <sstream>

namespace po_test
{
  inline double near_rel(double ac, double ex, double tol)
  {
    return std::fabs(ac - ex) <= std::fabs(ex) * tol;
  }

  inline double rel(double ac, double ex)
  {
    return std::fabs(ac - ex) / std::fabs(ex);
  }

  inline double abs(double ac, double ex)
  {
    return std::fabs(ac - ex);
  }

  std::string errors(double ac, double ex, double tol)
  {
    const double RE = rel(ac, ex);
    const double AE = abs(ac, ex);

    std::stringstream ss;
    ss<< std::endl
      << " ex = " << ex << " = " << std::hexfloat << ex << std::endl << std::defaultfloat
      << " ac = " << ac << " = " << std::hexfloat << ac << std::endl << std::defaultfloat
      << " RE = " << RE << " = " << std::hexfloat << RE << std::endl << std::defaultfloat
      << " AE = " << AE << " = " << std::hexfloat << AE << std::endl << std::defaultfloat
      << " tol= " << tol << " = " << std::hexfloat << tol << std::endl << std::defaultfloat;

    return ss.str();
  }


}

#endif


