#pragma once

#include <iostream>
#include <array>
#include <vector>

namespace lp {
std::vector<int> Gaus(std::vector<std::vector<int>> a);

std::vector<int> GetContribStrings(std::vector<std::vector<int>> &a, int i);
}  // namespace lp