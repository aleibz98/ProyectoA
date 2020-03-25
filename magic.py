import matplotlib.pyplot as plt
import subprocess
from subprocess import PIPE


def printList(a):
    string = ""
    for elem in a:
        lista = list(elem)
        string = string + "".join(lista) + ","
    string = swapDotComma(string)
    print(string)

def swapDotComma(string):
    lista = list(string)
    res = ""
    for char in lista:
        if char == ',': res = res + res.join('.')
        elif char == '.': res = res + res.join(',')
        else: res = res + res.join(char)

    return res

def averageProvesVsAlpha(a,b,c,d):
    plt.plot(a, b, label='teórica')
    plt.plot(a, c, label= 'claves insertadas')
    plt.plot(a, d, label= 'claves no insertadas')
    plt.xlabel('ratio de ocupación')
    plt.ylabel('media de probes')
    plt.title('Linear Probing')
    plt.legend()
    plt.show()

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

printList(keys)


for dict in total:
    values = []
    for key in keys:
        if key in dict: values.append(dict[key])
        else: values.append('-1')
    printList(values)



#Linear and quadratic
#teorica = []
#empiricaInsert = []
#empiricaNoInsert = []
#alpha = []

#for dict in total:
#    if dict['Nombre'] == 'LinearProbing':
#        teorica.append(dict['Media probes teórica'])
#        empiricaInsert.append(dict['Media probes empírica insertados'])
#        empiricaNoInsert.append(dict['Media probes empírica no insertados'])
#        alpha.append(dict['Ratio de ocupación'])

#averageProvesVsAlpha(alpha,teorica,empiricaInsert,empiricaNoInsert)






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




