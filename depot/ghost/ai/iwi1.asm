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
  MOV d,10
  MOV a,g
  MOV b,h
  SUB b,1
  INT 7
  JEQ 35,a,0
  JEQ 35,[3],0
  MOV [100],0
  JGT 29,f,h
  ADD d,22
  MOV [100],h
  SUB [100],f
; Label: up1
  JLT 35,d,[4]
  JGT 32,d,[4]
  JLT 35,[100],[5]
; Label: upaccept
  MOV [1],0
  MOV [4],d
  MOV [5],[100]
; Label: uplast
  MOV d,10
  MOV a,g
  MOV b,h
  ADD b,1
  INT 7
  JEQ 53,a,0
  JEQ 53,[3],2
  MOV [100],0
  JLT 47,f,h
  ADD d,22
  MOV [100],f
  SUB [100],h
; Label: down1
  JLT 53,d,[4]
  JGT 50,d,[4]
  JLT 53,[100],[5]
; Label: downaccept
  MOV [1],2
  MOV [4],d
  MOV [5],[100]
; Label: downlast
  MOV d,10
  MOV a,g
  MOV b,h
  ADD a,1
  INT 7
  JEQ 71,a,0
  JEQ 71,[3],1
  MOV [100],0
  JLT 65,e,g
  ADD d,22
  MOV [100],e
  SUB [100],g
; Label: right1
  JLT 71,d,[4]
  JGT 68,d,[4]
  JLT 71,[100],[5]
; Label: rightaccept
  MOV [1],1
  MOV [4],d
  MOV [5],[100]
; Label: rightlast
  MOV d,10
  MOV a,g
  MOV b,h
  SUB a,1
  INT 7
  JEQ 89,a,0
  JEQ 89,[3],3
  MOV [100],0
  JGT 83,e,g
  ADD d,22
  MOV [100],g
  SUB [100],e
; Label: left1
  JLT 89,d,[4]
  JGT 86,d,[4]
  JLT 89,[100],[5]
; Label: leftaccept
  MOV [1],3
  MOV [4],d
  MOV [5],[100]
; Label: leftlast
  MOV a,[1]
  INT 0
  MOV d,[1]
  HLT
