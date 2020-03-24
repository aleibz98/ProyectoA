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
    proc2 = subprocess.Popen(cmd2, stdout=PIPE, stdin=PIPE)
    stdout2, stderr2 = proc2.communicate(stdout)
    proc2.wait()
    output2.write(stdout2)
    output2.close()
