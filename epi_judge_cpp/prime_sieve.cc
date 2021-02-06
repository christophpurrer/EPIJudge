#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
using std::deque;

// Given n, return all primes up to and including n.
vector<int> GeneratePrimesSlow(int n) {
    vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if (i == 2 || i == 3) {
            primes.push_back(i);
        } else if (i % 2 == 0 || i % 3 == 0) {
            continue;
        } else if (static_cast<int>(std::sqrt(i)) * static_cast<int>(std::sqrt(i)) == i) {
            continue;
        } else {
            bool shouldAdd = true;
            for (int j = 2; j < i; j++) {
                if (i % j == 0) {
                    shouldAdd = false;
                    break;
                }
            }
            if (shouldAdd) {
                primes.push_back(i);
            }
        }
    }
    return primes;
}

vector<int> GeneratePrimes(int n) {
    vector<int> primes;
    deque<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p <= n; p++) {
        if (is_prime[p]) {
            primes.emplace_back(p);
        }
        // Sieve p's multiple
        for (int j = p; j <= n; j += p) {
            is_prime[j] = false;
        }
    }
    return primes;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "prime_sieve.cc", "prime_sieve.tsv",
                         &GeneratePrimes, DefaultComparator{}, param_names);
}
