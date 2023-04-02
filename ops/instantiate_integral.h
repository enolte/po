#ifndef PO_INSTANTIATE_INTEGRAL_H
#define PO_INSTANTIATE_INTEGRAL_H

#include "../utils/pow.h"
#include "expr_integral.h"

#include "is_expression.h"

namespace po
{
  namespace detail
  {
    static po::exponents get_integral_term_exponents(const po::exponents& t_exponents, std::size_t place, rank_type rank)
    {
      po::exponents ip_exponents(0zu, rank);

      for(auto i{0zu}; i != place; ++i)
        ip_exponents[i] = t_exponents[i];

      for(auto i{place + 1}; i < t_exponents.size(); ++i)
        ip_exponents[i-1] = t_exponents[i];

      return ip_exponents;
    }

    template<typename Expr>
    static double get_integral_term_coefficient(const po::exponents& t_exponents, const Expr& expr, double t_coefficient)
    {
      double ip_coefficient = t_coefficient;

      ip_coefficient /= (t_exponents[expr.place] + 1);

      ip_coefficient *= pow(expr.b, t_exponents[expr.place] + 1) - pow(expr.a, t_exponents[expr.place] + 1);

      return ip_coefficient;
    }
  }


  template<expression E1>
  polynomial& instantiate(polynomial& p, const expr_integral<E1> expr, rank_type rank)
  {
    instantiate(p, expr.expr1, expr_rank(expr.expr1));

    if(expr.place < p.rank())
    {
      polynomial ip = polynomial::make_zero(rank);
      for(const auto& t : p.terms)
      {
        const po::exponents ip_exponents = detail::get_integral_term_exponents(t.exponents, expr.place, rank);

        const scalar_type ip_coefficient = (scalar_type)detail::get_integral_term_coefficient(t.exponents, expr, t.coefficient);

        ip += {ip_coefficient, ip_exponents};
      }
      p = ip;

      return p;
    }
    else
    {
      p *= expr.b - expr.a;
      return p;
    }

  }

  template<is_constant E1>
  polynomial& instantiate(polynomial& p, const expr_integral<E1> expr, rank_type rank)
  {
    p = polynomial::make_zero(rank);

    if constexpr(is_scalar<E1>)
      p += expr.expr1 * (expr.b - expr.a);
    else
      p += expr.expr1.expr1 * (expr.b - expr.a);

    return p;
  }

}


#endif


