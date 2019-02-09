#ifndef UTIL_H_
#define UTIL_H_

/// �N�����v
template <typename T>
T Clamp(T x, T min, T max)
{
    if (x < min) { return min; }
    if (x > max) { return max; }
    return x;
}

#endif // !UTIL_H_
