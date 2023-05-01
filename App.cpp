#include <iostream>
using namespace std;

struct Registro{
    float v_punta_pala;
    float v_wind;
    float e_mechanic;
    float e_production;
    Registro* sig_reg;
};

struct Aerogenerador{
    int id;
    Aerogenerador* sig_aero;
    Aerogenerador* back_aero;
    Registro* sig_reg;
}*cab = NULL, *final = NULL;



void ingresar_Aerogenerador(int id){
    Aerogenerador* nuevo = new Aerogenerador;
    nuevo->id = id;
    nuevo->sig_reg = NULL;
    if(cab == NULL){
        final = nuevo;
        cab = nuevo;
        final->sig_aero = cab;
        final->back_aero = cab;
        cab->back_aero = final;
        cab->sig_aero = final;
    }
    else{
        final->sig_aero = nuevo;
        nuevo->back_aero = final;
        nuevo->sig_aero = cab;
        final = nuevo;
        cab->back_aero = final;
    }
}

void imprimir(){
    Aerogenerador *actual = new Aerogenerador();
	actual = cab;
	if (cab!=NULL) {
		do {
			cout << '\n' << actual -> id << '\n';
			actual = actual -> sig_aero;
		} while(actual!=cab);
	}else{
		cout << "Lista vacia" << '\n';
	}
}


int main(){
    
    return 0;
}