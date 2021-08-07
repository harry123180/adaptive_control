def partitionDisjoint( nums):
    lens = len(nums)

    for i in range(1,lens,1):
        fb = lens - i
        a = [None] * (i)
        b = [None] * fb
        for j in range(i):
            a[j] = nums[j]
        for u in range(fb):
            b[u] = nums[u+i]
        if(max(a)<=min(b)):
            return len(a)
            break
c = [5,0,3,8,6]
print(partitionDisjoint(c))


def partitionDisjoint(nums):
    left = []
    right = []
    if len(nums) == 2:
        left.append(nums[0])
        right.append(nums[1])
        return len(left)
    print(nums(len(nums) - 1))
    elif (max(nums) != nums[len(nums) - 1]):
        for x in range(len(nums)):
            if nums[x] <= nums[0]:
                left.append(nums[x])
            else:
                right.append(nums[x])
        return len(left)
    else:
        ans = len(nums) - 1
        return ans
print(partitionDisjoint(c))