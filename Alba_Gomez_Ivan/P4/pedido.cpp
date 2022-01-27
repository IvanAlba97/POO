#include "pedido.hpp"

using namespace std;

unsigned Pedido::N_pedidos = 0;

Pedido::Pedido(Usuario_Pedido& UP, Pedido_Articulo& PA, Usuario& usuario,const Tarjeta& tarjeta, const Fecha& f) 
: n_p_(N_pedidos+1), tarjeta_(&tarjeta), fPedido_(f),importe_(0.) {
	if(usuario.compra().empty()) throw Pedido::Vacio(&usuario);
	if(tarjeta.titular() != &usuario) throw Pedido::Impostor(&usuario);
	if(tarjeta.caducidad() < f) throw Tarjeta::Caducada(tarjeta.caducidad());
	if ( !tarjeta.activa() ) throw Tarjeta::Desactivada();
	auto carro = usuario.compra();
	for(auto& iter : carro) {
		if(ArticuloAlmacenable* AA = dynamic_cast<ArticuloAlmacenable*>(iter.first)) {
			if(iter.second > AA->stock()) {
				const_cast<Usuario::Articulos&>(usuario.compra()).clear();
				throw SinStock(iter.first);
			}
		} else {
			if(LibroDigital* LD = dynamic_cast<LibroDigital*>(iter.first)) {
				if(LD->f_expir() < f) { usuario.compra(*iter.first, 0); }
			}
		}
	}
	if(usuario.compra().empty()) throw Vacio(&usuario); //Comprobramos si se ha quedado vacío
	UP.asocia(*this, usuario);
	carro = usuario.compra();
	for(auto& iter : carro) {
		importe_ += (iter.first->precio()) * (iter.second);
		PA.pedir(*this, *iter.first, iter.first->precio(), iter.second);
		if(ArticuloAlmacenable* AA = dynamic_cast<ArticuloAlmacenable*>(iter.first)) {
			AA->stock() -= iter.second;
		}
	}
	const_cast<Usuario::Articulos&>(usuario.compra()).clear();
	n_p_ = ++ N_pedidos;
}

std::ostream& operator<<(std::ostream& os, const Pedido& p){
	os << left;
	os << "Núm. pedido: " << p.numero() << endl;
	os << setw(13) << "Fecha: " << p.fecha() << endl;
	os << setw(13) << "Pagado con: " << p.tarjeta()->tipo() << " nº: " << p.tarjeta()->numero() << endl;
	os << setw(13) << "Importe: " << fixed << setprecision(2) << p.total() << " €" << endl;
	return os;
}

