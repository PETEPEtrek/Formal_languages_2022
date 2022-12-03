//
// Created by Acer on 03.12.2022.
//

#include "Situation.hpp"

int32_t Situation::GetI() const {
    return i_;
}

char Situation::GetA() const {
    return A_;
}

std::string Situation::GetAlpha() const {
    return alpha_;
}

std::string Situation::GetBeta() const {
    return beta_;
}

bool Situation::operator==(const Situation& other) const {
    return (i_ == other.i_) && (alpha_ == other.alpha_) && (beta_ == other.beta_) && (A_ == other.A_);
}

bool Situation::operator<=(const Situation& other) const {
    if (i_ != other.i_) {
        return i_ < other.i_;
    }
    if (alpha_ != other.alpha_) {
        return alpha_ < other.alpha_;
    }
    if (beta_ != other.beta_) {
        return beta_ < other.beta_;
    }
    if (A_ <= other.A_) {
        return true;
    }
    return false;
}

bool Situation::operator!=(const Situation& other) const {
    return !(*this == other);
}

bool Situation::operator<(const Situation& other) const {
    return (*this <= other) && (*this != other);
}

bool Situation::operator>=(const Situation& other) const {
    return !(*this < other);
}

bool Situation::operator>(const Situation& other) const {
    return !(*this < other) && (*this != other);
}