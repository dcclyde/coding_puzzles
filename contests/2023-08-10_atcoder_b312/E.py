
N = int(input())

dat = {}
out = [0 for _ in range(N)]
for k in range(N):
    x1, y1, z1, x2, y2, z2 = tuple(map(int, input().split()))

    # add all faces of this cube to dat.
    curr_faces = {
        (x1, y1, x2, y2),
        (x1, z)
    }
