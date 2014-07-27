  INT 1
  MOV e,a
  MOV f,b
  INT 3
  MOV [0],a
  INT 5
  MOV g,a
  MOV h,b
  INT 3
  INT 6
  MOV [3],b
  ADD [3],2
  JLT 14,[3],4
  SUB [3],4
; Label: init3
  MOV [1],[3]
  MOV c,0
  MOV d,10
  MOV a,g
  MOV b,h
  SUB b,1
  INT 7
  JEQ 33,a,0
  JEQ 33,[3],0
  JGT 25,f,h
  ADD d,22
; Label: up1
  MOV a,[3]
  ADD a,0
  AND a,1
  JEQ 30,a,0
  ADD d,1
; Label: up2
  JLT 33,d,c
  MOV [1],0
  MOV c,d
; Label: uplast
  MOV d,10
  MOV a,g
  MOV b,h
  ADD b,1
  INT 7
  JEQ 50,a,0
  JEQ 50,[3],2
  JLT 42,f,h
  ADD d,22
; Label: down1
  MOV a,[3]
  ADD a,2
  AND a,1
  JEQ 47,a,0
  ADD d,1
; Label: down2
  JLT 50,d,c
  MOV [1],2
  MOV c,d
; Label: downlast
  MOV d,10
  MOV a,g
  MOV b,h
  ADD a,1
  INT 7
  JEQ 67,a,0
  JEQ 67,[3],1
  JLT 59,e,g
  ADD d,22
; Label: right1
  MOV a,[3]
  ADD a,1
  AND a,1
  JEQ 64,a,0
  ADD d,1
; Label: right2
  JLT 67,d,c
  MOV [1],1
  MOV c,d
; Label: rightlast
  MOV d,10
  MOV a,g
  MOV b,h
  SUB a,1
  INT 7
  JEQ 84,a,0
  JEQ 84,[3],3
  JGT 76,e,g
  ADD d,22
; Label: left1
  MOV a,[3]
  ADD a,3
  AND a,1
  JEQ 81,a,0
  ADD d,1
; Label: left2
  JLT 84,d,c
  MOV [1],3
  MOV c,d
; Label: leftlast
  MOV a,[1]
  INT 0
  MOV d,[1]
  HLT
