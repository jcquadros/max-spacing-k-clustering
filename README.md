# max-spacing-k-clustering

## Eu vou tentar organizar desde a entrada de dados até a criação do vetor de pesos. Definir estruturas de dados e funções que posteriormente vamos dividir.
### Estrutura de dados
- **Vetor Genérico**:
  - *Atributos*: int size,int size_max, void** values.
  - *Métodos*: init - (parametros: tamanho inicial), get - (parametros: índice), push_back - (parametros: ponteiro do dado a ser inserido), destroy.
- **Vértice**:
  - *Atributos*: char* identificador (nome), int* coordenadas (vetor).
  - *Metodos*:init, get_id, get_coordenadas,int get_distance(Vertice 1, Vertice2) - distancia euclidiana, destroy
- **Aresta(Edge)**
  - *Atributos*: int vertex1, int vertex2, weight.
  - *Metodos*: init, get_vertex1, get_vertex2, get_weight, destroy

### Entrada de dados
O algoritmo segue os seguintes passos:
- Abrir o arquivo de entrada, ler os vértices e armazená-los em um vetor genérico de vértices.
- Para cada vértice contido no vetor de vértices, calcular a distancia euclidiana entre os outros vértices e armazenar no vetor de arestas. Tomar cuidado para não repetir os vértices, pois a distância entre A e B é a mesma entre B e A. Seria algo como fazer um for i... e dentro outro for j=i+1...
- Ordenar o vetor

### MST (Sujestão. Calcular o numero máximo de arestas e parar o algoritmo assim que atingir o numero máximo de arestas da MST. Se quiser roubar mais. Verificar se é mais vantajoso remover K arestas ou não inserir as ultimas K arestas da MST.)
