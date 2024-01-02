
	PLEASE DO ,6 <- #127

	DO ,6SUB#1   <- #50	DO ,6SUB#9   <- #54
	DO ,6SUB#3   <- #51	DO ,6SUB#11  <- #55
	DO ,6SUB#5   <- #52	DO ,6SUB#13  <- #56
	DO ,6SUB#7   <- #53	DO ,6SUB#15  <- #57

	DO ,6SUB#17  <- #37	DO ,6SUB#25  <- #45
	DO ,6SUB#19  <- #38	DO ,6SUB#27  <- #60
	DO ,6SUB#21  <- #42	DO ,6SUB#29  <- #62
	DO ,6SUB#23  <- #43	DO ,6SUB#31  <- #63

	DO ,6SUB#33  <- #65	DO ,6SUB#57  <- #78
	DO ,6SUB#35  <- #66	DO ,6SUB#59  <- #80
	DO ,6SUB#37  <- #67	DO ,6SUB#61  <- #81
	DO ,6SUB#39  <- #68	DO ,6SUB#63  <- #82
	DO ,6SUB#41  <- #69	DO ,6SUB#65  <- #83
	DO ,6SUB#43  <- #70	DO ,6SUB#67  <- #84
	DO ,6SUB#45  <- #71	DO ,6SUB#69  <- #85
	DO ,6SUB#47  <- #72	DO ,6SUB#71  <- #86
	DO ,6SUB#49  <- #74	DO ,6SUB#73  <- #87
	DO ,6SUB#51  <- #75	DO ,6SUB#75  <- #88
	DO ,6SUB#53  <- #76	DO ,6SUB#77  <- #89
	DO ,6SUB#55  <- #77	DO ,6SUB#79  <- #90

	DO ,6SUB#81  <- #95	DO ,6SUB#105 <- #110
	DO ,6SUB#83  <- #97	DO ,6SUB#107 <- #112
	DO ,6SUB#85  <- #98	DO ,6SUB#109 <- #113
	DO ,6SUB#87  <- #99	DO ,6SUB#111 <- #114
	DO ,6SUB#89  <- #100	DO ,6SUB#113 <- #115
	DO ,6SUB#91  <- #101	DO ,6SUB#115 <- #116
	DO ,6SUB#93  <- #102	DO ,6SUB#117 <- #117
	DO ,6SUB#95  <- #103	DO ,6SUB#119 <- #118
	DO ,6SUB#97  <- #104	DO ,6SUB#121 <- #119
	DO ,6SUB#99  <- #106	DO ,6SUB#123 <- #120
	DO ,6SUB#101 <- #107	DO ,6SUB#125 <- #121
	DO ,6SUB#103 <- #109	DO ,6SUB#127 <- #122

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
