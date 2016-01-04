# TODO
# Canvas на весь экран(+)
# Запилить хранение объектов(+)
# Добалвение ребер
# Выделение вершин, ребро между которыми хотим добавить
# Запихать координаты в данный прямоугольник

import sys, time

from tkinter import *
from math import sqrt

# create the root window

maxVertex = 10
maxEdge = 5050
vertexR = 8
vertexNum = 0
WAIT = 0
ADD_VERTEX = 1
ADD_EDGE = 2
whatToDo = WAIT
focus1, focus2 = -1, -1

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
	global graph, vertexR, vertexNum, pos, focus1, focus2
	graph.delete('all')
	for i in range(vertexNum):
		if i == focus1 or i == focus2:
			VERTS[i] = graph.create_oval(pos[i][0] - vertexR, pos[i][1] - vertexR, pos[i][0] + vertexR, pos[i][1] + vertexR, fill = "red", outline="blue", width=2)
		else:
			VERTS[i] = graph.create_oval(pos[i][0] - vertexR, pos[i][1] - vertexR, pos[i][0] + vertexR, pos[i][1] + vertexR, fill = "red", outline="red", width=2)
	for i in range(vertexNum):
		for j in range(i):
			if w[i][j]:
				EDGES[i] = graph.create_line(pos[i][0], pos[i][1], pos[j][0], pos[j][1])

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
	print('Loaded')
	update()
	whatToDo = WAIT

def interactive(e):
	global whatToDo, vertexNum, pos, w, ADD_VERTEX, ADD_EDGE, focus1, focus2
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
		focus = -1
		for i in range(vertexNum):
			ro = sqrt(((pos[i][0] - e.x) ** 2) + ((pos[i][1] - e.y) ** 2))
			if 1.3 * ro <= vertexR:
				focus = i
				break
		if focus == -1:
			print('Can not find any vertex')
		elif focus1 == -1:
			focus1 = focus
			print('First selected :', focus1)
			update()
		elif focus2 == -1:
			if focus1 != focus:
				if w[focus1][focus]:
					print('The edge already exists')
				else:
					focus2 = focus
					print('Second vertex :', focus1, focus2)
					print('Edge have been added')
					w[focus1][focus2] = w[focus2][focus1] = 1
					focus1, focus2 = -1, -1
					update()
			else:
				focus1 = focus2 = -1
				update()
				print('Unselected')

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