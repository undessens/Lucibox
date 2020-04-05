import os

global duration
global tempo
duration = "8"
tempo = "135"

def rename(loopfile, myPath):
    index = loopfile.split(".")[0]
    finalName = "loop"+index+"_1.wav"
    loopfilePath = os.path.join(myPath, loopfile)
    finalNamePath = os.path.join(myPath, finalName)
    print(" rename: "+loopfilePath+" vers: "+finalNamePath)
    os.rename(loopfilePath ,finalNamePath )

def createTextFile(loopfile, myPath):
    index = loopfile.split(".")[0]
    finalName = "loop"+index+"_1_info.txt"
    myFile = open(os.path.join(myPath, finalName),"w+")
    myFile.write("duration "+duration+";\ntempo "+tempo+";\nexist 1;")

for root, dirs, files in os.walk("3/", topdown=False):
   for name in files:
      if(name.split(".")[1]=="wav" and len(name.split(".")[0])<3 ):
        print(os.path.join(root, name))
        rename(name, root)
        createTextFile(name, root)

   #for name in dirs:
      #print(os.path.join(root, name))



