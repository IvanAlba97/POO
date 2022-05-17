#ifndef ARTICULO_HPP
#define ARTICULO_HPP
#include "fecha.hpp"
#include "cadena.hpp"
#include <set>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <locale>

class Autor{
public:
	Autor(const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion) noexcept
    : nombre_(nombre), apellidos_(apellidos), direccion_(direccion) {}
	const Cadena& nombre() const noexcept { return nombre_; }
	const Cadena& apellidos() const noexcept { return apellidos_; }
	const Cadena& direccion() const noexcept { return direccion_; }
private:
	Cadena nombre_;
	Cadena apellidos_;
	Cadena direccion_;
};

class Articulo{
public:
	typedef std::set<Autor*> Autores;
	Articulo(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha_publi, const double precio);
	const Cadena referencia() const noexcept { return referencia_; }
	const Cadena& titulo() const noexcept { return titulo_; }
	const Fecha& f_publi() const noexcept { return f_publi_; }
	const double precio() const noexcept { return precio_; }
	double& precio() noexcept { return precio_; }
	const Autores& autores() const noexcept { return autores_; }
	class Autores_vacios{};
	virtual void impresion_especifica(std::ostream&) const = 0;
	virtual ~Articulo() {}
private:
	const Autores autores_;
	Cadena referencia_;
	Cadena titulo_;
	Fecha f_publi_;
	double precio_;
};

std::ostream& operator <<(std::ostream& os, const Articulo& ar) noexcept;

class LibroDigital : public Articulo {
public:
	LibroDigital(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha_publi, const double precio, const Fecha& fExp)
		: Articulo(autores, referencia, titulo, fecha_publi, precio), f_expir_(fExp) {}
	const Fecha f_expir() const noexcept { return f_expir_; }
	void impresion_especifica(std::ostream& os) const;
private:
	const Fecha f_expir_;
};

class ArticuloAlmacenable : public Articulo {
public:
	ArticuloAlmacenable(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha_publi, const double precio, unsigned stock = 0)
		: Articulo(autores, referencia, titulo, fecha_publi, precio), stock_(stock) {}
	const unsigned stock() const noexcept { return stock_; }
	unsigned& stock() noexcept { return stock_; }
protected:
	unsigned stock_;
};

class Libro : public ArticuloAlmacenable {
public:
	Libro(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha_publi, const double precio, unsigned paginas, unsigned stock = 0)
		: ArticuloAlmacenable(autores, referencia, titulo, fecha_publi, precio, stock), n_pag_(paginas) {}
	const unsigned n_pag() const noexcept { return n_pag_; }
	void impresion_especifica(std::ostream& os) const;
private:
	const unsigned n_pag_;
};

class Cederron : public ArticuloAlmacenable {
public:
	Cederron(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha_publi, const double precio, unsigned tamano, unsigned stock = 0)
		: ArticuloAlmacenable(autores, referencia, titulo, fecha_publi, precio, stock), tam_(tamano) {}
	const unsigned tam() const noexcept { return tam_; }
	void impresion_especifica(std::ostream& os) const;
private:
	const unsigned tam_;
};

#endif