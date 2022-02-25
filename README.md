#### Estudante: Nathália Oliveira Pereira
#### Matrícula: 180042980

Implementação do algoritmo de Bron Kerbosch para achar cliques maximais com e sem pivoteamento e de uma função para calcular o coeficiente de aglomeração médio de um grafo para a disciplina de Teoria e Aplicação de Grafos.

Para compilar o código no terminal Linux:
`
g++ bronkerbosch.cpp -o file
`

Para executar:
`
./file
`

%%MatrixMarket matrix coordinate pattern symmetric
%-------------------------------------------------------------------------------
% UF Sparse Matrix Collection, Tim Davis
% http://www.cise.ufl.edu/research/sparse/matrices/Newman/dolphins
% name: Newman/dolphins
% [social network of dolphins, Doubtful Sound, New Zealand]
% id: 2396
% date: 2003
% author: D. Lusseau
% ed: M. Newman
% fields: name title A id date author kind notes aux ed
% aux: nodename
% kind: undirected graph
%-------------------------------------------------------------------------------
% notes:
% Network collection from M. Newman                                          
% http://www-personal.umich.edu/~mejn/netdata/                               
%                                                                            
% The graph dolphins contains an undirected social network of frequent       
% associations between 62 dolphins in a community living off Doubtful Sound, 
% New Zealand, as compiled by Lusseau et al. (2003).  Please cite            
%                                                                            
%   D. Lusseau, K. Schneider, O. J. Boisseau, P. Haase, E. Slooten, and      
%   S. M. Dawson, The bottlenose dolphin community of Doubtful Sound features
%   a large proportion of long-lasting associations, Behavioral Ecology and  
%   Sociobiology 54, 396-405 (2003).                                         
%                                                                            
% Additional information on the network can be found in                      
%                                                                            
%   D. Lusseau, The emergent properties of a dolphin social network,         
%   Proc. R. Soc. London B (suppl.) 270, S186-S188 (2003).                   
%                                                                            
%   D. Lusseau, Evidence for social role in a dolphin social network,        
%   Preprint q-bio/0607048 (http://arxiv.org/abs/q-bio.PE/0607048)           
%-------------------------------------------------------------------------------
