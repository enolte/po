#include <iostream>
#include <cassert>
#include <chrono>
#include "../macros.h"

#include "../../induction/ls/exponents_sequence.h"

namespace po_test
{
  void test_exponents_sequences(std::size_t npoints, std::size_t length);

  void test_exponents_sequences()
  {
    test_exponents_sequences(0, 0);
    // TODO
/*
    test_exponents_sequences(0, 1);
    test_exponents_sequences(0, 2);
*/
    test_exponents_sequences(1, 0);
    test_exponents_sequences(1, 1);
    test_exponents_sequences(1, 2);
    test_exponents_sequences(2, 2);
    test_exponents_sequences(3, 2);
    test_exponents_sequences(5, 1);
    test_exponents_sequences(5, 3);
    test_exponents_sequences(5, 5);
    test_exponents_sequences(5, 7);
    test_exponents_sequences(5, 15);
    test_exponents_sequences(7, 2);
    test_exponents_sequences(7, 5);
    test_exponents_sequences(7, 7);
    test_exponents_sequences(7, 15);
    test_exponents_sequences(10, 3);
    test_exponents_sequences(10, 5);
    test_exponents_sequences(10, 6);
    test_exponents_sequences(10, 9);
    test_exponents_sequences(10, 10);
    test_exponents_sequences(10, 13);
    test_exponents_sequences(10, 19);
    test_exponents_sequences(10, 22);
    test_exponents_sequences(15, 7);
    test_exponents_sequences(15, 10);
    // test_exponents_sequences(15, 13);
    // test_exponents_sequences(15, 15);
    // test_exponents_sequences(15, 16);
    // test_exponents_sequences(15, 22);
  }

  void test_exponents_sequences(std::size_t npoints, std::size_t length)
  {
    const std::size_t ex_count = po::utils::C(npoints + length, length);

    using clock = std::chrono::high_resolution_clock;
    using namespace std::chrono_literals;

    const clock::time_point start = clock::now();

    std::size_t ac_count{};
    for(std::size_t l{}; l <= length; ++l)
    {
      po::exponents_sequence s(npoints, l);
      while(!s.end)
      {
        ++ac_count;
        ++s;
      }
    }

    const clock::time_point stop = clock::now();
    const clock::duration loop_time__ns = stop - start;

    if(loop_time__ns < 1000ns)
    {
      PO_TRACE(PO_MARKER << " npoints = " << npoints << ", length = " << length << ", num exponents_sequences = " << ac_count);
    }
    else
    {
      // PO_TRACE(" npoints = " << npoints << ", length = " << length << ", num exponents_sequences = " << ac_count << " : exec time: " << loop_time__ns.count() / 1000000. << " ms = " << loop_time__ns.count() / (double)ac_count << " ns / multiindex");
      PO_TRACE(PO_MARKER << " npoints = " << npoints << ", length = " << length << ", num exponents_sequences = " << ac_count << " : exec time: " << loop_time__ns.count() / 1000000. << " ms = " << loop_time__ns.count() / (double)ac_count << " ns / multiindex");
    }

    PO_ASSERT(ac_count == ex_count, ac_count);
  }


}