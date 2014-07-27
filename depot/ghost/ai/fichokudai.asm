  MOV a,[5]
  SUB a,31
  MOV [5],a
  JGT 18,a,100
; Label: fickle
  MOV a,255
  MOV b,0
  MOV c,255
; Label: fickle_three
  INC c
  JGT 12,[c],a
  MOV a,[c]
  MOV b,c
  JLT 7,c,3
; Label: fickle_seven
  MOV a,b
  INT 0
  INT 3
  INT 6
  INC [b]
  HLT
; Label: chokudai
  INT 1
  MOV e,a
  MOV f,b
  INT 3
  MOV [10],a
  INT 5
  MOV g,a
  MOV h,b
  INT 3
  INT 6
  MOV [13],b
  ADD [13],2
  JLT 32,[13],4
  SUB [13],4
; Label: init3
  MOV [11],[13]
  MOV c,0
  MOV d,10
  MOV a,g
  MOV b,h
  SUB b,1
  INT 7
  JEQ 51,a,0
  JEQ 51,[13],0
  JGT 43,f,h
  ADD d,22
; Label: up1
  MOV a,[13]
  ADD a,0
  AND a,1
  JEQ 48,a,0
  ADD d,1
; Label: up2
  JLT 51,d,c
  MOV [11],0
  MOV c,d
; Label: uplast
  MOV d,10
  MOV a,g
  MOV b,h
  ADD b,1
  INT 7
  JEQ 68,a,0
  JEQ 68,[13],2
  JLT 60,f,h
  ADD d,22
; Label: down1
  MOV a,[13]
  ADD a,2
  AND a,1
  JEQ 65,a,0
  ADD d,1
; Label: down2
  JLT 68,d,c
  MOV [11],2
  MOV c,d
; Label: downlast
  MOV d,10
  MOV a,g
  MOV b,h
  ADD a,1
  INT 7
  JEQ 85,a,0
  JEQ 85,[13],1
  JLT 77,e,g
  ADD d,22
; Label: right1
  MOV a,[13]
  ADD a,1
  AND a,1
  JEQ 82,a,0
  ADD d,1
; Label: right2
  JLT 85,d,c
  MOV [11],1
  MOV c,d
; Label: rightlast
  MOV d,10
  MOV a,g
  MOV b,h
  SUB a,1
  INT 7
  JEQ 102,a,0
  JEQ 102,[13],3
  JGT 94,e,g
  ADD d,22
; Label: left1
  MOV a,[13]
  ADD a,3
  AND a,1
  JEQ 99,a,0
  ADD d,1
; Label: left2
  JLT 102,d,c
  MOV [11],3
  MOV c,d
; Label: leftlast
  MOV a,[11]
  INT 0
  MOV d,[11]
  HLT
