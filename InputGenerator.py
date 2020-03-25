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