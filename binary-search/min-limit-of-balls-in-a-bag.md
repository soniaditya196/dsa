# 1760. Minimum Limit of Balls in a Bag

Given bags of balls `nums[i]` and at most `maxOperations` splits, minimize the **penalty**: the largest bag after the splits.

Each operation takes one bag and splits it into two bags with a positive number of balls.

## Core idea

The penalty is some integer `x` (the maximum bag size we allow). Smaller `x` is harder: you need more splits. Larger `x` is easier.

That relationship is **monotonic**:

1. If penalty `x` is achievable with ≤ `maxOperations` splits, every penalty `> x` is also achievable.
2. If `x` is not achievable, every penalty `< x` is also not achievable.

So we **binary search on the penalty** instead of simulating every split.

Search range:

- Low = `1` (bags cannot be empty).
- High = `max(nums)` (do nothing; the current largest bag is the penalty).

For each candidate `mid`, ask: *can every bag be reduced so that no bag is larger than* `mid`*, using at most* `maxOperations` *splits?*

If yes, try a smaller penalty (`r = mid - 1`). If no, we must allow a larger penalty (`l = mid + 1`).

## How many operations does a bag need?

To turn a bag of size `n` into bags of size at most `x`, you need enough splits so that every resulting bag is ≤ `x`.

The cheapest way is to produce bags of size `x` (plus a possible leftover). That takes:

```
ceil(n / x) - 1
```

splits. Equivalently, without floats:

```
(n - 1) / x
```

**Why** `ceil(n / x) - 1`**?**

- You want `ceil(n / x)` bags, each of size ≤ `x`.
- Starting from 1 bag, each split adds exactly one bag.
- So you need `ceil(n / x) - 1` splits.

Examples for `x = 3`:


| Bag size | Bags needed | Splits `(n - 1) / 3` |
| -------- | ----------- | -------------------- |
| 3        | 1           | 0                    |
| 4        | 2           | 1                    |
| 9        | 3           | 2                    |
| 8        | 3           | 2                    |


Bags are independent: total operations is the sum over all bags. If that sum is ≤ `maxOperations`, penalty `x` is possible.

Use a 64-bit sum: operations can overflow 32-bit `int`.

## Walkthrough

**Example 1:** `nums = [9]`, `maxOperations = 2`

Possible penalties from 1 to 9.

- Penalty 3: `(9 - 1) / 3 = 2` operations → OK.
- Penalty 2: `(9 - 1) / 2 = 4` operations → too many.

Minimum penalty is **3** (`9 → 6,3 → 3,3,3`).

**Example 2:** `nums = [2,4,8,2]`, `maxOperations = 4`

For penalty 2:

- 2 → 0 ops
- 4 → 1 op
- 8 → 3 ops
- 2 → 0 ops

Total 4, which matches the budget. Penalty 1 needs far more splits, so the answer is **2**.

## Complexity

- Time: `O(n log M)` where `M = max(nums)`. Each binary-search step scans the array.
- Space: `O(1)` extra.



## Code (`min-limit-of-balls-in-a-bag.cpp`)

`possible(mid)` returns whether penalty `mid` is feasible. Binary search records the smallest feasible `mid` in `ans`.