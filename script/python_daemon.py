import os
import sys
import glob
import time
import threading
import struct
import socket
import subprocess 
from OSC import OSCClient, OSCMessage, OSCServer

class SimpleServer(OSCServer):
    def __init__(self,t):
        OSCServer.__init__(self,t)
        self.selfInfos = t
        self.addMsgHandler('default', self.handleMsg)

    
    def handleMsg(self,oscAddress, tags, data, client_address):
        print("OSC message received on : "+oscAddress)

        splitAddress = oscAddress.split("/")
        print(splitAddress)
        
        ############## Lucibox Message #############

        if(splitAddress[1]=="truc"):
            if(splitAddress[2]=="chose"):
                print("chose")
            if(splitAddress[2]=="bidulle"):
                print("bidulle")

        ############## APP itself #############
        if(splitAddress[1]=="app"):
            if(splitAddress[2]=="close"):
                print("closing the app")
                closing_app()
            if(splitAddress[2]=="restart"):
                print("restart the app")
                restart_app()
        
        ############## RPI itself #############
        if(splitAddress[1]=="rpi"):
            if(splitAddress[2]=="shutdown"):
                print("Turning off the rpi")
                forwardPowerOff();

def forwardPowerOff():

	time.sleep(5)
	print("========= POWER OFF ======")
	subprocess.call(["/home/patch/lucibox/script/shutdown.sh"])

def closing_app():
    global runningApp
    runningApp = False
    print("Closing App")

def restart_app():

	subprocess.call(["quit_pd.sh"])
	cmd = ["pd",  "-nogui",  "-jack",  "/home/patch/lucibox/machines/6/simple_samplerloop.pd "]
	subprocess.call(cmd)

def main():
        
        # OSC CONNECT       
        myip = socket.gethostbyname(socket.gethostname())
	myip = "192.168.1.44"
        print("IP adress is : "+myip)
        try:
            server = SimpleServer((myip, 12344)) 
        except:
            print(" ERROR : creating server") 
        print("server created") 
        try:
            st = threading.Thread(target = server.serve_forever) 
        except:
            print(" ERROR : creating thread") 
        try:
            st.start()
        except:
            print(" ERROR : startin thread")

        print(" OSC server is running")  

        # MAIN LOOP 
        global runningApp
        runningApp = True

        while runningApp:
            # This is the main loop
            # Do something here
            try:
                time.sleep(1)
            except:
                print("User attempt to close programm")
                runningApp = False
        
        #CLOSING THREAD AND SERVER
        print(" Ending programme") 
        server.running = False
        print(" Join thread") 
        st.join()
        server.close()
        print(" This is probably the end") 



if __name__ == "__main__":
    main()
