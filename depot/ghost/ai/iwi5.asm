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
  JEQ 51,a,0
  JEQ 51,[3],0
  MOV [100],0
  JGT 45,f,h
  MOV [100],h
  SUB [100],f
  JGT 44,[6],10
  SUB d,20
  INT 3
  INT 6
  JEQ 45,a,1
; Label: up00
  ADD d,40
; Label: up0
; Label: up1
  JLT 51,d,[4]
  JGT 48,d,[4]
  JLT 51,[100],[5]
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
  JEQ 74,a,0
  JEQ 74,[3],1
  MOV [100],0
  JLT 68,e,g
  MOV [100],e
  SUB [100],g
  JGT 67,[6],10
  SUB d,20
  INT 3
  INT 6
  JEQ 68,a,1
; Label: right00
  ADD d,40
; Label: right0
; Label: right1
  JLT 74,d,[4]
  JGT 71,d,[4]
  JLT 74,[100],[5]
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
  JEQ 97,a,0
  JEQ 97,[3],2
  MOV [100],0
  JLT 91,f,h
  MOV [100],f
  SUB [100],h
  JGT 90,[6],10
  SUB d,20
  INT 3
  INT 6
  JEQ 91,a,1
; Label: down00
  ADD d,40
; Label: down0
; Label: down1
  JLT 97,d,[4]
  JGT 94,d,[4]
  JLT 97,[100],[5]
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
  JEQ 120,a,0
  JEQ 120,[3],3
  MOV [100],0
  JGT 114,e,g
  MOV [100],g
  SUB [100],e
  JGT 113,[6],10
  SUB d,20
  INT 3
  INT 6
  JEQ 114,a,1
; Label: left00
  ADD d,40
; Label: left0
; Label: left1
  JLT 120,d,[4]
  JGT 117,d,[4]
  JLT 120,[100],[5]
; Label: leftaccept
  MOV [1],3
  MOV [4],d
  MOV [5],[100]
; Label: leftlast
  MOV a,[1]
  INT 0
  MOV d,[1]
  HLT
