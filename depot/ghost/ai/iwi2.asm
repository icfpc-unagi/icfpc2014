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
  JLT 16,[3],4
  SUB [3],4
  INT 3
  MOV [6],a
; Label: init3
  MOV [1],[3]
  MOV [4],0
  MOV [5],0
  MOV [99],100
  MOV a,g
  MOV b,h
  SUB b,1
  MOV [101],a
  MOV [102],b
  INT 7
  JEQ 63,a,0
  JEQ 63,[3],0
  MOV [100],0
  JGT 33,f,h
  ADD [99],100
  MOV [100],h
  SUB [100],f
; Label: up1
  MOV c,[6]
  JLT 57,c,1
; Label: uploop
  DEC c
  MOV a,c
  INT 4
  MOV [104],[101]
  SUB [104],a
  JGT 43,[101],a
  MOV [104],a
  SUB [104],[101]
; Label: uploop1
  JGT 56,[104],100
  MOV [103],[104]
  MOV [104],[102]
  SUB [104],b
  JGT 50,[102],b
  MOV [104],b
  SUB [104],[102]
; Label: uploop2
  JGT 56,[104],100
  ADD [103],[104]
  INC [103]
  MOV [105],20
  DIV [105],[103]
  SUB [99],[105]
; Label: upcontinue
  JGT 35,c,0
; Label: upbreak
  JLT 63,[99],[4]
  JGT 60,[99],[4]
  JLT 63,[100],[5]
; Label: upaccept
  MOV [1],0
  MOV [4],[99]
  MOV [5],[100]
; Label: uplast
  MOV [99],100
  MOV a,g
  MOV b,h
  ADD a,1
  MOV [101],a
  MOV [102],b
  INT 7
  JEQ 107,a,0
  JEQ 107,[3],1
  MOV [100],0
  JLT 77,e,g
  ADD [99],100
  MOV [100],e
  SUB [100],g
; Label: right1
  MOV c,[6]
  JLT 101,c,1
; Label: rightloop
  DEC c
  MOV a,c
  INT 4
  MOV [104],[101]
  SUB [104],a
  JGT 87,[101],a
  MOV [104],a
  SUB [104],[101]
; Label: rightloop1
  JGT 100,[104],100
  MOV [103],[104]
  MOV [104],[102]
  SUB [104],b
  JGT 94,[102],b
  MOV [104],b
  SUB [104],[102]
; Label: rightloop2
  JGT 100,[104],100
  ADD [103],[104]
  INC [103]
  MOV [105],20
  DIV [105],[103]
  SUB [99],[105]
; Label: rightcontinue
  JGT 79,c,0
; Label: rightbreak
  JLT 107,[99],[4]
  JGT 104,[99],[4]
  JLT 107,[100],[5]
; Label: rightaccept
  MOV [1],1
  MOV [4],[99]
  MOV [5],[100]
; Label: rightlast
  MOV [99],100
  MOV a,g
  MOV b,h
  ADD b,1
  MOV [101],a
  MOV [102],b
  INT 7
  JEQ 151,a,0
  JEQ 151,[3],2
  MOV [100],0
  JLT 121,f,h
  ADD [99],100
  MOV [100],f
  SUB [100],h
; Label: down1
  MOV c,[6]
  JLT 145,c,1
; Label: downloop
  DEC c
  MOV a,c
  INT 4
  MOV [104],[101]
  SUB [104],a
  JGT 131,[101],a
  MOV [104],a
  SUB [104],[101]
; Label: downloop1
  JGT 144,[104],100
  MOV [103],[104]
  MOV [104],[102]
  SUB [104],b
  JGT 138,[102],b
  MOV [104],b
  SUB [104],[102]
; Label: downloop2
  JGT 144,[104],100
  ADD [103],[104]
  INC [103]
  MOV [105],20
  DIV [105],[103]
  SUB [99],[105]
; Label: downcontinue
  JGT 123,c,0
; Label: downbreak
  JLT 151,[99],[4]
  JGT 148,[99],[4]
  JLT 151,[100],[5]
; Label: downaccept
  MOV [1],2
  MOV [4],[99]
  MOV [5],[100]
; Label: downlast
  MOV [99],100
  MOV a,g
  MOV b,h
  SUB a,1
  MOV [101],a
  MOV [102],b
  INT 7
  JEQ 195,a,0
  JEQ 195,[3],3
  MOV [100],0
  JGT 165,e,g
  ADD [99],100
  MOV [100],g
  SUB [100],e
; Label: left1
  MOV c,[6]
  JLT 189,c,1
; Label: leftloop
  DEC c
  MOV a,c
  INT 4
  MOV [104],[101]
  SUB [104],a
  JGT 175,[101],a
  MOV [104],a
  SUB [104],[101]
; Label: leftloop1
  JGT 188,[104],100
  MOV [103],[104]
  MOV [104],[102]
  SUB [104],b
  JGT 182,[102],b
  MOV [104],b
  SUB [104],[102]
; Label: leftloop2
  JGT 188,[104],100
  ADD [103],[104]
  INC [103]
  MOV [105],20
  DIV [105],[103]
  SUB [99],[105]
; Label: leftcontinue
  JGT 167,c,0
; Label: leftbreak
  JLT 195,[99],[4]
  JGT 192,[99],[4]
  JLT 195,[100],[5]
; Label: leftaccept
  MOV [1],3
  MOV [4],[99]
  MOV [5],[100]
; Label: leftlast
  MOV a,[1]
  INT 0
  MOV d,[1]
  HLT
