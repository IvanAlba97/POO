#include "cadena.hpp"

using namespace std;

Cadena::Cadena(size_t tam, char s) : s_(new char[tam+1]), tam_(tam) {
	for(int i = 0; i < tam_; i++) s_[i] = s;
	s_[tam_] = '\0';
}

Cadena::Cadena(const Cadena& c) : s_(new char[c.tam_+1]), tam_(c.tam_) {
	strcpy(s_, c.s_);
}

Cadena::Cadena(const char* c) : s_(new char[strlen(c)+1]), tam_(strlen(c)) {
	strcpy(s_, c);
	s_[tam_] = '\0';
}

Cadena::Cadena(Cadena&& c) : s_(new char[c.tam_+1]), tam_(c.tam_) {
	strcpy(s_,c.s_);
	c.s_ = nullptr;
	c.tam_ = 0;
}

Cadena& Cadena::operator =(Cadena&& c) {
	if(this != &c) {
		s_ = c.s_;
		tam_ = c.tam_;
		c.s_ = nullptr;
		c.tam_ = 0;
	}
	return *this;
}

Cadena& Cadena::operator =(const Cadena& c) {
	if(this != &c) {
		delete[] s_;
		tam_ = c.length();
		s_ = new char[tam_ + 1];
		strcpy(s_, c.s_);
	}
	return *this;
}

Cadena& Cadena::operator =(const char* c) {
	delete[] s_;
	tam_ = strlen(c);
	s_ = new char[tam_ + 1];
	strcpy(s_, c);
	return *this;
}

Cadena& Cadena::operator +=(const Cadena& c) {
	tam_ = tam_ + c.length();
	char* aux = new char[tam_ + 1];
	strcpy(aux, s_);
	strcat(aux, c.s_);
	delete[] s_;
	s_ = new char[tam_ + 1];
	strcpy(s_, aux);
	delete[] aux;
	return *this;
}

char Cadena::operator [](size_t pos) const noexcept { return s_[pos]; }

char& Cadena::operator [](size_t pos) noexcept { return s_[pos]; }

char Cadena::at(size_t pos) const {
	if(pos >= tam_) throw out_of_range("Posicion no valida.");
	else return s_[pos];
}

char& Cadena::at(size_t pos) {
	if(pos >= tam_) throw out_of_range("Posicion no valida.");
	else return s_[pos];
}

Cadena Cadena::substr(int pos, size_t tam) const {
	if(tam >= tam_ || pos+tam >= tam_ || pos < 0) throw out_of_range("Fuera de rango.");
	else {
		char* aux = new char[tam + 1];
		memcpy(aux, s_+pos, tam);
		aux[tam] = '\0';
		Cadena cad(aux);
		delete[] aux;
		return cad;
	}
}

Cadena operator +(const Cadena& c1, const Cadena& c2) {
	Cadena aux(c1);
	aux += c2;
	return aux;
}

bool operator ==(const Cadena& c1, const Cadena& c2) { return strcmp(c1.c_str(), c2.c_str()) == 0; }

bool operator !=(const Cadena& c1, const Cadena& c2) { return strcmp(c1.c_str(), c2.c_str()) != 0; }

bool operator >(const Cadena& c1, const Cadena& c2) { return strcmp(c1.c_str(), c2.c_str()) > 0; }

bool operator >=(const Cadena& c1, const Cadena& c2) { return strcmp(c1.c_str(), c2.c_str()) >= 0; }

bool operator <(const Cadena& c1, const Cadena& c2) { return strcmp(c1.c_str(), c2.c_str()) < 0; }

bool operator <=(const Cadena& c1, const Cadena& c2) { return strcmp(c1.c_str(), c2.c_str()) <= 0; }

ostream& operator <<(ostream& o, const Cadena& c) {		//  Inserción
	o << c.c_str();
	return o;
}

istream& operator >>(istream& i, Cadena& c) {			// Extracción
	char cadena[33] = "";
	i.width(33);
	i >> cadena;
	c = cadena;
	return i;
}