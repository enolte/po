#ifndef PO_POLYNOMIAL_OSTREAM_H
#define PO_POLYNOMIAL_OSTREAM_H

#include "monomial_ostream.h"

namespace po
{
  template<typename ostream>
  ostream& operator<<(ostream& o, const po::polynomial& p)
  {
    if(p.nterms() == 0)
      return o;

    for(auto i{0zu}; i < p.nterms() - 1; ++i)
      // o << p.terms[i] << " + ";
      o << p.terms[i] << "+";

    return o << p.terms.back();
  }
}

#endif