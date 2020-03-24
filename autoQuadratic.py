import subprocess
from subprocess import PIPE

for i in range (10,110,10):
    outtest = "tests/input" + str(i) + "%.txt"
    cmd = ['./InputGenerator.x']
    proc = subprocess.Popen(cmd, stdout=PIPE, stdin=PIPE)
    stdout, stderr = proc.communicate(bytes("1234 500 " + str(i),'utf-8'))
    output = open(outtest,'wb+')
    output.write(stdout)
    output.close()

    outproc = "outputs/QuadraticProbing" + str(i) + "%.txt"
    output2 = open(outproc,'wb+')
    cmd2 = ["./QuadraticProbing.x"]
    print(i)
    for j in range (1,10):
        for k in range (1,10):
            print(j,k)
            proc2 = subprocess.Popen(cmd2, stdout=PIPE, stdin=PIPE)
            str1 = str(j) + " " + str(k) + "\n"
            stdout2, stderr2 = proc2.communicate(bytes(str1,'utf-8')+ stdout)
            proc2.wait()
            str2 = bytes("c1 = " + str(j) + "     c2 = " + str(k) + "\n",'utf-8')
            output2.write(str2 + stdout2 + bytes("\n\n",'utf-8'))
    output2.close()
