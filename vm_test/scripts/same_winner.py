import os,sys

def testdir(path):
	dirs = os.listdir(path)

	for file in dirs:
		if os.path.isdir(path + str(file)):
			testdir(path + str(file) + "/")
		if ".cor" in file:
			print path
			os.system("gtimeout 4s ./a.out " + path + str(file) + " test20.cor > res_aout")
			os.system("gtimeout 4s ./corewar " + path + str(file) + " test20.cor > res_corewar")
			os.system("diff res_aout res_corewar > res_diff")
			if len(open("res_diff").read()) > 1:
				print "ERROR FOR : " + str(file)
				os.system("cat res_diff")
			else:
				print "no diff for " + str(file)

path = sys.argv[1]
testdir(path)
