# TODO
# Canvas на весь экран(+)
# Запилить хранение объектов
# Добалвение ребер
# Выделение ребер, которые хочешь добавить

import sys, math

from tkinter import *

# create the root window

maxVertex = 100
maxEdge = 5050
vertexR = 8
vertexNum = 0
WAIT = 0
ADD_VERTEX = 1
ADD_EDGE = 2
whatToDo = WAIT

# граф хранится матрицой смежности
w = [[0] * maxVertex for i in range(maxVertex)]
pos = [[0] * 2 for i in range(maxVertex)]

VERTS = [0] * maxVertex
EDGES = [0] * maxEdge

def saveGraph(e):
	global pos, vertexNum, w
	fout = open('graph_save.txt', 'w')
	fout.write(str(vertexNum) + '\n')
	for i in range(vertexNum):
		fout.write(str(pos[i][0]) + ' ' + str(pos[i][1]) + '\n')

	for i in range(vertexNum):
		for j in range(vertexNum):
			fout.write(str(w[i][j]) + ' ')
		fout.write('\n')
	fout.close()
	whatToDo = WAIT
	print('saved')

def update():
	global graph, vertexR, vertexNum, pos
	graph.delete('all')
	for i in range(vertexNum):
		graph.create_oval(pos[i][0] - vertexR, pos[i][1] - vertexR, pos[i][0] + vertexR, pos[i][1] + vertexR, fill = "red", outline="black")
	for i in range(vertexNum):
		for j in range(i):
			if w[i][j]:
				graph.create_line(pos[i][0], pos[i][1], pos[j][0], pos[j][1])

def loadGraph(e):
	global vertexNum, pos, w
	fin = open('graph_read.txt', 'r')
	vertexNum = int(fin.readline())
	for i in range(vertexNum):
		x, y = map(float, fin.readline().split())
		pos[i][0] = x
		pos[i][1] = y
	for i in range(vertexNum):
		w[i] = fin.readline().split()
		for j in range(vertexNum):
			w[i][j] = int(w[i][j])

	fin.close()
	whatToDo = WAIT
	update()

focus1, focus2 = 0, 0

def interactive(e):
	global whatToDo, vertexNum, pos, w, ADD_VERTEX, ADD_EDGE
	if whatToDo == ADD_VERTEX:
		print('Adding vertex...')
		if vertexNum == maxVertex:
			print('Too much verteces...')
		else:
			pos[vertexNum][0] = e.x
			pos[vertexNum][1] = e.y
			vertexNum += 1
			update()
	elif whatToDo == ADD_EDGE:
		print('=)')
		

def addVertexStatus(e):
	global whatToDo, ADD_VERTEX
	whatToDo = ADD_VERTEX
	print('Add some verteces')

def addEdgeStatus(e):
	global whatToDo, ADD_EDGE
	whatToDo = ADD_EDGE
	focus1, focus2 = -1, -1
	print('Add some edges')

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
addVertexButton.bind("<Button-1>", addVertexStatus)
addEdgeButton.bind("<Button-1>", addEdgeStatus)

# создание графа

graph = Canvas(root, width = 850, height = 400)
graph.grid(row = 1, column = 0, columnspan = 4)
graph.bind("<Button-1>", interactive)

# Start the window's event-loop
root.mainloop()