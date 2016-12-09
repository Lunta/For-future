import cx_Freeze
import os

os.environ['TCL_LIBRARY'] = 'C:\\Users\\tkdql\\AppData\\Local\\Programs\\Python\\Python35\\tcl\\tcl8.6'
os.environ['TK_LIBRARY'] = 'C:\\Users\\tkdql\\AppData\\Local\\Programs\\Python\\Python35\\tcl\\tk8.6'
executables = [cx_Freeze.Executable(script='MeteorCrash.py', icon='MeteorCrash.ico')]

cx_Freeze.setup(
    name='Meteor Crash',
    options={'build_exe': {'packages':['pygame'],
                           'include_files': ['./SDL2/', './Resource/', 'ranking.txt']}},
    executables = executables
)