#ifndef Pedido_Articulo_HPP_
#define Pedido_Articulo_HPP_
#include<iostream>
#include <iomanip>
#include "articulo.hpp"
#include "pedido.hpp"

class LineaPedido{
public:
	explicit LineaPedido(double pr, unsigned c = 1);
	const double precio_venta() const noexcept { return precio_; }
	const unsigned cantidad() const noexcept { return cantidad_; }
private:
	double precio_;
	unsigned cantidad_;
};

std::ostream& operator <<(std::ostream& os, const LineaPedido& p);

class Pedido;
class Articulo;

class OrdenaPedidos : public std::binary_function<Pedido*,Pedido*,bool> {
public:
	bool operator()(const Pedido* p1,const Pedido* p2) const;
};

class OrdenaArticulos : public std::binary_function<Articulo*,Articulo*,bool> {
public:
	bool operator()(const Articulo* a1,const Articulo* a2) const { return (a1->referencia() < a2->referencia()); }
};

class Pedido_Articulo{
public:
	typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
	typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
	typedef std::map<Pedido*, ItemsPedido, OrdenaPedidos> PedArt;
	typedef std::map<Articulo*, Pedidos, OrdenaArticulos> ArtPed;
	void pedir(Pedido& ped, Articulo& art, double precio, unsigned cantidad=1);		// PEDIDO - ARTICULO
	void pedir(Articulo& art, Pedido& ped, double precio, unsigned cantidad=1); 	// ARTICULO - PEDIDO
	const ItemsPedido& detalle(Pedido& p);
	Pedidos ventas(Articulo& a);
	std::ostream& mostrarDetallePedidos(std::ostream& os) const;
	std::ostream& mostrarVentasArticulos(std::ostream& os) const;
private:
	PedArt ped_art_;
	ArtPed art_ped_;
};
std::ostream& operator <<(std::ostream& os,const Pedido_Articulo::ItemsPedido& ip);
std::ostream& operator <<(std::ostream& os,const Pedido_Articulo::Pedidos& p);

#endif