#include "gauss.h"

std::vector<int> lp::GetContribStrings(std::vector<std::vector<int>> &a, int i){
    std::vector<int> res;
    for (int j = 0; j < a[0].size(); ++j){
        if (a[i][j] == 1){
            res.emplace_back(j);
        }
    }
    return res;
}

std::vector<int> lp::Gaus(std::vector<std::vector<int>> &a) {
    int n = a.size();
    int m = a[0].size();
    assert(n > 0 && m > 0 && "WTF DUDE? size should be bigger than 0!");
    assert(n > m && "We use only tall matrixes!");
    std::vector<std::vector<int>> helper(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        helper[i][i] = 1;
    }
    int cur_string_num = 0;
    for (int j = 0; j < m; ++j) {
        for (int i = cur_string_num; i < n; ++i) {
            if (a[i][j] == 1) {
                std::swap(a[cur_string_num], a[i]);
                std::swap(helper[cur_string_num], helper[i]);
                break;
            }
        }
        for (int i = cur_string_num + 1; i < n; ++i) {
            if (a[i][0] == -1){
                continue;
            }
            if (a[i][j] == 0) {
                bool zero_string = true;
                for (int k = 0; k < m; ++k) {
                    if (a[i][k] == 1) {
                        zero_string = false;
                        break;
                    }
                }
                if (zero_string) {
                    a[i][0] = -1;
                    return GetContribStrings(helper, i);
                }
            } else {
                bool zero_string = true;
                for (int k = 0; k < m; ++k) {
                    a[i][k] ^= a[cur_string_num][k];
                    helper[i][k] ^= helper[cur_string_num][k];
                    if (a[i][k] == 1) {
                        zero_string = false;
                    }
                }
                if (zero_string) {
                    a[i][0] = -1;
                    return GetContribStrings(helper, i);
                }
            }
        }
        ++cur_string_num;
    }
    return {-1};
}
