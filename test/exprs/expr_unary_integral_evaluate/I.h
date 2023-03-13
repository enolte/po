#ifndef PO_INTEGRAL_I_H
#define PO_INTEGRAL_I_H

namespace po
{
  template<expression E1>
  constexpr expr_integral<E1> I(E1&& expr, parametric_interval&& i)
  {
    return integral(std::forward<E1>(expr), std::forward<parametric_interval>(i));
  }

  template<expression E1>
  constexpr expr_integral<E1> I(E1&& expr, const parametric_interval& i)
  {
    return integral(std::forward<E1>(expr), i);
  }
}

#endif


