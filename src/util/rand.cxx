#include <random>

#include "rand.hxx"

// W0000
typedef std::minstd_rand G;
typedef std::uniform_int_distribution<> D;

G g;

void set_seed(time_t t) {
    g = G(t);
}


int rand_int(int a, int b) {
    if (a > b) std::swap(a, b);
    D d(a, b);
    return d(g);
}
