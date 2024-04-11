#pragma once

#include <format>

namespace po_test
{
  template<typename ostream, typename T>
  ostream& operator<<(ostream& o, const std::vector<T>& x)
  {
    if(x.size() != 0)
    {
      for(auto i{0zu}; i < x.size() - 1; ++i)
        o.operator<<(x[i]) << ",";
      o.operator<<(x[x.size() - 1]);
    }

    return o;
  }

  template<typename ostream, typename T>
  ostream& operator<<(ostream& o, const std::valarray<T>& x)
  {
    if(x.size() != 0)
    {
      for(auto i{0zu}; i < x.size() - 1; ++i)
        o.operator<<(x[i]) << ",";
      o.operator<<(x[x.size() - 1]);
    }

    return o;
  }

  // TODO g++ 13.1 determinstically fails to terminate when trying to parse this.
  // So far, the below variations seem to make no difference.
#if 0
  namespace detail
  {
    template<typename ...X>
    double evaluate(int n, const po::polynomial& p, const double x[], X... xs)
    // double evaluate(const po::polynomial& p, const double x[], X... xs)
    // double evaluate(const po::polynomial& p, const double* x, X... xs)
    {
      if(sizeof ...(xs) == p.rank())
      {
        return p(xs...);
      }
      else
      {
        return evaluate(n+1, p, x, xs..., x[n]);
        // return evaluate(p, x, xs..., *++x);
      }
    }
  }

  double evaluate(const po::polynomial& p, const double x[])
  {
    return detail::evaluate(0, p, x);
    // return detail::evaluate<double>(p, x, x[0]);
  }
#endif

  using point = std::valarray<double>;

  template<std::size_t N>
  static std::vector<point> get_knots(const double vertices[][N], std::size_t simplex_dim, std::size_t degree)
  {
    using namespace po;

    const auto f = [vertices](std::size_t r, std::size_t c) { return vertices[c][r]; };

    std::vector<point> knots;
    for(po::exponents_sequence col(simplex_dim+1, degree); !col.end; ++col)
    {
      knots.emplace_back(po::ls::vandermonde::simplex_knot_point(f, col, N));
    }

    return knots;
  }

  template<std::size_t N>
  void verify_lagrange_basis(
    const std::vector<po::polynomial>& basis,
    const double points[][N],
    double tolerance);

  template<std::size_t N>
  void verify_lagrange_simplex_basis(
    const std::vector<po::polynomial>& basis,
    const double vertices[][N],
    std::size_t degree,
    std::size_t simplex_dim,
    double tolerance)
  {
    const auto knots = get_knots(vertices, simplex_dim, degree);

    double points[knots.size()][N];

    int i = 0;
    for(const auto& k : knots)
    {
      std::copy(std::cbegin(k), std::cend(k), points[i]);
      ++i;
    }

    verify_lagrange_basis(basis, points, tolerance);
  }

  template<std::size_t N>
  void verify_lagrange_basis(
    const std::vector<po::polynomial>& basis,
    const double points[][N],
    double tolerance)
  {
    for(auto i{0zu}; i < basis.size(); ++i)
    {
      const auto& p = basis[i];

      for(auto j{0zu}; j < basis.size(); ++j)
      {
        const auto& x = points[j];

        // evaluate(p, x);

        double px{po::nan};
        if constexpr(N == 2)
          px = p(x[0], x[1]);
        if constexpr(N == 3)
          px = p(x[0], x[1], x[2]);

        const double px_error = std::fabs(px - (i == j));

        const bool success = px_error <= tolerance;

        // PO_TRACE(" ** [" << j << "] " << (std::vector(x, x + N)));

        // Prep error message and report.
        if(!success)
        {
          const auto arg_format_str = [](std::size_t i) { return "{" + std::to_string(i) + "}"; };

          std::string format_str{"p[{0}]"};
          format_str += "(";
          for(auto i{0zu}; i < N-1; ++i)
            format_str += arg_format_str(i+1) + ", ";
          format_str += arg_format_str(N);
          format_str += ")";
          format_str += " = " + arg_format_str(N+1);

          auto msg = std::string{};
          if constexpr(N == 2)
            msg = std::vformat(format_str, std::make_format_args(i, x[0], x[1], px));
            // TODO C++26
            // msg = std::format(std::runtime_format(format_str), i, x[0], x[1], px);
          if constexpr(N == 3)
            msg = std::vformat(format_str, std::make_format_args(i, x[0], x[1], x[2], px));

          PO_ASSERT(success, msg);
        }
      }
    }
  }

}



