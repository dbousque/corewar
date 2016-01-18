.comment "LOL ALIVE"
.name "zork"

live:
	ld %2, r1
	sti r1, %232, r4
	zjmp %:live
