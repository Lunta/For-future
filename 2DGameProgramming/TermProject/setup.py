import cx_Freeze
import os

os.environ['TCL_LIBRARY'] = 'C:\\Users\\tkdql\\AppData\\Local\\Programs\\Python\\Python35\\tcl\\tcl8.6'
os.environ['TK_LIBRARY'] = 'C:\\Users\\tkdql\\AppData\\Local\\Programs\\Python\\Python35\\tcl\\tk8.6'

cx_Freeze.setup(
    name='Meteor Crash',
    version = "1.0",
    options={'build_exe': {'packages':['pygame'],
                           'include_files': ['./SDL2/', './Resource/', 'ranking.txt']}},
    executables = [cx_Freeze.Executable(script='MeteorCrash.py', icon='MeteorCrash.ico')]
)