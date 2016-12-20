#include "Math.h"

namespace Math {
	bool isEven (int x) {
		if (x % 2 == 0) {
			return true;
		}
		else {
			return false;
		}
	}

	int max(int x, int y) {
		if (x > y)
			return x;
		else
			return y;
	}

	int min(int x, int y) {
		if (x < y)
			return x;
		else
			return y;
	}

	int abs(int x) {
		if (x < 0)
			return -x;
		else
			return x;
	}
}