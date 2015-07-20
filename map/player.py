#!/usr/bin/env python
# -*- coding: Utf-8 -*

import pygame.mixer
import pygame
import time
from pygame.locals import *
import pygame.surfarray as surfarray
import sys, os
import socket
import random

class Player:
	def __init__(self, window, mp):
                try:
                        self.container = []
                        self.posX = 0
                        self.posY = 0
                        self.id = 0
                        self.window = window
                        self.info = {}
                        self.character = {}
                        self.levelUp = {}
                        self.dies = {}
                        self.eggs = {}
                        self.eggId = []
                        self.incantations = {}
                        self.mp = mp
                        self.players = []
                        self.endInca = 0
                        self.font = pygame.font.SysFont("monospace", 40)
                        self.label = self.font.render("Team : Unknown", 1, (255,255,0))
                        self.egg = pygame.image.load("../map/pierre/egg.png").convert_alpha()
                        self.createPlayer()
                        self.createLevelUp()
                        self.initDie()
                except:
                        sys.exit("Can't load l'image")

	def add(self, id, posX, posY, direction, level, team, mp):
		self.players.append(id)
		self.info[id, "direction"] = direction
		self.info[id, "level"] = level
		self.info[id, "team"] = team
		self.info[id, "posX"] = posX
		self.info[id, "posY"] = posY
		self.info[id, 5] = 1
		self.info[id, "position"] = mp.getPosition(self.info[id, "posX"], self.info[id, "posY"])
		self.info[id, "img"] = self.character[level, direction]
		self.info[id, "animation"] = False
		self.info[id, "egg"] = []
		self.info[id, "broad"] = 0
		self.info[id, "shieldStat"] = 0
		self.info[id, "queu"] = []
		self.info[id, "dead"] = False
		self.id += 1
		self.info[id, "position"] = self.info[id, "position"].move(105, 15)
		self.label = self.font.render(self.info[id, "team"], 10, (255, 0, 0))

	def update(self, id, posX, posY, direction, mp, winW, winH, item, perso, players, teamList):
		value = id in self.players
		if (value == True):
			self.info[id, "queu"].append([posX, posY, direction])
			self.info[id, "posX"] = self.info[id, "queu"][0][0]
			self.info[id, "posY"] = self.info[id, "queu"][0][1]
			self.info[id, "direction"] = self.info[id, "queu"][0][2]
			print self.info[id, "queu"][0][0], self.info[id, "queu"][0][1], self.info[id, "posX"], self.info[id, "posY"]
			self.info[id, "position"] = self.mp.getPosition(self.info[id, "posX"], self.info[id, "posY"])
			self.info[id, "position"] = self.info[id, "position"].move(105, 15)
			self.info[id, "img"] = self.character[self.info[id, "level"], self.info[id, "direction"]]
			self.info[id, "queu"].remove(self.info[id, "queu"][0])
			self.mp.updateMap(winW, winH, item, perso, players, teamList)
			self.getPlayer(id, self.info[id, "posX"], self.info[id, "posY"])
			pygame.display.update()

	def makeEggs(self, idEgg, id, posX, posY):
		value = id in self.players
		if (value == True):
			pos = self.mp.getPosition(posX, posY)
			pos = pos.move(105, 15)
                        rand1 = random.randint(10, 20)
                        rand2 = random.randint(5, 10)
			pos[0] = pos[0] + rand1
			pos[1] = pos[1] + rand2
			self.eggs[id, idEgg] = ([posX, posY, rand1, rand2])
			self.info[id, "egg"].append(idEgg)
			self.eggId.append(idEgg)
			self.window.blit(self.egg, self.eggs[id, idEgg])
			pygame.display.update()

	def hatchEggs(self, idEgg):
		value = idEgg in self.eggId
		if value == True:
			self.info[self.EggId[idEgg], "egg"].remove(idEgg)

	def shield(self, id):
		self.info[id, "shieldStat"] = 1;
		#self.getShield(id)

	def setLevel(self, id, level):
		value = id in self.players
		if (value == True):
			self.info[id, "level"] = level
			self.info[id, "img"] = self.character[self.info[id, "level"], self.info[id, "direction"]]
			#game.image.load("../map/icone/bronze.png").convert_alpha()
			pos = self.mp.getPosition(self.info[id, "posX"], self.info[id, "posY"])
			pos = pos.move(100, -30)
			self.window.blit(self.levelUp[level], pos)
			pygame.display.update()
			pygame.time.delay(200)

	def die(self, id, winW, winH, item, perso, players, teamList):
		value = id in self.players
		if (value == True):
			level = self.info[id, "level"]
			pos =  self.info[id, "position"]
			pos = pos.move(0, 20)
			self.mp.updateMap(winW, winH, item, perso, players, teamList)
			self.window.blit(self.dies[level], pos)
			self.players.remove(id)
			pygame.display.update()
			pygame.time.delay(100)
			self.mp.updateMap(winW, winH, item, perso, players, teamList)

	def broadcast(self, id):
		self.info[id, "broad"] = 1

	def incantation(self, tab):
		self.incantations[tab[1], tab[2], tab[3]] = tab
		try:
			img = pygame.image.load("../map/icone/unranked.png").convert_alpha()
		except:
			sys.exit("Can't load l'image")
		pos = self.mp.getPosition(int(tab[1]), int(tab[2]))
		pos = pos.move(100, -15)
		self.window.blit(img, pos)
		pygame.display.update()
		pygame.time.delay(100)

	def endIncatation(self, tab):
		i = 4
		while (i < len(tab)):
			self.setLevel(self.incantations[tab[1], tab[2], tab[3]][i], tab[3])
			i += 1

	def getBroadcast(self, id, pos, x, y):
		value = id in self.players
		if (value == True):
			if x == self.info[id, "posX"] and y == self.info[id, "posY"]:
				if self.info[id, "broad"] == 1:
					try:
						img = pygame.image.load("../map/player/broadcast.png").convert_alpha()
					except ValueError:
						sys.exit("Can't load l'image")
					pos = pos.move(35, -80)
					self.window.blit(img, pos)
					self.info[id, "broad"] = 0

	def getShield(self, id, x, y):
		if self.info[id, "shieldStat"] == 1:
			value = id in self.players
			if (value == True):
				if x == self.info[id, "posX"] and y == self.info[id, "posY"]:
					try:
						s = pygame.image.load("../map/player/fork.png").convert_alpha()
					except:
						sys.exit("Can't load l'image")
					pos = self.mp.getPosition(self.info[id, "posX"], self.info[id, "posY"])
					pos = pos.move(70, -5)
					self.window.blit(s, pos)
					self.info[id, "shieldStat"] = 0

	def getPlayer(self, id, x, y):
		if x == self.info[id, "posX"] and y == self.info[id, "posY"]:
                        pos = self.mp.getPosition(self.info[id, "posX"], self.info[id, "posY"])
                        pos = pos.move(105, 15)
			self.window.blit(self.label, (pos[0], pos[1] - 25))
			self.window.blit(self.info[id, "img"], pos)

	def display(self, id, winW, winH):
			value = id in self.players
			if (value == True):
				i = 0
				if len(self.info[id, "egg"]) != 0:
					while (i < len(self.info[id, "egg"])):
                                                pos = self.mp.getPosition(self.eggs[id, self.info[id, "egg"][i]][0], self.eggs[id, self.info[id, "egg"][i]][1])
                                                pos = pos.move(105, 15)
                                                pos = pos.move(self.eggs[id, self.info[id, "egg"][i]][2], self.eggs[id, self.info[id, "egg"][i]][3])
						self.window.blit(self.egg, pos)
						i += 1
			pygame.display.update()


	def createLevelUp(self):
		try:
			self.levelUp[2] = pygame.image.load("../map/icone/bronze.png").convert_alpha()
			self.levelUp[3] = pygame.image.load("../map/icone/silver.png").convert_alpha()
			self.levelUp[4] = pygame.image.load("../map/icone/gold.png").convert_alpha()
			self.levelUp[5] = pygame.image.load("../map/icone/platine.png").convert_alpha()
			self.levelUp[6] = pygame.image.load("../map/icone/diamond.png").convert_alpha()
			self.levelUp[7] = pygame.image.load("../map/icone/challenger.png").convert_alpha()
			self.levelUp[8] = pygame.image.load("../map/icone/master.png").convert_alpha()
		except:
			sys.exit("Can't load l'image")

	def initDie(self):
		try:
			self.dies[1] = pygame.image.load("../map/player/1D.png").convert_alpha()
			self.dies[2] = pygame.image.load("../map/player/1D.png").convert_alpha()
			self.dies[3] = pygame.image.load("../map/player/3D.png").convert_alpha()
			self.dies[4] = pygame.image.load("../map/player/4D.png").convert_alpha()
			self.dies[5] = pygame.image.load("../map/player/5D.png").convert_alpha()
			self.dies[6] = pygame.image.load("../map/player/6D.png").convert_alpha()
			self.dies[7] = pygame.image.load("../map/player/7D.png").convert_alpha()
			self.dies[8] = pygame.image.load("../map/player/7D.png").convert_alpha()
		except:
			sys.exit("Can't load l'image")

	def createPlayer(self):
		try:
			self.character[1, 1] = pygame.image.load("../map/player/1N.png").convert_alpha()
			self.character[1, 2] = pygame.image.load("../map/player/1E.png").convert_alpha()
			self.character[1, 3] = pygame.image.load("../map/player/1S.png").convert_alpha()
			self.character[1, 4] = pygame.image.load("../map/player/1O.png").convert_alpha()
			self.character[1, 5] = pygame.image.load("../map/player/1RN.png").convert_alpha()
			self.character[1, 6] = pygame.image.load("../map/player/1RE.png").convert_alpha()
			self.character[1, 7] = pygame.image.load("../map/player/1RS.png").convert_alpha()
			self.character[1, 8] = pygame.image.load("../map/player/1RO.png").convert_alpha()
			self.character[2, 1] = pygame.image.load("../map/player/2N.png").convert_alpha()
			self.character[2, 2] = pygame.image.load("../map/player/2E.png").convert_alpha()
			self.character[2, 3] = pygame.image.load("../map/player/2S.png").convert_alpha()
			self.character[2, 4] = pygame.image.load("../map/player/2O.png").convert_alpha()
			self.character[3, 1] = pygame.image.load("../map/player/3N.png").convert_alpha()
			self.character[3, 2] = pygame.image.load("../map/player/3E.png").convert_alpha()
			self.character[3, 3] = pygame.image.load("../map/player/3S.png").convert_alpha()
			self.character[3, 4] = pygame.image.load("../map/player/3O.png").convert_alpha()
			self.character[4, 1] = pygame.image.load("../map/player/4N.png").convert_alpha()
			self.character[4, 2] = pygame.image.load("../map/player/4E.png").convert_alpha()
			self.character[4, 3] = pygame.image.load("../map/player/4S.png").convert_alpha()
			self.character[4, 4] = pygame.image.load("../map/player/4O.png").convert_alpha()
			self.character[5, 1] = pygame.image.load("../map/player/5N.png").convert_alpha()
			self.character[5, 2] = pygame.image.load("../map/player/5E.png").convert_alpha()
			self.character[5, 3] = pygame.image.load("../map/player/5S.png").convert_alpha()
			self.character[5, 4] = pygame.image.load("../map/player/5O.png").convert_alpha()
			self.character[6, 1] = pygame.image.load("../map/player/6N.png").convert_alpha()
			self.character[6, 2] = pygame.image.load("../map/player/6E.png").convert_alpha()
			self.character[6, 3] = pygame.image.load("../map/player/6S.png").convert_alpha()
			self.character[6, 4] = pygame.image.load("../map/player/6O.png").convert_alpha()
			self.character[7, 1] = pygame.image.load("../map/player/7N.png").convert_alpha()
			self.character[7, 2] = pygame.image.load("../map/player/7E.png").convert_alpha()
			self.character[7, 3] = pygame.image.load("../map/player/7S.png").convert_alpha()
			self.character[7, 4] = pygame.image.load("../map/player/7O.png").convert_alpha()
			self.character[8, 1] = pygame.image.load("../map/player/8N.png").convert_alpha()
			self.character[8, 2] = pygame.image.load("../map/player/8E.png").convert_alpha()
			self.character[8, 3] = pygame.image.load("../map/player/8S.png").convert_alpha()
			self.character[8, 4] = pygame.image.load("../map/player/8O.png").convert_alpha()
		except:
			sys.exit("Can't load l'image")
