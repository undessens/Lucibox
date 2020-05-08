import os
import sys
import glob
import time
import threading
import struct
import socket
import subprocess 
from OSC import OSCClient, OSCMessage, OSCServer

#################################################
# This is Lucibox daemon
# Always running 
# start & stop puredata patches, start & stop openstagecontrol session
# turn off rpi, 
#
#
#################################################

class SimpleServer(OSCServer):
    def __init__(self,t):
        OSCServer.__init__(self,t)
        self.selfInfos = t
        self.addMsgHandler('default', self.handleMsg)

    
    def handleMsg(self,oscAddress, tags, data, client_address):
        global machine
        print("OSC message received on : "+oscAddress)

        splitAddress = oscAddress.split("/")
        print(splitAddress)
        
        ############## APP itself #############
        if(splitAddress[1]=="app"):
            if(splitAddress[2]=="close"):
                print("closing the app")
                quit_app()
            if(splitAddress[2]=="start"):
                print("starting the app")
                start_app()
            if(splitAddress[2]=="restart"):
                print("restart the app")
                quit_app()
                start_app()
        
        ############## RPI itself #############
        if(splitAddress[1]=="rpi"):
            if(splitAddress[2]=="shutdown"):
                print("Turning off the rpi")
                forwardPowerOff();

def forwardPowerOff():

    time.sleep(5)
    print("========= POWER OFF ======")
    os.chdir("/home/patch/lucibox/script/")
    subprocess.call(['./shutdown.sh'])
        
def closing_app():
    global runningApp
    runningApp = False
    print("Closing App")

def quit_app():
    print("========= QUIT PUREDATA ======")
    os.chdir("/home/patch/lucibox/script/")
    subprocess.call(["./quit_pd.sh"])
    print("======== PUREDATA QUITTED ====")

def start_app():
    global machine
    print("========= START PUREDATA======")
    cmd = ["pd",  "-nogui",  "-jack",  "/home/patch/lucibox/machines/"+str(machine)+"/nogui.pd"]
    subprocess.Popen(cmd)
    print("======== PUREDATA STARTED ====")
    print("========= START OPEN STAGE CONTROL ======")
    cmd = ["node",  "/home/patch/open-stage-control/app",  "-l",  "/home/patch/lucibox/machines/"+str(machine)+"/osc.json", "-s", "127.0.0.1:9999", "-o", "9998"]
    subprocess.Popen(cmd)
    print("========= OPEN STAGE CONTROL STARTED ======")

def main():
        
        # OSC CONNECT       
        myip = socket.gethostbyname(socket.gethostname())
        myip = "127.0.0.1"
        print("IP adress is : "+myip)
        try:
            server = SimpleServer((myip, 12345)) 
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

        #START ON BOOT
        global machine
        machine = 6
        start_app()
        print(" ===== STARTING MAIN LOOP ====" )
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
