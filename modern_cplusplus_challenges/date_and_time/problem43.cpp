#include <chrono>
#include <string>
#include <vector>
using namespace std;

struct user {
  std::string Name;
  date::time_zone const *Zone;

  explicit user(std::string_view name, std::string_view zone)
    : Name{name.data()}, Zone{date::locate_zone{zone.data()}} {}
};

template <class Duration, class TimeZonePtr>
void print_meeting_times(date::zoned_time<Duration, TimeZonePtr> const &time, std::vector<user> const &users) {
  std::cout << std::left << std::setw(15) << std::setfill(' ') << "Local time: " << time << std::endl;

  for (auto const &user : users) {
    std::cout << std::left << std::setw(15) << std::set
  }
}
