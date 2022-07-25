#include <boost/ut.hpp>
#include <cstdint>
#include <libxbitset/bitset.hpp>

namespace xstd {
boost::ut::suite bitupdate_test = [](){
    using namespace boost::ut;

    "bitmanip::update() (1)"_test = [](){
        volatile uint32_t val{0};
        xstd::bitmanip test(val);
        expect(that % 0x0000'0000 == test);
        val = 1;
        test.update();
        expect(that % 0x0000'0001 == test);
        val = 2;
        expect(that % 0x0000'0002 == val);
        expect(that % 0x0000'0001 == test);
    };

    "bitmanip::update() (2)"_test = [](){
        volatile uint32_t val{10};
        xstd::bitmanip test(val);
        expect(that % 0x0000'000A == test);
        val = 11;
        test.update();
        expect(that % 0x0000'000B == test);
        val = 12;
        expect(that % 0x0000'000C == val);
        expect(that % 0x0000'000B == test);
    };
};
}