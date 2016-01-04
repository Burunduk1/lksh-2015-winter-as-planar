import sys, math

from tkinter import *

# pnt class
class pnt:
  def __init__(self, x, y):
    self.x = x
    self.y = y

  @classmethod
  def byAngle(self, a):
    return pnt(math.cos(a), math.sin(a))
  
  def d2(s):
    return s.x * s.x + s.y * s.y
  def d(s):
    return math.sqrt(s.d2())
  def __add__(a, b):
    return pnt(a.x + b.x, a.y + b.y)
  def __str__(s):
    return "pnt<" + str(s.x) + "," + str(s.y) + ">"

pnt.__sub__ = lambda a, b: pnt(a.x - b.x, a.y - b.y)


# create the root window

maxVertex = 100
vertexR = 5

vertexNum = 0

# граф хранится матрицой смежности
w = [[0] * maxVertex for i in range(maxVertex)]
pos = [[0] * 2 for i in range(maxVertex)]

WAIT = 0
DRAW_GRAPH = 1
whatToDO = WAIT

def saveGraph(e):
	fout = open('graph_save.txt', 'w')
	fout.write(str(vertexNum))
	for i in range(vertexNum):
		for j in range(vertexNum):
			fout.write(str(w[i][j]) + ' ')
	fout.close()
	print('saved')

def update():
	global graph, vertexR, vertexNum, pos
	for i in range(vertexNum):
		graph.create_oval(pos[i][0] - vertexR, pos[i][1] - vertexR, pos[i][0] + vertexR, pos[i][1] + vertexR, fill = "green", outline="#00aa00")
	for i in range(vertexNum):
		for j in range(i):
			if w[i][j]:
				graph.create_line(pos[i][0], pos[i][1], pos[j][0], pos[j][1])
	print('updated')

def loadGraph(e):
	global vertexNum, pos, w
	fin = open('graph_read.txt', 'r')
	vertexNum = int(fin.readline())
	print(vertexNum)
	for i in range(vertexNum):
		x, y = map(int, fin.readline().split())
		pos[i][0] = x
		pos[i][1] = y
	for i in range(vertexNum):
		w[i] = fin.readline().split()
		for j in range(vertexNum):
			w[i][j] = int(w[i][j])

	fin.close()
	for i in range(vertexNum):
		print(w[i])
	update()

# начало графики
root = Tk()

# modify the window
root.title("Visualizer-1.0")
root.geometry("900x500")

addEdgeButton = Button(root, text="Add(Delete) Edge", width = 30, height = 4, bg = "white", fg = "red")
addVertexButton = Button(root, text="Add(Delete) Vertex", width = 30, height = 4, bg = "white", fg = "red")
saveGraphButton = Button(root, text="Save Graph to graph_save.txt", width = 30, height = 4, bg = "white", fg = "red")
loadGraphButton = Button(root, text="Load Graph from graph_read.txt", width = 30, height = 4, bg = "white", fg = "red")

addEdgeButton.grid(row = 0, column = 0)
addVertexButton.grid(row = 0, column = 1)
saveGraphButton.grid(row = 0, column = 2)
loadGraphButton.grid(row = 0, column = 3)

# bind'им кнопки
saveGraphButton.bind("<Button-1>", saveGraph)
loadGraphButton.bind("<Button-1>", loadGraph)

# создание графа

graph = Canvas(root, width = 300, height = 300)
graph.grid(row = 1, column = 0)

# Start the window's event-loop
root.mainloop()