# input
n = 16  # num of verts
dx = 1.0; dy = 0.0  # translation
sx = 0.1; sy = 0.1  # scale

# import stuff
import math

#create sequence of points on the circle
c = [(math.cos(2*math.pi*i/n), math.sin(2*math.pi*i/n)) for i in range(n+1)]

#print sequence
for i in range(n):
    print("%s, %s," % (dx, dy))
    print("%s, %s," % (sx*c[i][0]+dx, sy*c[i][1]+dy))
    print("%s, %s," % (sx*c[i+1][0]+dx, sy*c[i+1][1]+dy))
    print()