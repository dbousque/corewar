import os,sys

def testdir(path):
	dirs = os.listdir(path)

	for file in dirs:
		if os.path.isdir(path + str(file)):
			testdir(path + str(file) + "/")
		if ".cor" in file:
			print path
			os.system("gtimeout 4s ./a.out " + path + str(file) + " test20.cor > res_aout")
			os.system("gtimeout 4s ./corewar " + path + str(file) + " test20.cor -v 2 > res_corewar")
			res = '\n'.join([line for line in open("res_aout").read().split('\n')[3:-2] if "Cycle" not in line])
			fich = open("res_aout2", "w")
			fich.write(res)
			fich.close()
			res = '\n'.join([line for line in open("res_corewar").read().split('\n')[3:-2] if "Cycle" not in line])
			fich = open("res_corewar2", "w")
			fich.write(res)
			fich.close()
			for i in range(10000):
				continue
			os.system("diff res_aout2 res_corewar2 > res_diff")
			if len(open("res_diff").read()) > 1:
				print "ERROR FOR : " + str(file)
				#os.system("cat res_diff")
			else:
				print "no diff for " + str(file)

path = sys.argv[1]
testdir(path)
