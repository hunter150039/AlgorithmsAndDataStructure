//
// Created by windyear_office on 17-12-4.
//

#ifndef SORTALGORITHM_MERGE_SORT_H
#define SORTALGORITHM_MERGE_SORT_H

#include "basesort.h"

class MergeSort: public Sort{
public:
    explicit MergeSort(int length, int* p_array):Sort(length, p_array){
        //初始化了指针才能用,全部复制过去
        temp_array = new int[length];
        for(int k = 0; k < length; k++){
            temp_array[k] = array[k];
        }
    }


    ~MergeSort(){
        delete[] temp_array;
        temp_array = NULL;
    }
    //合并数组，需要额外使用一个数组空间临时保存。通过四个条件判断应该合并哪一个。
    void Merge(int low, int middle, int high){
        int i = low;
        int j = middle + 1;
        //一个临时保存数组的变量,这里有问题，数组越界。很难察觉。
        //所以有一种做法是声明一个跟原来数组一样长的数组变量作为类的成员，这样每次访问临时数组的时候就不会错。
        //数组是类的成员，保证了数组不会越界１
        //这一步不能缺少，因为每次归并之后数组是局部排好序的，如果不复制过去，每次都会归并原来还没有排序的数组。
        for(int k = low; k <= high; k++){
            temp_array[k] = array[k];
        }
        //这里很容易数组越界访问。k不能从０开始访问。
        for(int k = low; k <= high; k++){
            if(i > middle){
                array[k] = temp_array[j++];
            }
            else if(j > high){
                array[k] = temp_array[i++];
            }
            else if(temp_array[i] > temp_array[j]){
                array[k] = temp_array[j++];
            }
            else{
                array[k] = temp_array[i++];
            }
        }
    }

    void Merge_Sort(int low, int high){
        //判断什么时候递归就结束，十分重要的递归条件
        if(low >= high){
            return;
        }

        int middle = (low + high)/2;
        Merge_Sort(low, middle);
        Merge_Sort(middle + 1, high);
        Merge(low, middle, high);
    }
//可以有一种自底向上的方法，不同于第一种自顶向下的分治法。
//从两两合并开始，一直循环到最大的两个子数组合并，这里的关键是合并的连个子数组的大小sz,每次大小都翻倍。
    void Merge_Sort2(int low, int high){
        //数组长度
        int length = N;
        for(int sz = 1; sz < N; sz = 2 * sz){
            //这里的数组下标很容易就会乱，要认真对待
            //低索引值不能大于length - sz否则数组会越界。
            for(int low = 0 ; low < length -sz ; low = low + sz + sz){
                Merge(low, low + sz - 1, ((low + 2 * sz - 1) < (length - 1))?(low + 2 * sz - 1):(length - 1));
            }
        }
    }
private:
    int* temp_array;
};
#endif //SORTALGORITHM_MERGE_SORT_H
