#ifndef PO_POLYNOMIAL_OSTREAM_H
#define PO_POLYNOMIAL_OSTREAM_H

#include "monomial_ostream.h"

template<typename ostream>
ostream& operator<<(ostream& o, const po::polynomial& p)
{
  if(p.nterms() == 0)
    return o;

  for(auto i{0zu}; i < p.nterms() - 1; ++i)
    o << p.terms[i] << " + ";

  return o << p.terms.back();
}

#if 0
// TODO print in source code format. E.g., "{4, {0, 1}}, {3, {4, 2}}"
namespace po
{

  struct source
  {
    const polynomial& p;
  };

}

template<typename ostream>
ostream& operator<<(ostream& o, po::source&& s)
{
  const auto& p = s.p;
  if(p.nterms() == 0)
    return o;

  for(auto i{0zu}; i < p.nterms() - 1; ++i)
    o << p.terms[i] << " + ";

  return o << p.terms.back();
}

#endif

#endif


