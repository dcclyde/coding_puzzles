from template import *

def demo_debug_printouts():
    el()
    a = 'abcde'
    x = {'q': 14, 'apple': -3, 'monkey': 40}
    y = [[1, 5, 3, 2], [3, 6, 4, 2], [8, 9, 9, 5]]
    dbg(a, x, y)
    dbgY(print_details_helper(x.items()))
    dbgP(print_tsv_helper(y))
    dbgG("abbreviations pdh and pth work too", pdh(y))
    if local_run:
        print(
            "Use `local_run` boolean like this to run a more complicated debug function"
            " that will be totally skipped if the code executes on a different machine."
        )
    el()
    dbgc("any comment", a, "Use dbgc to put first arg on the left as a marker.")
    dbgcP("diff color", x, y, "color variants work too. dbgcP, dbgcR, dbgcG, etc.")

    print("demo all the different colors:")
    dbg("dbg")
    dbgG("dbgG")
    dbgP("dbgP")
    dbgY("dbgY")
    dbgR("dbgR")
    dbgB("dbgB")
    dbgW("dbgW")
    dbgBackground("dbgBackground")
    el()

demo_debug_printouts()
