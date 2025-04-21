n = int(input())
arr = list(map(int, input().split()))

ok = True

for i in range(n // 2):
    left = 2 * i + 1
    right = left + 1

    if left < n and arr[i] > arr[left]:
        print("NO")
        ok = False
        break
    if right < n and arr[i] > arr[right]:
        print("NO")
        ok = False
        break

if ok:
    print("YES")

    

