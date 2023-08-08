input: 
[q] [w] [e] [r] [t] [y] [u] [i] [o] [p]
   [a] [s] [d] [*] [g] [h] [j] [k] [l]
      [z] [x] [c] [v] [b] [n] [m]
output:
[f]

first_line=input()
second_line=input()
third_line=input()
s=''
for i in range(ord('a'),ord('z')+1):
 c=chr(i)
 if c not in first_line and c not in second_line and c not in third_line:
     s+='['+c+'] '
print(s.strip())