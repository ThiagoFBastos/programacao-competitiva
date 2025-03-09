def matrix_mul(a, b):
    c = [[0, 0], [0, 0]]    
    for k in range(2):
        for j in range(2):
            for i in range(2):
                c[k][j] += a[k][i] * b[i][j]
    return c

def matrix_pow(A, p):
    B = [[1, 0], [0, 1]]
    while p > 0:
        if p % 2 == 1:
            B = matrix_mul(A, B)
        A = matrix_mul(A, A)
        p >>= 1
    return B

def fib(n):
    if n < 0:
        A = matrix_pow([[-1, 1], [1, 0]], abs(n))
        return A[0][1]
    elif n < 2:
        return n
  
    A = matrix_pow([[1, 1], [1, 0]], n - 1)
   
    return A[0][0]