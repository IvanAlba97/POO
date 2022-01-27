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
		if ( iter.first->stock() < iter.second ) {
			for(auto&i :carro) usuario.compra(*i.first, 0);
			// usuario.compra().clear();
			throw Pedido::SinStock(iter.first);
		}
	}
	UP.asocia(*this, usuario);
	for(auto& iter : carro) {
		importe_ += iter.first->precio() * iter.second;
		PA.pedir(*iter.first, *this, iter.first->precio(), iter.second);
		iter.first->stock() -= iter.second;
	}
	const_cast<Usuario::Articulos&>(usuario.compra()).clear();
	n_p_ = ++ N_pedidos;
}

std::ostream& operator<<(std::ostream& os, const Pedido& p){
	os << left;
	os << "Núm. pedido: " << p.numero() << endl;
	os << setw(13) << "Fecha: " << p.fecha() << endl;
	os << setw(13) << "Pagado con: " << p.tarjeta()->tipo() << " n.o: " << p.tarjeta()->numero() << endl;
	os << setw(13) << "Importe: " << fixed << setprecision(2) << p.total() << " €" << endl;
	return os;
}

