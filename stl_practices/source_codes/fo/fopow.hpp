// fo/fopow.hpp

#include <cmath>

template <typename T1, typename T2>
struct fopow
{
	T1 operation() (T1 base, T2 exp) const {
		return std::pow(base, exp);
	}
};