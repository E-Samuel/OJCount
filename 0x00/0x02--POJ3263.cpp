// Source : http://poj.org/problem?id=3263
// Author : E-Samuel(彭翼)
// Date   : 2018-3-13

/***********************************************************************
 * 
 * 没看解析前，按照暴力姑且还是莽过去了，O(NM)的复杂度
 * 将上下两段代码进行比较，差别主要是体现在，如何处理将一个区间内的数都减一上
 * 书上的解法，是利用前缀和，将前ｎ项的加减关系用一个新数组存下来，从而把对一个区间的操
 * 作，转化为左右两个端点上的操作。
 * 很具有普适性哈，很多这种按照顺序的批量操作，其实都可以简化为前缀和(前ｎ个操作的累积)
 * 
 * 对于一个数组A
 * 前缀和：新建一个数组B,每一项B[i],保存A中[0,i]的和
 * 后缀和：新建一个数组B,每一项B[i],保存A中[i,n-1]的和
 * 
 * 其他注意事项：
 * 第一段代码那个大小排列，简直写的就是个垃圾！玩什么三目运算，好好用个swap()不行嘛？
 * 发现，那种单行if,如果后面不跟大括号，会好看一些来着
 * 用两个值去Hash,不用新建什么结构体，直接用个pair<typeA, typeB>就好
 * 
 * *********************************************************************/

#include<iostream>
#include<map>

using namespace std;

// 下面的代码，是没有运用容斥原理的暴力版，时间复杂度O(NM)
// int main() {
//     int N(0), I(0), H(0), R(0);
//     cin >> N >> I >> H >> R;
//     int *arr = new int[N+1]();
//     map<pair<int, int>, bool> Hash;
//     for(int i(1); i < N+1; i++) {
//         arr[i] = H;
//     }
//     for(int i(0); i < R; i++) {
//         int tem1, tem2, min;
//         cin >> tem1 >> tem2;
//         min = tem1;
//         tem1 = tem1 < tem2 ? tem1 : tem2;
//         tem2 = tem2 > min ? tem2 : min;
//         if(Hash.find(make_pair(tem1, tem2)) != Hash.end()) {continue;}
//         Hash[make_pair(tem1, tem2)] = true;
//         for(int j(tem1+1); j < tem2; j++) {
//             arr[j] = arr[j]-1;
//         }
//     }
//     for(int i(1); i < N+1; i++)ji
//         cout << arr[i] << endl;
//     }
//     delete[] arr;
//     return 0;
// }

//参考《进阶指南》优化后的解，时间复杂度O(N+M)
int main() {
    int N(0), I(0), H(0), R(0);
    cin >> N >> I >> H >> R;
    int *arr = new int[N]();
    int *sum = new int[N]();
    map<pair<int, int>, bool> Hash;
    for(int i(0); i < R; i++) {
        int tem1, tem2;
        cin >> tem1 >> tem2;
        if(tem1 > tem2) swap(tem1, tem2);
        if(Hash[make_pair(tem1, tem2)]) continue;
        sum[tem1 + 1]--; sum[tem2]++;
        Hash[make_pair(tem1, tem2)] = true;
    }
    for(int i(1); i <= N; i++) {
        arr[i] = arr[i-1] + sum[i];
        cout << (arr[i] + H) << endl;
    }
    delete[] arr;
    delete[] sum;
    return 0;
}