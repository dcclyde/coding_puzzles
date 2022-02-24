dat_raw = '6,13,1,15,2,0'
# dat_raw = '0,3,6'

dat = [q.strip() for q in dat_raw.split(',') if len(q.strip()) > 0]

dat = [int(q) for q in dat]



import copy

last_seen = {
    val: idx for idx, val in enumerate(dat)
}
curr = copy.deepcopy(dat)
target = 30 * (10**6)

while len(curr) < target:
    if len(curr) % (10**6) == 0:
        print(len(curr))
#     print(curr[-1], curr, last_seen)
    if curr[-1] in last_seen:
        next_number = (len(curr)-1) - last_seen[curr[-1]]
    else:
        next_number = 0
    last_seen[curr[-1]] = len(curr) - 1
    curr.append(next_number)


print(curr[-5:])
