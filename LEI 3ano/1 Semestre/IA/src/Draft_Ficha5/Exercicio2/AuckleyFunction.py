# ackley multimodal function
from numpy import arange
from numpy import exp
from numpy import sqrt
from numpy import cos
from numpy import e
from numpy import pi
from numpy import meshgrid
from matplotlib import pyplot
from mpl_toolkits.mplot3d import Axes3D

# funcao objetivo
def objectivo(x, y):
	return -20.0 * exp(-0.2 * sqrt(0.5 * (x**2 + y**2))) - exp(0.5 * (cos(2 * pi * x) + cos(2 * pi * y))) + e + 20

# define o intervalo para entrada
r_min, r_max = -5.0, 5.0
# amostra o intervalo de entrada uniformemente em incrementos de 0,1
xaxis = arange(r_min, r_max, 0.1)
yaxis = arange(r_min, r_max, 0.1)
# criar uma malha a partir do eixo
x, y = meshgrid(xaxis, yaxis)
# calcula os resultados
results = objectivo(x, y)
# cria um gráfico de superfície com o esquema de cores do jato
figure = pyplot.figure()
axis = figure.gca(projection='3d')
axis.plot_surface(x, y, results, cmap='jet')
# mostra o grafico
pyplot.show()