g++ --std=c++2a D.cpp -o a.out || break
g++ --std=c++2a -DDCCLYDE_BRUTEFORCE D.cpp -o b.out || break

for((k = 1; ; ++k)); do
    echo $k
    python gen.py > gen.in || break
    a.out < gen.in > fast.out 2> /dev/null || break
    b.out < gen.in > brute.out 2> /dev/null || break
    diff -w fast.out brute.out || break
done
