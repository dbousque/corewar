.name "test2"
.comment "yolo test2"

live %1
lldi 1, %2, r2
lldi 1, %2, r2
live %1
zjmp %-12
fork %-18
