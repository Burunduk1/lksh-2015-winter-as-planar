from tkinter import *
import sys

fin = sys.stdin
window = Tk()

canvas = Canvas(master=window, width=500, height=500)
canvas.pack()
 
n = int(fin.readline())

points = []

for i in range(n) :
	x, y = map(int, fin.readline().split())
	x = (x + 1) * 15
	y = (y + 1) * 15
	points.append((x, y))

R = 3
for i in range(n) :
	canvas.create_line(points[i - 1][0], points[i - 1][1], points[i][0], points[i][1], fill = "blue", width = 2)
for i in range(n) :
	x, y = points[i][0], points[i][1]
	canvas.create_oval(x - R, y - R, x + R, y + R, fill = "red")

#n = int(fin.readline())
#
#R = 3
#
#for i in range(n) :
#	x, y = map(int, fin.readline().split())
#	x = (x + 1) * 15
#	y = (y + 1) * 15
#	canvas.create_oval(x - R, y - R, x + R, y + R, fill = "red")
#
#fin.close()

window.mainloop()


