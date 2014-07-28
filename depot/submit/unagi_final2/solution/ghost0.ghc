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
  MOV [4],0
  MOV [5],0
  MOV [6],e
  SUB [6],g
  JGT 22,e,g
  MOV [6],g
  SUB [6],e
; Label: init5
  MOV [100],f
  SUB [100],h
  JGT 27,f,h
  MOV [100],h
  SUB [100],f
; Label: init6
  ADD [6],[100]
  MOV d,100
  MOV a,g
  MOV b,h
  SUB b,1
  INT 7
  JEQ 54,a,0
  JEQ 54,[3],0
  INT 3
  MOV [100],a
  XOR [100],0
  AND [100],3
  JGT 48,f,h
  JGT 45,[6],10
  SUB d,20
  INT 3
  INT 6
  JEQ 48,a,1
; Label: up00
  ADD d,40
  ADD [100],h
  SUB [100],f
; Label: up0
; Label: up1
  JLT 54,d,[4]
  JGT 51,d,[4]
  JLT 54,[100],[5]
; Label: upaccept
  MOV [1],0
  MOV [4],d
  MOV [5],[100]
; Label: uplast
  MOV d,100
  MOV a,g
  MOV b,h
  ADD a,1
  INT 7
  JEQ 80,a,0
  JEQ 80,[3],1
  INT 3
  MOV [100],a
  XOR [100],1
  AND [100],3
  JLT 74,e,g
  JGT 71,[6],10
  SUB d,20
  INT 3
  INT 6
  JEQ 74,a,1
; Label: right00
  ADD d,40
  ADD [100],e
  SUB [100],g
; Label: right0
; Label: right1
  JLT 80,d,[4]
  JGT 77,d,[4]
  JLT 80,[100],[5]
; Label: rightaccept
  MOV [1],1
  MOV [4],d
  MOV [5],[100]
; Label: rightlast
  MOV d,100
  MOV a,g
  MOV b,h
  ADD b,1
  INT 7
  JEQ 106,a,0
  JEQ 106,[3],2
  INT 3
  MOV [100],a
  XOR [100],2
  AND [100],3
  JLT 100,f,h
  JGT 97,[6],10
  SUB d,20
  INT 3
  INT 6
  JEQ 100,a,1
; Label: down00
  ADD d,40
  ADD [100],f
  SUB [100],h
; Label: down0
; Label: down1
  JLT 106,d,[4]
  JGT 103,d,[4]
  JLT 106,[100],[5]
; Label: downaccept
  MOV [1],2
  MOV [4],d
  MOV [5],[100]
; Label: downlast
  MOV d,100
  MOV a,g
  MOV b,h
  SUB a,1
  INT 7
  JEQ 132,a,0
  JEQ 132,[3],3
  INT 3
  MOV [100],a
  XOR [100],3
  AND [100],3
  JGT 126,e,g
  JGT 123,[6],10
  SUB d,20
  INT 3
  INT 6
  JEQ 126,a,1
; Label: left00
  ADD d,40
  ADD [100],g
  SUB [100],e
; Label: left0
; Label: left1
  JLT 132,d,[4]
  JGT 129,d,[4]
  JLT 132,[100],[5]
; Label: leftaccept
  MOV [1],3
  MOV [4],d
  MOV [5],[100]
; Label: leftlast
  MOV a,[1]
  INT 0
  MOV d,[1]
  HLT
