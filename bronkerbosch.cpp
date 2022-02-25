#include <bits/stdc++.h>

using namespace std;

// Número de relações e número de vértices
int k, n;

// Lista de adjacência de vértices
vector<vector<int>> edges;

// Vetor para armazenar todos os cliques maximais sem e com pivotamento
vector<vector<int>> ansWithoutPivot;
vector<vector<int>> ansPivot;

// Função para calcular o coeficiente de aglomeração médio do grafo
double clusteringCoeficient() {
    double totalClusteringCoefficient = 0;
    // Percorre todos os vértices do grafo
    for (int v = 1; v <= n; v++) {
        double localClusteringCoefficient = 0;
        // Percorre todos os vizinhos do vértice
        for (auto neighbour : edges[v]) {
            // Percorre os vizinhos do vizinho do vértice
            for (auto otherNeighbour : edges[neighbour]) {
                // Se o vizinho do vizinho do vértice também for vizinho do vértice, adiciona 1 à reposta
                for (auto u : edges[v]) {
                    if (otherNeighbour == u) localClusteringCoefficient++;
                }
            }
        }
        // Calcula o coeficiente de aglomeração do vértice se ele tiver mais de um vizinho
        if (edges[v].size() > 1)
            totalClusteringCoefficient += (double)localClusteringCoefficient/(edges[v].size()*(edges[v].size() - 1));
    }
    // Soma os coeficientes de cada vértice e divide pelo número de vértices
    return (double)totalClusteringCoefficient/n;
}

// Função para imprimir na tela os cliques maximais encontrados
void printAns(vector<vector<int>> ans) {
    // Imprime quantidade de cliques maximais
    cout << "Quantidade de cliques maximais: " << ans.size() << "\n\n";
    for (auto clique : ans) {
        // Imprime o número de vértices do clique maximal
        cout << "Tamanho do clique: " << clique.size() << '\n';
        // Imprime os vértices do clique maximal
        cout << "Elementos do clique: ";
        for (auto e : clique)
            cout << e << ' ';
        cout << "\n\n";
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
    
    //Retorna o vetor com a intersecção
    return I;
}

// Função para achar a diferença entre dois vetores
vector<int> difference(vector<int> A, vector<int> B) {
    // Ordena os dois vetores
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    
    // Vetor para armazenar a diferença entre dois conjuntos
    vector<int> D(A.size() + B.size());
    
    // Une os dois conjuntos
    auto it = set_difference(A.begin(), A.end(), B.begin(), B.end(), D.begin());
    D.resize(it - D.begin());
    
    //Retorna o vetor com a diferença
    return D;
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

// Função para escolher o vértice com maior grau como pivô
int choosePivot(vector<int> A) {
    // Vetor com pares com o grau de cada vértice e o próprio vértice
    vector<pair<int, int>> degrees;
    // Calcula o grau de cada vértice
    for (auto v : A) {
        degrees.push_back({edges[v].size(), v});
    }
    // Ordena pelo grau de cada vértice
    sort(degrees.begin(), degrees.end());
    // Se A for vazio, retorna 0
    if (degrees.empty()) return 0;
    // Senão, retorna vértice com maior grau
    return (degrees.back()).second;
}

// Algoritmo de BronKerbosch para clique maximal com pivotamento
void BronKerboschPivot(vector<int> R, vector<int> P, vector<int> X) {
    // Faz uma cópia do vetor P para evitar erros ao modificar o vetor P dentro do loop P
    vector<int> PCopy(P);
    
    // Adiciona clique maximal à reposta
    if (P.empty() and X.empty())
        ansPivot.push_back(R);
        
    // Escolhe um pivô
    int pivot = choosePivot(unite(P, X));
    
    // Chama a função recursivamente para cada vértice de P
    for (auto v : difference(P, edges[pivot])) {
        BronKerboschPivot(unite(R, {v}), intersect(PCopy, edges[v]), intersect(X, edges[v]));
        // Altera os conjuntos P e X
        PCopy.erase(find(PCopy.begin(), PCopy.end(), v));
        X = unite(X, {v});
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    freopen("soc-dolphins.txt", "r", stdin);

    // Lê input com númeor de relações e número de vértices
    cin >> n >> k;
    // Muda o tamanho do vetor de listas de adjacência
    edges.resize(n + 1);
    
    // R são os possíveis vértices que podem fazer parte de um clique
    // P são os vértices que ligam em R
    // X são so vértices já analidsados e que não estendem R
    vector<int> R, P, X;
    
    // Adiciona todos os vértices do grafo ao conjunto P
    for (int i = 1; i <= n; i++)
        P.push_back(i);
    
    // Lê o input do grafo não direcionado e adiciona os vizinhos de u na lista de ajacência de cada vértice
    for (int i = 0; i < k; i++) {
        int u, v; cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    
    // Chama a função para calcular coeficiente de aglomeração médio do grafo
    cout << "Coeficiente de aglomeração médio: " << clusteringCoeficient() << "\n\n\n";
    
    // Chama a função para encontrar os cliques maximais sem pivotamento
    cout << "Bron Kerbosch sem pivotamento: \n\n";
    BronKerboschWithoutPivot(R, P, X);
    printAns(ansWithoutPivot);
    
    cout << "\n\n";
    
    // Chama a função para encontrar os cliques maximais com pivotamento
    cout << "Bron Kerbosch com pivotamento: \n\n";
    BronKerboschPivot(R, P, X);
    printAns(ansPivot);

    return 0;
}