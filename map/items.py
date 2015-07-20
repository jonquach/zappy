#!/usr/bin/env python
# -*- coding: Utf-8 -*

import pygame.mixer
import pygame
import time
from pygame.locals import *
import pygame.surfarray as surfarray
import sys, os
import socket

class Items:
	"""docstring for ite"""
	def __init__(self, window, mp):
		self.mp = mp
		self.window = window
		self.dicts = {}
		self.container = []
		self.last = [0, 0, 0, 0, 0, 0, 0]
		self.stat = [0, 0, 0, 0, 0, 0, 0]
		self.item1 = []
		self.positions =[]
		self.initItem()
		self.coords = []

	def initItem(self):
		self.container.append(pygame.image.load("../map/pierre/food.png").convert_alpha())
		self.container.append(pygame.image.load("../map/pierre/p1.png").convert_alpha())
		self.container.append(pygame.image.load("../map/pierre/p2.png").convert_alpha())
		self.container.append(pygame.image.load("../map/pierre/p3.png").convert_alpha())
		self.container.append(pygame.image.load("../map/pierre/p4.png").convert_alpha())
		self.container.append(pygame.image.load("../map/pierre/p5.png").convert_alpha())
		self.container.append(pygame.image.load("../map/pierre/p6.png").convert_alpha())
		self.container.append(pygame.image.load("../map/pierre/egg.png").convert_alpha())

	def addItem(self, x, y, p1, p2, p3, p4, p5, p6, p7):
		value = (x,y) in self.coords
		if value == False:
			self.coords.append((x, y))
		self.dicts[x, y, 0] = p1
		self.dicts[x, y, 1] = p2
		self.dicts[x, y, 2] = p3
		self.dicts[x, y, 3] = p4
		self.dicts[x, y, 4] = p5
		self.dicts[x, y, 5] = p6
		self.dicts[x, y, 6] = p7
		listItem = [p1, p2, p3, p4, p5, p6, p7]
		pos = self.mp.getPosition(x, y)
		pos = pos.move(105, 40)
		pos = pos.move(2, 2)
		value = pos in self.item1
		if (value == False and p1 > 0):
			self.item1.append(pos)
		if (value == True and p1 == 0):
			self.item1.remove(pos)
		#self.setStat(x, y, listItem)

	def getItem1(self, winW, winH):
		self.mp.updateMap(winW, winH)
		for i in self.item1:
			self.window.blit(self.container[0], i)
		pygame.display.update(self.item1)
		return self.item1

	def setStat(self, x, y, listItem):
		i = 0
		while (i != 7):
			if (self.last[i] == 0 and listItem[i] != 0):
				self.stat[i] = 0
				self.last[i] = listItem[i]
			else:
				self.stat[i] = 1
			i += 1

	def displayItem(self, x, y, winW, winH):
		i = 0
		pos = self.mp.getPosition(x, y)
		pos = pos.move(105, 40)
		value = (x, y) in self.coords
		#print (value)
		if value == True:
			while i <= 6:
				if self.dicts[x, y, i] > 0 :
					pos = pos.move(i - 1, i * 2)
					self.positions.append(pos)
					self.window.blit(self.container[i], pos)
				i += 1
		return self.positions
