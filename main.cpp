#include <iostream>
#include <ctime>
#include <cassert>
#include <algorithm>
#include "TestHelper.h"

using namespace std;

template <typename T>
int __partition(T arr[], int l, int r){
    int p = rand()%(r-l+1)+l;
    swap(arr[l],arr[p]);

    //[l+1...j]<p; [j+1..i)>=p
    int j=l;
    for(int i=l+1;i<=r;i++)
        if(arr[i]<arr[l])
            swap(arr[i],arr[++j]);
    swap(arr[l],arr[j]);
    return j;

}

template <typename T>
int __selection(T arr[], int l, int r, int k){
    if(l==r){
        return arr[l];
    }
    // partition之后, arr[p]的正确位置就在索引p上
    int p = __partition(arr, l, r);

    if(k==p)
        return arr[p];
    else if(k<p)
        return __selection(arr, l,p-1,k);
    else
        return __selection(arr,p+1,r,k);

}

template <typename T>
int selection(T arr[], int n, int k){
    assert(k>=0&&k<n);
    srand(time(NULL));
    return __selection(arr, 0,n-1,k);
}

int main() {

    // 生成一个大小为n, 包含0...n-1这n个元素的随机数组arr
    int n = 10000;
    int* arr = TestHelper::generateOrderedArray(n);
    TestHelper::shuffleArray(arr, n);

    // 验证selection算法, 对arr数组求第i小元素, 应该为i
    for( int i = 0 ; i < n ; i ++ ){
        assert( selection(arr, n, i) == i );
        cout<<"test "<<i<<" complete."<<endl;
    }
    cout<<"Test selection completed."<<endl;

    delete[] arr;

    return 0;
}