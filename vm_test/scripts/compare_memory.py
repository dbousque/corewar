#!/usr/bin/env python
import os, sys

def find_diff(step, champion1, champion2, start):
	dump = start
	while True:
		os.system("./corewar " + champion1.replace(".s", ".cor") + " " + champion2.replace(".s", ".cor") + " -a -v 31 -d " + str(dump) + " > res_corewar")
		os.system("./a.out " + champion1.replace(".s", ".cor") + " " + champion2.replace(".s", ".cor") + " " + str(dump) + " > res_aout")
		fich = open("result_corewar" + str(dump), "w")
		fich.write('\n'.join([line for line in open("res_corewar").read().split('\n')[3:-2] if len([to_res for to_res in to_replace if to_res in line]) == 0]) + "\n")
		fich.close()
		print "ok"
		fich2 = open("result_aout" + str(dump), "w")
		fich2.write('\n'.join([line for line in open("res_aout").read().split('\n')[:-1] if len([to_res for to_res in to_replace if to_res in line]) == 0]) + "\n")
		fich2.close()
		os.system("diff result_corewar" + str(dump) + " result_aout" + str(dump) + " > res_diff" + str(dump))
		fich3 = open("res_diff" + str(dump))
		data = fich3.read()
		fich3.close()
		if len(data) > 1:
			if step == 1:
				print data
				print "DIFF AT " + str(dump)
				sys.exit(0)
			find_diff(step / 2, champion1, champion2, dump - step)
			break
		else:
			print "NO DIFF"
		dump += step

champion1 = sys.argv[1]
champion2 = sys.argv[2]

to_replace = ["       | -> load from"]

os.system("../asm " + champion1 + " > /dev/null")
os.system("../asm " + champion2 + " > /dev/null")
step = 1000
find_diff(step, champion1, champion2, step)
