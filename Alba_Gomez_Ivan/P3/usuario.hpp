#ifndef USUARIO_HPP
#define USUARIO_HPP
#include "cadena.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <unistd.h>

class Numero;
class Tarjeta;

class Clave{
public:

	class Incorrecta {
		public:
			Incorrecta(const Clave::Razon r);
			Clave::Razon razon() const;
		private:
			Clave::Razon r_;
	};

	Clave(const char*);
	Cadena clave() const; //devuelve la contraseña cifrada
	enum Razon { CORTA, ERROR_CRYPT };
	bool verifica(const char*) const;
	~Clave();
private:
	Cadena pass_c;
};

class Usuario{
	public:

		class Id_duplicado {
			public:
				Id_duplicado(const Cadena&);
				const Cadena& idd() const;
			private:
				Cadena idd_;
		};

	typedef std::map<Numero, Tarjeta*> Tarjetas;
	typedef std::unordered_map<Articulo*, unsigned> Articulos;
	Usuario(const Cadena&_id, const Cadena& _nomb, const Cadena& _apell, const Cadena& _direcc, const Clave& _pass);
	Usuario(const Usuario& that) = delete;
	Usuario& operator =(const Usuario &) = delete;
	const Cadena& id() const noexcept { return ID_; }
	const Cadena& nombre() const noexcept { return nombre_; }
	const Cadena& apellidos() const noexcept { return apell_; }
	const Cadena& direccion() const noexcept { return direcc_; }
	const Tarjetas& tarjetas() const noexcept { return tarjetas_; }
	const size_t n_articulos()const noexcept { return n_articulos_; }
	const Articulos& compra() const noexcept { return articulos_; }
	void es_titular_de(const Tarjeta&); 	// Se le asocia una tarjeta
	void no_es_titular_de(Tarjeta&); 		//Se desasocia una tarjeta
	void compra(const Articulo& a, size_t cant = 1);
	friend std::ostream& operator << (std::ostream& os, const Usuario &u) noexcept;
	~Usuario();
private:
	Cadena ID_, nombre_, apell_, direcc_;
	Clave pass_;
	Tarjetas tarjetas_;
	Articulos articulos_;
	size_t n_articulos_;
	static std::unordered_set<Cadena> registrados;
};

std::ostream& operator <<(std::ostream& os, const Usuario& u) noexcept;
void mostrar_carro (std::ostream& os, const Usuario& u);

#endif