#pragma once
#include "powers.h"
#include "usings.h"
#include "sqrt.h"

namespace lp {
namespace details {
std::vector<bool> DoSelection(size_t n);

std::vector<size_t> CherryPicking(std::vector<bool> &v, size_t m, size_t n);
}  // namespace details

std::vector<size_t> FindPrimes(size_t m, size_t n);
}  // namespace lp
