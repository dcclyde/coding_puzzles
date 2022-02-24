dat = '''$

out = ''
replacement_done = False
for c in dat[:-1]:
    if c == '$' and not replacement_done:
        # here we need to reproduce the line at the top.
        # We do still have access to `dat`.
        # Need to escape some stuff though I guess.
        out += "dat = " + ("'" + "'" + "'")
        out += dat
        out += ("'" + "'" + "'")
        replacement_done = True
    else:
        out += c

print(out)
'''

out = ''
replacement_done = False
for c in dat[:-1]:
    if c == '$' and not replacement_done:
        # here we need to reproduce the line at the top.
        # We do still have access to `dat`.
        # Need to escape some stuff though I guess.
        out += "dat = " + ("'" + "'" + "'")
        out += dat
        out += ("'" + "'" + "'")
        replacement_done = True
    else:
        out += c

print(out)
