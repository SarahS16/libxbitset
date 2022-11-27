#include <cinttypes>
#include <cstdio>
#include <libxbitset/bitset.hpp>

int main()
{
  xstd::bitset test(0xFFFF'FFFF);
  constexpr xstd::bitrange bitr_obj{ 0, 16 };
  test.insert<bitr_obj>(0xABCDUL);

  printf("0x%08" PRIX32 "\n", static_cast<std::uint32_t>(test.to_ulong()));

  return 0;
}
