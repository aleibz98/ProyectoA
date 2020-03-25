import subprocess
from subprocess import PIPE

cmd = ['ls', 'outputs/']
proc = subprocess.Popen(cmd, stdout=PIPE, stdin=PIPE)
stdout, stderr = proc.communicate()
folder = stdout.split()

total = []

for file in folder:
    dictionary = {}
    name = str(file)
    lista = list(name)
    lista[0] = ''
    lista[1] = ''
    lista[-1] = ''
    name = "".join(lista)
    actual = open("outputs/"+name,'r')
    for line in actual:
        line = str(line)
        k, v = line.split(': ')
        v = v.rstrip("\n")
        dictionary[k.replace("{'}",'')] = v
    total.append(dictionary)

keys = []
for dict in total:
    for key in dict:
        if key not in keys: keys.append(key)

print(keys)


for dict in total:
    values = []
    for key in keys:
            if key in dict: values.append(dict[key])
            else: values.append('')
    print(values)




#Podria ser facil tratarlo como json o algo asi, no se


#de linear y quadratic probing nos interesa:
#    Ratio de ocupacion:
 #   Media probes teórica:
  #Media probes empírica insertados:
  #  Media probes empírica no insertados:
#
#de double hashing nos interesa:


#de BloomFilters nos iteresa:
#    % de ocupacion
#    todos los datos printado en realidad

#de cuckoo hashing nos interesa:


#de MoveToFront nos interesa:


#de ExactFit nos interesa:





#Que hacemos con toda esa info?
#    Gráficos de comportamiento segun % de ocupacion
#    Gráficos de comportamiento de Bloom filter segun numero de hashes, % de ocupacion y las dos a la vez
#    Graficos de quadratic segun constantes (?)




