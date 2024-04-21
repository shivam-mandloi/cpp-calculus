import os
import subprocess

class RunScript:
    def __init__(self, args, filename = ""):
        self.wkDir = os.getcwd()
        self.filename = os.path.join(self.wkDir, filename)
        self.includeDir = os.path.join(self.wkDir, "include")
        self.args = ["g++",self.filename, "-I", self.includeDir,"-o","main.exe"] + args
        self.startRun = [os.path.join(self.wkDir,"./main.exe")]

    def PrintStatus(self, result):
        if result.returncode == 0:
            print(f"[*]Compilation successful!\nFile Name: {self.filename}")
        else:
            print("[!]Compilation failed")
            print("Error message:")
            print(result.stderr.decode())
            print(self.args)

    def Run(self):
        result = subprocess.run(self.args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        self.PrintStatus(result)

if(__name__ == "__main__"):
    filename = "main.cpp"
    script = RunScript([],filename)
    script.Run()