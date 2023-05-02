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
};
 


void ingresar_Aerogenerador(Aerogenerador* &cab,Aerogenerador* &final, int id){
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

Registro* registro(float puntaPala, float vWind, float eMechanic, float eProducida){
    Registro* registro = new Registro;
    registro->v_punta_pala = puntaPala;
    registro->v_wind = vWind;
    registro->e_mechanic = eMechanic;
    registro->e_production = eProducida;
    registro->sig_reg = NULL;
    return registro;
}

void ingresar_registro(Registro* &posicion, float puntaPala, float vWind, float eMechanic, float eProducida){
    Registro* nuevo = registro(puntaPala, vWind, eMechanic, eProducida);
    Registro* aux;
    if(posicion == NULL){
        posicion = nuevo;
    }else{
        aux = posicion;
        while(aux->sig_reg != NULL){
            aux = aux->sig_reg;
        }
        aux->sig_reg = nuevo;
    }
}

void imprimir(Aerogenerador* cab){
    Aerogenerador *actual = new Aerogenerador;
	Registro* aux;
    actual = cab;

	if (cab!=NULL) {
		do {
			cout << actual -> id << ':';
            aux = actual->sig_reg;
            while(aux != NULL){
                cout << aux-> v_punta_pala << " ";
                aux = aux -> sig_reg;
            }
			actual = actual -> sig_aero;
            cout << endl;
		} while(actual!=cab);
	}else{
		cout << "Lista vacia" << '\n';
	}
}


int main(){
    Aerogenerador* cab = NULL;
    Aerogenerador* final = NULL;
    for (int i = 0; i < 10; i++)
    {
        ingresar_Aerogenerador(cab, final, i);
    }
    int x = 10;
    Aerogenerador* aux = cab;
    do{
        ingresar_registro(aux->sig_reg, x--, 1, 1, 1);
        aux = aux->sig_aero;
    }while(aux != cab);
    aux = cab;
    x = 20;
    do{
        ingresar_registro(aux->sig_reg, x--, 1, 1, 1);
        aux = aux->sig_aero;
    }while(aux != cab);
    imprimir(cab);

    return 0;
}