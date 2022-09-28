#include <boost/ut.hpp>
#include <cstdint>
#include <libxbitset/bitset.hpp>

namespace xstd {
boost::ut::suite bittest_test = []() {
  using namespace boost::ut;

  "bitset::test() increment position (0)"_test = []() {
    xstd::bitset test_set(0);
    expect(that % false == test_set.test(0));
    expect(that % false == test_set.test(1));
    expect(that % false == test_set.test(2));
  };

  "bitset::test() increment position (1)"_test = []() {
    xstd::bitset test_set(1);
    expect(that % true == test_set.test(0));
    expect(that % false == test_set.test(1));
    expect(that % false == test_set.test(2));
  };

  "bitset::test() increment position (2)"_test = []() {
    xstd::bitset test_set(2);
    expect(that % false == test_set.test(0));
    expect(that % true == test_set.test(1));
    expect(that % false == test_set.test(2));
  };

  "bitset::test() increment position (10)"_test = []() {
    xstd::bitset test_set(0xA);
    expect(that % false == test_set.test(0));
    expect(that % true == test_set.test(1));
    expect(that % false == test_set.test(2));
  };

  "bitset::test() increment position upper half (0x1'FFFF)"_test = []() {
    xstd::bitset test_set(0x1'FFFF);
    expect(that % true == test_set.test(16));
    expect(that % false == test_set.test(17));
    expect(that % false == test_set.test(18));
  };

  "bitset::test() increment position lower half full (0xFFFF'FFFF)"_test =
    []() {
      xstd::bitset test_set(0xFFFF'FFFF);
      expect(that % true == test_set.test(0));
      expect(that % true == test_set.test(1));
      expect(that % true == test_set.test(2));
    };

  "bitset::test() increment position upper half full (0xFFFF'FFFF)"_test =
    []() {
      xstd::bitset test_set(0xFFFF'FFFF);
      expect(that % true == test_set.test(16));
      expect(that % true == test_set.test(17));
      expect(that % true == test_set.test(18));
    };

  "bitset::test() set out of range"_test = []() {
    // xstd::bitset test_set(0);
    // expect(throws<std::out_of_range>([&test_set](){test_set.test(32);}));
  };
};
}