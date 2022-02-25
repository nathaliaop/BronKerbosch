#include <bits/stdc++.h>

using namespace std;

// Número de relações e número de vértices
int k, n;

// Lista de adjacência de vértices
vector<vector<int>> edges;

// Vetor para armazenar todos os cliques maximais sem e com pivotamento
vector<vector<int>> ansWithoutPivot;
vector<vector<int>> ansPivot;

// Função para imprimir na tela os cliques maximais encontrados
void printAns(vector<vector<int>> ans) {
    for (auto clique : ans) {
        // Imprime o número de vértices do clique maximal
        cout << clique.size() << '\n';
        for (auto e : clique)
            // Imprime os vértices do clique maximal
            cout << e << ' ';
        cout << '\n';
    }
}

// Função para achar a união entre dois vetores
vector<int> unite(vector<int> A, vector<int> B) {
    // Ordena os dois vetores
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    
    // Vetor para armazenar a união entre dois conjuntos;
    vector<int> U(A.size() + B.size());
    
    // Une os dois conjuntos
    auto it = set_union(A.begin(), A.end(), B.begin(), B.end(), U.begin());
    U.resize(it - U.begin());
    
    //Retorna o vetor com a união
    return U;
}

// Função para achar a intersecção entre dois vetores
vector<int> intersect(vector<int> A, vector<int> B) {
    // Ordena os dois vetores
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    
    // Vetor para armazenar a intersecção entre dois conjuntos
    vector<int> I(A.size() + B.size());
    
    // Une os dois conjuntos
    auto it = set_intersection(A.begin(), A.end(), B.begin(), B.end(), I.begin());
    I.resize(it - I.begin());
    
    //Retorna o vetor com a união
    return I;
}

// Algoritmo de BronKerbosch para clique maximal sem pivotamento
void BronKerboschWithoutPivot(vector<int> R, vector<int> P, vector<int> X) {
    // Faz uma cópia do vetor P para evitar erros ao modificar o vetor P dentro do loop P
    vector<int> PCopy(P);
    
    // Adiciona clique maximal à reposta
    if (P.empty() and X.empty())
        ansWithoutPivot.push_back(R);
    
    // Chama a função recursivamente para cada vértice de P
    for (auto v : P) {
        BronKerboschWithoutPivot(unite(R, {v}), intersect(PCopy, edges[v]), intersect(X, edges[v]));
        // Altera os conjuntos P e X
        PCopy.erase(find(PCopy.begin(), PCopy.end(), v));
        X = unite(X, {v});
    }
}

// Algoritmo de BronKerbosch para clique maximal com pivotamento
void BronKerboschPivot(vector<int> &R, vector<int> &P, vector<int> &X) {}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // Lê input com númeor de relações e número de vértices
    cin >> n >> k;
    // Muda o tamanho do vetor de listas de adjacência
    edges.resize(n + 1);
    
    // R são os possíveis vértices que podem fazer parte de um clique
    // P são os vértices que ligam em R
    // X são so vértices já analidsados e que não estendem R
    vector<int> R, P, X;
    
    // Adiciona todos os vértices do grafo ao conjunto P
    for (int i = 1; i <= n; i++) {
        P.push_back(i);
    }
    
    // Lê o input do grafo não direcionado e adiciona os vizinhos de u na lista de ajacência de cada vértice
    for (int i = 0; i < k; i++) {
        int u, v; cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    
    // Chama a função para encontrar os cliques maximais
    BronKerboschWithoutPivot(R, P, X);
    
    printAns(ansWithoutPivot);

    return 0;
}