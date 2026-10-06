#include <bits/stdc++.h>
#include <random>
using namespace std;

typedef long long ll;                   //Enteros
typedef double nro;                     //Números decimales
typedef vector<nro> lista;              //Lista de números decimales
typedef pair<nro,nro> pareja;           //Duplas de números decimales
typedef pair<nro,int> cli;              //Duplas decimal-entero
typedef vector<pair<nro,int>> clientes; //Lista de duplas decimal-entero
typedef vector<pareja> listaparejas;    //Lista de duplas decimales
typedef vector<bool> listabool;         //Lista de booleanos (Verdadero/Falso)

//Macros declaradas para simplicidad en el código
#define forr(i, a, b) for(ll i = (a); i < (ll) (b); i++)    //Iteración de a a b-1
#define forn(i, n) forr(i, 0, n)                            //Iteración de 0 a n-1
#define SZ(x) int((x).size())
#define pb push_back
#define mp make_pair
#define all(c) (c).begin(),(c).end()

nro MAXN=1000000000;        //Máximo total
vector<ll> fact={1};        //Vector de factoriales, inicializa solo en 0!
std::random_device rd;      //Configuración de un número no determinístico random

//Generador de semilla
// std::mt19937 gen(1);     
std::mt19937 gen(rd());     //Determinación de semilla para números a generar

//Declaración de constantes decimales
nro limbajo=(double)1/12 ,limalto=(double)1/3, limbajo2=(double)5/6;    //Para los servicios
nro infot=(nro)20/60,sufot=(nro)40/60;                                  //Y para la caja
nro mediagr=(nro)10/60,sigmagr=(nro)2/60;
nro infins=(nro)5/60,supins=(nro)10/60;

//Generadores de distribuciones aleatorias para los cobros de servicios e insumos
std::uniform_real_distribution<> sfot(limbajo2,2);              //Gráfica
std::normal_distribution<> sgra(2,0.5);                         //Fotocopiadora
std::uniform_real_distribution<> sins(limbajo,limalto);         //Insumos

//Para los cobros de caja
std::uniform_real_distribution<> cobrofotocopiadora(infot,sufot);
std::normal_distribution<> cobrografica(mediagr,sigmagr);
std::uniform_real_distribution<> cobroinsumos(infins,supins); 



//Manejo de las respuestas finales

struct ans{
    //Estructura que guarda los resultados
    //La espera media y máxima en la ruta de servicio de fotocopia, servicio de gráfica y cajero.
    //	El número medio y máximo de personas en la cola de servicio de fotocopia, servicio de gráfica y en cajero. 
    //	La espera media y máxima en todas las colas para los clientes de las dos rutas.
    //	El tiempo medio total de espera para todos los clientes y el tiempo (numero) medio y máximo número total de clientes en el sistema simulado.
    nro emedfot,emedgra,emedcaj;      //Espera media en cada servicio
    nro permedfot,permedgra;        //Tiempo medio en sistema de cada trayectoria
    nro emaxfot,emaxgra,emaxcaj;      //Espera maxima en cada servicio
    nro permaxfot,permaxgra;        //Tiempo maximo en sistema de cada trayectoria
    nro permtot;                //Medio total de espera entre todos
    
    nro medfot,medgra,medcaj;   //Nro medio de personas en cada cola
    int maxfot,maxgra,maxcaj;  //Nro maximo en cada cola
    
    nro medtot;             //Medio de gente en el sistema
    int maxtot;             //Maximo de gente en el sistema
};

void updatetiempo(ans &elemento, int num,nro time){
    //Guarda en la estructura declarada el dato que se indique
    switch (num){
        case 1:
            elemento.emedfot=time;      //Espera media en fotocopiadora
        break;
        case 2:
            elemento.emedgra=time;      //Espera media en grafica
        break;
        case 3:
            elemento.emedcaj=time;      //Espera media en cajero
        break; 
        case 4:
            elemento.permedfot=time;    //Permanencia media de linea fotocopiadora
        break;
        case 5:
            elemento.permedgra=time;    //Permanencia media de linea grafica
        break;
        case 6:
            elemento.emaxfot=time;      //Espera maxima en fotocopiadora
        break;
        case 7:
            elemento.emaxgra=time;      //Espera maxima en grafica
        break;
        case 8:
            elemento.emaxcaj=time;      //Espera maxima en cajero
        break;
        case 9:
            elemento.permaxfot=time;    //Permanencia maxima de linea fotocopiadora
        break;
        case 10:
            elemento.permaxgra=time;    //Permanencia maxima de linea grafica
        break;
        case 11:
            elemento.permtot=time;      //Permanencia media total
        break;
    }
    return;
}

void updatecantidad(ans &elemento, int n,nro me,int ma){
    //Guarda en la estructura el dato que se indique
    switch (n){
        case 1:
            elemento.medfot=me;      //Media de personas en fila de fotocopiadora
        break;
        case 2:
            elemento.medgra=me;      //Media de personas en fila de grafica
        break;
        case 3:
            elemento.medcaj=me;      //Media de personas en fila de cajero
        break;
        case 4:
            elemento.maxfot=ma;      //Maximo de personas en fila de fotocopiadora
        break;
        case 5:
            elemento.maxgra=ma;      //Maximo de personas en fila de grafica
        break;
        case 6:
            elemento.maxcaj=ma;      //Maximo de personas en fila de cajero
        break;
        case 7:
            elemento.medtot=me;      //Media de personas en sistema
        break;
        case 8:
            elemento.maxtot=ma;      //Maximo de personas en sistema
        break;
    }
    return;
}

void imprimir(ans res){
    //Imprime resultados
    cout<<fixed<<setprecision(2);
    cout<<"RESULTADOS DE LA SIMULACION:"<<"\n";
    cout<<"Tiempo medio de espera en el servicio de fotocopiadora: "<<res.emedfot<<"\n";
    cout<<"Tiempo medio de espera en el servicio de grafica: "<<res.emedgra<<"\n";
    cout<<"Tiempo medio de espera en el cajero: "<<res.emedcaj<<"\n";
    cout<<"Tiempo medio de permanencia en el sistema por el servicio de fotocopiadora: "<<res.permedfot<<"\n";
    cout<<"Tiempo medio de permanencia en el sistema por el servicio de grafica: "<<res.permedgra<<"\n";
    cout<<"Tiempo maximo de espera en el servicio de fotocopiadora: "<<res.emaxfot<<"\n";
    cout<<"Tiempo maximo de espera en el servicio de grafica: "<<res.emaxgra<<"\n";
    cout<<"Tiempo maximo de espera en el cajero: "<<res.emaxcaj<<"\n";
    cout<<"Tiempo maximo de permanencia en el sistema por el servicio de fotocopiadora: "<<res.permaxfot<<"\n";
    cout<<"Tiempo maximo de permanencia en el sistema por el servicio de grafica: "<<res.permaxgra<<"\n";
    cout<<"Tiempo medio de permanencia en el sistema total: "<<res.permtot<<"\n";

    cout<<"Numero medio de personas en el servicio de fotocopiadora: "<<res.medfot<<"\n";
    cout<<"Numero medio de personas en el servicio de grafica: "<<res.medgra<<"\n";
    cout<<"Numero medio de personas en el cajero: "<<res.medcaj<<"\n";
    cout<<"Numero maximo de personas en el servicio de fotocopiadora: "<<res.maxfot<<"\n";
    cout<<"Numero maximo de personas en el servicio de grafica: "<<res.maxgra<<"\n";
    cout<<"Numero maximo de personas en el cajero: "<<res.maxcaj<<"\n";
    cout<<"Numero medio de personas en el sistema: "<<res.medtot<<"\n";
    cout<<"Numero maximo de personas en el sistema: "<<res.maxtot<<"\n";
    
}



//Cálculos de medios y máximos, y restas entre elementos de listas

pair<nro,nro> esperamediaymaxima(lista l){
    //Tomando una lista con tiempos de espera en una cola, recorre la lista calculando su máximo y promedio
    int k=SZ(l);
    nro max=-1,sum=0;
    forn(i,k){                  //Recorro todos los elementos de la lista
        sum+=l[i];              //Los sumo a un acumulado total
        if(max<l[i]) max=l[i];  //Veo el maximo
    }
    sum=sum/k;                  //Promedio y obtengo la media
    return {sum,max};
}

pair<nro,nro> esperamediaymaximacajero(clientes l){
    //Mismo código que la espera media y máxima normal, solo que en este caso obtiene los números de un par
    //Se usa para el caso cajero, cuando los tiempos de esperas se encuentran en una pareja y no "sueltos"
    int k=SZ(l);
    nro max=-1,sum=0;
    forn(i,k){
        sum+=l[i].first;                    //Suma a un acumulado
        if(max<l[i].first) max=l[i].first;  //Calcula máximo
    }
    sum=sum/k;                              //Calcula promedio
    return {sum,max};
}

pair<nro,nro> mediomaxpersonas(clientes llegada, clientes salida){
    //Esta función tiene como finalidad calcular un "promedio pesado" de la cantidad de personas
    //Es decir, contemplar no solo la cantidad de personas presentes, sino el tiempo en ese estado
    //Idea: veo el siguiente evento, actualizo y guardo el estado previo
    int maxi=-1,tam=SZ(llegada),cont=0;
    nro tprevio=0;               
    clientes parciales;                 //Guarda cantidad y tiempo para cada una
    int tfinal=salida[tam-1].first;     //Tiempo del último que se va
    int puntllegada=0,puntsalida=0;     //Cuenta cuántas llegadas y salidas se contabilizaron
    forn(i,2*tam){                      //Para cada elemento de llegada o salida
        //Cuando mi siguiente evento es una llegada (contemplando que tenga llegadas pendientes)
        if(puntllegada<tam and llegada[puntllegada].first<salida[puntsalida].first){
            //Guardo el estado de cantidad de personas y tiempo en el que estaba
            //El primer elemento es el tiempo (momento de llegada - tiempo previo), el segundo la cantidad de personas
            parciales.pb({llegada[puntllegada].first-tprevio,cont});
            //Sumo 1 persona
            cont++;
            //Mi tiempo previo pasa a ser mi llegada
            tprevio=llegada[puntllegada].first;
            //Contabilizo una llegada más
            puntllegada++;
        }else{          //Si el evento es una salida
            //Chequeo si mi cantidad hasta el momento de personas es la máxima
            maxi=max(maxi,cont);                            
            //Guardo mi estado hasta ahora
            parciales.pb({salida[puntsalida].first-tprevio,cont});  
            //Saco una persona
            cont--;
            //Guardo el tiempo previo
            tprevio=salida[puntsalida].first;
            //Contabilizo una salida
            puntsalida++;
        }
    }
    //En la próxima iteración calculo promedio pesado de la cantidad
    //Lo calculo como la sumatoria de cada cantidad multiplicada por el tiempo que estuvo
    nro sumatotal=0;
    forn(i,SZ(parciales)){
        sumatotal+=(parciales[i].first*parciales[i].second);
    }
    //Este resultado es la suma de personas en cada minuto
    //Para calcular el promedio, lo divido por el tiempo final 
    sumatotal=sumatotal/tfinal;
    return {sumatotal,maxi};
}

//Para cada usuario del sistema, se guarda su tiempo de llegada para luego poder compararlo con la salida
lista llegadasxid;
pair<lista,lista> resta(clientes salidas,ans &res){
    //Esta función resta tiempos de llegada y salida totales, obteniendo la permanencia de cada usuario
    pair<lista,lista> rta;  //Tiempos para cada servicio
    //Los IDs pares son de fotocopiadora y van al primer elemento
    //Los IDs impares son de gráfica y van al segundo
    nro medesp=0;       //Acumulado de todos los tiempos
    forn(i,SZ(salidas)){
        if(salidas[i].second % 2){                                      //Cuando es persona del servicio de gráfica
            nro x=salidas[i].first-llegadasxid[salidas[i].second/2];    //Tiempo en el sistema
            rta.second.pb(x);                                           //Guarda en lista correspondiente
            medesp+=x;
        }else{                                                          //Cuando es persona del servicio de fotocopiadora
            nro x=salidas[i].first-llegadasxid[salidas[i].second/2];    //Tiempo en el sistema
            rta.first.pb(x);                                            //Guarda en servicio correspondiente
            medesp+=x;
        }
    }
    //Calculo espera media total entre todos
    medesp=medesp/(SZ(salidas));
    //Guardo resultados en estructura de respuesta
    updatetiempo(res, 11, medesp );
    return rta;         //Devuelvo tiempos totales de cada servicio
}



//Algoritmos utilizados para el merge de listas

cli select_min(vector<clientes> &v, vector<int> &punt){
    cli min=v[0][punt[0]]; int chosen=0;
    forr(i,1,SZ(v)){            //Para cada elemento
        if(v[i][punt[i]].first<min.first){  //Chequea que sea el mínimo. Si lo es, lo guarda
            chosen=i;                       //Lista de la cual viene el mínimo
            min=v[i][punt[i]];              //Valor mínimo
        }
    }
    punt[chosen]++;             //Aumenta el puntero que corresponde
    return min;
}

clientes merge(vector<clientes> &v, vector<int> &punt){
    cli k=select_min(v,punt);
    clientes ans;
    while(k.first != MAXN ){          //Mientras tenga números los meto a mi lista final
        ans.pb(k);
        k=select_min(v,punt);         //Obtengo el mínimo
    }
    return ans;
}

pair<nro,int> select_min_caja(vector<clientes> &v, vector<int> &punt, int &poschosen){
    //Análogo a select_min, pero contemplando que se debe devolver el servicio del cual proviene el usuario
    nro min=v[0][punt[0]].first; int chosen=0;
    forr(i,1,SZ(v)){
        if(v[i][punt[i]].first<min){
            chosen=i;
            min=v[i][punt[i]].first;
        }
    }
    poschosen=chosen;
    punt[chosen]++;
    return {min,v[chosen][punt[chosen]-1].second};
}

clientes mergeCaja(vector<clientes> &v){
    //Análogo a merge, pero el parámetro tipo guarda si el usuario viene de la fotocopiadora o gráfica
    vector<int> punt(SZ(v),0);
    int tipo;
    pair<nro,int> prox=select_min_caja(v,punt,tipo);
    clientes ans;
    while(prox.first!=MAXN){
        ans.pb({prox.first,2*prox.second+tipo});
        prox=select_min_caja(v,punt,tipo);
    }
    return ans;
}



//Cálculos de los números combinatorios utilizados en las llegadas

void init_fact(int n){      //Calcula un vector de factoriales necesarios para realizar números combinatorios
    int pos=1,tam=0;
    while(pos<n){
        fact.pb(fact[pos-1]*pos);   //Agrega pos! al vector de factoriales
        pos++;
    }
    return;
}

nro exp(nro b, int e){      //Algoritmo de exponenciación logarítmico
    if (e == 0) return 1;
    nro p = exp(b, e/2);                //Calcula la raíz de la potencia
    p = (p * p);                        //Multiplica ese resultado
    return (e%2 == 0)? p : (b * p);     //Si e es impar, multiplica por b una vez más
}

ll comb(int k, int n){      //Calculador de números combinatorios
    ll ans=fact[n];
    ans=ans/fact[k];
    ans=ans/fact[n-k];
    return ans;
}



//Cálculo de los tiempos de servicio en cada sector

ll idaux=0;

clientes TiemposDeLlegada1(nro tiempo, nro probl, nro probs){      //Calcula la llegada de tiempos de una persona a un servicio
    //En esta función, se generarán los tiempos de llegada para cada grupo que llega al servicio pertinente
    nro lambda=tiempo*probl*probs;

    //Declaración de las distribuciones
    std::poisson_distribution<> dpoisson((nro)lambda);
    int p=dpoisson(gen);
    std::exponential_distribution<> dexp((nro)lambda/90);

    int llegadas=0;     //Guarda el nro de llegadas de grupos
    nro tac=0;

    clientes rta;
    nro t=dexp(gen);
    tac+=t;
    while(llegadas<p and tac<=tiempo){      //Mientras no me paso de llegadas ni de los 90 minutos
        rta.pb({tac,idaux++});
        llegadasxid.pb(tac);                //Guarda el instante de llegada del grupo
        llegadas++;                         //Aumenta la llegada
        t=dexp(gen);                        //Genera tiempos para la proxima llegada
        tac+=t;
    }
    rta.pb({MAXN,-1});
    return rta;
}

pair<clientes,clientes> TiemposDeLlegada2(nro tiempo, nro probl,int tgrup){      //Calcula la llegada de tiempos de parejas a ambos servicios
    //En esta función, se generarán los tiempos de llegada para cada grupo, y se armarán las listas con las personas que van a cada servicio
    nro lambda=tiempo*probl;

    std::binomial_distribution<> dbinom(1, (nro)0.7);       //Binomial que indica si el usuario va al servicio de fotocopiadora
    std::poisson_distribution<> dpoisson((nro)lambda);
    int p=dpoisson(gen);
    std::exponential_distribution<> dexp((nro)lambda/90);

    int llegadas=0;     //Guarda el nro de llegadas de grupos
    nro tac=0;

    clientes fot,gra;
    nro t=dexp(gen);
    int x;
    tac+=t;
    while(llegadas<p and tac<=tiempo){      //Mientras no me paso de llegadas ni de los 90 minutos
        forn(x,tgrup){                      //Meto a la gente del grupo a la fila que corresponde
            x=dbinom(gen);                  //Veo, si x es 1 va a fotocopiadora y si es 0 va a gráfica
            if(x) fot.pb({tac,idaux++});
            else gra.pb({tac,idaux++});
            llegadasxid.pb(tac);
        }
        llegadas++;
        t=dexp(gen);                        //Genera tiempos para la proxima llegada
        tac+=t;
    }
    fot.pb({MAXN,-1});
    gra.pb({MAXN,-1});
    return {fot,gra};
}

clientes TiemposDeServicioFotocopiadora(clientes tllegada,int cant, ans &res){           //Calcula los tiempos en fotocopiadora.
    int tam=SZ(tllegada);                       //Cantidad de personas
    
    //Para simular las múltiples fotocopiadoras, se arma un multiset que guarda el tiempo en el que se libera cada una de ellas
    multiset<nro> fotocopiadoras; 
    forn(i,cant) fotocopiadoras.insert(0);
    
    lista tespera(tam,0),tatencion(tam,0);              //Guardo espera y atencion de cada persona
    clientes tsalida;                                   //Será el tiempo de llegada + espera + atención
    forn(i,tam){
        nro tat=*fotocopiadoras.begin();                //Se selecciona la próxima fotocopiadora a desocuparse
        fotocopiadoras.erase(fotocopiadoras.begin());   //Se la quita del multiset
        tespera[i]=tat-tllegada[i].first;               //La espera es la diferencia entre lo que llega la persona y sale la anterior
        if(tespera[i]<0){tespera[i]=0;}                 //Si es menor a 0 no hay espera                       
        //Genera el tiempo para cada servicio
        tatencion[i]=sfot(gen);
        tsalida.pb({tllegada[i].first+tespera[i]+tatencion[i],tllegada[i].second});         //Contemplando lo dicho antes, guardo el tiempo de salida para continuar en el sistema
        fotocopiadoras.insert(tsalida[i].first);                                            //Se guarda el próximo instante en el que estará libre
    }
    //Guardo los resultados
    int num=1;
    pair<nro,nro> esperasFinales=esperamediaymaxima(tespera);
    updatetiempo(res,num,esperasFinales.first);
    updatetiempo(res,num+5,esperasFinales.second);
    pair<nro,int> personas = mediomaxpersonas(tllegada,tsalida); //Hay que armar un tcola que suma llegada + espera
    updatecantidad(res,num,personas.first,0);
    updatecantidad(res,num+3,0,personas.second);
    return tsalida;
}

clientes TiemposDeServicioGrafica(clientes tllegada, ans &res){           //Calcula los tiempos en la grafica
    int tam=SZ(tllegada);                           //Cantidad de personas
    lista tespera(tam,0),tatencion(tam,0);          //Guardo espera y atencion de cada persona
    clientes tsalida;                               //Será el tiempo de llegada + espera + atención
    forn(i,tam){
        if(i>0){
            tespera[i]=tsalida[i-1].first-tllegada[i].first;    //La espera es la diferencia entre lo que llega la persona y sale la anterior
            if(tespera[i]<0){tespera[i]=0;}                     //Si es menor a 0 no hay espera
        }
        tatencion[i]=sgra(gen);
        tsalida.pb({tllegada[i].first+tespera[i]+tatencion[i],tllegada[i].second});        //Contemplando lo dicho antes, guardo el tiempo de salida para continuar en el sistema
    }
    //Guardo los resultados
    int num=2;
    pair<nro,nro> esperasFinales=esperamediaymaxima(tespera);
    updatetiempo(res,num,esperasFinales.first);
    updatetiempo(res,num+5,esperasFinales.second);
    pair<nro,int> personas = mediomaxpersonas(tllegada,tsalida); //Hay que armar un tcola que suma llegada + espera
    updatecantidad(res,num,personas.first,0);
    updatecantidad(res,num+3,0,personas.second);
    return tsalida;
}

clientes TiempoEnInsumos(clientes tllegada){              //Calcula tiempo tomando insumos
    clientes tsalida(SZ(tllegada));
    forn(i,SZ(tllegada)){       //Para cada elemento
        nro k=sins(gen);
        tsalida[i].first=tllegada[i].first+k;       //Le sumo un tiempo de insumos
        tsalida[i].second=tllegada[i].second;       //Guardo el servicio del que viene
    }
    return tsalida;
}

clientes TiemposEnCaja(clientes tllegada,ans &res){       //Calcula la atención en la caja
    int cl=SZ(tllegada);
    lista tespera(cl,0),tatencion(cl,0);
    clientes tsalida;      //Salida = Llegada + atención + espera
    forn(i,cl){
        //El tiempo de espera se calcula análogo a los servicios
        if(i>0){
            tespera[i]=tsalida[i-1].first-tllegada[i].first;
            if(tespera[i]<0){tespera[i]=0;}
        }
        //Para el cálculo de la atención se suma la atención por servicios e insumos
        if(tllegada[i].second){         //Es usuario de gráfica
            tatencion[i]=cobrografica(gen);
        }else{                          //Es usuario de fotocopiadora
            tatencion[i]=cobrofotocopiadora(gen);
        }
        tatencion[i]+=cobroinsumos(gen);
        //Guardo tiempo final de salida
        tsalida.pb({tllegada[i].first+tespera[i]+tatencion[i],tllegada[i].second});
    }
    //Guarda resultados
    pair<nro,nro> esperaFinal=esperamediaymaxima(tespera);
    updatetiempo(res,3,esperaFinal.first);
    updatetiempo(res,8,esperaFinal.second);
    pair<nro,int> personas = mediomaxpersonas(tllegada,tsalida); //Hay que armar un tcola que suma llegada + espera
    updatecantidad(res,3,personas.first,0);
    updatecantidad(res,6,0,personas.second);
    return tsalida;
}



int main(){  
    init_fact(5);
    
    ans resultados;
    //Calcula tiempos de llegada
    //De a 1
    clientes fot1=TiemposDeLlegada1(90,0.6,0.7);
    clientes gr1=TiemposDeLlegada1(90,0.6,0.3);
    //Parejas
    pair<clientes,clientes> llegadasauxiliares=TiemposDeLlegada2(90,0.4,2);
    clientes fot2=llegadasauxiliares.first;
    clientes gr2=llegadasauxiliares.second;
    //Merges
    vector<clientes> f={fot1,fot2}; vector<int> p={0,0};
    clientes fotocopiadora=merge(f,p);
    vector<clientes> g={gr1,gr2}; vector<int> c={0,0};
    clientes grafica=merge(g,c);
    
    //Junta todas las llegadas por servicio en una lista
    vector<clientes> lxs={fot1,fot2,gr1,gr2};
    vector<int> pxs(6,0);
    clientes llegadas=merge(lxs,pxs);

    //Calcula los tiempos en servicio con las llegadas juntas
    clientes tiemposFot, tiemposGraf; 
    tiemposFot=TiemposDeServicioFotocopiadora(fotocopiadora,2,resultados);
    tiemposGraf=TiemposDeServicioGrafica(grafica,resultados);

    //Calcula los tiempos en insumos. Deja constancia del ID de cada persona en el sistema para luego
    clientes filaFot,filaGraf;
    filaFot=TiempoEnInsumos(tiemposFot);
    filaGraf=TiempoEnInsumos(tiemposGraf);

    //Ordena los tiempos en cada servicio que pueden estar desacomodados. Guarda ID para los cálculos finales
    sort(all(filaFot)); sort(all(filaGraf));
    filaFot.pb({MAXN,MAXN}); filaGraf.pb({MAXN,MAXN});
    //Hacer el merge de las 2 filas: una funcion nueva o parametrizo la otra
    vector<clientes> filasParaCaja={filaFot,filaGraf};
    clientes filaFinal=mergeCaja(filasParaCaja);

    //Atencion en caja, igual que antes solo que con un if además
    clientes salidas=TiemposEnCaja(filaFinal,resultados);

    //Calcula resultados. Primero obtiene tiempos de permanencia en el sistema, luego calcula con ellos
    pair<lista,lista> tiemposfinalesxservicio=resta(salidas,resultados);
    pair<nro,nro> totfot=esperamediaymaxima(tiemposfinalesxservicio.first);
    pair<nro,nro> totgra=esperamediaymaxima(tiemposfinalesxservicio.second);
    updatetiempo(resultados, 4,totfot.first);
    updatetiempo(resultados, 9,totfot.second);
    updatetiempo(resultados, 5,totgra.first);
    updatetiempo(resultados, 10,totgra.second);

    //Después quedan los cálculos de la cantidad de personas en el sistema
    pair<nro,int> cantidadesTotales = mediomaxpersonas(llegadas,salidas);
    updatecantidad(resultados,7,cantidadesTotales.first,0);
    updatecantidad(resultados,8,0,cantidadesTotales.second);

    imprimir(resultados);

    return 0;
}