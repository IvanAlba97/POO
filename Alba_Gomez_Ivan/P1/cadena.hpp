#ifndef CADENA_HPP_
#define CADENA_HPP_

#include <iostream>
#include <cstring>

using namespace std;

#include <iterator> 

class Cadena {
	public:
		// TIPOS DENTRO DE CADENA
		typedef char* iterator;
        typedef const char* const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

		// CONSTRUCTORES
		explicit Cadena(size_t tam = 0, char s = ' ');
		Cadena(const Cadena&);
		Cadena(const char*);

		// CONSTRUCTOR DE COPIA CON SEMÁNTICA DE MOVIMIENTO
		Cadena(Cadena&&);

		// OPERADOR DE ASIGNACIÓN CON SEMÁNTICA DE MOVIEMIENTO
		Cadena& operator =(Cadena&&);

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
		const char* c_str() const { return s_; }
		Cadena substr(int, size_t) const;
		/*operator const char*() const { return s_; }*/		// Se elimina en la P1

		// ITERADORES
		inline iterator begin() noexcept { return s_; }
		inline const_iterator begin() const noexcept { return s_; }
	    inline iterator end() noexcept { return s_ + tam_; }
	    inline const_iterator end() const noexcept { return s_ + tam_; }
	    inline const_iterator cbegin() const noexcept { return s_; }
	    inline const_iterator cend() const noexcept { return s_ + tam_; }
	    inline reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
		inline const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
	    inline reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
	    inline const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
	    inline const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }
	    inline const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }

		// DESTRUCTOR
		~Cadena() { delete[] s_; }
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

// OPERADORES DE INSERCIÓN Y EXTRACCIÓN
ostream& operator <<(ostream& o, const Cadena& c);		// Inserción
istream& operator >>(istream& i, Cadena& c);			// Extracción


// P2: HASH
namespace std{
	template <>
	struct hash<Cadena> {
		size_t operator() (const Cadena& cad) const {
			hash<string> hs;
			const char* p = cad.c_str();
			string s(p);
			size_t res = hs(s);
			return res;
		}
	};
}

#endif