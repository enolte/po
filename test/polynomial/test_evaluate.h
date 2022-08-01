#include "../../polynomial.h"

#include "test_evaluate_gH.h"
#include "test_evaluate_naive.h"

void test_evaluate()
{
  test_evaluate_naive();
  test_evaluate_gH();
}


