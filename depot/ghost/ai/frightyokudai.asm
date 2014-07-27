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
  JLT 15,[3],4
  SUB [3],4
  MOV [4],a
; Label: init3
  MOV [1],[3]
  MOV c,0
  MOV d,10
  MOV a,g
  MOV b,h
  SUB b,1
  INT 7
  JEQ 38,a,0
  JEQ 38,[3],0
  JEQ 28,[4],1
  JGT 30,f,h
  ADD d,22
  JEQ 30,a,a
; Label: yabaiup
  JLT 30,f,h
  ADD d,22
; Label: up1
  MOV a,[3]
  ADD a,0
  AND a,1
  JEQ 35,a,0
  ADD d,1
; Label: up2
  JLT 38,d,c
  MOV [1],0
  MOV c,d
; Label: uplast
  MOV d,10
  MOV a,g
  MOV b,h
  ADD b,1
  INT 7
  JEQ 59,a,0
  JEQ 59,[3],2
  JEQ 49,[4],1
  JLT 51,f,h
  ADD d,22
  JEQ 51,a,a
; Label: yabaidown
  JGT 51,f,h
  ADD d,22
; Label: down1
  MOV a,[3]
  ADD a,2
  AND a,1
  JEQ 56,a,0
  ADD d,1
; Label: down2
  JLT 59,d,c
  MOV [1],2
  MOV c,d
; Label: downlast
  MOV d,10
  MOV a,g
  MOV b,h
  ADD a,1
  INT 7
  JEQ 80,a,0
  JEQ 80,[3],1
  JEQ 70,[4],1
  JLT 72,e,g
  ADD d,22
  JEQ 72,a,a
; Label: yabairight
  JGT 72,e,g
  ADD d,22
; Label: right1
  MOV a,[3]
  ADD a,1
  AND a,1
  JEQ 77,a,0
  ADD d,1
; Label: right2
  JLT 80,d,c
  MOV [1],1
  MOV c,d
; Label: rightlast
  MOV d,10
  MOV a,g
  MOV b,h
  SUB a,1
  INT 7
  JEQ 100,a,0
  JEQ 100,[3],3
  JEQ 90,[4],1
  JGT 92,e,g
  ADD d,22
; Label: yabaileft
  JLT 92,e,g
  ADD d,22
; Label: left1
  MOV a,[3]
  ADD a,3
  AND a,1
  JEQ 97,a,0
  ADD d,1
; Label: left2
  JLT 100,d,c
  MOV [1],3
  MOV c,d
; Label: leftlast
  MOV a,[1]
  INT 0
  MOV d,[1]
  HLT
