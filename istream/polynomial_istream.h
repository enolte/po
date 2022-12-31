#ifndef PO_POLYNOMIAL_ISTREAM_H
#define PO_POLYNOMIAL_ISTREAM_H

#include "monomial_istream.h"

namespace po
{
  template<typename istream>
  istream& operator>>(istream& i, polynomial& p)
  {
    double coefficient;
    char left_bracket, right_bracket;
    std::string csv_exponents;
    char plus;

    po::monomial m;

    i >> std::ws;
    while(i)
    {
      i >> m >> std::ws >> plus >> std::ws;
      p += m;
    }

    return i;
  }


}

#endif


