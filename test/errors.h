#ifndef PO_NUMERICAL_ERRORS_H
#define PO_NUMERICAL_ERRORS_H

#include <cmath>
#include <sstream>
#include <iomanip>

namespace po_test
{
  inline bool near_rel(const double& ac, const double& ex, double tol)
  {
    return std::fabs(ac - ex) <= std::fabs(ex) * tol;
  }

  inline bool near_abs(const double& ac, const double& ex, double tol)
  {
    return std::fabs(ac - ex) <= tol;
  }

  inline double rel(const double& ac, const double& ex)
  {
    return std::fabs(ac - ex) / std::fabs(ex);
  }

  inline double abs(const double& ac, const double& ex)
  {
    return std::fabs(ac - ex);
  }

  inline std::string errors(const double& ac, const double& ex, double tol = 0x1p-52, unsigned int precision = 6)
  {
    const double RE = rel(ac, ex);
    const double AE = abs(ac, ex);

    std::stringstream ss;
    ss << std::endl
       << std::setprecision(precision) << " ac = " << ac << " = " << std::hexfloat << ac << std::endl << std::defaultfloat
       << std::setprecision(precision) << " ex = " << ex << " = " << std::hexfloat << ex << std::endl << std::defaultfloat
       << std::setprecision(precision) << " RE = " << RE << " = " << std::hexfloat << RE << std::endl << std::defaultfloat
       << std::setprecision(precision) << " AE = " << AE << " = " << std::hexfloat << AE << std::endl << std::defaultfloat
       << std::setprecision(precision) << " tol= " << tol << " = " << std::hexfloat << tol << std::endl << std::defaultfloat;

    return ss.str();
  }

}

#endif


