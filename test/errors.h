#ifndef PO_NUMERICAL_ERRORS_H
#define PO_NUMERICAL_ERRORS_H

#include <cmath>
#include <sstream>

namespace po_test
{
  inline bool near_rel(const double& ac, const double& ex, double tol)
  {
    return std::fabs(ac - ex) <= std::fabs(ex) * tol;
  }

  inline double rel(const double& ac, const double& ex)
  {
    return std::fabs(ac - ex) / std::fabs(ex);
  }

  inline double abs(const double& ac, const double& ex)
  {
    return std::fabs(ac - ex);
  }

  inline std::string errors(const double& ac, const double& ex, double tol)
  {
    const double RE = rel(ac, ex);
    const double AE = abs(ac, ex);

    std::stringstream ss;
    ss<< std::endl
      << " ac = " << ac << " = " << std::hexfloat << ac << std::endl << std::defaultfloat
      << " ex = " << ex << " = " << std::hexfloat << ex << std::endl << std::defaultfloat
      << " RE = " << RE << " = " << std::hexfloat << RE << std::endl << std::defaultfloat
      << " AE = " << AE << " = " << std::hexfloat << AE << std::endl << std::defaultfloat
      << " tol= " << tol << " = " << std::hexfloat << tol << std::endl << std::defaultfloat;

    return ss.str();
  }

}

#endif


