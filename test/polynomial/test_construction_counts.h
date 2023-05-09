#include <cassert>
#include <functional>
#include "../macros.h"
#include "../../polynomial.h"

void test_count(std::uint64_t expected_count, std::function<void(void)> f)
{
  const std::uint64_t count_before = po::polynomial::construction_count();

  f();

  const std::uint64_t count_after = po::polynomial::construction_count();
  const std::uint64_t count_diff = count_after - count_before;

  PO_ASSERT(count_diff == expected_count, count_diff);
}

void test_construction_counts()
{
  PO_LINE; test_count(1, [](){ po::polynomial p; });
  PO_LINE; test_count(1, [](){ po::polynomial{{}}; });
  PO_LINE; test_count(1, [](){ po::polynomial(po::polynomial::make_constant(po::rank<0>{}, 0)); });
  PO_LINE; test_count(1, [](){ po::polynomial(po::polynomial::make_constant(po::rank<31>{}, 0)); });

  PO_LINE; test_count(1, [](){ po::polynomial p; +p; });
  PO_LINE; test_count(2, [](){ po::polynomial p; p = +p; });

  PO_LINE; test_count(1, [](){ po::polynomial p; -p; });
  PO_LINE; test_count(2, [](){ po::polynomial p; p = -p; });
  PO_LINE; test_count(2, [](){ po::polynomial p; p -= 2*p; });
  PO_LINE; test_count(3, [](){ po::polynomial p; p = p - 2*p; });

  PO_LINE; test_count(1, [](){ po::polynomial p; p + p; });
  PO_LINE; test_count(2, [](){ po::polynomial p; p = p + p; });
  PO_LINE; test_count(1, [](){ po::polynomial p; p += p; });

  PO_LINE; test_count(1, [](){ po::polynomial p; p - p; });
  PO_LINE; test_count(2, [](){ po::polynomial p; p = p - p; });
  PO_LINE; test_count(1, [](){ po::polynomial p; p -= p; });

  PO_LINE; test_count(1, [](){ po::polynomial p; p += 2; });

  PO_LINE; test_count(1, [](){ po::polynomial p; p *= 2.; });
  PO_LINE; test_count(1, [](){ po::polynomial p; p *= 2; });
  PO_LINE; test_count(1, [](){ po::polynomial p; p *= {0.5}; });

}

