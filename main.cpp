#include "ksuffix.hpp"

int main() {
    std::string backPolishNotation;
    char x;
    int64_t k;
    std::cin >> backPolishNotation >> x >> k;
    auto kSuffix = KSuffix(backPolishNotation, x, k);
    std::cout <<  kSuffix.FindLenOfKSuffix();
    return 0;
}



