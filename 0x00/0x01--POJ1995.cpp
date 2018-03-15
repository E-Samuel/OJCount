// Source : http://poj.org/problem?id=1995
// Author : E-Samuel(彭翼)
// Date   : 2018-3-7

/***********************************************************************
 * 
 * 单纯的算指数，太过暴力，时间必然超限。
 * 故使用快速幂思想，将指数拆成多个2的n次方的和。
 * 
 * 利用如下规律
 * 1: (a * b) % c = (a % c) * (b % c) % c
 * 2: pow(a, pow(2,n)) = pow(a, pow(2,n-1)) * pow(a, pow(2,n-1))
 * 多次取模，保证了单次运算的数字不会太大(然而还是超了int)
 * 利用a的pow(2,n)次方，等于a的pow(2,n-1)的平方，进行递推，总共乘法次数，由直接算幂
 * 次的O(N)简化为了O(logN),大幅减少计算量
 * 
 * 其他注意事项
 * 依次取指数的各个位，可以用(index & 1)，查出最末位是否为零，然后再进行(index >>= 1)
 * 将下一位移至最末，进行判断
 * 这种……计算量比较大的题，还是别用int了吧，long long比较靠谱
 * 
 * *********************************************************************/
#include<iostream>

using namespace std;

int quikePower(int base, int index, int modNum) {
    int res(1);
    for(; index; index >>= 1) {
        if(index & 1)
            res = (long long)res * base % modNum;
        base = (long long)base * base % modNum;
    }
    return res;
}

int main() {
    int z(0), player(0), modNum(0);
    cin >> z;
    int *resArr = new int[z];
    for(int i(0); i < z; i++) {
        cin >> modNum >> player;
        int res(0);
        for(int j(0); j < player; j++) {
            int base(0), index(0);
            cin >> base >> index;
            res = (res + quikePower(base, index, modNum)) % modNum;
        }
        resArr[i] = res;
    }
    for(int i(0); i < z; i++)
        cout << resArr[i] << endl;
    return 0;
}