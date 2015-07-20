4#!/usr/bin/env python
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
from items import Items
import random
import select
import threading

class Parser:
    """Check all command et execute command"""

    def __init__(self, window, winW, winH):
        self.players = []
        self.itX = []
        self.itY = []
        self.winW = winW
        self.winH = winH
        self.win = window
        self.dicts = {}
        self.action = {}
        self.pic = 0
        self.teamList = ["Team : "]
        self.threadList = {}
        self.mp = Map(window, winW, winH)
        self.perso = Player(window, self.mp)
        self.item = Items(window, self.mp)
        self.initCommands()
        self.initAction()
        self.stat = 0

    def initCommands(self):
        self.dicts["msz"] = self.Cmsz
        self.dicts["pnw"] = self.Cpnw
        self.dicts["enw"] = self.Cenw
        self.dicts["pbc"] = self.Cpbc
        self.dicts["eht"] = self.Ceht
        self.dicts["edi"] = self.Cedi
        self.dicts["ppo"] = self.Cppo
        self.dicts["plv"] = self.Cplv
        self.dicts["pfk"] = self.Cpfk
        self.dicts["pdi"] = self.Cpdi
        self.dicts["bct"] = self.Cbct
        self.dicts["pex"] = self.Cpex
        self.dicts["pin"] = self.Cpin
        self.dicts["pic"] = self.Cpic
        self.dicts["pie"] = self.Cpie
        self.dicts["pdr"] = self.Cpdr
        self.dicts["pgt"] = self.Cpgt
        self.dicts["ebo"] = self.Cebo
        self.dicts["sgt"] = self.Csgt
        self.dicts["seg"] = self.Cseg
        self.dicts["smg"] = self.Csmg
        self.dicts["tna"] = self.Ctna
        self.dicts["suc"] = self.Cunknown
        self.dicts["sbp"] = self.Cunknown

    def initAction(self):
        self.action["msz"] = self.mp.displayMap
        self.action["pnw"] = self.perso.add
        self.action["enw"] = self.perso.makeEggs
        self.action["pbc"] = self.perso.broadcast
        self.action["eht"] = self.perso.hatchEggs
        self.action["edi"] = self.perso.hatchEggs
        self.action["ppo"] = self.perso.update
        self.action["plv"] = self.perso.setLevel
        self.action["pfk"] = self.perso.shield
        self.action["pdi"] = self.perso.die
        self.action["bct"] = self.item.addItem

    def checkCommand(self, command):
        if command[0] == "BIENVENUE":
            return
        print command
        if (self.dicts[command[0]](command) == False):
            print "Invalid Command =>" + command[0]

    def updateMap(self, winW, winH):
        self.winW = winW
        self.winH = winH
        self.mp.updateMap(winW, winH, self.item, self.perso, self.players, self.teamList)

    def play_music(self, song, lop):
        try:
            if not pygame.mixer.get_init():
                pygame.mixer.init()
            pygame.mixer.music.load(song)
            pygame.mixer.music.set_volume(float(50.00)/100)
            channel = pygame.mixer.music.play(lop)
        except:
            print "Could not load music"

    def checkInt(self, valArray, size):
        i = 1
        while (i < size):
            if (valArray[i].isdigit == False):
                print "ioJAIODJOJIOJDIOJ"
                return False
            i += 1
        return True

    def run(self, id):
        self.perso.execCommand(id)

    def Cmsz(self, command):
        if (len(command) != 3 or self.checkInt(command, 3) == False):
            return False
        self.action[command[0]](int(command[1]) - 1,
                                int(command[2]) - 1)
        self.stat = 1
        self.displayAll()
        self.play_music("bgm/Rick_Rolled.wav", -1)

    def Cpnw(self, command):
        if (len(command) != 7 or self.checkInt(command, 6) == False):
            return False
        self.action[command[0]](int(command[1]),
                                int(command[2]),
                                int(command[3]),
                                int(command[4]),
                                int(command[5]),
                                command[6], self.mp)
        self.players.append(int(command[1]))

    def Cenw(self, command):
        if (len(command) != 5 or self.checkInt(command, 5) == False):
            return False
        self.action[command[0]](int(command[1]),
                                int(command[2]),
                                int(command[3]),
                                int(command[4]))

    def Cpbc(self, command):
        if (len(command) <= 3 or self.checkInt(command, 1) == False):
            return False
        self.action[command[0]](int(command[1]))

    def Ceht(self, command):
        if (len(command) != 2 or self.checkInt(command, 2) == False):
            return False
        self.action[command[0]](int(command[1]))

    def Cedi(self, command):
        if (len(command) != 2 or self.checkInt(command, 2) == False):
            return False

    def Cppo(self, command):
        if (len(command) != 5 or self.checkInt(command, 5) == False):
            return False
        self.action[command[0]](int(command[1]),
                                  int(command[2]),
                                  int(command[3]),
                                  int(command[4]),
                                  self.mp,
                                  self.winW,
                                  self.winH,
                                  self.item,
                                  self.perso, self.players, self.teamList)

    def Cplv(self, command):
        if (len(command) != 3 or self.checkInt(command, 3) == False):
            return False
        self.action[command[0]](int(command[1]),
                                int(command[2]))

    def Cpfk(self, command):
        if (len(command) != 2 or self.checkInt(command, 2) == False):
            return False
        self.action[command[0]](int(command[1]))

    def Cpdi(self, command):
        if (len(command) != 2 or self.checkInt(command, 2) == False):
            return False
        self.action[command[0]](int(command[1]), self.winW, self.winH, self.item, self.perso, self.players, self.teamList)
        value = int(command[1]) in self.players
        if value == True:
            self.players.remove(int(command[1]))

    def Cbct(self, command):
        o = 0
        i = 0
        if (len(command) != 10 or self.checkInt(command, 10) == False):
            return False
        self.action[command[0]](int(command[1]),
                                  int(command[2]),
                                  int(command[3]),
                                  int(command[4]),
                                  int(command[5]),
                                  int(command[6]),
                                  int(command[7]),
                                  int(command[8]),
                                  int(command[9]))
        while i < len(self.itX):
            if (int(command[1]) == self.itX[i]):
                if (int(command[2]) == self.itY[i]):
                    o += 1
            i += 1
        if (o == 0):
            self.itX.append(int(command[1]))
            self.itY.append(int(command[2]))

    def Cpex(self, command):
        if (len(command) != 2 or self.checkInt(command, 2) == False):
            return False

    def Cpin(self, command):
        if (len(command) != 11 or self.checkInt(command, 10) == False):
            print "pin failed!"
            return False

    def Ctna(self, command):
        if len(command) != 2:
            return False
        self.teamList.append(command[1])

    def Cpic(self, command):
        if len(command) <= 4:
            return False
        self.perso.incantation(command)
        self.pic = 1

    def Cpie(self, command):
        if (len(command) != 4 or self.checkInt(command, 4) == False):
            return False
        if command[3] == 1:
            self.perso.endIncantation(command)

    def Cpdr(self, command):
        if (len(command) != 3 or self.checkInt(command, 3) == False):
            return False

    def Cpgt(self, command):
        if (len(command) != 3 or self.checkInt(command, 3) == False):
            return False

    def Cebo(self, command):
        if (len(command) != 2 or self.checkInt(command, 2) == False):
            return False

    def Csgt(self, command):
        if len(command) != 2:
            return False
        try:
            float(command[1])
        except:
            return False

    def Cseg(self, command):
        try:
            if len(command) != 2:
                return False
            loading = pygame.image.load("../map/logo/victory.png").convert_alpha()
            self.win.blit(loading, (0,0))
            pygame.display.update()
            team = "Team : "
            team += command[1]
            myfont = pygame.font.Font("Lato-Light.ttf", 30)
            label = myfont.render(team, 1, (255, 255, 255))
            self.play_music("bgm/victory.wav", 0)
            while 1:
                Kinput = pygame.key.get_pressed()
                if (Kinput[pygame.K_ESCAPE]):
                    sys.exit()
                pygame.event.pump()
                self.win.blit(label, (550, 200))
                pygame.display.update()
        except:
            sys.exit("VICTORY")

    def Csmg(self, command):
        if len(command) != 1:
            return False

    def Cunknown(self, command):
        if len(command) != 1:
            return False
        pass

    def displayPlayers(self):
        i = 0
        while i < len(self.players):
            self.perso.display(self.players[i], self.winW, self.winH)
            i += 1

    def displayItems(self):
        i = 0
        while i < len(self.itX):
            self.item.displayItem(self.itX[i], self.itY[i], self.winW, self.winH)
            i += 1

    def displayMap(self):
        self.mp.updateMap(self.winW, self.winH, self.item, self.perso, self.players, self.teamList)

    def displayAll(self):
        if (self.stat == 1):
            self.displayMap()
            self.displayPlayers()
            pygame.display.update()
