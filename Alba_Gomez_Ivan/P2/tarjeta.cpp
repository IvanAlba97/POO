#include "tarjeta.hpp"
#include <iomanip>
#include <cstring>
#include <string.h>
#include <cctype>

using namespace std;

bool luhn(const Cadena&);

Numero::Numero(const Cadena& num) {
	char keys[] = "./ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	size_t ii = strcspn (num.c_str(), keys);
	if(ii<num.length()) throw Incorrecto(Razon::DIGITOS);
	char* pch;
	char*aux = new char[30];
	pch = strpbrk (const_cast<char*>(num.c_str()), "1234567890");
	int i = 0;
	while (pch != NULL){
		aux[i++]=*pch;
		pch = strpbrk (pch+1,"1234567890");
	}
	aux[i]='\0';
	Cadena n(aux);
	delete[] aux;
	//si no esta entre 13 y 19 caracteres, incluidos
	if(n.length()>19 || n.length()<13) throw Incorrecto(Razon::LONGITUD);
	//si numero invalido segun el algoritmo de luhn
	if(!luhn(n)) throw Incorrecto(Razon::NO_VALIDO);
	numero_ = n;
}

Numero::~Numero(){}

Numero::operator const char*() const { return numero_.c_str(); }

Numero::Incorrecto::Incorrecto(const Numero::Razon r) : r_(r) {}

Numero::Razon Numero::Incorrecto::razon() const { return r_; }

void eliminarChar(Cadena& cad, size_t pos){
	Cadena nuevo = cad.substr(0, pos);
	//fuera de clase
	if ((pos + 1) < cad.length()) nuevo += Cadena(cad.substr(pos+1, cad.length()));
	cad = move(nuevo);
}

Tarjeta::Tarjeta(const Numero& n, Usuario& u, const Fecha& f) : numero_(n), usuario_(&u), caducidad_(f), activa_(1), tipo_(esTipo()) {
	if (f < Fecha()) throw Caducada(f);
	usuario_->es_titular_de(*this);
}

Tarjeta::~Tarjeta(){ if(usuario_) usuario_->no_es_titular_de(*this); }

std::ostream& operator <<(std::ostream& os, const Tarjeta& t) {
	os << t.tipo() << std::endl << t.numero() << std::endl;
	//Transformar nombre y apellidos en mayúsculas
	Cadena aux = t.titular()->nombre(); //Se asigna nombre a una cadena auxiliar modificable
	int i=0;
	while(aux[i]!='\0') { if (islower(aux[i])) aux[i]=toupper(aux[i]);i++; }
	os << aux << " ";
	i=0;
	aux = t.titular()->apellidos(); //Se asigna apellidos a una cadena auxiliar modificable
	while(aux[i]!='\0') { if (islower(aux[i])) aux[i]=toupper(aux[i]);i++; }
	os << aux << std::endl;
	//Se formatea la fecha para mostrarla
	os << "Caduca: " << std::setfill ('0') << std::setw (2) << t.caducidad().mes() << "/" << std::setw (2) << (t.caducidad().anno() % 100) << std::endl;
	return os;
}

ostream& operator <<(ostream& os, const Tarjeta::Tipo& tipo) {
	switch(tipo) {
		case Tarjeta::VISA: os << "VISA"; break;
		case Tarjeta::Mastercard: os << "Mastercard"; break;
		case Tarjeta::Maestro: os << "Maestro"; break;
		case Tarjeta::JCB: os << "JCB"; break;
		case Tarjeta::AmericanExpress: os << "AmericanExpress"; break;
		case Tarjeta::Otro: os << "Otro"; break;
		default: os << "Error";
	}
	return os;
}

bool operator <(const Numero& a, const Numero& b) { return strcmp(a, b) < 0; }

bool operator <(const Tarjeta& a, const Tarjeta& b) { return a.numero() < b.numero(); }

bool operator >(const Tarjeta& a, const Tarjeta& b) { return b.numero() < a.numero(); }

bool& Tarjeta::activa(bool a) { 
	activa_ = a;
	return activa_;
}

Tarjeta::Caducada::Caducada(const Fecha& f) : fecha_caducada(f) {}

Tarjeta::Num_duplicado::Num_duplicado(const Numero& n) : numer_(n) {}

const Numero& Tarjeta::Num_duplicado::que() const { return numer_; }

Tarjeta::Desactivada::Desactivada(){}

void Tarjeta::anula_titular(){
	activa_=false;
	const_cast<Usuario*&>(usuario_) = nullptr;
}

Tarjeta::Tipo Tarjeta::esTipo(){
	int a = atoi(numero_.num().substr(0, 2).c_str());
	switch(a/10){
		case 3:
			if(a == 34 || a == 37) return Tarjeta::AmericanExpress;
			else return Tarjeta::JCB;
			break;
		case 4:
			return Tarjeta::VISA;
			break;
		case 5:
			return Tarjeta::Mastercard;
			break;
		case 6:
			return Tarjeta::Maestro;
			break;
		default:
			return Tarjeta::Otro;
	}
}