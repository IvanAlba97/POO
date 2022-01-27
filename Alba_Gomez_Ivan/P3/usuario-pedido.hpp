#ifndef USUARIO_PEDIDO_HPP_
#define USUARIO_PEDIDO_HPP_
#include <map>
#include <set>

class Pedido;
class Usuario;

class Usuario_Pedido {
public:
	typedef std::set<Pedido*> Pedidos;
	typedef std::map<Usuario*, Pedidos> UsuarioP;
	typedef std::map<Pedido*, Usuario*> PedidoU;
	void asocia(Usuario& us, Pedido& ped) { usu_ped_[&us].insert(&ped); ped_usu_[&ped] = &us; }
	void asocia(Pedido& ped, Usuario& us) { asocia(us, ped); }
	Pedidos& pedidos(Usuario& us) { return usu_ped_.find(&us)->second; }
	Usuario* cliente(Pedido& ped) { return ped_usu_.find(&ped)->second; }
private:
	UsuarioP usu_ped_;
	PedidoU ped_usu_;
};

#endif

// El .cpp no hace falta