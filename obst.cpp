#include <iostream>
#include <vector>
#include <climits>

using namespace std;

float optimalBST(vector<float>& p, int n) {
    vector<vector<float>> cost(n + 2, vector<float>(n + 1, 0));  // cost[i][j] = cost of subtree from i to j

    vector<vector<float>> sum(n + 2, vector<float>(n + 1, 0));   // sum[i][j] = sum of p[i..j]

    // Base case: cost[i][i-1] = 0 (empty subtree)
    for (int i = 1; i <= n; ++i) {
        cost[i][i] = p[i - 1];
        sum[i][i] = p[i - 1];
    }

    // Build up for chains of length 2 to n
    for (int len = 2; len <= n; ++len) {
        for (int i = 1; i <= n - len + 1; ++i) {
            int j = i + len - 1;
            cost[i][j] = FLT_MAX;
            sum[i][j] = sum[i][j - 1] + p[j - 1];

            for (int r = i; r <= j; ++r) {
                float c = ((r > i) ? cost[i][r - 1] : 0) +
                          ((r < j) ? cost[r + 1][j] : 0) +
                          sum[i][j];
                if (c < cost[i][j])
                    cost[i][j] = c;
            }
        }
    }

    return cost[1][n]; // Minimum expected search cost
}

int main() {
    vector<float> p = {0.10, 0.20, 0.30, 0.40}; // probabilities for keys k1, k2, k3, k4
    int n = p.size();
    float minCost = optimalBST(p, n);

    cout << "Minimum expected search cost: " << minCost << "\n";

    return 0;
}
