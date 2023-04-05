#ifndef PO_INSTANTIATE_ANTIDERIVATIVE_H
#define PO_INSTANTIATE_ANTIDERIVATIVE_H

#include "../utils/pow.h"
#include "expr_antiderivative.h"

#include "is_expression.h"

#include <algorithm>

namespace po
{
  template<expression E1>
  polynomial& instantiate(polynomial& p, const expr_antiderivative<E1> expr, rank_type rank)
  {
    instantiate(p, expr.expr1, expr_rank(expr.expr1));

    if(expr.place < p.rank())
    {
      polynomial ap = p;
      for(auto& t : ap.terms)
      {
        t.coefficient /= t.exponents[expr.place] + 1;
        t.exponents[expr.place] += 1;
      }

      ap.update_degrees();

      p = ap;

      return p;
    }
    else
    {
      polynomial ap = polynomial::make_zero(expr.place + 1);
      for(const auto& t : p.terms)
      {
        po::exponents ax(0zu, ap.rank());
        std::copy_n(std::cbegin(t.exponents), p.rank(), std::begin(ax));
        ax[expr.place] = 1;

        ap += {t.coefficient, ax};
      }

      p = ap;

      return p;
    }

  }

  template<constant E1>
  polynomial& instantiate(polynomial& p, const expr_antiderivative<E1> expr, rank_type rank)
  {
    p = polynomial::make_zero(expr.place + 1);

    if constexpr(is_scalar<E1>)
      p += expr.expr1;
    else
      p += expr.expr1.expr1;

    p.terms[0].exponents[expr.place] = 1;
    p.update_degrees();

    return p;
  }

}


#endif


