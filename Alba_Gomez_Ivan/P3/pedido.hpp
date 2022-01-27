#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_
#include "usuario.hpp"
#include "tarjeta.hpp"
#include "fecha.hpp"
#include "articulo.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"
#include<iomanip>
#include<iostream>

class Pedido_Articulo;
class Tarjeta;
class Usuario_Pedido;
class Pedido {
public:
	Pedido(Usuario_Pedido& UP, Pedido_Articulo& PA, Usuario& usuario, const Tarjeta& tarjeta, const Fecha& f= Fecha());
	const int numero() const noexcept { return n_p_; }
	const Tarjeta* tarjeta() const noexcept { return tarjeta_; }
	const Fecha fecha() const noexcept { return fPedido_; }
	const double total() const noexcept { return importe_; }
	static unsigned n_total_pedidos() noexcept { return N_pedidos; }

	class Vacio{
		public:
			Vacio(Usuario* us) : us_(us) {}
			Usuario& usuario() const{return *us_;}
		private:
			Usuario* us_;
	};

	class Impostor{
		public:
			Impostor(Usuario* us) : us_(us) {}
			Usuario& usuario() const{return *us_;}
		private:
			Usuario* us_;
	};

	class SinStock{
		public:
			SinStock(Articulo* art) : art_(art) {}
			Articulo& articulo() const{return *art_;}
		private:
			Articulo* art_;
	};

private:
	int n_p_;
	const Tarjeta* tarjeta_;
	Fecha fPedido_;
	double importe_;
	static unsigned N_pedidos;
}

std::ostream& operator <<(std::ostream& os, const Pedido& p);

#endif