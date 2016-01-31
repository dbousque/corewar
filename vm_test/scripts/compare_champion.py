import os, sys, time

champion1 = sys.argv[1]
champion2 = sys.argv[2]

to_replace = ["       | -> load from"]

os.system("../asm " + champion1 + " > /dev/null")
os.system("../asm " + champion2 + " > /dev/null")
os.system("./corewar " + champion1.replace(".s", ".cor") + " " + champion2.replace(".s", ".cor") + " -a -v 31 > res_corewar")
os.system("./a.out " + champion1.replace(".s", ".cor") + " " + champion2.replace(".s", ".cor") + " > res_aout")
fich = open("result_corewar", "w")
fich.write('\n'.join([line for line in open("res_corewar").read().split('\n')[:-1] if len([to_res for to_res in to_replace if to_res in line]) == 0]) + "\n")
fich2 = open("result_aout", "w")
fich2.write('\n'.join([line for line in open("res_aout").read().split('\n')[:-1] if len([to_res for to_res in to_replace if to_res in line]) == 0]) + "\n")
os.system("diff result_corewar result_aout > res_diff")
fich3 = open("res_diff").read()
if len(fich3) > 1:
	print fich3
else:
	print "NO DIFF"
