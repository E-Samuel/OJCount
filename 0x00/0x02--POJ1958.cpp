// Source : http://poj.org/problem?id=1958
// Author : E-Samuel(彭翼)
// Date   : 2018-3-9

/***********************************************************************
 * 
 * 多阶汉诺塔问题，思路很单纯，暴力递归就好，不过这个有几个注意事项
 * 四阶的最优解，不是单纯的把n-2个盘子移走，然后再用三阶把剩下两盘移过去就可以
 * 得把问题拆分成，先把前i个盘子用四阶移到中间柱子上，剩下的形成一个(n-i)的三阶hanoi
 * 移动，最后把之前的那i个，用四阶移向目标柱，完成
 * 
 * 具象化成代码如下：
 * hanoi_4[n] = min(hanoi_4[i]*2 + hanoi_3[n-i]) (1 <= i < n)
 * 计算的过程中，可以把中间值，比如每项的hanoi_4[i]算出来的值存下来，省得重复计算
 * 
 * 其他注意事项：
 * min值的初始化可以用(0x7fffffff)，这个是最大的32位int数
 * 3阶汉诺的通项公式是，hanoi_3(n) = (1 << n) - 1
 * 
 * *********************************************************************/

#include<iostream>

using namespace std;

static int* res;

int hanoi_3(int n) {
    return (1 << n) - 1;
}

int hanoi_4(int n) {
    if(n == 1) {
        return 1;
    }else {
        int min(0x7fffffff);
        for(int i(1); i < n; i++) {
            int tem = (res[i] ? res[i] : hanoi_4(i)) * 2 + hanoi_3(n-i);
            if(tem < min) {min = tem;}
        }
        return min;
    }
}

int main() {
    res = new int[13]();
    for(int i(1); i <= 12; i++) {
        res[i] = hanoi_4(i);
        cout << res[i] << endl;
    }
    return 0;
}