# Documentação da Implementação

- **Autor:** Enrique George Rodrigues
- **Curso:** Licenciatura Engenharia de Sistemas Informáticos
- **Instituição:** Instituto Politécnico do Cávado e do Ave
- **Contato:** hello.basi@proton.me
- **Data:** Março 2024

## Prefácio

Este documento descreve a implementação de um grafo em C, onde pretende-se aplicar conceitos avançados de teoria dos grafos e programação em C para resolver um problema computacional com grau de complexidade média, relacionando estruturas de dados, algoritmos de procura e técnicas de otimização. O objetivo foi desenvolver uma solução capaz de calcular o somatório máximo possível de inteiros a partir de uma matriz de inteiros de dimensões arbitrárias, considerando regras específicas de conexão entre os inteiros.

Para esta implementação, foi necessário criar uma estrutura de dados dinâmica capaz de se adaptar ao tamanho do grafo dado. O grafo é representado utilizando uma tabela de hash para os vértices, onde cada vértice corresponde a um elemento da matriz. As arestas do grafo representam as ligações entre os vértices de acordo com as regras estabelecidas para calcular o somatório máximo e são representadas numa lista ligada. O algoritmo utilizado para calcular este somatório é baseado em um método de busca em profundidade (DFS), adaptado para percorrer o grafo de forma a otimizar o cálculo. A implementação também inclui o algoritmo de Dijkstra para calcular o caminho mínimo possível entre dois vértices.

## Palavras-chave

Grafo, Estruturas de Dados, Programação em C, Tabela de Hash, Lista Ligada, Função de Hash, Estruturas de Dados Dinâmicas

## Estrutura da Implementação

### Vértices

Os vértices estão numa tabela de hash. A escolha de uma tabela de hash para guardar os vértices foi feita visando otimizar a velocidade de acesso e pesquisa de vértices no grafo. Aqui estão alguns dos motivos pelos quais uma tabela de hash foi selecionada:

- **Velocidade de Acesso:** O tempo médio de acesso a um vértice é O(1), tornando as operações de inserção, remoção e busca extremamente rápidas em comparação com estruturas de dados lineares como listas ou arrays.

- **Tratamento de Colisões**: Utilizamos uma estratégia de tratamento de colisões usando listas ligadas simples. Isto permite que vários vértices sejam guardados no mesmo índice da tabela de hash, lidando eficientemente com colisões sem comprometer significativamente o desempenho.

- **Adaptação Dinâmica**: A estrutura da tabela de hash é dinamicamente adaptável, ajustando-se automaticamente conforme o número de vértices cresce, o que é ideal para grafos de tamanho variável.

### Arestas

Cada vértice mantém uma lista ligada de arestas para representar as suas ligações com outros vértices. Esta escolha foi feita por várias razões:

- **Facilidade de Inserção e Remoção**: As listas ligadas permitem inserções e remoções eficientes de arestas. Em grafos dinâmicos, onde as conexões entre vértices podem mudar com o tempo, essa flexibilidade é essencial.

- **Uso de Memória Eficiente**: Comparado a uma matriz de adjacências, as listas ligadas utilizam apenas espaço proporcional ao número de arestas presentes no grafo, tornando-as mais eficientes em termos de memória para grafos esparsos.

- **Suporte a Peso nas Arestas**: Cada aresta na lista ligada pode incluir um peso, o que é útil para algoritmos como Dijkstra, que requerem informações sobre o peso das arestas.

## Operações

As operações principais do grafo têm a seguinte notação _Big O_ associada:

- **Inserção de Vértice**: O(1) no caso médio, devido ao acesso constante na tabela de hash.

- **Remoção de Vértice**: O(1) no caso médio, devido ao acesso constante na tabela de hash.

- **Inserção de Aresta**: O(1) para adicionar uma aresta a uma lista ligada de vértices adjacentes dado que é adicionado no início da lista.

- **Remoção de Aresta**: O(n) para remover uma aresta de uma lista ligada de vértices adjacentes onde `n` é o número de arestas adjacentes.

- **Busca de Vértice por ID**: O(1) no caso médio, devido ao acesso direto à tabela de hash.

- **Busca de Aresta**: O(n), onde n é o número de arestas adjacentes a ele.

Esta estrutura e notação Big O são ideais para suportar operações eficientes em grafos de tamanho variável, mantendo uma implementação simples e escalável.

## Memória

A implementação do grafo foi projetada com considerações cuidadosas em relação ao uso eficiente de memória e escolhas de tipos de dados.

### Escolha de Tipos de Dados

Foram utilizados tipos de dados `unsigned int` para representar identificadores de vértices e pesos de arestas. A escolha de `unsigned int` foi feita por várias razões:

- **Não tem Peso Negativo**: O grafo não permite pesos negativos nas arestas, portanto, utilizando `unsigned int`, conseguimos representar um intervalo maior de valores positivos do que com `int`, utilizando todo o espectro dos 32 bits. Isto permite suportar grafos maiores com um maior número de vértices e arestas.

- **Uso Eficiente de Memória**: O tipo `unsigned int` utiliza 4 bytes de memória, permitindo que representemos um número máximo muito grande de vértices e arestas sem desperdício significativo de memória.

### Tamanho Máximo do Grafo

O tamanho máximo do grafo que esta implementação pode suportar depende do sistema e da quantidade de memória disponível. Aqui estão algumas considerações gerais:

- **Número de Vértices**: A implementação utiliza uma tabela de hash para os vértices. A capacidade máxima da tabela de hash depende do tamanho da tabela (`hashSize`). Em sistemas modernos, podemos criar tabelas de hash com milhões de entradas sem problemas, desde que haja memória suficiente.

- **Número de Arestas**: O número máximo de arestas que podemos representar é diretamente proporcional ao número de vértices e à densidade do grafo. Como as arestas são representadas em listas ligadas, o número de arestas que podem ser armazenadas é limitado apenas pela memória disponível.

### Otimização de Uso de Memória

Para otimizar o uso de memória, cada vértice armazena apenas as arestas que ele possui, o que é adequado para grafos esparsos. Grafos densos (com um grande número de arestas por vértice) podem consumir mais memória, mas a estrutura é eficiente para a maioria dos casos de uso.

## Testes de Desempenho

Os testes de desempenho foram realizados para avaliar o desempenho da implementação do grafo em termos de tempo de CPU. Os testes foram executados em um sistema com as seguintes especificações:

- **Memória RAM**: 16GB DDR4 2300MHz
- **CPU**: Ryzen 3 1200
- **Armazenamento**: Kingston A400 SSD

### Metodologia de Teste

Para medir o desempenho, utilizamos a biblioteca de tempo (`time.h`) em C, que nos permite medir o tempo de execução das operações do grafo. Os testes foram projetados para avaliar o tempo de execução das operações principais do grafo, incluindo importação e exportação de grafos em formato de texto e binário, busca de vértices e areastas, e cálculo do caminho mínimo e somatório máximo.

### Considerações sobre o Hardware

O sistema utilizado para os testes possui uma quantidade suficiente de memória RAM e um processador de entrada, que são adequados para avaliar o desempenho da implementação em condições típicas de uso.

### Objetivo dos Testes

O objetivo dos testes de desempenho é verificar a eficiência da implementação em termos de tempo de execução das operações, garantindo que o grafo possa manipular um grande número de vértices e arestas de forma eficiente.

### Teste de Criação e Adição de Vértices

**Procedimento**:

- Inserir 1.000.000 (um milhão) de vértices no grafo.
- Medir o tempo de execução da inserção dos vértices no grafo.
- Repetir o teste 10 vezes para calcular a média e o desvio padrão dos tempos de execução.

**Resultados**:

- **Tempo Médio**: O tempo médio para criar e adicionar 1.000.000 (um milhão) de vértices ao grafo foi de `0,223000s` (segundos).
- **Desvio Padrão**: O desvio padrão dos tempos de execução foi de aproximadamente `0,00356s` (segundos).

### Teste de Criação e Adição de Arestas

**Procedimento**:

- Inserir 1.000.000 (um milhão) de arestas no grafo.
- Medir o tempo de execução da inserção das arestas no grafo.
- Repetir o teste 10 vezes para calcular a média e o desvio padrão dos tempos de execução.

**Resultados**:

- **Tempo Médio**: O tempo médio para criar e adicionar 1.000.000 (um milhão) de arestas ao grafo foi de `s` (segundos).
- **Desvio Padrão**: O desvio padrão dos tempos de execução foi de aproximadamente `s` (segundos).

### Teste de Importar de Ficheiro Texto

**Procedimento**:

- Importar um grafo de um ficheiro de texto com 1.000.000 (um milhão) de vértices e até 10 arestas para cada vértice.
- Medir o tempo de execução da importação.
- Repetir o teste 10 vezes para calcular a média e o desvio padrão dos tempos de execução.

**Resultados**:
