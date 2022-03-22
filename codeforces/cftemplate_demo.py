from cftemplate import *

def demo():
    a = 'abcde'
    x = {'q': 14, 'apple': -3, 'monkey': 40}
    y = [[1, 5, 3, 2], [3, 6, 4, 2], [8, 9, 9, 5]]
    dbg(a, x, y)
    dbgY(print_details_helper(x.items()))
    dbgP(print_tsv_helper(y))
    dbgG("abbreviations work too", pdh(y))
    if local_run:
        print(
            "Use `local_run` boolean like this to run a more complicated debug function"
            " that will be totally skipped if the code executes on a different machine."
        )

demo()
