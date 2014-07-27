  MOV a,255
  MOV b,0
  MOV c,255
  INC c
  JGT 7,[c],a
  MOV a,[c]
  MOV b,c
  JLT 3,c,3
  MOV a,b
  INT 0
  INT 3
  INT 6
  INC [b]
  HLT
