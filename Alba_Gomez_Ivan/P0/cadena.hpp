#ifndef CADENA_HPP_
#define CADENA_HPP_

#include <iostream>
#include <cstring>

class Cadena {
	public:
		// CONSTRUCTORES
		explicit Cadena(size_t tam = 0, char s = ' ');
		Cadena(const Cadena&);
		Cadena(const char*);
		// OPERADORES
		Cadena& operator =(const Cadena&);
		Cadena& operator =(const char*);
		Cadena& operator +=(const Cadena&);
		// OPERADORES DE ACCESO A LA CADENA
		char operator [](size_t) const noexcept;
		char& operator [](size_t) noexcept;
		char at(size_t) const;
		char& at(size_t);
		// MÉTODOS OBSERVADORES
		const size_t length() const noexcept { return tam_; }
		// MÉTODO SUBSTR
		Cadena substr(int, size_t) const;
		~Cadena() { delete[] s_; }
		operator const char*() const { return s_; }
	private:
		char* s_;
		size_t tam_;	// size_t = unsigned int
};

// OPERADORES
Cadena operator +(const Cadena&, const Cadena&);

// OPERADORES BOOLEANOS
bool operator ==(const Cadena&, const Cadena&);
bool operator !=(const Cadena&, const Cadena&);
bool operator >(const Cadena&, const Cadena&);
bool operator >=(const Cadena&, const Cadena&);
bool operator <(const Cadena&, const Cadena&);
bool operator <=(const Cadena&, const Cadena&);

#endif