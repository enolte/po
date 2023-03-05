#ifndef PO_STORAGE_FLAT_ACC_MULT_H
#define PO_STORAGE_FLAT_ACC_MULT_H

#include "find_term.h"

namespace po
{
  inline namespace flat_model
  {
    /*
     * Accumulate a scalar, implements multiplication.
     */
    static void accumulate_mult(storage& terms, scalar_type s)
    {
      for(auto& term : terms)
        term.coefficient *= s;
    }

    /*
     * Accumulate a monomial, implements multiplication.
     */
    static void accumulate_mult(storage& terms, const scalar_type& c, const po::exponents& exponents)
    {
      for(auto& term : terms)
      {
        term.exponents += exponents;
        term.coefficient *= c;
      }
    }

    /*
     * Accumulate a storage object, implements multiplication.
     */
    static void accumulate_mult(storage& p, const storage& q)
    {
      if(q.size() == 0)
      {
        p.clear();
        return;
      }

      storage acc;

      for(auto& tp : p)
        for(const auto& tq : q)
        {
          if(const auto found = find_term(acc, tp.exponents + tq.exponents); found != std::cend(acc))
            found->coefficient += tp.coefficient * tq.coefficient;
          else
            acc.emplace_back(tp.coefficient * tq.coefficient, tp.exponents + tq.exponents);
        }

      p = acc;
    }

    /*
     * Accumulate an init-list of monomials, implements multiplication.
     */
    static void accumulate_mult(storage& p, std::initializer_list<monomial>&& q)
    {
      if(q.size() == 0)
      {
        p.clear();
        return;
      }

      storage acc;

      for(auto& tp : p)
        for(auto& tq : q)
        {
          if(const auto found = find_term(acc, tp.exponents + tq.exponents); found != std::cend(acc))
            found->coefficient += tp.coefficient * tq.coefficient;
          else
            acc.emplace_back(tp.coefficient * tq.coefficient, tp.exponents + tq.exponents);
        }

      p = acc;
    }

  }

}

#endif

