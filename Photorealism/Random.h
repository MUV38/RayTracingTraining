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

// 半径1の円上の点を一様サンプリング
void SampleDisk(double& x, double& y)
{
    double u1 = Rnd();
    double u2 = Rnd();
    x = std::sqrt(u1) * std::cos(2.0 * M_PI * u2);
    y = std::sqrt(u1) * std::sin(2.0 * M_PI * u2);
}

#endif // !RANDOM_H_
