#include <chrono>

unsigned int week_day(int const y, unsigned int const m, unsigned int const d) {
  if (m < 1 || m > 12 || d < 1 || d > 31) {
    return 0;
  }

  auto const dt = date::year_month_day{year{y}, month{m}, day{d}};
  auto const tiso = iso_week::year_weeknum_weekday{dt};

  return (unsigned int)tiso.weekday();
}
