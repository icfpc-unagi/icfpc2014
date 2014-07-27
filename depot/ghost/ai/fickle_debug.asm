  MOV a,255
  INT 8
  MOV b,0
  INT 8
  MOV c,255
  INT 8
; Label: loop
  INC c
  INT 8
  JGT 16,[c],a
  INT 8
  MOV a,[c]
  INT 8
  MOV b,c
  INT 8
  JLT 6,c,3
  INT 8
; Label: set_direction
  MOV a,b
  INT 8
  INT 0
  INT 8
  INT 3
  INT 8
  INT 6
  INT 8
  INC [b]
  INT 8
  HLT
