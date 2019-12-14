sub r1, r1, r1
sub r2, r2, r2
sub r3, r3, r3
addi r3, r3, 5
addi r2, r2, 10
sd r1, r1
addi r1, r1, 1
jlt r3, r1, r2
hlt
