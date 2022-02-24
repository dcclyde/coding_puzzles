from typing import Dict, Union

Tree = Dict[str, Union[str, "Tree"]]


def decompress(compressed: str, tree: Tree) -> str:
    out = []
    start = 0
    ctr = 0
    while start < len(compressed):
        # print(start, out)
        curr_idx = start
        curr_dict = tree
        while True:
            ctr += 1
            if ctr >= 10:
                return None
            # print(curr_dict)
            # print(compressed[curr_idx])
            # print('')
            curr_dict = curr_dict[compressed[curr_idx]]
            if not isinstance(curr_dict, dict):
                out.append(curr_dict)
                # print(curr_dict)
                curr_idx += 1
                break
            else:
                curr_idx += 1
                if curr_idx >= len(compressed):
                    break
        start = curr_idx
    return ''.join(out)


# Examples
print(decompress('110100100', {'0': 'a', '1': {'0': 'n', '1': 'b'}}))
# print(decompress('0111010100', {'0': {'0': 'x', '1': 'z'}, '1': 'y'}))
