#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:
        int minimumSize(vector<int>& nums, int maxOperations) {
            int n = nums.size(), ans;
            int l = 1, r = *max_element(nums.begin(), nums.end());
    
            auto possible = [&] (int mid) {
                long long int sum = 0;
                for (int i = 0; i < n; i++) {
                    sum += ( nums[i] - 1 ) / mid ;
                }
                return sum <= maxOperations;
            };
    
            while (l <= r) {
    
                int mid = l + (r - l) / 2;
    
                if (possible(mid)) {
                    r = mid - 1;
                    ans = mid;
                } else {
                    l = mid + 1;
                }
    
            }
    
            return ans;
        }
    };

int main() {
    return 0;
}
