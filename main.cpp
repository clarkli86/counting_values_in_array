/*
ԭ��
��������A����СΪn������Ԫ��Ϊ1��n�����֣������е����ֳ����˶�Σ��е�����û�г��֡�������㷨�ͳ���ͳ����Щ����û�г��֣���Щ���ֳ����˶��ٴΡ��ܹ���O(n)��ʱ�临�Ӷȣ�O(1)�Ŀռ临�Ӷ�Ҫ�������ô��
����
�����Ŀ������һ�����ɵġ���������Ҫ�������ۣ����������֮�󣬿�����л���ֱ�����Ͳ����˼��ɡ������֪�����ɣ��Ǹ���ô���أ�
�ڿ�ʼ����֮ǰ��˵���������⣺

ԭ������û������ġ���������ˣ��ܼ򵥵ġ�
O(1)�Ŀռ京�壬����ʹ�ñ����������ܿ����������map����������

�����Ŀ����ֱ�ӵĽⷨ�������������O(n^2)�ĸ��Ӷȣ�O(1)�Ŀռ䡣�ռ������ˣ�����ʱ��û�С�

�ܶ����Ƶ���Ŀ��������XOR�ķ����������ϸ��һ�£������Ŀ������ô�����������Ŀ�Ϳ�����XOR����Ŀ�Ĳ������Ķ�����ֱ�ӵľ��ǣ�ÿһ�����ֵ��ظ��Ĵ����ǲ�ͬ�ġ�

���о����Կռ任ʱ��ķ�����������hash map����������������ʱ�������ˣ����ǿռ�û�����㡣

������������ʱ�临�Ӷ�O(n)���ռ临�Ӷ�O(1)���㷨�أ����ܿ����µĿռ䣬��ôֻʣ�£��ظ���������A����ô�������������A�أ�

���ȣ����ǽ���һ�����α�������ķ���,���Ƕ����������0��ʼ��

��һ�α���������ÿһ��A[i] = A[i] * n
�ڶ��α���������ÿһ��i��A[A[i]/n]++
�����α���������ÿһ��i��A[i] % n���ǳ��ִ���

A[i]Ӧ�ó�����A�е�A[i]λ�ã�����n���ٳ���n�������׵����ر任���ڶ��α���������A[i]�������ڵ�λ�ò�����1�������Բ��Գ���n�ģ���ÿһ��i���ֵĴ���������A[i]��nȡ�ࡣ

����һ�����α����ķ�����Ҳ�������˼·����Ŀ��������1��n��Ϊ�˷����㷨���ǣ��Լ�����洢���㣬���ǿ���0-n-1���������ͬ�ġ� ����A[i]������λ����i���������A������������λ��Ӧ����A[i] % n���ҵ�����λ�ã�����δ������λ���أ���1ô�� ��Ȼ�����ԣ�������һ�����ɣ����Ǽ�n��������ԭ��

��n���Ա�֤A[i] % n�ǲ����
A���飬���ÿһ��Ԫ�ر�ʾΪA[i] = x + k*n������x<n������k��������Ҫͳ�Ƶ�Ƶ�ʡ�

���������Ҳ�ܹ����ף�ΪʲôA[i]��A�е�λ�ã���ʾΪA[i] % n�˰ɡ�����ڶ���˼·��ת��Ϊ�������£�
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