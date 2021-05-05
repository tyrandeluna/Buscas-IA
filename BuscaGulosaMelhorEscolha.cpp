#include <iostream>
#include <list>
#include <algorithm>
#include <queue>

using namespace std;

/*
Arad - 0
Timissoara - 1
Zerind - 2
Sibiu - 3
Oradea - 4
Lugoj - 5
Fagaras - 6
Rimnicu Vilcea - 7
Mehadia - 8
Drobeta - 9
Craiova - 10
Pitesti - 11
Bucharest - 12
Giurgiu - 13
Urziceni - 14
Hirsova - 15
Eforie - 16
Vaslui - 17
Iasi - 18
Neamt - 19
*/
string cidadesString[20] = {
    "Arad",
    "Timisoara",
    "Zerind",
    "Sibiu",
    "Oradea",
    "Lugoj",
    "Fagaras",
    "Rimnicu Vilcea",
    "Mehadia",
    "Drobeta",
    "Craiova",
    "Pitesti",
    "Bucharest",
    "Giurgiu",
    "Urziceni",
    "Hirsova",
    "Eforie",
    "Vaslui",
    "Iasi",
    "Neamt"
};

int cidadesHeuristica[20] = {
    366,
    329,
    374,
    253,
    380,
    244,
    176,
    193,
    241,
    242,
    160,
    100,
    0,
    77,
    80,
    151,
    161,
    199,
    226,
    234
};

class Cidade {
public:
    int idCidade;
    int distancia;
    Cidade(int idCidade);
};

Cidade::Cidade(int id){
    this->idCidade = id;
}

class Mapa {
    int V; // numero de vertices
    list<Cidade> *adj; //ponteiro para um array que contem a lista de adjacencia
public:
    Mapa(int V);
    void AdicionarEstrada(int c1, int c2);
    list<Cidade> MostrarMapa(int v);
    void MontarMapa(Mapa mapa);
    int FindByName(string Name);
    void BuscaGulosaMelhorEscolha(string inicio, string destino);
};

Mapa::Mapa(int v){
    this->V = v;
    adj = new list<Cidade>[v];
}

void Mapa::AdicionarEstrada(int c1, int c2){
    Cidade cidade(c2);
    adj[c1].push_back(cidade);
}

//verifica se o item está na borda
bool Contem(list<int> lista, int elem){
    list<int>::iterator it;
    for(it = lista.begin(); it != lista.end(); ++it){
        if(*it == elem){
            return true;
            break;
        }
    }
    return false;
}

void Mapa::MontarMapa(Mapa mapa){
    mapa.AdicionarEstrada(0, 1);
    mapa.AdicionarEstrada(0, 2);
    mapa.AdicionarEstrada(0, 3);
    mapa.AdicionarEstrada(1, 0);
    mapa.AdicionarEstrada(1, 5);
    mapa.AdicionarEstrada(2, 0);
    mapa.AdicionarEstrada(2, 4);
    mapa.AdicionarEstrada(3, 0);
    mapa.AdicionarEstrada(3, 4);
    mapa.AdicionarEstrada(3, 6);
    mapa.AdicionarEstrada(3, 7);
    mapa.AdicionarEstrada(4, 2);
    mapa.AdicionarEstrada(4, 3);
    mapa.AdicionarEstrada(5, 1);
    mapa.AdicionarEstrada(5, 8);
    mapa.AdicionarEstrada(6, 3);
    mapa.AdicionarEstrada(6, 12);
    mapa.AdicionarEstrada(7, 3);
    mapa.AdicionarEstrada(7, 10);
    mapa.AdicionarEstrada(7, 11);
    mapa.AdicionarEstrada(8, 9);
    mapa.AdicionarEstrada(8, 5);
    mapa.AdicionarEstrada(9, 10);
    mapa.AdicionarEstrada(9, 8);
    mapa.AdicionarEstrada(10, 11);
    mapa.AdicionarEstrada(10, 7);
    mapa.AdicionarEstrada(11, 12);
    mapa.AdicionarEstrada(11, 10);
    mapa.AdicionarEstrada(11, 7);
    mapa.AdicionarEstrada(12, 13);
    mapa.AdicionarEstrada(12, 14);
    mapa.AdicionarEstrada(12, 6);
    mapa.AdicionarEstrada(12, 11);
    mapa.AdicionarEstrada(13, 12);
    mapa.AdicionarEstrada(14, 17);
    mapa.AdicionarEstrada(14, 15);
    mapa.AdicionarEstrada(14, 12);
    mapa.AdicionarEstrada(15, 16);
    mapa.AdicionarEstrada(15, 14);
    mapa.AdicionarEstrada(16, 15);
    mapa.AdicionarEstrada(17, 14);
    mapa.AdicionarEstrada(17, 18);
    mapa.AdicionarEstrada(18, 17);
    mapa.AdicionarEstrada(18, 19);
    mapa.AdicionarEstrada(19, 18);
}

int Mapa::FindByName(string nome){
    list<Cidade> lista;
    int index = 0;
    while(index < 20) {
        if(cidadesString[index] == nome) {
            break;
        }
        index++;
    }

    return index;
}

void Mapa::BuscaGulosaMelhorEscolha(string inicio, string destino) {
	list<int> borda; // lista que simula a fila de prioridade da borda
	bool explorados[V]; // vetor de explorados
    std::list<Cidade>::iterator it;
    int totalHeuristica = 0; // variavel que irá guardar o custo total

    for(int i = 0; i < 20; i++) { // todos explorados são setados como false
        explorados[i] = false;
    }

    int indexInicio = FindByName(inicio); //pega o id da cidade inicio pelo nome
    int indexDestino = FindByName(destino); //pega o id da cidade destino pelo nome

    borda.push_back(indexInicio);

    while(true) {
        int node;

        if(borda.empty()) { // falha se borda for vazio
            break;
        }

        node = borda.front(); // pega primeiro no na borda
        cout << "Cidade atual: " << cidadesString[node] << endl;

        borda.pop_front(); // remove o nó da borda

        explorados[node] = true; // nó é explorado
        cout << "Entrou no explorado: " << cidadesString[node] << " | h(n) = " << cidadesHeuristica[node] << "." << endl;

        totalHeuristica += cidadesHeuristica[node];
        for (it = adj[node].begin(); it != adj[node].end(); ++it){
            if(explorados[it->idCidade] == false && Contem(borda, it->idCidade) == false) { // se nó não foi explorado e não está na borda
                if(it->idCidade == indexDestino) { // se é o destino fim
                    cout << "Destino: " << cidadesString[it->idCidade] << endl;
                    cout << "Total: " << totalHeuristica << endl;
                    return;
                } else { // não é o destino, então add na borda de acordo com o custo
                    if(cidadesHeuristica[it->idCidade] < cidadesHeuristica[borda.front()]) {
                        borda.push_front(it->idCidade);
                        cout << "Entrou na borda: " << cidadesString[it->idCidade] << endl;
                    } else {
                        borda.push_back(it->idCidade); 
                        cout << "Entrou na borda: " << cidadesString[it->idCidade] << endl;
                    }
                }
            }
        }
    }
}

int main(){
    int nVertice = 20;
    Mapa mapa(nVertice); //criando o mapa com 20 cidades

    mapa.MontarMapa(mapa);

    mapa.BuscaGulosaMelhorEscolha("Neamt", "Bucharest");
    // mapa.BuscaGulosaMelhorEscolha("Eforie", "Bucharest");
    // mapa.BuscaGulosaMelhorEscolha("Lugoj", "Bucharest");
    // mapa.BuscaGulosaMelhorEscolha("Arad", "Bucharest");
    // mapa.BuscaGulosaMelhorEscolha("Vaslui", "Bucharest");
    // mapa.BuscaGulosaMelhorEscolha("Oradea", "Bucharest");
    // mapa.BuscaGulosaMelhorEscolha("Iasi", "Bucharest");
    // mapa.BuscaGulosaMelhorEscolha("Timisoara", "Bucharest");
    // mapa.BuscaGulosaMelhorEscolha("Zerind", "Bucharest");
    // mapa.BuscaGulosaMelhorEscolha("Hirsova", "Bucharest");
    
    return 0;
}