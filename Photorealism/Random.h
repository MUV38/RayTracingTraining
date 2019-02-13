#ifndef RANDOM_H_
#define RANDOM_H_

#include <random>

// メルセンヌツイスタ
std::random_device rndDevice;
std::mt19937 mt(rndDevice());
std::uniform_real_distribution<> dist(0, 1);
inline double Rnd()
{
    return dist(mt);
}

#endif // !RANDOM_H_
