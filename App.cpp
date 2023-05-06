#include <iostream>
using namespace std;

struct Registro{
    float v_punta_pala;
    float v_wind;
    float e_mechanic;
    float e_production;
    int hour;
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

Registro* registro(float puntaPala, float vWind, float eMechanic, float eProducida, int hour){
    Registro* registro = new Registro;
    registro->hour = hour;
    registro->v_punta_pala = puntaPala;
    registro->v_wind = vWind;
    registro->e_mechanic = eMechanic;
    registro->e_production = eProducida;
    registro->sig_reg = NULL;
    return registro;
}

void ingresar_registro(Registro* &posicion, float puntaPala, float vWind, float eMechanic, float eProducida, int hour){
    Registro* nuevo = registro(puntaPala, vWind, eMechanic, eProducida, hour);
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

//Por cada 2000 joules se generan 750MW cada 10minutos
//Cada joule produce 0,375MW
float productionEnergy(float energyMechanic){
     return energyMechanic*0.375;   
}

void lowerEnergy(Aerogenerador* cab){
    Aerogenerador* aux = cab;
    Registro* reg;
    do{
        reg = aux -> sig_reg;
        while(reg != NULL){
            if(reg -> e_production < 0)
                cout << "A ingresado un valor negativo en la energia mecanica." << endl;           
            else if(reg->e_production <= 5000)
                cout << "A las " << reg -> hour << " se tuvo una baja produccion de " << reg -> e_production << endl;
            else
                cout << "A las " << reg ->hour << " se tuvo un buena produccion de " << reg -> e_production << endl;
            reg = reg->sig_reg;
        }
        aux = aux -> sig_aero;
    }while(aux != cab);   
}

float perdidaEnergy(float energy){
    float temp = energy * 0.03;
    cout << "La energia perdidad durante su transportacion a diferentes lugares es de: " << temp << endl;
    cout << "La energia total seria de: " << energy - temp << endl;
    energy -= temp;
    return energy;
}

void mayorEnergy(Aerogenerador* cab){
    Aerogenerador * aux = cab;
    Registro * registro;
    int i = 0;
    float sumaEnergy, mayor = 0, array[15];
    
    do{
        registro = aux -> sig_reg;
        sumaEnergy = 0;
        while(registro != NULL){
            sumaEnergy += registro->e_production;
            array[i] = sumaEnergy;
            registro = registro->sig_reg;
            i++;
        }
        if(mayor < sumaEnergy){
            mayor = sumaEnergy;
        }
        aux = aux -> sig_aero;
    }while(aux != cab);

    i = 0;
    aux = cab;
    while(aux != cab) {
        if(array[i] == mayor){
            cout << "El aerogenerador " << aux -> id << " es el de mayor produccion total de: " << mayor << endl;
        }
        i++;
        aux = aux-> sig_aero;
    }
}

void LeesEnergy(Aerogenerador * cab){
    Aerogenerador * aux = cab;
    Registro * registro;
    int hour, hour1, hour2, hour3, hour4;
    float sumaEnergy1, sumaEnergy2, sumaEnergy3, sumaEnergy4, menor = 0;
    
    do{
        registro = aux->sig_reg;
        while(registro!=NULL){
            if(registro->hour == 6)
                sumaEnergy1 += registro->e_production;
            else if(registro->hour == 12)
                sumaEnergy2 += registro->e_production;
            else if(registro->hour ==18)
                sumaEnergy3 += registro->e_production;
            else if(registro->hour == 24)
                sumaEnergy4 += registro->e_production;
            registro = registro->sig_reg;
        }
        aux = aux-> sig_aero;
    }while(aux!=cab);

    if(sumaEnergy1 < sumaEnergy2 && sumaEnergy1 < sumaEnergy3 && sumaEnergy1 < sumaEnergy4)
        cout<<"La hora con menor produccion de energia fue la hora 6 con un total de: " << sumaEnergy1 <<endl;
    else if(sumaEnergy2 < sumaEnergy1 && sumaEnergy2 < sumaEnergy3 && sumaEnergy2 < sumaEnergy4)
        cout<<"La hora con menor produccion de energia fue la hora 12 con un total de: " << sumaEnergy2 <<endl;
    else if(sumaEnergy3 < sumaEnergy1 && sumaEnergy3 < sumaEnergy2 && sumaEnergy3 < sumaEnergy4)
        cout<<"La hora con menor produccion de energia fue la hora 18 con un total de: " << sumaEnergy3 <<endl;
    else if(sumaEnergy4 < sumaEnergy1 && sumaEnergy4 < sumaEnergy2 && sumaEnergy4 < sumaEnergy3)
        cout<<"La hora con menor produccion de energia fue la hora 24 con un total de: " << sumaEnergy4 <<endl;
}

void reparticleEnergy(float energy){
    //casas(55%), alumbrados(25%), edificaciones publicas(hospitales, gobernacion,)(20%)    
    cout << "La energia total producida en las casas de las personas residentes en la Guajira sera de: " << energy * 0.55 << "MW" << endl;
    cout << "La energia total producida en los alumbrados de las ciudadas de Guajira sera de: " << energy * 0.25 << "MW" << endl;
    cout << "La energia total producida en las edificaciones publicas de la Guajira sera de: " << energy * 0.20 << "MW" << endl;
    cout << "El total de energia que se producio en la guajira fue de: " << energy << endl;
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
        ingresar_registro(aux -> sig_reg, x--, 1, 1, 1, 1);
        aux = aux -> sig_aero;
    }while(aux != cab);
    aux = cab;
    x = 20;

    do{
        ingresar_registro(aux->sig_reg, x--, 1, 1, 1, 1);
        aux = aux->sig_aero;
    }while(aux != cab);
    imprimir(cab);

    return 0;
}