t = int(input())

for _ in range(t):
     is_left = []
     pos = 0

     n = int(input())

     for i in range(n):
          ins = input().strip()

          if ins == 'LEFT':
               is_left.append(True)
               pos -= 1
          elif ins == 'RIGHT':
               is_left.append(False)
               pos += 1
          else:
               index = int(ins.split()[-1]) - 1

               is_left.append(is_left[index])

               if is_left[index]:
                    pos -= 1
               else:
                    pos += 1
     
     print(pos)
