#include <type_traits>
#include <concepts>

namespace static_asserts
{
  template<typename E>
  struct expr_verify_operands
  {
    template<typename F>
    constexpr static void verify_operand_type()
    {
      if constexpr(std::is_lvalue_reference_v<F>)
      {
        static_assert(std::is_const_v<std::remove_reference_t<F>>);
      }
      else
      {
        static_assert(!std::is_reference_v<F>);
        static_assert(std::is_const_v<F>);
      }
    }

    constexpr static void verify_types()
    {
      if constexpr(po::is_polynomial<E> || po::is_constant<E>)
      {
        verify_operand_type<E>();
      }
      else
      {
        if constexpr(po::is_unary_expression<E>)
        {
          using E1 = typename E::_E1;
          using F1 = typename E::F1;

          static_assert(std::is_const_v<std::remove_reference_t<F1>>);
          static_assert(std::same_as<std::remove_cvref_t<E1>, std::remove_cvref_t<F1>>);

          expr_verify_operands<F1>::verify_types();
          verify_operand_type<F1>();
        }
        else
        {
          using E1 = typename E::_E1;
          using E2 = typename E::_E2;

          using F1 = typename E::F1;
          using F2 = typename E::F2;

          static_assert(std::is_const_v<std::remove_reference_t<F1>>);
          static_assert(std::same_as<std::remove_cvref_t<E1>, std::remove_cvref_t<F1>>);

          static_assert(std::is_const_v<std::remove_reference_t<F2>>);
          static_assert(std::same_as<std::remove_cvref_t<E2>, std::remove_cvref_t<F2>>);

          expr_verify_operands<F1>::verify_types();
          expr_verify_operands<F2>::verify_types();
          verify_operand_type<F1>();
          verify_operand_type<F2>();
        }

      }
    }
  };
}

