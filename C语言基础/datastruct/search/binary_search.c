#include <stdio.h>
#include <math.h>
//折半查找加法和除法运算mid = (high-low)/2
//插值查找，进行复杂的四则运算
//斐波那契查找进行加减法运算mid = low+F(k-1)-1


//折半查找
int Binary_Search(int *a,int n,int key){
    int low,high,mid;
    low = 1;
    high = n;
    while(low <= high){
        mid = (low + high)/2;
        if(key < a[mid])
          high = mid -1;
        else if (key> a[mid])
          low = mid+1;
        else
          return mid;
    }
    return -1;
}
//插值查找	表长较大，关键字分布比较均匀的查找表
//针对极端不均匀的数据，不适合插值查找
//mid = (low+high)/2 = low+(high-low)/2
//=low+(high-low)*(key-a[low])/(a[high]-a[low])
int Interpolation_Search(int *a,int n,int key){
	int low,high,mid;
	low = 1;
	high = n;
	while(low <= high){
		mid = low +floor((high-low)*(key-a[low])/(a[high]-a[low]));
		if(key <a[mid])
			high = mid+1;
		else if(key > a[mid])
			low = mid+1;
		else 
			return mid;
	}
	return -1;
}
//斐波那契查找

