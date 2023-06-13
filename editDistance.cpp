#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int EditDistance(const string& x, const string& y) {
    int m = x.length();
    int n = y.length();

    // Create a table to store the edit distances
    vector<vector<int> > dp(m + 1, vector<int>(n + 1, 0));

    // Initialize the table with base cases
    for (int i = 0; i <= m; ++i) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= n; ++j) {
        dp[0][j] = j;
    }

    // Compute the edit distances
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (x[i - 1] == y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
            }
        }
    }

    // Print the sequence of operations
    int i = m, j = n;
    vector<string> operations;
    while (i > 0 && j > 0) {
        if (x[i - 1] == y[j - 1]) {
            --i;
            --j;
        } else if (dp[i][j] == dp[i - 1][j - 1] + 1) {
            operations.push_back("Substitute \"" + string(1, x[i - 1]) + "\" into \"" + string(1, y[j - 1]) + "\"");
            --i;
            --j;
        } else if (dp[i][j] == dp[i - 1][j] + 1) {
            operations.push_back("Delete \"" + string(1, x[i - 1]) + "\"");
            --i;
        } else if (dp[i][j] == dp[i][j - 1] + 1) {
            operations.push_back("Insert \"" + string(1, y[j - 1]) + "\"");
            --j;
        }
    }

    while (i > 0) {
        operations.push_back("Delete \"" + string(1, x[i - 1]) + "\"");
        --i;
    }

    while (j > 0) {
        operations.push_back("Insert \"" + string(1, y[j - 1]) + "\"");
        --j;
    }

    // Reverse the vector of operations to get the correct order
    reverse(operations.begin(), operations.end());

    // Print the operations
    for (size_t k = 0; k < operations.size(); ++k) {
        cout << operations[k] << endl;
    }

    // Return the minimum edit distance
    return dp[m][n];
}

int main() {
    string x = "clarks";
    string y = "kirk";
    int distance = EditDistance(x, y);
    cout << "Minimum edit distance: " << distance << endl;

    return 0;
}
