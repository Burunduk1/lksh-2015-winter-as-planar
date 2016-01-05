# TODO
# Canvas на весь экран(+)
# Запилить хранение объектов(+)
# Добалвение ребер
# Выделение вершин, ребро между которыми хотим добавить
# Запихать координаты в данный прямоугольник

import sys, time, threading

killed = False

from tkinter import *
from math import sqrt

# create the root window

maxVertex = 100
maxEdge = 5050
vertexR = 8
vertexNum = 0
WAIT = 0
ADD_VERTEX = 1
ADD_EDGE = 2
MOVE_VERTEX = 3
PHYSICS_MOVE = 4
whatToDo = WAIT
focus1, focus2 = -1, -1
physicsPowConst = 0.7
physicsDistConst = 100

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
		graph.create_text(pos[i][0] - vertexR - 3, pos[i][1] - vertexR - 3, text=str(i + 1))
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
		l = fin.readline().split()
		for j in range(vertexNum):
			if j < len(l):
				w[i][j] = int(l[j])
			else:
				w[i][j] = 0

	fin.close()
	print('Loaded')
	update()
	whatToDo = WAIT

def interactive(e):
	global whatToDo, vertexNum, pos, w, ADD_VERTEX, ADD_EDGE, focus1, focus2, MOVE_VERTEX, PHYSICS_MOVE
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
			update()
		elif focus2 == -1:
			if focus1 != focus:
				focus2 = focus
				if w[focus1][focus2]:
					w[focus1][focus2] = w[focus2][focus1] = 0
					print('Edge have been removed ', focus1, focus2)
				else:
					w[focus1][focus2] = w[focus2][focus1] = 1
					print('Edge have been added ', focus1, focus2)
				focus1, focus2 = -1, -1
				update()
			else:
				focus1 = focus2 = -1
				update()
				print('Unselected')

vertexToMove = -1
def moveVertexInteractive(e):
	global whatToDo, vertexNum, pos, w, ADD_VERTEX, ADD_EDGE, focus1, focus2, MOVE_VERTEX, vertexToMove
	if whatToDo != MOVE_VERTEX:
		return
	if vertexToMove == -1:
		for i in range(vertexNum):
			ro = sqrt(((pos[i][0] - e.x) ** 2) + ((pos[i][1] - e.y) ** 2))
			if 1.3 * ro <= vertexR:
				vertexToMove = i
				break
	pos[vertexToMove][0] = e.x
	pos[vertexToMove][1] = e.y
	update()

def addVertexStatus(e):
	global whatToDo, ADD_VERTEX
	whatToDo = ADD_VERTEX
	print('Add some verteces')

def addEdgeStatus(e):
	global whatToDo, ADD_EDGE
	whatToDo = ADD_EDGE
	focus1, focus2 = -1, -1
	print('Add some edges')

def moveVertexStatus(e):
	global whatToDo, MOVE_VERTEX, vertexToMove
	whatToDo = MOVE_VERTEX
	vertexToMove = -1
	print('Move vertex!')

def unfocusVertex(e):
	global vertexToMove
	vertexToMove = -1

def interactivAdd():
	global whatToDo, vertexNum, pos, w, ADD_VERTEX, ADD_EDGE, focus1, focus2, MOVE_VERTEX, PHYSICS_MOVE
	while not killed:
		s = list(sys.stdin.readline().split())
		# add_e u v(добавляет ребро u v)
		# delete_e u v(удаляет ребро u v)
		# add_v x y(добавляет новую вершину)
		# ch_pos v x y(изменить позицию вершины v на позицию x, y)
		for i in range(1, len(s)):
			s[i] = int(s[i])
		if s[0] == 'add_e':
			u, v = s[1], s[2]
			if u > vertexNum or v > vertexNum:
				print('Incorrect verteces')
				continue
			u -= 1
			v -= 1
			if w[u][v]:
				print('The edge already exists')
				continue
			w[u][v] = w[v][u] = 1
			print('successefully added')
		elif s[0] == 'delete_e':
			u, v = s[1], s[2]
			if u > vertexNum or v > vertexNum:
				print('Incorrect verteces')
				continue
			u -= 1
			v -= 1
			if not w[u][v]:
				print('Already deleted')
				continue
			w[u][v] = w[v][u] = 0
			print('successefully deleted', u + 1, v + 1)
		elif s[0] == 'add_v':
			x, y = s[1], s[2]
			pos[vertexNum][0], pos[vertexNum][1] = x, y
			vertexNum += 1
		elif s[0] == 'ch_pos':
			v, x, y = s[1], s[2], s[3]
			if v > vertexNum:
				print('Incorrect vertex')
				continue
			v -= 1
			pos[v][0], pos[v][1] = x, y
			print('successefully changed', v, x, y)
		update()

def physicsMoveStart(e):
	print('Nop')
	
# начало графики
root = Tk()

# modify the window
root.title("Visualizer-1.0")
root.geometry("900x500")

buttonWidth = 22
addEdgeButton = Button(root, text="Add(Delete) Edge", width = 15, height = 4, bg = "white", fg = "red")
addVertexButton = Button(root, text="Add(Delete) Vertex", width = 15, height = 4, bg = "white", fg = "red")
saveGraphButton = Button(root, text="Save Graph to graph_save.txt", width = 23, height = 4, bg = "white", fg = "red")
loadGraphButton = Button(root, text="Load Graph from graph_read.txt", width = 25, height = 4, bg = "white", fg = "red")
moveVertexButton = Button(root, text="Move Vertex", width = buttonWidth, height = 4, bg = "white", fg = "red")
startPhysics = Button(root, text="Start Physics", width = buttonWidth, height = 4, bg = "white", fg = "red")

addEdgeButton.grid(row = 0, column = 0)
addVertexButton.grid(row = 0, column = 1)
saveGraphButton.grid(row = 0, column = 2)
loadGraphButton.grid(row = 0, column = 3)
moveVertexButton.grid(row = 0, column = 4)
startPhysics.grid(row = 0, column = 5)

# bind'им кнопки
saveGraphButton.bind("<Button-1>", saveGraph)
loadGraphButton.bind("<Button-1>", loadGraph)
addVertexButton.bind("<Button-1>", addVertexStatus)
addEdgeButton.bind("<Button-1>", addEdgeStatus)
moveVertexButton.bind("<Button-1>", moveVertexStatus)
startPhysics.bind("<Button-1>", physicsMoveStart)

# создание графа

graph = Canvas(root, width = 850, height = 400)
graph.grid(row = 1, column = 0, columnspan = 6)
graph.bind("<Button-1>", interactive)
graph.bind("<B1-Motion>", moveVertexInteractive)
graph.bind("<ButtonRelease-1>", unfocusVertex)

threading.Thread(target=interactivAdd, daemon=True).start()

# Start the window's event-loop
root.mainloop()


