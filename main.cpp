/*
原题
给定数组A，大小为n，数组元素为1到n的数字，不过有的数字出现了多次，有的数字没有出现。请给出算法和程序，统计哪些数字没有出现，哪些数字出现了多少次。能够在O(n)的时间复杂度，O(1)的空间复杂度要求下完成么？
分析
这个题目，是有一定技巧的。技巧是需要慢慢积累，待经验多了之后，可以灵感或者直觉，就产生了技巧。如果不知道技巧，那该怎么办呢？
在开始分析之前，说明两个问题：

原数组是没有排序的。如果排序了，很简单的。
O(1)的空间含义，可以使用变量，但不能开辟数组或者map等来计数。

这个题目，很直接的解法就是两层遍历，O(n^2)的复杂度，O(1)的空间。空间满足了，但是时间没有。

很多类似的题目，都会用XOR的方法，大家仔细想一下，这个题目，可以么？或者这个题目和可以用XOR的题目的差异在哪儿？最直接的就是，每一个数字的重复的次数是不同的。

还有就是以空间换时间的方法，例如用hash map或者数组来计数。时间满足了，但是空间没有满足。

那怎样才能有时间复杂度O(n)，空间复杂度O(1)的算法呢？不能开辟新的空间，那么只剩下，重复利用数组A。那么该如何利用数组A呢？

首先，我们介绍一种三次遍历数组的方法,我们都考虑数组从0开始：

第一次遍历：对于每一个A[i] = A[i] * n
第二次遍历：对于每一个i，A[A[i]/n]++
第三次遍历：对于每一个i，A[i] % n就是出现次数

A[i]应该出现在A中的A[i]位置，乘以n、再除以n，很容易的来回变换；第二次遍历，对于A[i]本来所在的位置不断增1，但绝对不对超出n的，那每一个i出现的次数，就是A[i]对n取余。

还有一种两次遍历的方法，也是上面的思路：题目中数组是1到n，为了方便算法考虑，以及数组存储方便，我们考虑0-n-1，结果是相同的。 考虑A[i]，现在位置是i，如果采用A来计数，它的位置应该是A[i] % n，找到计数位置，该如何处理这个位置呢？加1么？ 显然不可以，这里有一个技巧，就是加n，有两个原因

加n可以保证A[i] % n是不变的
A数组，最后每一个元素表示为A[i] = x + k*n，其中x<n，并且k就是我们要统计的频率。

这样，大家也能够明白，为什么A[i]在A中的位置，表示为A[i] % n了吧。上面第二种思路，转换为代码如下：
*/

#include <iostream>
#include <ctime>
#include <map>
using namespace std;

int * random_array(int size) {
    int * a = new int[size];
    std::srand(std::time(0));
    cout << "{";
    for(int i = 0; i < size; ++i) {
        a[i] = rand() % size + 1;
        cout << a[i] << ", ";
    }
    cout << "}" << endl;
    return a;
}

// Use negative value for counting. If a[i] is negative it means such a value has been found
int* count_neg(int * arr, int n) {
    int *a = new int[n];
    memcpy(a, arr, sizeof(int)* n);

    for(int i = 0; i < n; ++i) {
        while(a[i] > 0) {
            // No need to swap
            if(a[i] == i + 1) {
                a[i] = -1;
            }
            // Found another a[i]
            else if(a[a[i] - 1] <= 0) {
                --a[a[i] - 1];
                a[i] = 0;
            }
            // Found the first a[i]
            else {
                int temp = a[a[i] - 1];
                a[a[i] - 1] = -1;
                a[i] = temp;
            }
        }
    }
    for(int i = 0; i < n; ++i) {
        a[i] = -a[i];
    }    
    return a;
}

int* count_rem(int *arr, int n) {
    int *a = new int[n];
    memcpy(a, arr, sizeof(int)* n);

    for(int i = 0; i < n; ++i) {
        a[i] = a[i] * n;
    }
    for(int i = 0; i < n; ++i) {
        ++a[a[i]/n - 1];
    }
    for(int i = 0; i < n; ++i) {
        a[i] = a[i] % n;
    }
    return a;
}

int* count_quo(int *arr, int n) {
    int *a = new int[n];
    memcpy(a, arr, sizeof(int)* n);

    for(int i = 0; i < n; ++i) {
        // The biggest possible value for the original a[i] is n, so we use n + 1 as the divider
        a[a[i] % (n + 1) - 1] += n + 1;
    }    
    for(int i = 0; i < n; ++i) {
        a[i] = a[i] / (n + 1);
    }
    return a;
}
void main()
{
    // Generate random array
    int n = 100;
    int *a = random_array(n);
    // Get the count in a naive way
    map<int, int> count;
    for(int i = 0; i < n; ++i) {
        ++count[a[i]];
    }
    {
        int * res = count_neg(a, n);
        // Verify result
        for(int i = 0; i < n; ++i) {
            if(res[i] != count[i + 1]) {
                cerr << "Error: i = " << i << ", res[i] = " << res[i] << ", count[i + 1] = " << count[i + 1] << endl;
                break;
            }
        }
    }
    {
        int * res = count_rem(a, n);
        // Verify result
        for(int i = 0; i < n; ++i) {
            if(res[i] != count[i + 1]) {
                cerr << "Error: i = " << i << ", res[i] = " << res[i] << ", count[i + 1] = " << count[i + 1] << endl;
                break;
            }
        }
    }
    {
        int * res = count_quo(a, n);
        // Verify result
        for(int i = 0; i < n; ++i) {
            if(res[i] != count[i + 1]) {
                cerr << "Error: i = " << i << ", res[i] = " << res[i] << ", count[i + 1] = " << count[i + 1] << endl;
                break;
            }
        }
    }
}