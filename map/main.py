#!/usr/bin/env python
# -*- coding: Utf-8 -*

import pygame.mixer
import pygame
import time
from pygame.locals import *
import pygame.surfarray as surfarray
import sys, os
import socket
from player import Player
from map import Map
from parser import Parser
from items import Items
import random
import select
import signal

args = ["msz", "bct", "tna", "pnw", "ppo", "plv", "pin", "pex", "pbc",
             "pic", "pie", "pfk", "pdr", "pgt", "pdi", "enw", "eht", "ebo",
             "edi", "sgt", "seg", "smg", "suc", "sbp", "BIENVENUE"]

def init_graph():
        try:
                pygame.init()
                pygame.mouse.set_visible(False)
                window = pygame.display.set_mode((1280, 800), pygame.HWSURFACE | pygame.DOUBLEBUF)
                return window
        except:
                sys.exit("init pygame failed")

def checkInput():
        try:
                socket.inet_aton(socket.gethostbyname(sys.argv[1]))
        except socket.error:
                print("Not a valid IP ADDR.")
                return (False)
        if (sys.argv[2].isdigit() == True
        and int(sys.argv[2]) > 1023
        and int(sys.argv[2]) < 65535):
		return (True)
        print("Port is not valid.")
        return (False)

def init_client():
        try:
                host = socket.gethostbyname(sys.argv[1])
                port = int(sys.argv[2])
                try:
                        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                except:
                        print("Failed to make socket")
                        return (-1)
                try:
                        sock.connect((host, port))
                except:
                        print "Could not connect to the server."
                        return -1
                return (sock)
        except:
                sys.exit("init client failed")

def sendGraphic(data, sock):
        print data
        if (data == "BIENVENUE\n"):
                print ("GRAPHIC")
                sock.send("GRAPHIC\n")

def loading(window):
        try:
                loading = pygame.image.load("../map/logo/loading.jpg").convert_alpha()
                window.blit(loading, (0,0))
                pygame.display.update()
                pygame.time.delay(5000)
        except:
                sys.exit("Could not load welcome image")

def parseServMsg(data, parser, bigMap):
        commandArray = data.split('\n')
        caseArray = []
        for i in commandArray:
                caseArray.append(i.split())
        j = 0
        while (j < len(caseArray)):
            Kinput = pygame.key.get_pressed()
            if (Kinput[pygame.K_ESCAPE]):
                    Loop = 0
                    return
            if (Kinput[pygame.K_LEFT]):
                if (bigMap == True):
                    winW += 200
                    parser.updateMap(winW, winH)
            if (Kinput[pygame.K_RIGHT]):
                if (bigMap == True):
                    winW -= 200
                    parser.updateMap(winW, winH)
            if (Kinput[pygame.K_DOWN]):
                if (bigMap == True):
                    winH += 100
                    parser.updateMap(winW, winH)
            if (Kinput[pygame.K_UP]):
                if (bigMap == True):
                    winH -= 100
                    parser.updateMap(winW, winH)
            pygame.event.pump()
            if (caseArray[j]):
                value = caseArray[j][0] in args
                if (value == True):
                        if caseArray[j][0] == "msz":
                                if (int(caseArray[j][1]) > 15 and int(caseArray[j][2]) > 15):
                                    bigMap = True
                        if (parser.checkCommand(caseArray[j]) == True):
                                return True
            j += 1
        pygame.display.set_caption("EPIQQ")
        return (bigMap)

def connectLoop(sock):
        winW = 1200
        winH = 0
        Loop = 1
        window = init_graph()
        parser = Parser(window, winW, winH)
        loading(window)
        i = 0
        bigMap = False
        sock.setblocking(0)
        while (Loop is not 0):
                Kinput = pygame.key.get_pressed()
                if (Kinput[pygame.K_ESCAPE]):
                        Loop = 0
                        pygame.event.pump()
                        return
                try:
                        if (Loop == 1):
                                sock.send("GRAPHIC\n")
                                Loop = 2
                        if (Kinput[pygame.K_ESCAPE]):
                                Loop = 0
                                return
                        if (Kinput[pygame.K_LEFT]):
                                if (bigMap == True):
                                        winW += 200
                                        parser.updateMap(winW, winH)
                        if (Kinput[pygame.K_RIGHT]):
                                if (bigMap == True):
                                        winW -= 200
                                        parser.updateMap(winW, winH)
                        if (Kinput[pygame.K_DOWN]):
                                if (bigMap == True):
                                        winH += 100
                                        parser.updateMap(winW, winH)
                        if (Kinput[pygame.K_UP]):
                                if (bigMap == True):
                                        winH -= 100
                                        parser.updateMap(winW, winH)
                        pygame.event.pump()
                        data = sock.recv(32000)
                        bigMap = parseServMsg(data, parser, bigMap)
                        parser.displayAll()
                except:
                        parser.displayAll()
                        continue

def clientConnect():
        sock = init_client()
        if (sock == -1):
            return False
        return (connectLoop(sock))

def sighandler(signal, frame):
        sys.exit("You leave the game")

if __name__ == "__main__":
        signal.signal(signal.SIGINT, sighandler)
        try:
                os.environ["HOME"]
        except:
                sys.exit("No HOME env")
	if (len(sys.argv) != 3):
		sys.exit("Usage: python map.py [IP] [PORT]")
        if (checkInput() == False):
                sys.exit()
        if (clientConnect() == False):
                sys.exit()
