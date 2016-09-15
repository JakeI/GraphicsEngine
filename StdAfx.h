/*
Einstellungen:
Algemain > Zeichensatz > Multibyte-Zeichensatz-Verwenden
CV++ Verzeichnisse > Include verzeichnisse > "C:\A\C_Programme\gluw\Glew and Glut\freeglut\include" (add)
CV++ Verzeichnisse > Include verzeichnisse > "C:\A\C_Programme\gluw\Glew and Glut\glew-1.11.0\include" (add)
Linker > Eingabe > Zusätzliche Abhänighkeiten > "freeglut.lib; glew32.lib" (add)
CV++ Verzeichnisse > Bibliotecsverzeichnisse > "C:\A\C_Programme\gluw\Glew and Glut\glew-1.11.0\lib" (add)
CV++ Verzeichnisse > Bibliotecsverzeichnisse > "C:\A\C_Programme\gluw\Glew and Glut\freeglut\lib" (add)
Copy "C:\A\C_Programme\gluw\Glew and Glut\freeglut.dll" and "C:\A\C_Programme\gluw\Glew and Glut\glew32.dll" to project Folder
*/


#ifndef STDAFX_H
#define STDAFX_H

#include <fstream>
#include <string>
#include <sstream>
#include <cctype>

#include <vector>
#include <map>
#include <list>
#include <queue>
#include <set>

#include <time.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include <algorithm>

// Includeverzeichnisse: "C:\A\C_Programme\glm\glm"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GL/GL.h>

#endif
