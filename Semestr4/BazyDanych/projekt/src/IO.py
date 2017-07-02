import os
import json
import sys

class stdinInputReader(object):
	def __init__(self):
		self.endOfStream = False
	def next(self):
		line = sys.stdin.readline().strip()
		if line == '':
			self.endOfStream = True
			return line
		return json.loads(line)




