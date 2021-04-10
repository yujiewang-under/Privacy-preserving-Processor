import sys

arglist=list(sys.argv)
#print(sys.argv)
fn_in=arglist[1]
fn_out=arglist[2]
#print(arglist,fn_in,fn_out)
fin = open(fn_in)
fout=open(fn_out,'w+')

for line in fin:
	line=line.strip('\n')
	ele=line.split(',')

	if ele[0]=="add":
		fout.write("000000")
		fout.write(format(int(ele[1]), '05b'))
		fout.write(format(int(ele[2]), '05b'))
		fout.write(format(int(ele[3]), '05b'))
		fout.write(format(0, '05b'))
		fout.write("100000\n")
	if ele[0]=="sub":
		fout.write("000000")
		fout.write(format(int(ele[1]), '05b'))
		fout.write(format(int(ele[2]), '05b'))
		fout.write(format(int(ele[3]), '05b'))
		fout.write(format(0, '05b'))
		fout.write("100010\n")
	if ele[0]=="and":
		fout.write("000000")
		fout.write(format(int(ele[1]), '05b'))
		fout.write(format(int(ele[2]), '05b'))
		fout.write(format(int(ele[3]), '05b'))
		fout.write(format(0, '05b'))
		fout.write("100100\n")
	if ele[0]=="or":
		fout.write("000000")
		fout.write(format(int(ele[1]), '05b'))
		fout.write(format(int(ele[2]), '05b'))
		fout.write(format(int(ele[3]), '05b'))
		fout.write(format(0, '05b'))
		fout.write("100101\n")
	if ele[0]=="slt":
		fout.write("000000")
		fout.write(format(int(ele[1]), '05b'))
		fout.write(format(int(ele[2]), '05b'))
		fout.write(format(int(ele[3]), '05b'))
		fout.write(format(0, '05b'))
		fout.write("101010\n")

	if ele[0]=="lw":
		fout.write("100011")
		fout.write(format(int(ele[1]), '05b'))
		fout.write(format(int(ele[2]), '05b'))
		fout.write(format(int(ele[3]), '016b'))
		fout.write("\n")
	if ele[0]=="sw":
		fout.write("101011")
		fout.write(format(int(ele[1]), '05b'))
		fout.write(format(int(ele[2]), '05b'))
		fout.write(format(int(ele[3]), '016b'))
		#print(format(int(65528), '016b'),ele[3])
		fout.write("\n")

	if ele[0]=="beq":
		fout.write("000100")
		fout.write(format(int(ele[1]), '05b'))
		fout.write(format(int(ele[2]), '05b'))
		fout.write(format(int(ele[3]), '016b'))
		fout.write("\n")

	if ele[0]=="addi":
		fout.write("001000")
		fout.write(format(int(ele[1]), '05b'))
		fout.write(format(int(ele[2]), '05b'))
		fout.write(format(int(ele[3]), '016b'))
		fout.write("\n")

fout.write("00010000000000001111111111111111\n");