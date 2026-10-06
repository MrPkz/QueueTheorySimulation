#include <bits/stdc++.h>
#include <random>
using namespace std;

#ifdef LOCAL
#define DBG(x) cerr << #x << " = " << (x) << endl
#define RAYA cerr << "===============================" << endl
#else
#define DBG(x)
#define RAYA cerr << "===============================" << endl
#endif

typedef long long ll;
typedef double nro;
typedef vector<nro> lista; 
typedef pair<nro,nro> pareja;
typedef vector<pareja> listaparejas; 
typedef vector<bool> listabool;
#define forr(i, a, b) for(ll i = (a); i < (ll) (b); i++)
#define forn(i, n) forr(i, 0, n)
#define SZ(x) int((x).size())
#define pb push_back
#define mp make_pair
#define all(c) (c).begin(),(c).end()

nro MAXN=1000000000;        //Máximo total
vector<ll> fact={1};        //Vector de factoriales
std::random_device rd;      //Configuración de un número no determinístico random
std::mt19937 gen(1);     //Generador de semilla

//Generadores de distribuciones aleatorias. Primero las constantes
//Para los servicios
nro limbajo=(double)1/12 ,limalto=(double)1/3, limbajo2=(double)5/6;
//Y para la caja
nro infot=(nro)20/60,sufot=(nro)40/60;
nro mediagr=(nro)10/60,sigmagr=(nro)2/60;
nro infins=(nro)5/60,supins=(nro)10/60;
//Para los cobros de servicios e insumos
std::uniform_real_distribution<> sfot(limbajo2,2);
std::normal_distribution<> sgra(2,0.5);
std::uniform_real_distribution<> sins(limbajo,limalto);        //Ver esto
//Para los cobros de caja
std::uniform_real_distribution<> cobrofotocopiadora(infot,sufot);
std::normal_distribution<> cobrografica(mediagr,sigmagr);
std::uniform_real_distribution<> cobroinsumos(infins,supins); 



//Manejo de las respuestas finales

struct ans{
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
    int k=SZ(l);
    nro max=-1,sum=0;
    forn(i,k){                  //Recorro todos los elementos de la lista
        sum+=l[i];              //Los sumo a un acumulado total
        if(max<l[i]) max=l[i];  //Veo el maximo
    }
    sum=sum/k;                  //Promedio y obtengo la media
    return {sum,max};
}

pair<nro,nro> esperamediaymaximacajero(vector<pair<nro,int>> l){
    //Mismo código que la espera media y máxima normal, solo que en este caso obtiene los numeros de un par
    int k=SZ(l);
    nro max=-1,sum=0;
    forn(i,k){
        sum+=l[i].first;
        if(max<l[i].first) max=l[i].first;
    }
    sum=sum/k;
    return {sum,max};
}

pair<nro,int> mediomaxpersonas(lista llegada, lista salida){
    int maxi=-1,tam=SZ(llegada),cont=0;     //En maxi se guarda el maximo, en cont la cantidad de personas en cada momento
    nro tprevio=0;                          //Guarda tiempo previo para hacer los cálculos
    vector<pair<nro,int>> parciales;        //Guarda la cantidad de personas que hay en un cierto intervalo de tiempo. Ej: 2 personas durante un minuto
    int tfinal=salida[tam-1];
    int puntllegada=0,puntsalida=0;
    forn(i,2*tam){
        if(puntllegada<tam and llegada[puntllegada]<salida[puntsalida]){
            parciales.pb({llegada[puntllegada]-tprevio,cont});      //Meto en la lista el intervalo previo
            cont++;                                                 //Sumo 1 llegada
            tprevio=llegada[puntllegada];
            puntllegada++;
        }else{
            maxi=max(maxi,cont);                                //Revisa si el valor que habia hasta ahora fue el maximo
            parciales.pb({salida[puntsalida]-tprevio,cont});    //Meto en la lista el intervalo previo
            cont--;                                             //Saco 1 persona de la cantidad
            tprevio=salida[puntsalida];
            puntsalida++;
        }
    }
    nro sumatotal=0;
    //Se realiza el promedio total de personas
    forn(i,SZ(parciales)){
        sumatotal+=(parciales[i].first*parciales[i].second);
        // cout<<"SUMAPARCIAL: "<<sumatotal<<endl;
    }
    sumatotal=sumatotal/tfinal;
    return {sumatotal,maxi};
}

pair<nro,nro> mediomaxpersonascajero(vector<pair<nro,int>> llegada, vector<pair<nro,int>> salida){
    //El proceso es análogo al otro proceso mediomaxpersonas
    int maxi=-1,tam=SZ(llegada),cont=0;
    nro tprevio=0;
    vector<pair<nro,int>> parciales;
    int tfinal=salida[tam-1].first;
    int puntllegada=0,puntsalida=0;
    forn(i,2*tam){
        if(puntllegada<tam and llegada[puntllegada].first<salida[puntsalida].first){
            parciales.pb({llegada[puntllegada].first-tprevio,cont});
            cont++;
            tprevio=llegada[puntllegada].first;
            puntllegada++;
        }else{
            maxi=max(maxi,cont);
            parciales.pb({salida[puntsalida].first-tprevio,cont});
            cont--;
            tprevio=salida[puntsalida].first;
            puntsalida++;
        }
    }
    nro sumatotal=0;
    forn(i,2*tam){
        sumatotal+=(parciales[i].first*parciales[i].second);
    }
    sumatotal=sumatotal/tfinal;
    return {sumatotal,maxi};
}

pair<nro,int> mediomaxpersonastotal(lista llegada, vector<pair<nro,int>> salida){
    //Análogo al primer proceso mediomaxpersonas, sacando elementos de salida desde un par
    int maxi=-1,tam=SZ(llegada),cont=0;
    nro tprevio=0;
    vector<pair<nro,int>> parciales;
    int tfinal=salida[tam-1].first;
    int puntllegada=0,puntsalida=0;
    forn(i,2*tam){
        if(puntllegada<tam and llegada[puntllegada]<salida[puntsalida].first){
            parciales.pb({llegada[puntllegada]-tprevio,cont});
            cont++;
            tprevio=llegada[puntllegada];
            puntllegada++;
        }else{
            maxi=max(maxi,cont);
            parciales.pb({salida[puntsalida].first-tprevio,cont});
            cont--;
            tprevio=salida[puntsalida].first;
            puntsalida++;
        }
    }
    nro sumatotal=0;
    forn(i,2*tam){
        sumatotal+=(parciales[i].first*parciales[i].second);
    }
    sumatotal=sumatotal/tfinal;
    //cout<<sumatotal<<"\n";
    return {sumatotal,maxi};
}

pair<lista,lista> resta(lista fotocopiadora,lista grafica,vector<pair<nro,int>> salidas,ans &res){      //Resta tiempos de llegada y salida totales
    pair<lista,lista> rta;
    //fotocopiadora par, grafica impar
    nro medesp=0;       //Acumulado de todos los tiempos
    int pf=0,pg=0;
    forn(i,SZ(salidas)){
        if(salidas[i].second % 2){                          //Cuando es persona del servicio de gráfica
            nro x=salidas[i].first-grafica[pg++];
            // cout<<salidas[i].first<<" "<<grafica[pg-1]<<endl;
            rta.second.pb(x);
            // cout<<pg-1<<" "<<x<<endl;
            medesp+=x;
        }else{
            nro x=salidas[i].first-fotocopiadora[pf++];     //Cuando es persona del servicio de fotocopiadora
            rta.first.pb(x);
            medesp+=x;
        }
    }
    //Calculo espera media total entre todos
    medesp=medesp/(SZ(salidas));
    updatetiempo(res, 11, medesp );
    return rta;         //Devuelvo tiempos totales de cada servicio
}



//Algoritmos merge

nro select_min(vector<lista> &v, vector<int> &punt){
    nro min=v[0][punt[0]]; int chosen=0;
    forr(i,1,SZ(v)){            //Para cada elemento
        if(v[i][punt[i]]<min){  //Chequea que sea el mínimo. Si lo es, lo guarda
            chosen=i;
            min=v[i][punt[i]];  
        }
    }
    punt[chosen]++;             //Aumenta el puntero que corresponde
    return min;
}

lista merge(vector<lista> &v, vector<int> &punt){
    nro k=select_min(v,punt);
    lista ans;
    while(k != MAXN ){          //Mientras tenga números los meto a mi lista final
        ans.pb(k);
        k=select_min(v,punt);
    }
    return ans;
}

pair<nro,int> select_min_caja(vector<vector<pair<nro,int>>> &v, vector<int> &punt, int &poschosen){ //Análogo a select_min
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

vector<pair<nro,int>> mergeCaja(vector<vector<pair<nro,int>>> &v){  //Análogo a merge
    vector<int> punt(SZ(v),0);
    int tipo;
    pair<nro,int> prox=select_min_caja(v,punt,tipo);
    vector<pair<nro,int>> ans;
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
        fact.pb(fact[pos-1]*pos);
        pos++;
    }
    return;
}

nro exp(nro b, int e){      //Algoritmo de exponenciación logarítmico
    if (e == 0) return 1;
    nro p = exp(b, e/2);
    p = (p * p);
    return (e%2 == 0)? p : (b * p);
}

ll comb(int k, int n){      //Calculador de números combinatorios
    //cout<<k<<" "<<n;
    ll ans=fact[n];
    //cout<<ans;
    ans=ans/fact[k];
    //cout<<ans;
    ans=ans/fact[n-k];
    //cout<<ans;
    return ans;
}



//Cálculo de los tiempos de servicio en cada sector

lista TiemposDeLlegada1(nro tiempo, nro probl, nro probs){      //Calcula la llegada de tiempos de una persona a un servicio
    //cout<<"ENTRO A FUNCION\n";
    
    //En esta función, se generarán los tiempos de llegada para cada grupo que llega al servicio
    nro lambda=tiempo*probl*probs;
    //cout<<"LAMBDA: "<<lambda<<endl;
    //cout<<"ARME EL LAMBDA\n";

    std::poisson_distribution<> dpoisson((nro)lambda);

    int p=dpoisson(gen);

    std::exponential_distribution<> dexp((nro)lambda/90);

    //cout<<"ARME LA EXPONENCIAL\n";

    int llegadas=0;     //Guarda el nro de llegadas de grupos
    nro tac=0;

    lista rta;
    nro t=dexp(gen);
    tac+=t;
    while(llegadas<p and tac<=tiempo){      //Mientras no me paso de llegadas ni de los 90 minutos
        rta.pb(tac);
        llegadas++;
        t=dexp(gen);                        //Genera tiempos para la proxima llegada
        tac+=t;
        //cout<<tac<<endl;
    }
    rta.pb(MAXN);
    //cout<<"Poisson generado: "<<p;
    //cout<<endl;
    //cout<<"Llegadas contadas: "<<llegadas;
    //cout<<endl;
    return rta;
}

pair<lista,lista> TiemposDeLlegada2(nro tiempo, nro probl,int tgrup){      //Calcula la llegada de tiempos de parejas a ambos servicios
    //cout<<"ENTRO A FUNCION\n";
    
    //En esta función, se generarán los tiempos de llegada para cada grupo que llega al servicio
    nro lambda=tiempo*probl;
    //cout<<"LAMBDA: "<<lambda<<endl;
    //cout<<"ARME EL LAMBDA\n";

    std::binomial_distribution<> dbinom(1, (nro)0.7);
    std::poisson_distribution<> dpoisson((nro)lambda);

    int p=dpoisson(gen);

    std::exponential_distribution<> dexp((nro)lambda/90);

    //cout<<"ARME LA EXPONENCIAL\n";

    int llegadas=0;     //Guarda el nro de llegadas de grupos
    nro tac=0;

    lista fot,gra;
    nro t=dexp(gen);
    int x;
    tac+=t;
    while(llegadas<p and tac<=tiempo){      //Mientras no me paso de llegadas ni de los 90 minutos
        forn(x,tgrup){                      //Meto a la gente del grupo a la fila que corresponde
            x=dbinom(gen);
            if(x) fot.pb(tac);
            else gra.pb(tac);
        }
        llegadas++;
        t=dexp(gen);                        //Genera tiempos para la proxima llegada
        tac+=t;
        //cout<<tac<<endl;
    }
    fot.pb(MAXN);
    gra.pb(MAXN);
    //cout<<"Poisson generado: "<<p;
    //cout<<endl;
    //cout<<"Llegadas contadas Fot: "<<SZ(fot);
    //cout<<"Llegadas contadas Gra: "<<SZ(gra);
    //cout<<endl;
    return {fot,gra};
}

lista TiemposDeServicio(lista tllegada,char s, ans &res){           //Calcula los tiempos en cada servicio
    int tam=SZ(tllegada);                       //Cantidad de personas
    lista tespera(tam,0),tatencion(tam,0);      //Guardo espera y atencion de cada persona
    lista tsalida;                              //Será el tiempo de llegada + espera + atención
    forn(i,tam){
        if(i>0){
            tespera[i]=tsalida[i-1]-tllegada[i];    //La espera es la diferencia entre lo que llega la persona y sale la anterior
            if(tespera[i]<0){tespera[i]=0;}         //Si es menor a 0 no hay espera
        }
        if(s=='U'){                            //Genera el tiempo para cada servicio
            //cout<<"Kgenerado:";
            tatencion[i]=sfot(gen);
            //cout<<tatencion[i]<<endl;
        }else if(s=='N'){
            tatencion[i]=sgra(gen);
        }
        tsalida.pb(tllegada[i]+tespera[i]+tatencion[i]);        //Contemplando lo dicho antes, guardo el tiempo de salida para continuar en el sistema
        // if(s=='U') cout<<tsalida[i]<<endl;
    }
    //Guardo los resultados
    int num=1; if(s=='N') num++;
    pair<nro,nro> esperasFinales=esperamediaymaxima(tespera);
    updatetiempo(res,num,esperasFinales.first);
    updatetiempo(res,num+5,esperasFinales.second);
    pair<nro,int> personas = mediomaxpersonas(tllegada,tsalida);
    updatecantidad(res,num,personas.first,0);
    updatecantidad(res,num+3,0,personas.second);
    return tsalida;
}

vector<pair<nro,int>> TiempoEnInsumos(lista tllegada){              //Calcula tiempo tomando insumos
    vector<pair<nro,int>> tsalida(SZ(tllegada));
    forn(i,SZ(tllegada)){       //Para cada elemento
        //tsalida.pb(0);
        nro k=sins(gen);
        //cout<<"K GENERADO: "<<k<<endl;
        //cout<<limbajo<<limalto<<limbajo2<<endl;
        tsalida[i].first=tllegada[i]+k;     //Le sumo un tiempo de insumos
        tsalida[i].second=i;                //Le asigno servicio para poder dividirlos luego en la lista
    }
    return tsalida;
}

vector<pair<nro,int>> TiemposEnCaja(vector<pair<nro,int>> tllegada,ans &res){       //Calcula la atención en la caja
    int clientes=SZ(tllegada);
    lista tespera(clientes,0),tatencion(clientes,0);
    vector<pair<nro,int>> tsalida;      //Salida = Llegada + atención + espera
    forn(i,clientes){
        //El tiempo de espera se calcula análogo a los servicios
        if(i>0){
            tespera[i]=tsalida[i-1].first-tllegada[i].first;
            if(tespera[i]<0){tespera[i]=0;}
        }
        //Para el cálculo de la atención se suma la atención por servicios e insumos
        if(tllegada[i].second){
            //cout<<"Kgenerado:";
            tatencion[i]=cobrografica(gen);
            //cout<<tatencion[i]<<endl;
        }else{
            tatencion[i]=cobrofotocopiadora(gen);
        }
        tatencion[i]+=cobroinsumos(gen);
        tsalida.pb({tllegada[i].first+tespera[i]+tatencion[i],tllegada[i].second});
    }
    //Guarda resultados
    pair<nro,nro> esperaFinal=esperamediaymaxima(tespera);
    updatetiempo(res,3,esperaFinal.first);
    updatetiempo(res,8,esperaFinal.second);
    pair<nro,int> personas = mediomaxpersonascajero(tllegada,tsalida);
    updatecantidad(res,3,personas.first,0);
    updatecantidad(res,6,0,personas.second);
    return tsalida;
}



int main(){  
    init_fact(5);
    
    ans resultados;
    //Calcula tiempos de llegada
    //De a 1
    lista fot1=TiemposDeLlegada1(90,0.6,0.7);
    lista gr1=TiemposDeLlegada1(90,0.6,0.3);
    //Parejas
    pair<lista,lista> llegadasauxiliares=TiemposDeLlegada2(90,0.4,2);
    lista fot2=llegadasauxiliares.first;
    lista gr2=llegadasauxiliares.second;

    //Merges
    vector<lista> f={fot1,fot2}; vector<int> p={0,0};
    lista fotocopiadora=merge(f,p);
    vector<lista> g={gr1,gr2}; vector<int> c={0,0};
    lista grafica=merge(g,c);
    
    //Junta todas las llegadas por servicio en una lista
    vector<lista> lxs={fot1,fot2,gr1,gr2};
    vector<int> pxs(6,0);
    lista llegadas=merge(lxs,pxs);

    //Calcula los tiempos en servicio con las llegadas juntas
    lista tiemposFot, tiemposGraf; 
    tiemposFot=TiemposDeServicio(fotocopiadora,'U',resultados);
    tiemposGraf=TiemposDeServicio(grafica,'N',resultados);

    //Calcula los tiempos en insumos. Deja constancia del ID de cada persona en el sistema para luego
    vector<pair<nro,int>> filaFot,filaGraf;
    filaFot=TiempoEnInsumos(tiemposFot);
    filaGraf=TiempoEnInsumos(tiemposGraf);

    //Ordena los tiempos en cada servicio que pueden estar desacomodados. Guarda ID para los cálculos finales
    sort(all(filaFot)); sort(all(filaGraf));
    filaFot.pb({MAXN,MAXN}); filaGraf.pb({MAXN,MAXN});
    //Hacer el merge de las 2 filas: una funcion nueva o parametrizo la otra
    vector<vector<pair<nro,int>>> filasParaCaja={filaFot,filaGraf};
    vector<pair<nro,int>> filaFinal=mergeCaja(filasParaCaja);
    //cout<<"FILA CAJA FINAL: "; for(auto u:filaFinal) cout<<u.first<<" "<<u.second<<" - "; cout<<endl;
    //cout<<SZ(filaFinal)<<"\n";

    //Atencion en caja, igual que antes solo que con un if además
    vector<pair<nro,int>> salidas=TiemposEnCaja(filaFinal,resultados);
    //cout<<"FINAL:"<<endl;
    //for(auto u:salidas) cout<<u.first<<endl;
    //cout<<SZ(salidas)<<"\n";

    //Calcula resultados. Primero obtiene tiempos de permanencia en el sistema, luego calcula con ellos
    pair<lista,lista> tiemposfinalesxservicio=resta(fotocopiadora,grafica,salidas,resultados);
    pair<nro,nro> totfot=esperamediaymaxima(tiemposfinalesxservicio.first);
    pair<nro,nro> totgra=esperamediaymaxima(tiemposfinalesxservicio.second);
    updatetiempo(resultados, 4,totfot.first);
    updatetiempo(resultados, 9,totfot.second);
    updatetiempo(resultados, 5,totgra.first);
    updatetiempo(resultados, 10,totgra.second);

    //Después quedan los cálculos de la cantidad de personas en el sistema
    pair<nro,int> cantidadesTotales = mediomaxpersonastotal(llegadas,salidas);
    updatecantidad(resultados,7,cantidadesTotales.first,0);
    updatecantidad(resultados,8,0,cantidadesTotales.second);

    imprimir(resultados);

    return 0;
}