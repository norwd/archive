
	PLEASE DO ,6 <- #127

	DO ,6SUB#1   <- #242	DO ,6SUB#9   <- #246
	DO ,6SUB#3   <- #243	DO ,6SUB#11  <- #247
	DO ,6SUB#5   <- #244	DO ,6SUB#13  <- #248
	DO ,6SUB#7   <- #245	DO ,6SUB#15  <- #249

	DO ,6SUB#17  <- #108	DO ,6SUB#25  <- #96
	DO ,6SUB#19  <- #80	DO ,6SUB#27  <- #76
	DO ,6SUB#21  <- #92	DO ,6SUB#29  <- #110
	DO ,6SUB#23  <- #78	DO ,6SUB#31  <- #111

	DO ,6SUB#33  <- #193	DO ,6SUB#57  <- #213
	DO ,6SUB#35  <- #194	DO ,6SUB#59  <- #215
	DO ,6SUB#37  <- #195	DO ,6SUB#61  <- #216
	DO ,6SUB#39  <- #196	DO ,6SUB#63  <- #217
	DO ,6SUB#41  <- #197	DO ,6SUB#65  <- #226
	DO ,6SUB#43  <- #198	DO ,6SUB#67  <- #227
	DO ,6SUB#45  <- #199	DO ,6SUB#69  <- #228
	DO ,6SUB#47  <- #200	DO ,6SUB#71  <- #229
	DO ,6SUB#49  <- #209	DO ,6SUB#73  <- #230
	DO ,6SUB#51  <- #210	DO ,6SUB#75  <- #231
	DO ,6SUB#53  <- #211	DO ,6SUB#77  <- #232
	DO ,6SUB#55  <- #212	DO ,6SUB#79  <- #233

	DO ,6SUB#81  <- #109	DO ,6SUB#105 <- #149
	DO ,6SUB#83  <- #129	DO ,6SUB#107 <- #151
	DO ,6SUB#85  <- #130	DO ,6SUB#109 <- #152
	DO ,6SUB#87  <- #131	DO ,6SUB#111 <- #153
	DO ,6SUB#89  <- #132	DO ,6SUB#113 <- #162
	DO ,6SUB#91  <- #133	DO ,6SUB#115 <- #163
	DO ,6SUB#93  <- #134	DO ,6SUB#117 <- #164
	DO ,6SUB#95  <- #135	DO ,6SUB#119 <- #165
	DO ,6SUB#97  <- #136	DO ,6SUB#121 <- #166
	DO ,6SUB#99  <- #145	DO ,6SUB#123 <- #167
	DO ,6SUB#101 <- #146	DO ,6SUB#125 <- #168
	DO ,6SUB#103 <- #148	DO ,6SUB#127 <- #169

	PLEASE DO .8 <- #0
	PLEASE DO %50 .8 <- #1
	PLEASE DO %50 .8 <- '#1$.8'~#3
	PLEASE DO %50 .8 <- '#2$.8'~#13
	PLEASE DO %50 .8 <- '#4$.8'~#53

	PLEASE DO .9 <- #0
	PLEASE DO %50 .9 <- #1
	PLEASE DO %50 .9 <- '#1$.9'~#3
	PLEASE DO %50 .9 <- '#2$.9'~#13
	PLEASE DO %50 .9 <- '#4$.9'~#53

	DO .5 <- '#1$"!8$.9'~#1"'~#3
	DO (4) NEXT

	DO ,1 <- #1
	PLEASE DO .1 <- #0
	DO (1) NEXT
	PLEASE GIVE UP

(4)	DO (5) NEXT
	DO .8 <- '?.8$#15'~#170
	PLEASE RESUME #1

(5)	DO (11) NEXT
(11)	PLEASE RESUME .5

(9)     PLEASE FORGET #1	

	PLEASE DO .6 <- #8
	PLEASE DO %50 .6 <- #9
	PLEASE DO %50 .6 <- '#1$.6'~#83
	PLEASE DO %50 .6 <- '#2$.6'~#77

	DO .5 <- '#1$"#15~'"?.1$.9"~#85'"'~#3
	DO (3) NEXT

	PLEASE DO .6 <- .6~#7
	DO .5 <- '#1$"#15~'"?.1$.8"~#85'"'~#3
	DO (3) NEXT

	PLEASE DO %50 .6 <- '#4$.6'~#53
	PLEASE DO %50 .6 <- '#8$.6'~#213
	PLEASE DO %50 .6 <- '#16$.6'~#853

	DO .5 <- "#1$!V6~#16'"~#3
	DO (6) NEXT
	DO (2) NEXT

(6)	DO (5) NEXT
	PLEASE FORGET #1
	DO .5 <- !6$#16'~#384
	DO (7) NEXT
	DO .9 <- #0
	DO (2) NEXT
(7)	DO (5) NEXT
	PLEASE FORGET #1
	DO .8 <- #0
	DO (2) NEXT

(3)	DO (5) NEXT

(2)	PLEASE FORGET #1
	PLEASE READ OUT ,6SUB"!6$#1'~#2731"

	DO .2 <- #1
	PLEASE DO (12) NEXT
(12)	DO FORGET #1
	DO .5 <- "?!1~.2'$#1"~#3
	PLEASE DO .1 <- '?.1$.2'~#21845
	DO (13) NEXT
	DO .2 <- !2$#0'~#43691
	DO (12) NEXT
(13)	DO (11) NEXT
	PLEASE FORGET #1

(1)	DO .5 <- !1$#32'~#1536
	DO (5) NEXT
	DO (9) NEXT
