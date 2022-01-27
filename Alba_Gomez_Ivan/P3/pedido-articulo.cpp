#include "pedido-articulo.hpp"

using namespace std;

LineaPedido::LineaPedido(double pr, unsigned c) : precio_(pr), cantidad_(c) {}

std::ostream& operator <<(std::ostream& os, const LineaPedido& p) {
	os << fixed << setprecision(2) << p.precio_venta() << " €\t" << p.cantidad();
	return os;
}

bool OrdenaPedidos::operator()(const Pedido* p1,const Pedido* p2) const { return (p1->numero() < p2->numero()); }

void Pedido_Articulo::pedir (Pedido& ped, Articulo& art, double precio, unsigned cantidad) {
	ped_art_[&ped].insert(make_pair(&art,LineaPedido(precio,cantidad)));
	art_ped_[&art].insert(make_pair(&ped,LineaPedido(precio,cantidad)));
}

void Pedido_Articulo::pedir (Articulo& a, Pedido& p, double precio, unsigned cantidad) {
	pedir(p,a,precio,cantidad);
}

const Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& p) {
	return ped_art_.find(&p)->second;
}

Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo& a) {
	if(art_ped_.find(&a)!=art_ped_.end()) {
		return art_ped_.find(&a)->second;
	}else{
		Pedido_Articulo::Pedidos vacio;
		return vacio;
	}
}

ostream& Pedido_Articulo::mostrarDetallePedidos(ostream& os) const {
	double precio = 0.0;
	for(auto& iter : ped_art_){
		os << "Pedido núm. " << iter.first->numero();
		os << "\tCliente: " << iter.first->tarjeta()->titular()->nombre() << " \n";
		os << "Fecha: " << iter.first->fecha() << iter.second;
		precio += iter.first->total();
	}
	os << "TOTAL VENTAS: " << fixed<< setprecision(2) << precio << " €" << endl;
	return os;
}

ostream& Pedido_Articulo::mostrarVentasArticulos(ostream& os) const {
	for(auto& iter: art_ped_) {
		os << "Ventas de " << "[" << iter.first->referencia() << "]";
		os << "\"" << iter.first->titulo() << "\" \n" << iter.second << endl;
	}
	return os;
}

ostream& operator <<(ostream&os, const Pedido_Articulo::ItemsPedido& ip) {
	double precio = 0;
	Pedido_Articulo::ItemsPedido::const_iterator i;
	os << endl << "====================================================\n" << endl;
	os << " PVP \t Cant. \t Articulo \n";
	os << "====================================================\n" << endl;
	for(i = ip.begin(); i != ip.end(); ++i) {
		os << " " << i->second.precio_venta() << "€\t";
		os << i->second.cantidad() << "\t";
		os << "[" << i->first->referencia() << "] ";
		os << "\"" << i->first->titulo() << "\" " << endl;
		precio = precio + i->second.precio_venta() * i->second.cantidad();
	}
	os << "===================================================\n" << endl;
	os << fixed;
	os << setprecision(2) << precio << " €" << endl;
	return os;
}

ostream& operator <<(ostream&os, const Pedido_Articulo::Pedidos& pedidos) {
	double precio = 0;
	unsigned total = 0;
	Pedido_Articulo::Pedidos::const_iterator i;
	os << "====================================================\n" << endl;
	os << " PVP \t Cant. \t Fecha venta \n";
	os << "====================================================\n" << endl;
	for(auto iter : pedidos){
		os << " " << iter.second.precio_venta() << "€\t";
		os << iter.second.cantidad() << "\t";
		os << iter.first->fecha() << endl;
		precio += (iter.second.precio_venta() * iter.second.cantidad());
		total += iter.second.cantidad();
	}
	os << "====================================================\n" << endl;
	os << fixed;
	os << setprecision(2) << precio << " €\t" << total <<endl ;
	return os;
}