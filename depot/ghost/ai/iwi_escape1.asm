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
  JEQ 49,a,0
  JEQ 49,[3],0
  INT 3
  MOV [100],a
  ADD [100],g
  ADD [100],h
  XOR [100],0
  AND [100],3
  JGT 43,f,h
  SUB d,20
; Label: up1
  JLT 49,d,[4]
  JGT 46,d,[4]
  JLT 49,[100],[5]
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
  JEQ 70,a,0
  JEQ 70,[3],1
  INT 3
  MOV [100],a
  ADD [100],g
  ADD [100],h
  XOR [100],1
  AND [100],3
  JLT 64,e,g
  SUB d,20
; Label: right1
  JLT 70,d,[4]
  JGT 67,d,[4]
  JLT 70,[100],[5]
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
  JEQ 91,a,0
  JEQ 91,[3],2
  INT 3
  MOV [100],a
  ADD [100],g
  ADD [100],h
  XOR [100],2
  AND [100],3
  JLT 85,f,h
  SUB d,20
; Label: down1
  JLT 91,d,[4]
  JGT 88,d,[4]
  JLT 91,[100],[5]
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
  JEQ 112,a,0
  JEQ 112,[3],3
  INT 3
  MOV [100],a
  ADD [100],g
  ADD [100],h
  XOR [100],3
  AND [100],3
  JGT 106,e,g
  SUB d,20
; Label: left1
  JLT 112,d,[4]
  JGT 109,d,[4]
  JLT 112,[100],[5]
; Label: leftaccept
  MOV [1],3
  MOV [4],d
  MOV [5],[100]
; Label: leftlast
  MOV a,[1]
  INT 0
  MOV d,[1]
  HLT
