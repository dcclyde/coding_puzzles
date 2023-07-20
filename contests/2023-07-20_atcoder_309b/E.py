
'''
Given some tree.
Start with False everywhere.
M instances of:
    Vertex v_j and all descendants up to g_j generations become True.

How many Trues in final tree?

***********

It's hard to view it as "for each v, is v covered?"
    because of the different depths per insurance policy.

I think this could be a dfs situation.

'''

N, NUM_INSURANCES = list(map(int, input().split()))
parent = list(map(int, input().split()))

children = [[] for _ in range(N)]
for k, par in enumerate(parent):
    children[par-1].append(k+1)

policies = {}
for _ in range(NUM_INSURANCES):
    owner, depth = list(map(int, input().split()))
    owner -= 1
    if owner in policies:
        policies[owner] = max(policies[owner], depth)
    else: policies[owner] = depth

out = 0
todo = [(0, -1)]  # start at the root
while len(todo) > 0:
    curr, curr_depth = todo.pop()
    if curr in policies:
        curr_depth = max(curr_depth, policies[curr])
    if curr_depth >= 0:
        out += 1
        next_depth = curr_depth - 1
    else:
        next_depth = -1

    for o in children[curr]:
        todo.append((o, next_depth))

print(out)
