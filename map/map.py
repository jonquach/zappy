#!/usr/bin/env python
# -*- coding: Utf-8 -*

import pygame.mixer
import pygame
import time
from pygame.locals import *
import pygame.surfarray as surfarray
import sys, os
import socket

class Map:
	def __init__(self, window, winW, winH):
                try:
                        self.window = window
                        self.winH = winH
                        self.winW = winW
                        self.width = 0
                        self.height = 0
                        self.load = 0
                        self.font = pygame.font.SysFont("monospace", 35)
                        self.label = self.font.render("Team:", 1, (255,255,0))
                        self.floor = pygame.image.load("../map/ground/slice02_02.png").convert_alpha()
                        self.accueil = pygame.image.load("../map/texture/sky.jpg").convert()
                        self.start = self.getStart()
                        pygame.display.set_caption("ZAPPY")
                        self.pos = self.displayMap(10, 10)
                except:
                        sys.exit("Could not load map image")

	def displayMap(self, width, height):
		self.width = width
		self.height = height
		self.window.blit(self.accueil, (0,0))
		a = (self.winW  - 180) / 2
		b = self.winH
		c = 0
		i = 0
		coords = []
		position = self.floor.get_rect()
		position = position.move(a, b)
		while (i <= self.height) :
			while (c <= 40 * self.width):
				position = position.move(65, 35)
				self.window.blit(self.floor, position)
				coords.append(position)
				c += 40
			i += 1
			position = self.getStart()

			position = position.move(-65 * i, 35 * i)
			coords.append(position)
			c = 0
		return coords

	def displayItemMap(self, item, perso, players):
		self.window.blit(self.accueil, (0,0))
		a = (self.winW  - 180) / 2
		b = self.winH
		c = 0
		i = 0
		coords = []
		x = 0
		y = 0
		position = self.floor.get_rect()
		position = position.move(a, b)
		while (i <= self.height) :
			while (c <= 40 * self.width):
				position = position.move(65, 35)
				pos = self.getPosition(x, y)
				self.window.blit(self.floor, position)
				pos = pos.move(105, 40)
				item.displayItem(x, y, self.winW, self.winH)
				j = 0
				while (j < len(players)):
					perso.getBroadcast(players[j], position, x, y)
					perso.getPlayer(players[j], x, y)
					perso.getShield(players[j], x, y)
					j += 1
				coords.append(position)
				c += 40
				x += 1
			i += 1
			position = self.getStart()
			position = position.move(-65 * i, 35 * i)
			coords.append(position)
			y += 1
			x = 0
			c = 0

		return coords

	def getStart(self):
		position = self.floor.get_rect()
		position = position.move((self.winW  - 180) / 2, self.winH)
		return position

	def updateMap(self, winW, winH, item, perso, players, teamList):
		self.winW = winW
		self.winH = winH
		self.pos = self.displayItemMap(item, perso, players)
		y = 0
		x = 10
		for a in teamList:
			self.label = self.font.render(a, 10, (255,0,0))
			self.window.blit(self.label, (x, y))
			if x == 10:
				x += 25
			y += 35
		pygame.display.update(self.pos)

	def clear_case(self, posX, posY):
		position = self.floor.get_rect()
		self.window.blit(self.floor, position, position)
		pygame.display.update()

	def getPosition(self, posX, posY):
		position = self.floor.get_rect()
		position = self.getStart()
		position = position.move(posY * (-65), posY * 35)
		position = position.move(posX * 65, posX * 35)
		return position
