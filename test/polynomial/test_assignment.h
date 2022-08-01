#include "../../polynomial.h"
#include "compare.h"
#include <cassert>

void test_assign_polynomial();
void test_assign_init_list();
void test_assign_scalar();

void test_assignment()
{
  test_assign_polynomial();
  test_assign_init_list();
  test_assign_scalar();

  PO_LINE;
}

void test_assign_polynomial()
{
  {
    po::polynomial p{{4.2, {4, 0, 7, 6, 5}}, {5.5, {3, 1, 1, 0, 0}}};

    po::polynomial q(3.1, po::rank<6>{});

    q = p;

    assert(q == p);
    assert(q.rank() == 5);
  }

}

void test_assign_init_list()
{
  {
    po::polynomial p{{4.2, {4, 0, 7, 6, 5}}, {5.5, {3, 1, 1, 0, 0}}};

    p = {{0.77, {2, 2, 2, 2, 2}}, {0.1, {1, 2, 3, 4, 5}}};

    assert(p.rank() == 5);
    assert(unordered_equal(
      p.terms,
      {
        {0.77, {2, 2, 2, 2, 2}},
        {0.1, {1, 2, 3, 4, 5}}
      }));
  }

}

void test_assign_scalar()
{
  {
    po::polynomial p{{4.2, {4, 0, 7, 6, 5}}, {5.5, {3, 1, 1, 0, 0}}};

    p = 51.4;

    assert(p.rank() == 5);
    assert(unordered_equal(
      p.terms,
      {
        {51.4, {0, 0, 0, 0, 0}}
      }));
  }

}