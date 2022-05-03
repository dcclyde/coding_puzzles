from template import *

def demo_debug_printouts():
    print("hi")
    dbgBackground("Debug printouts")
    el()
    a = 'abcde'
    x = {'q': 14, 'apple': -3, 'monkey': 40}
    y = [[1, 5, 3, 2], [3, 6, 4, 2], [8, 9, 9, 5]]
    dbg(a, x, y)
    dbgY(pdh(x.items()))
    dbg(pdh(y))
    dbgP(print_tsv_helper(y))
    dbgG("abbreviations pdh and pth work too", pdh(y))
    print("apples")
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
    el(3)

def demo_output():
    dbgBackground("Output helpers")
    a = 2
    b = 14
    c = "apple"
    ps(a, b)
    dbg("handle 0-indexing vs 1-indexing")
    ps1(a, b)
    el()

    dat = [15, 83, 1]
    dbg("print a whole list at once")
    pv(dat)
    el()

    dbg("but what if the list is 0-indexed and output should be 1-indexed?")
    pv1(dat)
    el()

    dbg("sometimes you want to print the list with one item per line.")
    pvn(dat)
    dbgP("(pvn1 also works.)")
    el()

    dbg("you can also print a 2D array or some strings that way.")
    da = [[1, 5, 3], [2, 8, 1], [3, 6, 5, 4, 7, 5, 2]]
    pvn(da)
    el()
    db = ["apple", "banana", "cake"]
    pvn(db)
    el(3)


def demo_input():
    dbgBackground("Input helpers")
    dbg("I added lm1() and nn1() which convert from 1-indexed to 0-indexed.")
    dbgR("Example: you code `a, b = lm1()` and data file says `2 5`. Now a=1 and b=4.")
    dbg("I'm too lazy to set up an actual demo. I tested it when implementing but it might break one day...")
    el(3)

def demo_logic():
    dbgBackground("Helpers that would actually get used in main logic")

    ### bits_set counts the number of "1" bits in an integer.
    # Nicknames: pop_count, pct
    a = 14  # 1110
    pa = bits_set(a)
    dbgc("bits_set", a, bin(a), bits_set(a))
    dbg("Nicknames: pop_count, pct")
    assert pa == 3
    el()


    dbgc("fst_true, lst_true", "Binary search helpers, see template_demo.py for explanation")
    dbg("Nicknames: first_true, last_true")
    ### fst_true and lst_true run binary searches.
    # Nicknames: first_true, last_true.
    # Pass in first legal value and last legal value.
    # The functions will never evaluate at a point outside your given range.

    # If you call fstTrue(a, b, f) and f is false on the whole range [a,b]
    #     then output is b+1, since fstTrue assumes you already know f is true there.
    # Similar edge cases:
    # fstTrue(a,b,f), f is true on the whole range: return a
    # lstTrue(a,b,f), f is false on the whole range: return a-1
    # lstTrue(a,b,f), f is true on the whole range: return b

    dat = list(range(4, 60, 3))
    # Note usage: If you want a complicated predicate, just define it right in
    # the middle of your ongoing function. That way it can refer to all local variables.
    def check(k):
        return dat[k] > 20
    binsearch_result = fstTrue(0, len(dat)-1, check)
    binsearch_result_again = fstTrue(0, len(dat)-1, lambda k: dat[k] > 20)
    assert binsearch_result == binsearch_result_again
    assert binsearch_result == 6

    # assert some of the edge case results
    assert fstTrue(0, 10, lambda x: x > 20) == 11
    assert fstTrue(0, 10, lambda x: x > -20) == 0
    assert lstTrue(0, 10, lambda x: True) == 10
    assert lstTrue(0, 10, lambda x: False) == -1

    # Undefined behaviour, don't do this.
    # (It's bad because bad_helper_pred is not increasing.)
    bad_helper = [True, False, True, False, True]
    def bad_helper_pred(k):
        return bad_helper[k]
    bad_usage = fstTrue(0, len(bad_helper)-1, bad_helper_pred)
    el()


    YES()  # Just prints `YES`, I often use it like "return YES()" to quickly print an answer and quit.
    NO()
    No()  # prints `No`. Sometimes they want only first letter capitalized.
    el()

    # steps_orthogonal, steps_diagonal, steps_8dirs
    dbg("steps_orthogonal, steps_diagonal, steps_8dirs")
    dat = [
        'ADFSDEIFEW',
        'PAWOLFEEWO',
        'PQOPEREWOX',
        'PEPFWOZISD',
        'WAORIEODOW',
    ]
    R = len(dat)
    C = len(dat[0])
    for desired in {'APPLE', 'WOLF'}:
        found = False
        for r in range(R):
            for c in range(C):
                for dr, dc in steps_8dirs:  # ! This is the key line that's demoing the new thing.
                    found = True
                    for k in range(len(desired)):
                        rr, cc = r + k*dr, c + k*dc
                        if rr < 0 or rr >= R or cc < 0 or cc >= C or dat[rr][cc] != desired[k]:
                            found = False
                            break
                    if found:
                        print(f"Found {desired} at {(r,c)} in direction {(dr,dc)}.")
                        break
                if found: break
            if found: break
    el()


    dbgc("cdiv, fdiv")
    # I use cdiv very often and fdiv rarely, since usually integer division is good enough.
    # The difference between fdiv and // is that fdiv will still output the floor
    #     even with negative operands, while // will round toward 0.
    for a in range(-5, 5):
        for b in range(-5, 5):
            if b == 0: continue
            dbg(a, b)
            dbgcP("cdiv", cdiv(a,b))
            dbgcG("fdiv vs //", fdiv(a,b), a//b)
            el()

    dbgcR("runtime", TIME())




demo_debug_printouts()
demo_output()
demo_input()
demo_logic()
