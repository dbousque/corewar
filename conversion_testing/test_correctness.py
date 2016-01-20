

import os, sys

path = sys.argv[1]
dirs = os.listdir(path)

for file in dirs:
	if ".s"in file:
		os.system("./a.out " + path + str(file) + " > /dev/null")
		os.system("cp " + path + str(file.replace(".s", ".cor")) + " res_aout")
		os.system("./asm " + path + str(file) + " > /dev/null")
		os.system("cp " + path + str(file.replace(".s", ".cor")) + " res_asm")
		os.system("diff res_aout res_asm > res_diff")
		if len(open("res_diff").read()) > 1:
			print "ERROR FOR : " + str(file)
		else:
			print "no diff for " + str(file)
