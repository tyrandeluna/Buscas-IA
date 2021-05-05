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

class Cidade {
public:
    int idCidade;
    int distancia;
    Cidade(int idCidade, int distancia);
};

Cidade::Cidade(int id, int distancia){
    this->idCidade = id;
    this->distancia = distancia;
}

class Mapa {
    int V; // numero de vertices
    list<Cidade> *adj; //ponteiro para um array que contem a lista de adjacencia
public:
    Mapa(int V);
    void AdicionarEstrada(int c1, int c2, int distancia);
    list<Cidade> MostrarMapa(int v);
    void MontarMapa(Mapa mapa);
    int FindByName(string Name);
    void BuscaLargura(string inicio, string destino);
};

Mapa::Mapa(int v){
    this->V = v;
    adj = new list<Cidade>[v];
}

void Mapa::AdicionarEstrada(int c1, int c2, int distancia){
    Cidade cidade(c2, distancia);
    adj[c1].push_back(cidade);
}

list<Cidade> Mapa::MostrarMapa(int v){
    std::list<Cidade>::iterator it;
    list<Cidade> lista;
    for(int i = 0; i < v; i++) {
        lista = adj[i];
        for (it = lista.begin(); it != lista.end(); ++it){
            cout << "Cidade: " << i << " | Vizinho: " << it->idCidade << " | Distancia: " << it->distancia << "\n";
        }
    }
    return adj[v];
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
    mapa.AdicionarEstrada(0, 1, 118);
    mapa.AdicionarEstrada(0, 2, 75);
    mapa.AdicionarEstrada(0, 3, 140);
    mapa.AdicionarEstrada(1, 0, 118);
    mapa.AdicionarEstrada(1, 5, 111);
    mapa.AdicionarEstrada(2, 0, 75);
    mapa.AdicionarEstrada(2, 4, 71);
    mapa.AdicionarEstrada(3, 0, 140);
    mapa.AdicionarEstrada(3, 4, 151);
    mapa.AdicionarEstrada(3, 6, 99);
    mapa.AdicionarEstrada(3, 7, 80);
    mapa.AdicionarEstrada(4, 2, 71);
    mapa.AdicionarEstrada(4, 3, 151);
    mapa.AdicionarEstrada(5, 1, 111);
    mapa.AdicionarEstrada(5, 8, 70);
    mapa.AdicionarEstrada(6, 3, 99);
    mapa.AdicionarEstrada(6, 12, 211);
    mapa.AdicionarEstrada(7, 3, 80);
    mapa.AdicionarEstrada(7, 10, 146);
    mapa.AdicionarEstrada(7, 11, 97);
    mapa.AdicionarEstrada(8, 9, 75);
    mapa.AdicionarEstrada(8, 5, 70);
    mapa.AdicionarEstrada(9, 10, 120);
    mapa.AdicionarEstrada(9, 8, 75);
    mapa.AdicionarEstrada(10, 11, 138);
    mapa.AdicionarEstrada(10, 7, 146);
    mapa.AdicionarEstrada(11, 12, 101);
    mapa.AdicionarEstrada(11, 10, 138);
    mapa.AdicionarEstrada(11, 7, 97);
    mapa.AdicionarEstrada(12, 13, 90);
    mapa.AdicionarEstrada(12, 14, 85);
    mapa.AdicionarEstrada(12, 6, 211);
    mapa.AdicionarEstrada(12, 11, 101);
    mapa.AdicionarEstrada(13, 12, 90);
    mapa.AdicionarEstrada(14, 17, 142);
    mapa.AdicionarEstrada(14, 15, 98);
    mapa.AdicionarEstrada(14, 12, 85);
    mapa.AdicionarEstrada(15, 16, 86);
    mapa.AdicionarEstrada(15, 14, 98);
    mapa.AdicionarEstrada(16, 15, 86);
    mapa.AdicionarEstrada(17, 14, 142);
    mapa.AdicionarEstrada(17, 18, 92);
    mapa.AdicionarEstrada(18, 17, 92);
    mapa.AdicionarEstrada(18, 19, 87);
    mapa.AdicionarEstrada(19, 18, 87);
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

void Mapa::BuscaLargura(string inicio, string destino) {
	list<int> borda; // lista que simula a fila de prioridade da borda
	bool explorados[V]; // vetor de explorados
    std::list<Cidade>::iterator it;
    int totalCaminho = 0;

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
        cout << "Entrou no explorado: " << cidadesString[node] << "." << endl;

        for (it = adj[node].begin(); it != adj[node].end(); ++it){
            if(explorados[it->idCidade] == false && Contem(borda, it->idCidade) == false) { // se nó não foi explorado e não está na borda
                totalCaminho += it->distancia;
                if(it->idCidade == indexDestino) { // se é o destino fim
                    cout << "Destino: " << cidadesString[it->idCidade] << endl;
                    cout << "Tamanho total: " << totalCaminho << endl;
                    return;
                } else { // não é o destino, então add na borda
                    borda.push_back(it->idCidade); 
                    cout << "Entrou na borda: " << cidadesString[it->idCidade] << endl;
                }
            }
        }
    }
}

int main(){
    int nVertice = 20;
    Mapa mapa(nVertice); //criando o mapa com 20 cidades

    mapa.MontarMapa(mapa);

    mapa.BuscaLargura("Neamt", "Bucharest");
    // mapa.BuscaLargura("Eforie", "Bucharest");
    // mapa.BuscaLargura("Lugoj", "Bucharest");
    // mapa.BuscaLargura("Arad", "Bucharest");
    // mapa.BuscaLargura("Vaslui", "Bucharest");
    // mapa.BuscaLargura("Oradea", "Bucharest");
    // mapa.BuscaLargura("Iasi", "Bucharest");
    // mapa.BuscaLargura("Timisoara", "Bucharest");
    // mapa.BuscaLargura("Zerind", "Bucharest");
    // mapa.BuscaLargura("Hirsova", "Bucharest");
    
    return 0;
}