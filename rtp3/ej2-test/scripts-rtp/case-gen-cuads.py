from pylab import *

import random

 # Como utilizar
 #Para armar una instancia hay que determinar:
 #			- Un metodo que posicione los elementos : Seccion GENERADORES DE POSICIONES
 #			- Un metodo que asigne de determinada forma las pociones a los gimnasios: Seccion GENERADORES DE POCIONES
 #			- Un metodo que genere lainstancia con lo anterior: Seccion INSTANCIAS
 #
 # Ploteo
 # Para cisualizar lainstancia se debe pasar a la funcion de ploeteo el nombre de la funcion generadora de instancias (verejemplo)


###############################################
#			GENERADORES DE POSICIONES
def randomPositions(n, notin=[]):
	li = []
	x = 1
	while len(li)<n:
		t = 2*pi*rand()
		r = sqrt(randint(0,1000))
		v =(int(r*cos(t)), int(r*sin(t)))

		if v in notin or v in li:
			continue

		li.append(v)

	return li

def randomPositions2(n, notin=[], maxRad=1000, maxXY=100):
	li = []
	x = 1
	while len(li)<n:
		t = 2*pi*rand()
		r = sqrt(randint(0, maxRad))
		v =(int(r*cos(t))+randint(-maxXY,maxXY), int(r*sin(t))+randint(-maxXY,maxXY))

		if v in notin or v in li:
			continue

		li.append(v)

	return li

def circularPositions(n, notin=[], rad_circ=10, dist_anillos = 10):
	li = []
	while n>0:

		noSePisaron = True
		y = 0
		while noSePisaron and n>0	:
			t = y
			v = (int(rad_circ*cos(t)), int(rad_circ*sin(t)))

			if v in notin or v in li:
				rad_circ = rad_circ + dist_anillos
				noSePisaron = False
				continue

			li.append(v)
			n = n-1
			y = y+1

	return li

def circularPositions2(n, rad_circ=10, x=0, y=0):
	li=[]
	incremento = 2*pi / n
	arc=incremento
	for i in range(0, n):
		v = (int(rad_circ*cos(arc)) + x, int(rad_circ*sin(arc)) + y)
		arc = arc + incremento
		li.append(v)
	return li

def circularPositions3(n, rad_c=10, x=0, y=0):
	li=[]
	incremento = 2*pi / n
	arc=incremento
	for i in range(0, n):
		rad_circ = randint(0, rad_c)
		v = (int(rad_circ*cos(arc)) + x, int(rad_circ*sin(arc)) + y)
		arc = arc + incremento
		li.append(v)
	return li

###############################################
#			GENERADORES DE POCIONES

#En base a la cantidadde cada tipo de lugar y la capacidad de mochila
#asigna pociones de forma que hayasolucion (osea que no muera en las podas basicas)

def randomPotions(gyms, pps, k_bag):
	gym_res = []
	pociones_totales = 3*len(pps)

	for gym in gyms:
		pociones = randint(1, min(k_bag, pociones_totales))
		gym_res.append((gym, pociones))
		pociones_totales = pociones_totales - pociones
	return gym_res

def randomPotions2(gyms, poc):
	gym_res = []

	for gym in gyms:
		gym_res.append((gym, poc))
	return gym_res

def kPotions(gyms, k):
	gym_res = [];
	for gym in gyms:
		pociones = k
		gym_res.append((gym, pociones))
	return gym_res

###############################################
#				UTILITARIOS
def plotInstance(i):

	for ((x, y), p) in i[0]:
	    plot(x, y, 'ro')

	for (x, y) in i[1]:
	    plot(x, y, 'bo')

	show()

def saveInstance(instance, file, mode="w"):
	g = instance[0]
	p = instance[1]
	m = instance[2]

	target = open(file, mode)

	target.write(str(len(g))+" "+str(len(p))+" "+str(m)+"\n")

	for gym in g:
		target.write(str(gym[0][0])+" "+str(gym[0][1])+" "+str(gym[1])+"\n")
	for pp in p:
		target.write(str(pp[0])+" "+str(pp[1])+"\n")

	target.close()

###############################################
#				INSTANCIAS

 #Random: Determinado N
 #		  Posiciones random
 #		  Pociones random pero con solucion
 #		  #gyms y #pp random
 #		  mochila K=10
def randomInstance(n):
	cg = randint(1,n-1)
	mochila = 10
	gyms = randomPositions(n-cg)
	pps = randomPositions(n-len(gyms), gyms)
	gymsD = randomPotions(gyms, pps, mochila)

	return gymsD, pps, mochila

 #Disposicio circular: Determinado numero de gimnasios y pp
 #		  Posiciones en forma de anillos concentricos de radios 2, 1.5 1 0.5
 #		  Pociones random pero con solucion
 #		  #gyms y #pp random
 #		  mochila K=10
def circularInstance(cant_gyms, cant_pp):
	mochila = 10
	gyms = circularPositions(cant_gyms,rad_circ=20, dist_anillos= 30)
	pps = circularPositions(cant_pp, notin=gyms, rad_circ=50, dist_anillos = 10)
	gymsD = randomPotions(gyms, pps, mochila)

	return gymsD, pps, mochila

def circularInstance2(cant_gyms, cant_pp):
	mochila = cant_gyms*6
	gyms = circularPositions2(cant_gyms,rad_circ=5)
	pps = circularPositions2(cant_pp, rad_circ=10)
	gymsD = kPotions(gyms,3)

	return gymsD, pps, mochila

 #Mochila de capacidad 0: determinado numero de gimnasios y pp
 #		  Posiciones en forma de anillos concentricos de radios 2, 1.5 1 0.5
 #		  Pociones random pero con solucion
 #		  mochila K=0
def noBagInstance(cant_gyms, cant_pp):
	pass

 #Todos gimnasios: Determinado N (se parametriza cuanto de uno y de otro)
 #		  Posiciones en forma de anillos concentricos de radios 2, 1.5 1 0.5
 #		  Pociones random pero con solucion
 #		  #pp = 0
 #		  mochila K=10
def noPPInstance(n):
	gyms = randomPositions(n)
	gymsD = randomPotions(gyms, pps, 10)
	return gymsD, [], 10

def someWithZeroInstance(n):
	cg = randint(1,n-1)
	mochila = 10
	gyms = randomPositions(n-cg)
	pps = randomPositions(n-len(gyms), gyms)
	
	k = int(n*0.2)
	gymsD = randomPotions(gyms[k:n], pps, mochila)
	gyms0 = kPotions(gyms[1:k], 0)

	return gymsD + gyms0, pps, mochila

def ddInstance(pp = 1, gms = 1):	
	tot = 0

	cants = []

	while len(cants) < 4:
		if gms-tot == 0:
			cants.append(0)
		else:
			r = randint(0, gms-tot)
			tot += r
			cants.append(r)

	#objetos remanentes - se los doy al que popee
	if gms-tot > 0:
		el = cants.pop()
		el+=gms-tot
		cants.append(el)

	powers = []

	poc = 0
	total = 0
		
	cantItLimit = 100
	it = 0
	while len(powers) < 4 and it < cantItLimit:
		canti = cants[len(powers)]

		if canti == 0:
			powers.append(0)
			continue

		div = int(ceil(3*pp/canti))

		if div <= 1:
			powers.append(div*canti)
			continue

		poc = randint(1, div)
		if not poc in powers:
			total += int(poc*canti)
			if total <= int(3*pp):
				powers.append(poc)	
			else:
				powers.append(0)
		
		it+=1
	
	while(len(powers) < 4):
		powers.append(0)
	
	zipeada = zip(cants, powers)
	
	shuffle(zipeada)
	
	unzipeada = zip(*zipeada)
	
	cants = list(unzipeada[0])
	powers = list(unzipeada[1])

	cantsOut = list(cants)
	powersOut = list(powers)
			
	maxRad = 0
	maxXY = 0
	
	gyms = []
	gymPos = []
	gymD = []

	cant1 = cants.pop()
	if cant1 > 0:
		gyms = circularPositions3(cant1,15*cant1,20*cant1,20*cant1)
		gymPos = gyms
		gymD = randomPotions2(gyms, powers.pop())

		maxRad = 15*cant1
		maxXY = 20*cant1

	cant2 = cants.pop()
	if cant2 > 0:
		gyms = circularPositions3(cant2,15*cant2,20*cant2,-20*cant2)
		gymsmPos = gymPos + gyms
		gymD = gymD + randomPotions2(gyms, powers.pop())
		
		if 15*cant2 > maxRad:
			maxRad = 15*cant2
			maxXY = 20*cant2

	cant3 = cants.pop()
	if cant3 > 0:
		gyms = circularPositions3(cant3,15*cant3,-20*cant3,20*cant3)
		gymPos = gymPos + gyms
		gymD = gymD + randomPotions2(gyms, powers.pop())
		
		if 15*cant3 > maxRad:
			maxRad = 15*cant3
			maxXY = 20*cant3

	cant4 = cants.pop()
	if cant4 > 0:
		gyms = circularPositions3(cant4,15*cant4,-20*cant4,-20*cant4)
		gymPos = gymPos + gyms
		gymD = gymD + randomPotions2(gyms, powers.pop())
		
		if 15*cant4 > maxRad:
			maxRad = 15*cant4
			maxXY = 20*cant4

	pps = randomPositions2(pp, gymPos, maxRad, maxXY)

	return gymD, pps, cantsOut, powersOut

###################i############################
#				MAIN

random.seed(45)

fileNameWeak = "familiaWeak.txt"
#fileNameStrong = "familiaStrong.txt"

acum = 0
'''
for i in xrange(5, 16):
	lim = i
	tam = i
	
	for j in xrange(1, tam*2):
		pp = randint(1, tam)
		gms = tam-pp

		while pp*3 < gms:
			pp = randint(1, tam)
			gms = tam-pp
		
		r = ddInstance(pp, gms)

		cants = r[2]
		powers = r[3]
		
		kBag = max(powers) + 3
			
		rOut = (r[0], r[1], kBag)
		open(fileNameWeak, 'a').close()
		saveInstance(rOut,fileNameWeak,"a")

		kBag = sum([p*c for p,c in zip(powers,cants)])
		
		rOut = (r[0], r[1], kBag)
		open(fileNameStrong, 'a').close()
		saveInstance(rOut,fileNameStrong,"a")

		acum = acum + 1
'''
for i in xrange(150, 501, 50):
	lim = i
	tam = i
	
	lim = lim*(0.50)
	lim = int(lim)

	for j in xrange(1, lim):
		pp = randint(1, tam)
		gms = tam-pp

		while pp*3 < gms:
			pp = randint(1, tam)
			gms = tam-pp
		
		r = ddInstance(pp, gms)

		cants = r[2]
		powers = r[3]
		
		kBag = max(powers) + 3
			
		rOut = (r[0], r[1], kBag)
		open(fileNameWeak, 'a').close()
		saveInstance(rOut,fileNameWeak,"a")
		'''
		kBag = sum([p*c for p,c in zip(powers,cants)])
		
		rOut = (r[0], r[1], kBag)
		open(fileNameStrong, 'a').close()
		saveInstance(rOut,fileNameStrong,"a")
		'''
		acum = acum + 1
		 
print(acum)

