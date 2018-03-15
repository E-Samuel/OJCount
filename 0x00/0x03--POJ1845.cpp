// Source : http://poj.org/problem?id=1845
// Author : E-Samuel(彭翼)
// Date   : 2018-3-15

/***********************************************************************
 * 
 * 一道非常有意思的数论题(如果不知道那个知识点的话，几乎无从下手)
 * 算术的基本定理(唯一分解定理)：任一整数，n > 1都可以表示成素数的乘积，且在不考虑乘积
 * 顺序的情况下，该表达式是唯一的，即
 * n = P1 * P2 * ……　* Pk (P1 <= P2 <= ……　<= Pk)
 * 上式可唯一表示成：
 * n = pow(P1, a1) * pow(P2, a2)…… * pow(Pk, ak), (ai > 0, i = 1, 2…… ,k)
 * 由此可以得出两个推论(其实嘛，感觉就是可以理解为，全部拆散为不可分的质数，然后再组合)
 * 比如哈，21000 = pow(2, 3) * pow(3, 1) * pow(5, 3) * pow(7, 1)
 * 1: 21000 约数的总和为
 * (1 + 2 + 4 + 8) * (1 + 3) * (1 + 5 + 25 + 125) * (1 + 7)
 * 仔细看看，是不是等同于，把所能分成的所有质数，各自组合然后加到了一起，然后第二个推论
 * 就显而易见了
 * 2: 21000 约数的个数为
 * (3 + 1) * (1 + 1) * (3 + 1) * (1 + 1)
 * 
 * 嗯，通过上述素因子分解，我们得出了答案应该怎么表示，但是强算的话，太过暴力，时间稳爆
 * 这里运用了分治法(递归……)，由于乘起来挺有规律哈，从零次方一直到n次方，所以嘛，可以对
 * 半分开，将高次幂提取公因子，使得后项与前项相同，然后递归就好……配合快速幂，时间复杂度
 * 可以稳到O(logN)
 * 
 * 其他注意事项：
 * 1: 质因数分解，不能直接单纯的循环整到sqrt(N)，因为最后极有可能，在拆掉很多项质数后
 * 留下了一个大于sqrt(N)的质数，而且如果N本来就是质数，那一项都拆不出，会漏掉他自己这
 * 个因子，所以嘛(我在底下的代码下加了标记，注意这个地方，考虑周全！)
 * 2: while(cin >> A >> B),这个只有在输入EOF后才会结束
 * 3: sqrt得对浮点数操作，数组new完之后得delete[]，高次幂用long long，及时取余防爆
 * 
 * *********************************************************************/

#include<iostream>
#include<cmath>

using namespace std;

typedef struct node {
    int prime;
    int power;
} Node;

//分解质因数
int factoring(int A, Node *arr) {
    int tem(2), num(0);
    int max = int(sqrt((double)A));
    while(tem <= max) {
        while(A % tem == 0) {
            A /= tem;
            if(!arr[num].power) arr[num].prime = tem;
            arr[num].power++;
        }
        if(arr[num].power) num++;
        tem++;
    }
    //若A为质数,或者没有拆完的数！
    if(A != 1) {
        arr[num].prime = A;
        arr[num].power = 1;
        num++;
    }
    return num;
}

//快速幂
int quickPower(int base, int index) {
    int modNum(9901), res(1);
    for(; index; index >>= 1) {
        if(index & 1)
            res = (long long)res * base % modNum;
        base = (long long)base * base % modNum;
    }
    return res;
}

//递归分治，将总和算出来
int sumDiv(int base, int index) {
    int modNum(9901);
    long long res(0);
    if(index == 0) return 1;
    if(index == 1) return (base + 1) % modNum;
    if(index & 1) {
        res = 1 + quickPower(base, (index + 1) / 2);
        res *= sumDiv(base, (index - 1) / 2);
    }else {
        res = 1 + quickPower(base, index / 2 + 1);
        res *= sumDiv(base, index / 2 -1);
        res %= modNum;
        res += quickPower(base, index / 2);
    }
    return (res % modNum);
}

int main() {
    int A(0), B(0), modNum(9901);
    while(cin >> A >> B) {
        //连int最大值都没爆的数，真不信能拆出超过20个质数
        if(A == 0) continue;
        Node *arr = new node[20]();
        int num = factoring(A, arr);
        long long res(1);
        for(int i(0); i < num; i++) {
            arr[i].power *= B;
            res = res * sumDiv(arr[i].prime, arr[i].power) % modNum;
        }
        cout << (res % modNum) << endl;
        delete[] arr;
    }
    return 0;
}