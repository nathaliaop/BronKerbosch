#include <bits/stdc++.h>

using namespace std;

// Vetor para armazenar todos os cliques maximais sem e comn pivoteamento
vector<vector<int>> ans_without_pivot;
vector<vector<int>> ans_pivot;

// Função para achar a união entre dois vetores
vector<int> unite(vector<int> &A, vector<int> &B) {
    // Vetor para armazenar a união entre dois conjuntos
    vector<int> U(A.size() + B.size());
    
    // Une os dois conjuntos
    auto it = set_union(A.begin(), A.end(), B.begin(), B.end(), U.begin());
    U.resize(it - U.begin());
    
    //Retorna o vetor com a união
    return U;
}

// Função para achar a intersecção entre dois vetores
vector<int> intersect(vector<int> A, vector<int> B) {
    // Vetor para armazenar a intersecção entre dois conjuntos
    vector<int> I(A.size() + B.size());
    
    // Une os dois conjuntos
    auto it = set_intersection(A.begin(), A.end(), B.begin(), B.end(), I.begin());
    I.resize(it - I.begin());
    
    //Retorna o vetor com a união
    return I;
}

// Algoritmo de BronKerbosch para clique maximal sem pivoteamento
void BronKerbosch_without_pivot(vector<int> &R, vector<int> &P, vector<int> &X) {
    if (P.empty() and X.empty())
        ans_without_pivot.push_back(R);
    for (auto v: P) {
        // BronKerbosch(unite(R, {v}, intersect(P, ), intersect()));
    }
}

// Algoritmo de BronKerbosch para clique maximal com pivoteamento
void BronKerbosch_pivot(vector<int> &R, vector<int> &P, vector<int> &X) {}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // Número de relações e número de golfinhos
    int k, n; cin >> n >> k;
    
    // Lista de adjacência de vértices
    vector<vector<int>> edges(n);
    
    // R são os possíveis vértices que podem fazer parte de um clique
    // P são os vértices que ligam em R
    // X são so vértices já analidsados e que não estendem R
    vector<int> R, P, X;
    
    // Adiciona todos os vértices do grafo ao conjunto P
    for (int i = 1; i <= n; i++) {
        P.push_back(i);
    }
    
    // Lê o input e adiciona os vizinhos de u na lista de ajacência deste
    for (int i = 0; i < k; i++) {
        int u, v; cin >> u >> v;
        edges[u].push_back(v);
    }

    return 0;
}