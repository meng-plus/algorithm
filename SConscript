from building import *
import os

cwd = GetCurrentDir()
src = Glob('src/algorithms/*.c')
CPPPATH = [cwd+"/src"]

group = DefineGroup('third_party', src, depend = [''], CPPPATH = CPPPATH)

list = os.listdir(cwd)
for item in list:
    if os.path.isfile(os.path.join(cwd, item, 'SConscript')):
        group = group + SConscript(os.path.join(item, 'SConscript'))

Return('group')
