import platform
import os

if platform.architecture()[0] == '32bit':
    os.environ['PYSDL2_DLL_PATH'] = './SDL2/x86'
else:
    os.environ['PYSDL2_DLL_PATH'] = './SDL2/x64'

from Framework import *
MyGame = Framework()

MyGame.run()

#  map size : 16m x 10.4m
