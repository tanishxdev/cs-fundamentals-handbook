<!-- MY DSA LEARNING TEMPLATE -->

# Problem: EXAMPLE

GFG Link: https://www.geeksforgeeks.org/problems/cyclically-rotate-an-array-by-one2614/1  
LeetCode (General): https://leetcode.com/problems/rotate-array/

---

## 1. Problem Statement

English:  
Given an array of n integers, rotate it left by 1 position in-place. The first element moves to the end.

Hinglish:  
Array diya hai, ek baar left rotate karo — pehla element last mein, baaki ek step left.

---

## 2. Input / Output / Constraints

Input Example: arr = [1, 2, 3, 4, 5]  
Output Expected: [2, 3, 4, 5, 1]  

Constraints:  
1 ≤ n ≤ 10⁵  
-10⁹ ≤ arr[i] ≤ 10⁹

---

## 3. Examples (All Cases Covered)

Example 1:  
Input: [10, 20, 30, 40, 50]  
Output: [20, 30, 40, 50, 10]  
Why: Normal case, shows full shift

Example 2:  
Input: [5]  
Output: [5]  
Why: n = 1 → no rotation needed

Example 3:  
Input: []  
Output: []  
Why: Empty array → return as-is

Example 4:  
Input: [1, 1, 1, 1]  
Output: [1, 1, 1, 1]  
Why: All duplicates → rotation doesn't change

Example 5:  
Input: [1, 2]  
Output: [2, 1]  
Why: Smallest n > 1 → test boundary

---

## 4. Intuition & Core Thinking

Array is like a conveyor belt of boxes.  
Left rotate by 1 = move belt one step left → first box falls off and goes to the end.

Key Questions:  
- Can I shift without losing data? → Yes, save first element  
- Can I avoid O(n) space? → Yes, do in-place  
- Can I generalize to k rotations? → Yes, use reversal trick

---

# APPROACHES (Brute → Optimal)

---

## Approach 1: Brute Force – Shift with Temp

### Intuition  
Like passing a baton in a relay race.  
First runner (arr[0]) is removed → everyone moves forward → first runner joins at the end.

### Why This Approach?  
- Most natural way to think  
- Teaches in-place shifting  
- Easy to dry run and debug

### Why Move to Next?  
- O(n) shifts → slow for large n  
- Not extensible to rotate by k efficiently  
- Interviewers expect better in-place solution

---

### Algorithm  
1. If n <= 1 → return  
2. Save first = arr[0]  
3. For i from 0 to n-2: arr[i] = arr[i+1]  
4. arr[n-1] = first

---

### Pseudocode  

```
function rotateLeftByOne(arr):  
    if arr.length <= 1:  
        return  
    first = arr[0]  
    for i from 0 to arr.length-2:  
        arr[i] = arr[i+1]  
    arr[arr.length-1] = first
```
---

### Dry Run: [A B C D]  
first = A  
i=0: arr[0] = B → [B B C D]  
i=1: arr[1] = C → [B C C D]  
i=2: arr[2] = D → [B C D D]  
arr[3] = A → [B C D A] Done

---

### Code

#### C++

```cpp
void rotateBrute(vector<int>& arr) {  
    int n = arr.size();  
    if (n <= 1) return;  
    int first = arr[0];  
    for (int i = 0; i < n - 1; i++) {  
        arr[i] = arr[i + 1];  
    }  
    arr[n - 1] = first;  
}
```

#### JavaScript
```js
function rotateBrute(arr) {  
    if (arr.length <= 1) return;  
    let first = arr[0];  
    for (let i = 0; i < arr.length - 1; i++) {  
        arr[i] = arr[i + 1];  
    }  
    arr[arr.length - 1] = first;  
}

```
* Time Complexity: O(n)  
* Space Complexity: O(1)

---

## Approach 2: Using Extra Array (Temp Array)

### Intuition  
Make a new conveyor belt.  
Copy elements from index 1 to n-1 → add arr[0] at end → copy back.

### Why This Approach?  
- Super clear logic  
- No shifting confusion  
- Great for understanding indexing

### Why Move to Next?  
- Uses O(n) extra space → not allowed in interviews  
- Two passes → slower in practice  
- Not in-place

---

### Algorithm  
1. If n <= 1 → return  
2. Create temp array of size n  
3. For i from 1 to n-1: temp[i-1] = arr[i]  
4. temp[n-1] = arr[0]  
5. Copy temp → arr

---

### Pseudocode 
``` 
function rotateTemp(arr):  
    if arr.length <= 1: return  
    temp = new array of size n  
    for i from 1 to n-1:  
        temp[i-1] = arr[i]  
    temp[n-1] = arr[0]  
    arr = temp
```
---

### Code

#### C++
```cpp
void rotateTemp(vector<int>& arr) {  
    int n = arr.size();  
    if (n <= 1) return;  
    vector<int> temp(n);  
    for (int i = 1; i < n; i++) {  
        temp[i - 1] = arr[i];  
    }  
    temp[n - 1] = arr[0];  
    arr = temp;  
}
```


#### JavaScript

```js
function rotateTemp(arr) {  
    if (arr.length <= 1) return;  
    let temp = [];  
    for (let i = 1; i < arr.length; i++) {  
        temp[i - 1] = arr[i];  
    }  
    temp[arr.length - 1] = arr[0];  
    for (let i = 0; i < arr.length; i++) {  
        arr[i] = temp[i];  
    }  
}
```

* Time Complexity: O(n)  
* Space Complexity: O(n)

---

## Approach 3: Reversal Algorithm (Optimal & General)

### Intuition  
Reverse = Swap blocks  
To left rotate by k:  
1. Reverse first k → brings them to front in reverse  
2. Reverse rest → brings them to end in reverse  
3. Reverse all → fixes order

For k=1:  
[A B C D E] → Reverse [A] (no change) → Reverse [B C D E] → [E D C B A] → Reverse all → [B C D E A]

### Why This Approach?  
- O(1) space  
- Works for any k  
- Elegant & interview favorite  
- No data loss

### Why This is Final?  
- No better in-place method exists  
- Generalizes to k rotations  
- Impresses interviewer

---

### Algorithm (Left Rotate by k)  
1. k = k % n  
2. If k == 0 → return  
3. Reverse 0 to k-1  
4. Reverse k to n-1  
5. Reverse 0 to n-1

---

### Pseudocode  
```
function rotateByK(arr, k):  
    n = arr.length  
    if n == 0: return  
    k = k % n  
    if k == 0: return  
    reverse(arr, 0, k-1)  
    reverse(arr, k, n-1)  
    reverse(arr, 0, n-1)
```
---

### Dry Run: [1 2 3 4 5], k=2  
Step 1: Reverse [0,1] → [2 1 3 4 5]  
Step 2: Reverse [2,4] → [2 1 5 4 3]  
Step 3: Reverse all → [3 4 5 1 2] Correct!

---

### Code

#### C++
```cpp
void reverse(vector<int>& arr, int start, int end) {  
    while (start < end) {  
        swap(arr[start++], arr[end--]);  
    }  
}  
void rotateReversal(vector<int>& arr, int k) {  
    int n = arr.size();  
    if (n == 0) return;  
    k %= n;  
    if (k == 0) return;  
    reverse(arr, 0, k - 1);  
    reverse(arr, k, n - 1);  
    reverse(arr, 0, n - 1);  
}
```
#### JavaScript

```JavaScript
function reverse(arr, start, end) {  
    while (start < end) {  
        [arr[start], arr[end]] = [arr[end], arr[start]];  
        start++;  
        end--;  
    }  
}  
function rotateReversal(arr, k) {  
    let n = arr.length;  
    if (n === 0) return;  
    k = k % n;  
    if (k === 0) return;  
    reverse(arr, 0, k - 1);  
    reverse(arr, k, n - 1);  
    reverse(arr, 0, n - 1);  
}

Time Complexity: O(n)  
Space Complexity: O(1)
```
---

## Approach 4: STL / Built-in (Production)

### Intuition  
Use language’s optimized rotate — handles edge cases, fast, clean.

### Why This?  
- Real-world code  
- One-liner  
- STL is highly optimized

### Why Not Always?  
- Interviewers want logic  
- May ask to implement manually

---

### Code

#### C++
```cpp
#include <algorithm>  
void rotateSTL(vector<int>& arr) {  
    if (arr.empty()) return;  
    std::rotate(arr.begin(), arr.begin() + 1, arr.end());  
}
```

#### JavaScript (No built-in rotate → use shift + push)

```js
function rotateSTL(arr) {  
    if (arr.length <= 1) return;  
    let first = arr.shift();  
    arr.push(first);  
}
```
* Time Complexity: O(n)  
* Space Complexity: O(1)

---

## 5. Edge Case List (Line-wise)

Edge Case: Empty array  
Input: []  
Expected: []  
Handled: Yes (early return)

Edge Case: n = 1  
Input: [7]  
Expected: [7]  
Handled: Yes (loop skipped)

Edge Case: n = 2  
Input: [A, B]  
Expected: [B, A]  
Handled: Yes

Edge Case: k > n  
Input: k=7, n=3  
Expected: k = 7 % 3 = 1  
Handled: Yes (k %= n)

Edge Case: Duplicates  
Input: [1, 1]  
Expected: [1, 1]  
Handled: Yes

---

## 6. Complexity Summary

Approach: Brute Shift  
Time: O(n)  
Space: O(1)  
Best For: Learning basics

Approach: Temp Array  
Time: O(n)  
Space: O(n)  
Best For: Clarity

Approach: Reversal  
Time: O(n)  
Space: O(1)  
Best For: Interviews (optimal)

Approach: STL / Built-in  
Time: O(n)  
Space: O(1)  
Best For: Production code

---

## 7. Final Consolidated Code

### C++
```cpp
#include <bits/stdc++.h>  
using namespace std;  

class Solution {  
public:  
    // 1. Brute  
    void brute(vector<int>& a) {  
        if (a.size() <= 1) return;  
        int first = a[0];  
        for (int i = 0; i < a.size()-1; i++) a[i] = a[i+1];  
        a.back() = first;  
    }  

    // 2. Temp Array  
    void tempArr(vector<int>& a) {  
        int n = a.size();  
        if (n <= 1) return;  
        vector<int> t(n);  
        for (int i = 1; i < n; i++) t[i-1] = a[i];  
        t[n-1] = a[0];  
        a = t;  
    }  

    // 3. Reversal (k)  
    void reverse(vector<int>& a, int l, int r) {  
        while (l < r) swap(a[l++], a[r--]);  
    }  
    void reversal(vector<int>& a, int k) {  
        int n = a.size();  
        if (n == 0) return;  
        k %= n;  
        if (k == 0) return;  
        reverse(a, 0, k-1);  
        reverse(a, k, n-1);  
        reverse(a, 0, n-1);  
    }  

    // 4. STL  
    void stl(vector<int>& a) {  
        if (a.empty()) return;  
        rotate(a.begin(), a.begin()+1, a.end());  
    }  
};
```
### JavaScript


```JavaScript
class Solution {  
    // 1. Brute  
    brute(arr) {  
        if (arr.length <= 1) return;  
        let first = arr[0];  
        for (let i = 0; i < arr.length-1; i++) {  
            arr[i] = arr[i+1];  
        }  
        arr[arr.length-1] = first;  
    }  

    // 2. Temp  
    temp(arr) {  
        if (arr.length <= 1) return;  
        let t = [];  
        for (let i = 1; i < arr.length; i++) t[i-1] = arr[i];  
        t[arr.length-1] = arr[0];  
        for (let i = 0; i < arr.length; i++) arr[i] = t[i];  
    }  

    // 3. Reversal  
    reverse(arr, l, r) {  
        while (l < r) [arr[l++], arr[r--]] = [arr[r], arr[l]];  
    }  
    reversal(arr, k) {  
        let n = arr.length;  
        if (n === 0) return;  
        k %= n;  
        if (k === 0) return;  
        this.reverse(arr, 0, k-1);  
        this.reverse(arr, k, n-1);  
        this.reverse(arr, 0, n-1);  
    }  

    // 4. Built-in style  
    builtin(arr) {  
        if (arr.length <= 1) return;  
        arr.push(arr.shift());  
    }  
}
```
---

## 8. Interview Strategy

1. Start: "Let me do brute force with shift" → Show basics  
2. "But this is O(n) shifts. Can we do better?"  
3. "Yes! Reversal trick → works for any k, O(1) space"  
4. "In production, I'd use STL rotate or arr.push(arr.shift())"  
5. "Edge cases? → n=0,1, k>n → handled with k%=n"

---
