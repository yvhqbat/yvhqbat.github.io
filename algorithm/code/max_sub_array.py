def max_sub_array(arr):
    max = 0
    x = 0
    y = 0
    n = len(arr)
    for i in range(0,n):
        for j in range(i,n):
            arr_sum = 0
            for k in range(i,j+1):
                arr_sum = arr_sum + arr[k]
                if arr_sum > max:
                    max = arr_sum
                    x = i
                    y = j
    print(x,y)
    return max

def max_sub_array_recursive(arr, first, last):
    if first==last:
        return arr[first]
    mid = (first+last)//2
    m1 = max_sub_array_recursive(arr,first, mid)
    m2 = max_sub_array_recursive(arr,mid+1,last)

    left_max=arr[mid]
    left=left_max
    for i in range(mid-1,first-1,-1):
        left += arr[i]
        if left>left_max:
            left_max = left

    right_max=arr[mid+1]
    right=arr[mid+1]
    for i in range(mid+2,last+1):
        right += arr[i]
        if right>right_max:
            right_max=right
    m3=left_max+right_max
    return max(m1,m2,m3)

arr=[1,2,5,-3,5,-30]
print(max_sub_array(arr))
print(max_sub_array_recursive(arr, 0, len(arr)-1))



