lex part1.l
yacc -d part1.y
cc -o part1 y.tab.c -ll -Ly
./part1<t.txt 
