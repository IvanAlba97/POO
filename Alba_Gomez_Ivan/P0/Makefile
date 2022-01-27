VPATH=../Tests-auto:.
#compilador
CXX=clang++
#banderas del compilador
CPPFLAGS = -I../Tests-auto -I. -DP0
CXXFLAGS = -std=c++17 -g -Wall -pedantic
#-fmax-errors=15
#LDFLAGS =
#ficheros creados
EJECUTABLES =test-fechacadena-auto test-fechacadena-consola 
OBJETOS = test-fechacadena-auto.o test-fechacadena-consola.o fecha.o cadena.o
###
all:$(EJECUTABLES)
###
test-fechacadena-auto: test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o fecha.o cadena.o #test-P0-auto.o
	$(CXX) -o $@ $(LDFLAGS) $^

test-fechacadena-consola: test-fechacadena-consola.o fecha.o cadena.o 
	$(CXX) -o $@ $(LDFLAGS) $^

test-fechacadena-auto.o: test-fechacadena-auto.cpp fecha.hpp cadena.hpp

test-fechacadena-consola.o: test-fechacadena-consola.cpp fecha.hpp cadena.hpp

fecha.o: fecha.cpp fecha.hpp

cadena.o: cadena.cpp cadena.hpp

test-caso0-fecha-auto.o test-caso0-cadena-auto.o: test-auto.hpp fecha.hpp cadena.hpp fct.h
###

clean:
	$(RM) $(OBJETOS) $(EJECUTABLES) *~
#*- */
