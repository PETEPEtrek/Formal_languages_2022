#pragma once

#include <string>

class Situation {
private:
    char A_;
    std::string alpha_;
    std::string beta_;
    int32_t i_;

public:
    Situation(char A, std::string alpha, std::string beta, int32_t i)
        : A_(A), alpha_(std::move(alpha)), beta_(std::move(beta)), i_(i) {}

    int32_t GetI() const;

    char GetA() const;

    std::string GetAlpha() const;

    std::string GetBeta() const;

    bool operator==(const Situation& other) const;

    bool operator!=(const Situation& other) const;

    bool operator<=(const Situation& other) const;

    bool operator<(const Situation& other) const;

    bool operator>=(const Situation& other) const;

    bool operator>(const Situation& other) const;
};
