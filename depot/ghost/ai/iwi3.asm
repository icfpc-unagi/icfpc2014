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
  MOV d,100
  MOV a,g
  MOV b,h
  SUB b,1
  INT 7
  JEQ 39,a,0
  JEQ 39,[3],0
  MOV [100],0
  JGT 33,f,h
  SUB d,20
  INT 3
  INT 6
  JEQ 31,a,1
  ADD d,40
; Label: up0
  MOV [100],h
  SUB [100],f
; Label: up1
  JLT 39,d,[4]
  JGT 36,d,[4]
  JLT 39,[100],[5]
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
  JEQ 61,a,0
  JEQ 61,[3],1
  MOV [100],0
  JLT 55,e,g
  SUB d,20
  INT 3
  INT 6
  JEQ 53,a,1
  ADD d,40
; Label: right0
  MOV [100],e
  SUB [100],g
; Label: right1
  JLT 61,d,[4]
  JGT 58,d,[4]
  JLT 61,[100],[5]
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
  JEQ 83,a,0
  JEQ 83,[3],2
  MOV [100],0
  JLT 77,f,h
  SUB d,20
  INT 3
  INT 6
  JEQ 75,a,1
  ADD d,40
; Label: down0
  MOV [100],f
  SUB [100],h
; Label: down1
  JLT 83,d,[4]
  JGT 80,d,[4]
  JLT 83,[100],[5]
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
  JEQ 105,a,0
  JEQ 105,[3],3
  MOV [100],0
  JGT 99,e,g
  SUB d,20
  INT 3
  INT 6
  JEQ 97,a,1
  ADD d,40
; Label: left0
  MOV [100],g
  SUB [100],e
; Label: left1
  JLT 105,d,[4]
  JGT 102,d,[4]
  JLT 105,[100],[5]
; Label: leftaccept
  MOV [1],3
  MOV [4],d
  MOV [5],[100]
; Label: leftlast
  MOV a,[1]
  INT 0
  MOV d,[1]
  HLT
