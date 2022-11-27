#include <boost/ut.hpp>
#include <cstdint>
#include <libxbitset/bitset.hpp>

namespace xstd {
boost::ut::suite bitmanip_test = []() {
  using namespace boost::ut;

  "class bitmanip lower half (0)"_test = []() {
    volatile uint32_t val{ 0 };
    xstd::bitmanip test(val);
    expect(that % 0x0000'0000 == val);
    test.set(0UL);
    expect(that % 0x0000'0000 == val);
    test.save();
    expect(that % 0x0000'0001 == val);
    test.set(1UL);
    expect(that % 0x0000'0001 == val);
    expect(that % 0x0000'0003 == test);
    test.save();
    expect(that % 0x0000'0003 == val);
    expect(that % 0x0000'0003 == test);

    expect(that % 0x0000'0003 == test);
    val = 1;
    test.update();
    expect(that % 0x0000'0001 == test);
    val = 2;
    expect(that % 0x0000'0002 == val);
    expect(that % 0x0000'0001 == test);
  };

  "class bitmanip lower half (10)"_test = []() {
    volatile uint32_t val{ 10 };
    xstd::bitmanip test(val);
    expect(that % 0x0000'000A == val);
    test.set(0UL);
    expect(that % 0x0000'000A == val);
    test.save();
    expect(that % 0x0000'000B == val);
    test.set(2UL);
    expect(that % 0x0000'000B == val);
    expect(that % 0x0000'000F == test);
    test.save();
    expect(that % 0x0000'000F == val);
    expect(that % 0x0000'000F == test);

    expect(that % 0x0000'000F == test);
    val = 11;
    test.update();
    expect(that % 0x0000'000B == test);
    val = 12;
    expect(that % 0x0000'000C == val);
    expect(that % 0x0000'000B == test);
  };

  "class bitmanip upper half (0)"_test = []() {
    volatile uint32_t val{ 0 };
    xstd::bitmanip test(val);
    expect(that % 0x0000'0000 == val);
    test.set(16UL);
    expect(that % 0x0000'0000 == val);
    test.save();
    expect(that % 0x0001'0000 == val);
    test.set(17UL);
    expect(that % 0x0001'0000 == val);
    expect(that % 0x0003'0000 == test);
    test.save();
    expect(that % 0x0003'0000 == val);
    expect(that % 0x0003'0000 == test);

    expect(that % 0x0003'0000 == test);
    val = 65536;
    test.update();
    expect(that % 0x0001'0000 == test);
    val = 65537;
    expect(that % 0x0001'0001 == val);
    expect(that % 0x0001'0000 == test);
  };

  "class bitmanip destructor"_test = []() {
    volatile uint32_t val{ 0 };
    {
      xstd::bitmanip test(val);
      test.set(0UL);
      test.set(1UL);
    }
    expect(that % 0x0000'0003 == val);
  };
};
}