/**
* このファイルはeduptから持ってきたものです
* 便宜上、namespaceは削除しています
* https://github.com/githole/edupt
*/

#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <climits>

// Xor-Shiftによる乱数ジェネレータ
class XorShift {
	unsigned int seed_[4];
public:
	unsigned int next(void) { 
		const unsigned int t = seed_[0] ^ (seed_[0] << 11);
		seed_[0] = seed_[1]; 
		seed_[1] = seed_[2];
		seed_[2] = seed_[3];
		return seed_[3] = (seed_[3] ^ (seed_[3] >> 19)) ^ (t ^ (t >> 8)); 
	}

	double next01(void) {
		return (double)next() / UINT_MAX;
	}

	// [min_value, max_value]
	double next(double min_value, double max_value) {
		const double inv = (max_value - min_value);
		return ((double)next() * (inv / std::numeric_limits<unsigned long long>::max())) + min_value;
	}

	XorShift(const unsigned int initial_seed) {
		unsigned int s = initial_seed;
		for (int i = 1; i <= 4; i++){
			seed_[i-1] = s = 1812433253U * (s^(s>>30)) + i;
		}
	}
};

typedef XorShift Random;

#endif
