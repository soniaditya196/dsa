# 400. Nth Digit

Given an integer `n`, return the `n`th digit of the infinite integer sequence:

```
123456789101112131415...
```

The sequence is made by joining all positive integers together.

## Core idea

Do not build the sequence. `n` can be very large, so first skip complete digit-length groups:

- 1-digit numbers: `1` to `9`
- 2-digit numbers: `10` to `99`
- 3-digit numbers: `100` to `999`
- and so on

For numbers with `len` digits:

```
count = 9 * 10^(len - 1)
total digits = len * count
```

If `n` is larger than `len * count`, the answer is not in this group. Subtract that whole group and move to the next digit length.

## Digit groups

| Digit length | Number range | Count of numbers | Total digits |
| ------------ | ------------ | ---------------- | ------------ |
| 1            | 1 - 9        | 9                | 9            |
| 2            | 10 - 99      | 90               | 180          |
| 3            | 100 - 999    | 900              | 2700         |
| 4            | 1000 - 9999  | 9000             | 36000        |

Once `n` fits inside a group, find:

1. Which actual number contains the digit.
2. Which index inside that number is the answer.

The group starts at:

```
start = 10^(len - 1)
```

The target number is:

```
start + (n - 1) / len
```

The target digit index inside that number is:

```
(n - 1) % len
```

We use `n - 1` because indexing inside the group is zero-based.

## Walkthrough

**Example:** `n = 10000`

Start with 1-digit numbers:

```
n = 10000
len = 1, count = 9, start = 1
```

There are `1 * 9 = 9` digits in this group, so skip them:

```
n = 10000 - 9 = 9991
len = 2, count = 90, start = 10
```

There are `2 * 90 = 180` digits in this group, so skip them:

```
n = 9991 - 180 = 9811
len = 3, count = 900, start = 100
```

There are `3 * 900 = 2700` digits in this group, so skip them:

```
n = 9811 - 2700 = 7111
len = 4, count = 9000, start = 1000
```

Now `7111 <= 4 * 9000`, so the answer is inside the 4-digit numbers.

Find the number:

```
start += (n - 1) / len
start += 7110 / 4
start += 1777
start = 2777
```

Find the digit index:

```
index = (n - 1) % len
index = 7110 % 4
index = 2
```

The number is `2777`. Index `2` is the third digit, so the answer is:

```
7
```

## Why use `long long`?

The number of digits in a group can be large. For example, the 9-digit group has:

```
9 * 100000000 * 9
```

digits, which does not safely fit in a 32-bit `int`. So `len`, `count`, and `start` should be `long long`.

## Complexity

- Time: `O(log n)`, because there are only about 10 digit-length groups for 32-bit `n`.
- Space: `O(1)` extra.



## Code (`find-nth-digit.cpp`)

The loop removes complete digit-length groups. After the loop, `(n - 1) / len` finds the target number and `(n - 1) % len` finds the digit inside that number.
