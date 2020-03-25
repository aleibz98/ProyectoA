from subprocess import call

g= 'g++'
o = '-o'
call([g,'LinearProbing.cpp',o,'LinearProbing.x'])
call([g,'QuadraticProbing.cpp',o,'QuadraticProbing.x'])
call([g,'BloomFilter_Alex.cpp',o,'BloomFilter.x'])
call([g,'CuckooHashing.cpp',o,'CuckooHashing.x'])
call([g,'DoubleHashing.cpp',o,'DoubleHashing.x'])
call([g,'ExactFit.cpp',o,'ExactFit.x'])
call([g,'MovetoFront.cpp',o,'MovetoFront.x'])


py = 'python'

call([py,'autoLinear.py'])
call([py,'autoQuadratic.py'])
call([py,'autoBloom.py'])
call([py,'autoCuckoo.py'])
call([py,'autoMoveToFront.py'])
call([py,'autoDoubleHashing.py'])
call([py,'autoExactFit.py'])


call([py,'magic.py'])