#include "fecha.hpp"

#include <ctime>

using namespace std;

bool Fecha::fechaValida() const {
	static int diasMes[]= { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if(anno_<AnnoMinimo || anno_>AnnoMaximo) return false;
	if(mes_ < 1 || mes_ > 12) return false;
	if(dia_ < 1 || dia_ > 31) return false;
	if(diasMes[mes_ - 1] < dia_) return false;
	// Es febrero
	if(mes_==2) {
		if(anno_%4 == 0 && (anno_%400 == 0 || anno_%100 != 0)) {
			// Es bisiesto
			if(dia_>29) return false;
			else return true;
		} else {
			if(dia_>28) return false;
			else return true;
		}
	}
	return true;
}

Fecha::Fecha(int dia, int mes, int anno) : dia_(dia), mes_(mes), anno_(anno) {
	time_t tiempo_calendario = time(0);
	tm* tiempo_descompuesto = localtime(&tiempo_calendario);
	int d = tiempo_descompuesto->tm_mday;
	int m = tiempo_descompuesto->tm_mon + 1;
	int a = tiempo_descompuesto->tm_year + 1900;
	if(dia == 0) dia_ = d;
	if(mes == 0) mes_ = m;
	if(anno == 0) anno_ = a;
	if(!fechaValida()) throw Invalida("Fecha no válida.");
}

Fecha::Fecha(const char* cad) {
	time_t tiempo;
	tm *tm;
	tiempo = time(NULL);
	tm = localtime(&tiempo);
	int d, m, a;
	int num = sscanf(cad, "%d/%d/%d", &d, &m, &a);
	if(num != 3) throw Invalida("Formato de cadena incorrecto.");
	if(d == 0) dia_ = tm->tm_mday; else dia_ = d;
	if(m == 0) mes_ = 1 + tm->tm_mon; else mes_ = m;
	if(a == 0) anno_ = 1900 + tm->tm_year; else anno_ = a;
	if(!fechaValida()) throw Invalida("Fecha no válida.");
}

Fecha& Fecha::operator ++() { return *this += 1; }

Fecha& Fecha::operator --() { return *this -= 1; }

Fecha Fecha::operator ++(int) {
	Fecha aux(*this);
	*this += 1;
	return aux;
}

Fecha Fecha::operator --(int) {
	Fecha aux(*this);
	*this -= 1;
	return aux;
}

Fecha Fecha::operator +(int d) const {
	Fecha aux(*this);
	aux += d;
	return aux;
}

Fecha Fecha::operator -(int d) const {
	Fecha aux(*this);
	aux -= d;
	return aux;
}

Fecha& Fecha::operator +=(int d) {
	static int diasPorMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if(d > 0) {
		for(int i = 0; i < d; i++) {
			if(mes_ == 2 && anno_%4 == 0) {		// Bisiesto
				if(dia_ == 29) { dia_ = 1; mes_++; }
				else { dia_++; }
			} else if(diasPorMes[mes_-1] == dia_ && mes_ < 12) { dia_ = 1; mes_++; }
			else if(diasPorMes[mes_-1] == dia_ && mes_ == 12) { dia_ = 1; mes_ = 1; anno_++; }
			else if(diasPorMes[mes_-1] != dia_) { dia_++; }
		}
	} else if(d < 0) {
		for(int i = d; i < 0; i++) {
			if(mes_ == 3 && anno_%4 == 0) {		// Bisiesto
				if(dia_ == 1) { dia_ = 29; mes_--; }
				else { dia_--; }
			} else if(dia_ == 1 && mes_ > 1) { dia_ = diasPorMes[mes_-2]; mes_--; }
			else if(dia_ == 1 && mes_ == 1) { dia_ = diasPorMes[mes_-2]; mes_ = 12; anno_--; }
			else if(dia_ != 1) { dia_--; }
		}
	}
	if(!fechaValida()) throw Invalida ("Fecha no valida en el operator +=().");
	return *this;
}

Fecha& Fecha::operator -=(int d) { *this += (-d); return *this; }

Fecha::operator const char *() const {
	char* aux = new char[40];
	tm f = {};
	f.tm_mday = dia_;
	f.tm_mon = mes_ - 1;
	f.tm_year = anno_ - 1900;
	mktime(&f);
	strftime(aux, 40, "%A %d de %B de %Y", &f);
	return aux;
}

bool operator ==(const Fecha& f1, const Fecha& f2) { return (f1.dia() == f2.dia() && f1.mes() == f2.mes() && f1.anno() == f2.anno()); }

bool operator !=(const Fecha& f1, const Fecha& f2) { return !(f1 == f2); }

bool operator >(const Fecha& f1, const Fecha& f2) {
	if(f1.anno() > f2.anno()) return true;
	else if(f1.anno() == f2.anno() && f1.mes() > f2.mes()) return true;
	else if(f1.anno() == f2.anno() && f1.mes() == f2.mes() && f1.dia() > f2.dia()) return true;
	else return false;
}

bool operator <(const Fecha& f1, const Fecha& f2) { return (f2 > f1); }

bool operator >=(const Fecha& f1, const Fecha& f2) { return !(f1 < f2); }	// !(f1 < f2) = (f1 > f2 || f1 == f2)

bool operator <= (const Fecha& f1, const Fecha& f2) { return !(f1 > f2); }	// !(f1 > f2) = (f1 < f2 || f1 == f2)

