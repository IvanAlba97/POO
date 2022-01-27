#include "articulo.hpp"
#include "fecha.hpp"
#include "cadena.hpp"
#include <iomanip>
#include <stdlib.h>
#include <iostream>
#include <locale>

using namespace std;

Articulo::Articulo(const Cadena& r, const Cadena& t, const Fecha& f, double p, unsigned s):referencia_(r), titulo_(t), f_publi_(f), precio_(p), stock_(s){}

Cadena Articulo::referencia() const { return referencia_; }

Cadena Articulo::titulo() const { return titulo_; }

Fecha Articulo::f_publi() const { return f_publi_; }

double Articulo::precio() const { return precio_; }

unsigned Articulo::stock() const { return stock_; }

double& Articulo::precio() { return precio_; }

unsigned& Articulo::stock() { return stock_; }

std::ostream& operator <<(std::ostream& os, const Articulo& ar) noexcept {
	std::locale::global( std::locale(""));
	os << "[" << ar.referencia() << "]\"";
	os << ar.titulo() << "\", " << ar.f_publi().anno() << ". " << fixed << setprecision(2) << ar.precio() << " €.";
	return os;
}