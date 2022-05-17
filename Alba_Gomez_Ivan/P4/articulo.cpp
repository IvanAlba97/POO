#include "articulo.hpp"
#include "fecha.hpp"
#include "cadena.hpp"

using namespace std;

Articulo::Articulo(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha_publi, const double precio)
 : autores_(autores), referencia_(referencia), titulo_(titulo), f_publi_(fecha_publi), precio_(precio) {
	if(autores.empty()) throw Autores_vacios();
}

std::ostream& operator <<(std::ostream& os, const Articulo& ar) noexcept {
	std::locale::global( std::locale( "" ));
	os<<"["<<ar.referencia()<<"] \"";
	os<<ar.titulo()<<"\", de ";
	const auto& autores = ar.autores();
	auto i = autores.begin();
	os << (*i)->apellidos();
	while (++i != autores.end()) { os << ", " << (*i)->apellidos(); }
	os << ". " << ar.f_publi().anno() << ". " <<fixed<<setprecision(2)<<ar.precio()<<" €\n\t";
	ar.impresion_especifica(os);
	return os;
}

void LibroDigital::impresion_especifica(ostream& os) const {
	os << "A la venta hasta el " << f_expir_ << '.';
}

void Libro::impresion_especifica(ostream& os) const {
	os << n_pag_ << " págs., " << stock_ << " unidades.";
}

void Cederron::impresion_especifica(ostream& os) const {
	os << tam_ << " MB, " << stock_ << " unidades.";
}
