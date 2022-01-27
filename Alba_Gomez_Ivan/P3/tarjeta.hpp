#ifndef TARJETA_HPP
#define TARJETA_HPP
#include "cadena.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"
#include "usuario.hpp"

class Usuario;
class Clave;

class Numero {
public:

	class Incorrecto {
		public:
			Incorrecto(const Numero::Razon r);
			Numero::Razon razon() const;
		private:
			Numero::Razon r_;
	};
	
	enum Razon { LONGITUD, DIGITOS, NO_VALIDO };
	Numero(const Cadena&);
	operator const char*() const;
	const Cadena& num() const { return numero_; }
	~Numero();
private:
	Cadena numero_;
};

void eliminarChar(Cadena& cad, size_t pos);

class Tarjeta{
public:

	class Caducada{
		public:
			Caducada(const Fecha& f);
			const Fecha& cuando() const { return fecha_caducada; }
		private:
			Fecha fecha_caducada;
	}

	class Num_duplicado{
		public:
			Num_duplicado(const Numero&);
			const Numero& que() const;
		private:
			Numero numer_;
	};

	class Desactivada{
		public:
			Desactivada();
	};

	enum Tipo { Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress };
	Tarjeta(const Numero& n, Usuario& usuario, const Fecha& caducidad);
	Tarjeta(const Tarjeta& that) = delete;
	Tarjeta& operator =(const Tarjeta &) = delete;
	const Tarjeta::Tipo& tipo() const { return tipo_; }
	const Numero& numero() const { return numero_; }
	Usuario* titular() const { return usuario_; }
	const Fecha& caducidad() const { return caducidad_; }
	const bool activa() const { return activa_; }
	bool& activa(bool a = true);
	void anula_titular();
	Tipo esTipo();
	friend std::ostream& operator<<(std::ostream& os, const Tarjeta& t);
	~Tarjeta();
private:
	Numero numero_;
	Usuario* const usuario_;
	Fecha caducidad_;
	bool activa_;	// 1(activa), 0(inactiva)
	Tipo tipo_;
};

std::ostream& operator <<(std::ostream& os, const Tarjeta& t);
std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo& tipo);
bool operator <(const Numero& a, const Numero& b);
bool operator <(const Tarjeta& a, const Tarjeta& b);
bool operator >(const Tarjeta& a, const Tarjeta& b);

#endif