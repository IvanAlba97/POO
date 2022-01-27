#ifndef ARTICULO_HPP
#define ARTICULO_HPP
#include "fecha.hpp"
#include "cadena.hpp"

class Articulo {
public:
	Articulo(const Cadena& r, const Cadena& t, const Fecha& f, double p, unsigned s);
	Cadena referencia() const;
	Cadena titulo() const;
	Fecha f_publi() const;
	double precio() const;
	double& precio();
	unsigned stock() const;
	unsigned& stock();
private:
	Cadena referencia_;
	Cadena titulo_;
	Fecha f_publi_;
	double precio_;
	unsigned stock_;
};

std::ostream& operator <<(std::ostream& os, const Articulo& ar) noexcept;

#endif