import os

cpp_file = 'E.cpp'
flags_both = ["-DDCCLYDE_LOCAL"]
setup_commands = [
    # compile fast
    f"g++ --std=c++2a {cpp_file} -o a.out {' '.join(flags_both)}",
    # compile bruteforce
    f"g++ --std=c++2a -DDCCLYDE_BRUTEFORCE {cpp_file} -o b.out {' '.join(flags_both)}",
]
for q in setup_commands:
    os.system(q)

test_count = 0
while True:
    test_count += 1
    print(f"TEST {test_count}")
    # os.system('./generator ' + str(seed) + ' > input.txt')
    os.system('./generator > gen.in')
    os.system('./a.out < gen.in > fast.out')
    os.system('./b.out < gen.in > brute.out')
    gin = open('gen.in').read()
    fout = open('fast.out').read()
    bout = open('brute.out').read()
    if fout != bout:
        print(gin)
        print('\n' + '='*30 + '\n')
        print(fout)
        print('\n' + '-'*30 + '\n')
        print(bout)
        exit(1)
