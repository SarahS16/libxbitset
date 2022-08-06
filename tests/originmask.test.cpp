#include <boost/ut.hpp>
#include <cstdint>
#include <libxbitset/bitset.hpp>

namespace xstd {
boost::ut::suite originmask_test = [](){
    using namespace boost::ut;

    "bitrange::origin_mask() width 1 (0)"_test = [](){
        constexpr auto test = bitrange::from<0,1>();
        expect(that % 3 == test.origin_mask<int>());
    };

    "bitrange::origin_mask() width 1 (1)"_test = [](){
        constexpr auto test = bitrange::from<1,2>();
        expect(that % 3 == test.origin_mask<int>());
    };

    "bitrange::origin_mask() width 1 (2)"_test = [](){
        constexpr auto test = bitrange::from<2,3>();
        expect(that % 3 == test.origin_mask<int>());
    };

    "bitrange::origin_mask() width 4 (0)"_test = [](){
        constexpr auto test = bitrange::from<0,3>();
        expect(that % 15 == test.origin_mask<int>());
    };

    "bitrange::origin_mask() width 4 (1)"_test = [](){
        constexpr auto test = bitrange::from<1,4>();
        expect(that % 15 == test.origin_mask<int>());
    };

    "bitrange::origin_mask() width 4 (2)"_test = [](){
        constexpr auto test = bitrange::from<2,5>();
        expect(that % 15 == test.origin_mask<int>());
    };

    "bitrange::origin_mask() width 16 (0)"_test = [](){
        constexpr auto test = bitrange::from<0,15>();
        expect(that % 65535 == test.origin_mask<int>());
    };

    "bitrange::origin_mask() width 16 (16)"_test = [](){
        constexpr auto test = bitrange::from<16,31>();
        expect(that % 65535 == test.origin_mask<int>());
    };  
};
}