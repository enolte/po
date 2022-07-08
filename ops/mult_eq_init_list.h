#ifndef PO_MULT_EQ_INIT_LIST_H
#define PO_MULT_EQ_INIT_LIST_H

#include "mult_eq_monomial.h"

#include "../field.h"
#include "../monomial.h"

namespace po
{
  /*
   * Multiply a terms(p) by a init-list(q). Implement p *= q;
   *
   */
  void mult_eq(std::vector<monomial>& p, std::initializer_list<monomial>& q)
  {
    if(q.size() == 0)
      return;

    if(p.size() == 0)
      return;

    std::vector<monomial> acc;

    for(auto& tp : p)
      for(auto& tq : q)
      {
        if(const auto found = find(acc, tp.exponents + tq.exponents); found != std::cend(acc))
          found->coefficient += tp.coefficient * tq.coefficient;
        else
          acc.emplace_back(tp.coefficient * tq.coefficient, tp.exponents + tq.exponents);
      }

    p = acc;
  }
}

#endif


