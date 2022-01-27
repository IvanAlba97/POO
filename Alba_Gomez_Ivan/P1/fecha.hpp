#ifndef FECHA_HPP_
#define FECHA_HPP_

#include <iostream>
#include <ctime>
#include <stdio.h>

using namespace std;

class Fecha {
	public:
		// CONSTANTES
		static const int AnnoMinimo = 1902, AnnoMaximo = 2037;

		// CONSTRUCTORES
		explicit Fecha(int dia = 0, int mes = 0, int anno = 0);
		Fecha(const char*);

		// OPERADORES
		Fecha& operator ++();				// ++f -> f.operator++()	(Preincremento)
		Fecha operator ++(int);				// f++ -> f.operator++(0)	(Postincremento)
		Fecha& operator --();				// --f -> f.operator--()	(Predecremento)
		Fecha operator --(int);				// f-- -> f.operator--(0)	(Postdecremento)
		Fecha operator +(int dias) const;	// f+n -> f.operator+(n)
		Fecha operator -(int dias) const;	// f-n -> f.operator-(n)
		Fecha& operator +=(int dias);			// f+=n -> f.operator+=(n)
		Fecha& operator -=(int dias);			// f-=n -> f.operator-=(n)
		/*operator const char*() const;*/	// Se elimina en la P1

		// METODOS OBSERVADORES
		int dia() const noexcept { return dia_; }
		int mes() const noexcept { return mes_; }
		int anno() const noexcept { return anno_; }
		const char* cadena() const;

		// CLASE INVALIDA
		class Invalida {
			public:
				Invalida(const char* motivo) : por_que_(motivo) {}
				const char* por_que() const { return por_que_; }
			private:
				const char* por_que_;
		};
	private:
		int dia_, mes_, anno_;
		bool fechaValida() const;
};

// OPERADORES BOOLEANOS
bool operator ==(const Fecha&, const Fecha&);
bool operator !=(const Fecha&, const Fecha&);
bool operator >(const Fecha&, const Fecha&);
bool operator >=(const Fecha&, const Fecha&);
bool operator <(const Fecha&, const Fecha&);
bool operator <=(const Fecha&, const Fecha&);

// OPERADORES DE INSERCIÓN Y EXTRACCIÓN
ostream& operator <<(ostream& o, const Fecha& f);
istream& operator >>(istream& i, Fecha& f);

#endif