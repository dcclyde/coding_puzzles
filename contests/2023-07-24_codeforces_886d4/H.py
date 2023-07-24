'''
Basically, if there are multiple paths to get somewhere
    then they should all have the same total weight.
'''

def solve_one():
    N, NUM_CONDITIONS = list(map(int,input().split()))
    graph = [[] for _ in range(N)]
    for _ in range(NUM_CONDITIONS):
        a, b, delta = list(map(int,input().split()))
        a -= 1
        b -= 1
        graph[a].append((b, delta))
        graph[b].append((a, -delta))
    # print(graph)

    loc = [None for _ in range(N)]
    for base in range(N):
        if loc[base] is not None: continue
        # start a graph search from here.

        todo = [base]
        loc[base] = 0
        # print(todo)
        while len(todo) > 0:
            curr = todo.pop()
            for o, delta in graph[curr]:
                # print(curr, o, delta)
                if loc[o] is None:
                    loc[o] = loc[curr] + delta
                    todo.append(o)
                elif loc[o] == loc[curr] + delta:
                    continue
                else:
                    print("NO")
                    return

    print("YES")
    return

T = int(input())
for _ in range(T):
    solve_one()
