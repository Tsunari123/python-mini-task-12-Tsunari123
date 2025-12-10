import matrix_ as mat

m = [[1.0, 2.0], [3.0, 4.0]]
result = mat.matrix_power(m, 3)
print("Test 1 - [[1,2],[3,4]]^3:")
print(result)

m2 = [[1.0, 2.0, 3.0], 
      [4.0, 5.0, 6.0], 
      [7.0, 8.0, 9.0]]
result2 = mat.matrix_power(m2, 2)
print("\nTest 2 - [[1,2,3],[4,5,6],[7,8,9]]^2:")
print(result2)

result3 = mat.matrix_power(m, 1)
print("\nTest 3 - [[1,2],[3,4]]^1:")
print(result3)

identity = [[1.0, 0.0], [0.0, 1.0]]
result4 = mat.matrix_power(identity, 10)
print("\nTest 4 - Identity matrix^10:")
print(result4)