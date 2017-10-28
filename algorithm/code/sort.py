# 排序

# 1. 插入排序
# 时间复杂度O（n^2），算法稳定.
def insertion_sort(arr):
    for j in range(1,len(arr)):
        key = arr[j]
        i = j-1
        while i>=0 and arr[i]>key:
            arr[i+1] = arr[i]  # 将arr[i]往后移动
            i = i-1
        arr[i+1] = key
    return arr

arr=[3,2,1,3,5,7]
print(arr)
print(insertion_sort(arr))
print(arr)  # arr 也被改变

# 2. 归并排序
# def merge(arr, first, mid, last):
#
# def merge_sort(arr, first, last):
#     if first < last:
#         mid = (first + last)//2
#         merge_sort(arr, first, mid)
#         merge_sort(arr, mid+1, last)
#         merge(arr,first, mid, last)
