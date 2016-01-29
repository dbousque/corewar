import os, sys, time

champion = sys.argv[1]

os.system("../asm " + champion + " > /dev/null")
os.system("./corewar " + champion.replace(".s", ".cor") + " " + champion.replace(".s", ".cor") + " -a -v 21 > res_corewar")
os.system("./a.out " + champion.replace(".s", ".cor") + " " + champion.replace(".s", ".cor") + " > res_aout")
fich = open("result_corewar", "w")
fich.write('\n'.join(open("res_corewar").read().split('\n')[3:-2]) + "\n")
fich2 = open("result_aout", "w")
fich2.write('\n'.join(open("res_aout").read().split('\n')[:-1]) + "\n")
os.system("diff result_corewar result_aout > res_diff")
fich3 = open("res_diff").read()
if len(fich3) > 1:
	print fich3
else:
	print "NO DIFF"
