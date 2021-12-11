#include "utils.h"   

long long Rand(long long l, long long h) {
    return l + rand() * 1LL * rand() % (h - l + 1);
}