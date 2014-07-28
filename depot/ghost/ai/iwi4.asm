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
  JEQ 40,a,0
  JEQ 40,[3],0
  MOV [100],0
  JGT 34,f,h
  MOV [100],h
  SUB [100],f
  JGT 33,[100],10
  SUB d,20
  INT 3
  INT 6
  JEQ 34,a,1
; Label: up00
  ADD d,40
; Label: up0
; Label: up1
  JLT 40,d,[4]
  JGT 37,d,[4]
  JLT 40,[100],[5]
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
  JEQ 63,a,0
  JEQ 63,[3],1
  MOV [100],0
  JLT 57,e,g
  MOV [100],e
  SUB [100],g
  JGT 56,[100],10
  SUB d,20
  INT 3
  INT 6
  JEQ 57,a,1
; Label: right00
  ADD d,40
; Label: right0
; Label: right1
  JLT 63,d,[4]
  JGT 60,d,[4]
  JLT 63,[100],[5]
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
  JEQ 86,a,0
  JEQ 86,[3],2
  MOV [100],0
  JLT 80,f,h
  MOV [100],f
  SUB [100],h
  JGT 79,[100],10
  SUB d,20
  INT 3
  INT 6
  JEQ 80,a,1
; Label: down00
  ADD d,40
; Label: down0
; Label: down1
  JLT 86,d,[4]
  JGT 83,d,[4]
  JLT 86,[100],[5]
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
  JEQ 109,a,0
  JEQ 109,[3],3
  MOV [100],0
  JGT 103,e,g
  MOV [100],g
  SUB [100],e
  JGT 102,[100],10
  SUB d,20
  INT 3
  INT 6
  JEQ 103,a,1
; Label: left00
  ADD d,40
; Label: left0
; Label: left1
  JLT 109,d,[4]
  JGT 106,d,[4]
  JLT 109,[100],[5]
; Label: leftaccept
  MOV [1],3
  MOV [4],d
  MOV [5],[100]
; Label: leftlast
  MOV a,[1]
  INT 0
  MOV d,[1]
  HLT
