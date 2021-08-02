
from timer import timer
import random
import logging
# from ExpectError import ExpectError
# from ExpectError ipmort ExpectError

def my_sqrt(x):
    """Computes the square root of x, using the Newton-Raphson method"""
    approx = None
    guess = x / 2
    while approx != guess:
        approx = guess
        guess = (approx + x / approx) / 2
    return approx

def my_sqrt_with_log(x):
    """Computes the square root of x, using the Newton-Raphson method"""
    approx = 0
    guess = x / 2
    while approx != guess:
        print("approx ="+str(approx))
        approx = guess
        guess = (approx + x / approx) / 2
    return approx  

def assertEquals(x, y, epsilon=1e-8):
    assert abs(x - y) < epsilon


def my_sqrt_checked(x): 
    root = my_sqrt(x) 
    assertEquals(root * root, x) 
    return root 

def sqrt_program(arg):
    try:
        x = int(arg) 
    except ValueError:
        print("Illegal Input")
    else:
        if x < 0:
            print("Illegal Number") 
        else:
            print('The root of', x, 'is', my_sqrt(x))

def my_sqrt_fixed(x):
    assert 0 <= x
    if x == 0:
        return 0
    return my_sqrt(x)

x = int(input())

##
# print(my_sqrt_with_log(x))
##

## Automating Test Execution
# issue:
# 1. we need five lines of code for a single test
# 2. we do not care for rounding errors 
# 3. we only check a single input (and a signle result)
##
result = my_sqrt(x) 
expected_result = 2.0
if result == expected_result: 
    print("Test passed") 
else:
    print("Test failed")

##
print("ASSERT TEST")
assert my_sqrt(4) == 2

EPSILON = 1e-8
assert abs(my_sqrt(4) - 2) < EPSILON
##

## Test pass 
assertEquals(my_sqrt(4), 2)
assertEquals(my_sqrt(9), 3)
assertEquals(my_sqrt(100), 10)

## Generating Test 
assertEquals(my_sqrt(2) * my_sqrt(2), 2)
assertEquals(my_sqrt(3) * my_sqrt(3), 3)
assertEquals(my_sqrt(42.11) * my_sqrt(42.11), 42.11)

for n in range(1, 1000):
    assertEquals(my_sqrt(n) * my_sqrt(n), n) 


## Timer 
logging.basicConfig(level=logging.DEBUG)
with timer() as t:
    for n in range(1, 10000):
        assertEquals(my_sqrt(n) * my_sqrt(n), n)
# print(t.elapsed_time())

## Random 
logging.basicConfig(level=logging.DEBUG)
with timer() as t:
    for i in range(10000):
        x = 1 + random.random() * 1000000
        assertEquals(my_sqrt(x) * my_sqrt(x), x) 
# print(t.elapsed_time())

print(my_sqrt_checked(2.0))

sqrt_program("4")

# 모듈 없음 
# with ExpectTimeout(1):
sqrt_program("-1")

sqrt_program("xyzzy")

assert my_sqrt_fixed(0) == 0
assert my_sqrt_fixed(-1) == 0

# our best chance with testing is to 
# 1. Test the program on several, well-chosen inputs; and 
# 2. Check results extensively and automatically 
# This is what we do in the remainder of this course: 
# Devise techniques that help us to thoroughly test a program, as well as techniques that help us checking its state for correctness.

