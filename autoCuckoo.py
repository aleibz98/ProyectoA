import subprocess
from subprocess import PIPE

for i in range (10,110,10):
    intest = "tests/input" + str(i) + "%.txt"
    input = open(intest,'rb')
    stdout = input.read()
    input.close()
    outproc = "outputs/CuckooHashing" + str(i) + "%.txt"
    cmd = ["./CuckooHashing.x"]
    proc = subprocess.Popen(cmd, stdout=PIPE, stdin=PIPE)
    stdout, stderr = proc.communicate(stdout)
    output = open(outproc,'wb+')
    output.write(stdout)
    output.close()
