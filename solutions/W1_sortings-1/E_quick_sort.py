import random

def quicksort(array):
    if len(array) < 2:
        return array
    else:
        pivot = random.choice(array)
        less = [i for i in array if i < pivot]
        equal = [i for i in array if i == pivot]
        greater = [i for i in array if i > pivot] 
    return quicksort(less) + equal + quicksort(greater)

N = int(input())
arr = list(map(int, input().split()))
print(*quicksort(arr))
