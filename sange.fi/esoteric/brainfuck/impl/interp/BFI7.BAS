'BF program emulator, for Casio CFX-9800G

'é=length (including the 8 at the end)
'Casio  BF   
'0      >
'1      <
'2      +
'3      -
'4      .
'5      ,
'6      [
'7      ]
'8      255 (end)

'Echo: ,+[-.,+]
'      526345278,é=9

'Casio  Basic           Casio           Basic
'->     =               8->H            H=8
'=>     if then         X>1=>0->Y       if X>1 then Y=0
'Gto    goto            Goto 2          goto 2
'Lbl    line label      Lbl 1           1
'Dsz                    Dsz T:1->B      T=T-1:if T<>0 then 1->B
'Isz                    Isz S:Goto 2    S=S+1:if S<>0 then Goto 2
''      rem             'blah           'blah
'""     text            "abc"           print "abc"
'~      range           0->A[0]~A[100]  for R=0 to 100:A[R]=0:next R
'?      input           ?->W            input W
'/|     print           A/|             print A
': <-'  :             
'Mat                    8->Mat A[R,C]
'=,<>,<,>,>=,<=


'0->G[0]~G[2000]
1
  'E->Mat B[1,C]
2
  'Mat A[1,E]->F
  'F=0=>Goto 7
  'E+1->E
  'F=0=>D+1->D
  'F=1=>D-1->D
  'F=2=>(G[D]+1) MOD 256->G[D]
  'F=3=>(G[D]+255) MOD 256->G[D]
  'F=4=>G[D]/|
  'F=5=>?->G[D]
  'F<>6=>Goto 6
    '1->B:E->A
3
    'A=é=>Goto 4
    'Mat A[1,A]=6=>B+1->B
    'Mat A[1,A]=7=>B-1->B
    'B<=0=>Goto 4
    'A+1->A:Goto 3
4 
    'G[D]<>0=>Goto 5
    'A+1->E:Goto 2
5
    'C+1->C:Goto 1
6
    'F<>7=>Goto 2
    'Mat B[1,C]-1->E:C+1->C
'Goto 2
7

