import subprocess
import os
import sys
import time
import shutil
import glob
import copy

#set the make comand based on the operating system
makecmd = "mingw32-make"

def check_command_valid(command):
    if (not target == "1" and
        not target == "c"):
        print("invalid target")
        sys.exit()

print(" -- Select build target -- ")
print("1: main")
print("c: clean")

target = input("> ")

check_command_valid(target)

if target == "c":
    print("Cleaning...")
    if os.path.exists("build") and os.path.isdir("build"):
        try:
            subprocess.run([makecmd, 'clean', '-j8'], cwd="build", check=True)
        except subprocess.CalledProcessError:
            #do nothing
            pass
        #delete entire build folder
        shutil.rmtree("build")
    print("All build files cleaned")
    sys.exit()
    
start_time = time.time()

#check whether the specified path exists or not
buildPath="./build"
buildPathExists = os.path.exists(buildPath)

if not buildPathExists:
    os.mkdir(buildPath, 0o777)

cmd = ['cmake', '..']
cmd.append("-G")
cmd.append("MinGW Makefiles")

os.chdir("./build")
p = subprocess.Popen(cmd)
p.wait()
subprocess.call([makecmd, '-j8', "main"])

end_time = time.time()
minutes, seconds = divmod((end_time - start_time)% 3600, 60)
print('\n Done in {:02.0f}m{:02.0f}s! See {} for compiled output'.format(minutes, seconds, os.path.join(sys.path[0], 'build')))

subprocess.run("main.exe")

os.chdir("../..")