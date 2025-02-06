# Documentação

Eu alterei a estrutura do projeto e utilizei conceitos que ainda não foram
ensinados na disciplina, mas que possuo conhecimento sobre. Espero que isso não
seja um problema. Mas caso venha a ser, gostaria de uma oportunidade para
resolvê-lo.

Apesar do uso de *overengineering*, achei que essa seria uma boa oportunidade
para praticar e entender melhor, além dos conceitos ensinados na disciplina, o
uso de:

- Headers
- Doxygen
- Include Guards
- Ponteiros
- Alocação e liberação de memória stack e heap
- Structs e enums

## Nível do Projeto

O projeto contempla as funcionalidades dos níveis Novato, Aventureiro e Mestre.

Há uma "adição" na funcionalidade, do nível Mestre, onde o usuário deve
escolher duas propriedades para a comparação. Nela eu não permiti que a segunda
propriedade escolhida seja a mesma da primeira.

## Índice

- [Documentação](#documentação)
  - [Nível do Projeto](#nível-do-projeto)
  - [Índice](#índice)
  - [Estrutura do Projeto](#estrutura-do-projeto)
    - [NOTA](#nota)
  - [Compilação](#compilação)
  - [Funcionamento do projeto](#funcionamento-do-projeto)
    - [1. Registro de cartas](#1-registro-de-cartas)
    - [2. Registro de duas cartas e comparação da propriedade "População"](#2-registro-de-duas-cartas-e-comparação-da-propriedade-população)
    - [3. Registro de duas cartas e comparação da propriedade escolhida pelo usuário](#3-registro-de-duas-cartas-e-comparação-da-propriedade-escolhida-pelo-usuário)
    - [4. Registro de duas cartas e comparação de duas propriedades escolhidas pelo usuário](#4-registro-de-duas-cartas-e-comparação-de-duas-propriedades-escolhidas-pelo-usuário)
    - [Validação](#validação)
    - [Compatibilidade](#compatibilidade)
  - [Passo a passo dos fluxos](#passo-a-passo-dos-fluxos)
    - [Registro de cartas](#registro-de-cartas)
    - [Registro de duas cartas e comparação da propriedade "População"](#registro-de-duas-cartas-e-comparação-da-propriedade-população)
      - [Possíveis resultados da comparação](#possíveis-resultados-da-comparação)
    - [Registro de duas cartas e comparação da propriedade escolhida pelo usuário](#registro-de-duas-cartas-e-comparação-da-propriedade-população)
    - [Registro de duas cartas e comparação de duas propriedades escolhidas pelo usuário](#registro-de-duas-cartas-e-comparação-de-duas-propriedades-escolhidas-pelo-usuário)

## Estrutura do Projeto

O projeto segue a seguinte estrutura de diretórios:

```bash
.
├── README.md                       # Documentação do projeto
├── apps
│   └── logicaSuperTrunfo.c         # Arquivo principal com a função `main`
├── include                         # Arquivos de cabeçalhos contendo as declarações das funções
│   ├── card.h
│   ├── city.h
│   ├── interface.h
│   └── util.h
└── src                             # Arquivos de implementação das funções declaradas nos cabeçalhos
    ├── card.c
    ├── city.c
    ├── interface.c
    └── util.c
```

---

### NOTA

**Essa estrutura foi baseada na estrutura utilizada pelo professor Samuel
Martins no curso [Dominando Estruturas de Dados 1](https://github.com/xavecoding/dominando-estruturas-de-dados-1).
O uso de ponteiros, das funções `calloc` e `free`, da estrutura de dados
`struct`, de *include guards* e qualquer outro tema que não tenha sido abordado
na disciplina "Introdução à Programação de Computadores", foi aprendido no curso
mencionado. A excessão é o uso da documentação Doxygen, que eu aprendi enquanto
resolvia este desafio.**

## Compilação

O comando usado para compilar foi:

```bash
gcc apps/logicaSuperTrunfo.c -o logicaSuperTrunfo src/*.c -I include
```

Explicação:

- `gcc`: Compilador utilizado.
- `apps/logicaSuperTrunfo.c`: Arquivo principal com a função main.
- `-o logicaSuperTrunfo`: Nome do executável gerado.
- `src/*.c`: Arquivos com a implementação das funções declaradas nos cabeçalhos.
- `-I include`: Diretório que contém os arquivos de cabeçalho.

Deve-se especificar os arquivos ou diretórios necessários durante a compilação
para garantir que todas as dependências sejam incluídas.

## Funcionamento do projeto

O projeto possui quatro fluxos:

### 1. Registro de cartas

Neste fluxo, o usuário pode registrar os dados de cidades e visualizar as
informações cadastradas logo após cada registro.

- O número máximo de cidades que podem ser cadastradas é **32**,
correspondente à quantidade de cartas no jogo original.
- As cidades são armazenadas em uma lista de ponteiros chamada `city_list`,
que é alocada na memória estática.
- Cada elemento dessa lista é um ponteiro para uma estrutura do tipo `City`,
que é alocada dinamicamente na memória heap à medida que o usuário cadastra
novas cidades.
- A estrutura `City` organiza os dados de cada cidade, incluindo:
  - Estado.
  - Código da carta.
  - Nome da cidade.
  - População.
  - Área.
  - Densidade populacional: calculada como a razão entre População e Área.
  - PIB.
  - PIB per capita: calculado como a razão entre PIB e População.
  - Número de pontos turísticos.

### 2. Registro de duas cartas e comparação da propriedade "População"

Neste fluxo, o usuário registra os dados de duas cartas conforme solicitado
pelo programa. Após o registro, são exibidos os valores tratados de cada carta e
o resultado da comparação do valor da propriedade "População" das cartas
registradas.

### 3. Registro de duas cartas e comparação da propriedade escolhida pelo usuário

Neste fluxo, o usuário registra os dados de duas cartas conforme solicitado
pelo programa. Após o registro, são exibidos os valores tratados de cada carta e
as propriedades passíveis a comparação. O usuário deve escolher qual propriedade
deseja comparar e, logo em seguida, o resultado da comparação é exibido.

### 4. Registro de duas cartas e comparação de duas propriedades escolhidas pelo usuário

Neste fluxo, o usuário registra os dados de duas cartas conforme solicitado
pelo programa. Após o registro, são exibidos os valores tratados de cada carta e
as propriedades passíveis a comparação. O usuário deve escolher duas
propriedades, uma a uma, para a comparação. Logo em seguida, o programa exibe o
resultado da comparação, que é feita através da soma das
propriedades escolhidas.

**OBS.:** A segunda propriedade deve ser diferente da primeira.

---

Ao rodar o projeto, o programa apresenta ao usuário os fluxos de execução e
pergunta ao usuário qual fluxo ele deseja executar:

```terminal
O programa possui as seguintes funcionalidades:

1. Registro de cartas: Permite registrar cartas e ver os dados registrados para cada carta.

2. Registro de duas cartas e comparacao entre a propriedade "Populacao": Permite registrar duas cartas, ver os dados de cada uma, fazer a comparacao entre os valores da propriedade "Populacao" e ver qual a carta vencedora, que será a que tiver maior valor de "Populacao".

3. Registro de duas cartas e comparacao entre uma propriedade, a escolha do usuario: Permite registrar duas cartas, ver os dados de cada uma, fazer a comparacao entre os valores da propriedade escolhida e ver qual a carta vencedora, que será a que tiver maior valor na propriedade escolhida, com excessão de "Densidade Populacional", que terá como verncedora a carta com menor valor.

4. Registro de duas cartas e comparacao entre duas propriedades, a escolha do usuario: Permite registrar duas cartas, ver os dados de cada uma, fazer a comparacao entre os valores das propriedades escolhidas e ver qual a carta vencedora, que será a que tiver maior valor de soma das propriedades escolhidas.

Escolha o numero da opcao que deseja executar: 
```

### Validação

Caso o usuário insira um valor inválido, uma mensagem será exibida informando
que o valor inserido é inválido e será solicitado um novo valor até que o
usuário insira uma opção válida.

### Compatibilidade

Na exibição dos dados, caracteres que podem não ser interpretados corretamente
em todos os terminais (como acentos ortográficos) foram removidos para garantir
a compatibilidade.

## Passo a passo dos fluxos

### Registro de cartas

Caso o fluxo escolhido seja o fluxo de registro de cartas, as propriedades da
primeira carta serão solicitadas uma a uma:

```bash
Escolha o numero da opcao que deseja executar: 1   # Número referente ao registro de cartas

Digite o estado: 
```

```bash
Digite o estado: A   # Valor 'A' inserido
Digite o codigo da carta:
```

```bash
Digite o estado: A
Digite o codigo da carta: A01   # Valor "A01" inserido
Digite o nome da cidade: 
```

até que todos os valores sejam inseridos:

```bash
Digite o estado: A
Digite o codigo da carta: A01
Digite o nome da cidade: Sao Paulo
Digite a populacao: 12325000
Digite a area: 1521.11
Digite o PIB: 699280000000
Digite o numero de pontos turisticos: 50
```

Após a inserção de todos os valores, o programa informa que o registro da carta
foi bem sucedido, mostra os valores tratados da carta e pergunta ao usuário se
deseja registrar outra carta:

```bash
Carta registrada com sucesso.

Estado: A
Codigo da Carta: A01
Nome da Cidade: Sao Paulo
Populacao: 12325000
Area: 1521.11 km²
Densidade Populacional: 8102.64 pessoas/km²
PIB: 699.28 bilhoes de reais
PIB per Capta: 56737 reais
Numero de Pontos Turisticos: 50

Registrar outra carta? (S/N): 
```

- Caso o usuário opte por não registrar outra carta, o programa encerra sua
execução.
- Caso o usuário opte por continuar cadastrando, o processo se repetirá até um
limite de 32 cartas registradas. Então, o programa exibe a seguinte mensagem e
termina sua execução:

```bash
Numero maximo de registros atingido.
```

---

### Registro de duas cartas e comparação da propriedade "População"

Caso o fluxo escolhido seja o fluxo de registro de duas cartas e comparacao da
propriedade "População", as propriedades da primeira e segunda cartas serão
solicitadas uma a uma:

```bash
Escolha o numero da opcao que deseja executar: 2   # Número referente ao registro de duas e cartas comparação da "População"

Digite o estado: 
```

```bash
Digite o estado: A   # Valor 'A' inserido
Digite o codigo da carta:
```

```bash
Digite o estado: A
Digite o codigo da carta: A01   # Valor "A01" inserido
Digite o nome da cidade: 
```

até que todos os valores sejam inseridos:

```bash
Digite o estado: A
Digite o codigo da carta: A01
Digite o nome da cidade: Sao Paulo
Digite a populacao: 12325000
Digite a area: 1521.11
Digite o PIB: 699280000000
Digite o numero de pontos turisticos: 50
```

Logo em seguida o programa pede a inserção dos dados da segunda, de um a um,
até que todos os dados sejam inseridos:

```bash
Digite o estado da segunda carta: B
Digite o codigo da segunda carta: B01
Digite o nome da cidade da segunda carta: Cidade Aleatoria
Digite a populacao da segunda carta: 150000000
Digite a area da segunda carta: 1510.08
Digite o PIB da segunda carta: 596000000000
Digite o numero de pontos turisticos da segunda carta: 39
```

Após receber os dados, o programa exibe os dados registrados e calculados
para cada carta:

```bash
Dados registrados para a carta 1:

Estado da carta 1: A
Codigo da carta 1: A01
Nome da Cidade da carta 1: Sao Paulo
Populacao da carta 1: 1232500
Area da carta 1: 1521.11 km²
Densidade Populacional da carta 1: 810.26 pessoas/km²
PIB da carta 1: 699.28 bilhoes de reais
PIB per Capta da carta 1: 567367 reais
Numero de Pontos Turisticos da carta 1: 50
Super Poder da carta 1: 699281833984.00

Dados registrados para a carta 2:

Estado da carta 2: B
Codigo da carta 2: B01
Nome da Cidade da carta 2: Cidade Aleatoria
Populacao da carta 2: 150000000
Area da carta 2: 1510.08 km²
Densidade Populacional da carta 2: 99332.49 pessoas/km²
PIB da carta 2: 596.00 bilhoes de reais
PIB per Capta da carta 2: 3973 reais
Numero de Pontos Turisticos da carta 2: 39
Super Poder da carta 2: 596149993472.00
```

Em seguida, o programa realiza e exibe a comparação do valor de "População"
das duas cartas:

```bash
Comparação de cartas

Carta 1 - Estado: A, Código: A, Populacao: 1232500
Carta 2 - Estado: B, Código: B, Populacao: 150000000
Resultado: Carta 2 e a vencedora!
```

Após apresentar os resultados da comparação, o programa encerra sua
execução.

---

### Registro de duas cartas e comparação da propriedade escolhida pelo usuário

Caso o fluxo escolhido seja o fluxo de registro de duas cartas e comparação de
uma propriedade à escolha do usuário, as propriedades da primeira e segunda
cartas serão solicitadas uma a uma, como feito no fluxo de
[Registro de duas cartas e comparação da propriedade "População"](#registro-de-duas-cartas-e-comparação-da-propriedade-população).
Em seguida o programa pergunta qual propriedade o usuário deseja comparar:

```bash
As seguintes propriedades estao disponiveis para a comparacao entre as cartas:

1. Populacao
2. Area
3. Densidade Populacional
4. PIB
5. PIB per Capta
6. Numero de pontos turisticos

Escolha o numero da propriedade que deseja comparar: 
```

Após escolher a propriedade o programa faz a comparação, exibe o resultado
ao usuário e pergunta se o usuário deseja comparar outra propriedade.
Digamos que o usuário escolha a propriedade "Área":

```bash
Escolha o numero da propriedade que deseja comparar: 2   # Número 2 inserido

Comparação da propriedade "Area" das cartas:
Carta 1 - Estado: A, Código: A01, Area: 1521.11
Carta 2 - Estado: B, Código: B01, Area: 1510.08
Resultado: Carta 1 e a vencedora!

Comparar outra propriedade? (S/N):
```

- Caso o usuário deseje comparar outra propridade, o programa exibirá a seguinte
mensagem e fará a comparação:

  ```bash
  Escolha o numero da propriedade que deseja comparar: 
  ```

- Caso o usuário não deseje fazer outra comparação, o programa irá encerrar a
sua execução.

#### Possíveis resultados da comparação

- `Resultado: Carta 1 e a vencedora!`
- `Resultado: Carta 2 e a vencedora!`
- `Resultado: Houve um empate!`

---

### Registro de duas cartas e comparação de duas propriedades escolhidas pelo usuário

Caso o fluxo escolhido seja o fluxo de registro de duas cartas e comparação de
duas propriedades à escolha do usuário, as propriedades da primeira e segunda
cartas serão solicitadas uma a uma, como feito no fluxo de
[Registro de duas cartas e comparação da propriedade "População"](#registro-de-duas-cartas-e-comparação-da-propriedade-população).
Em seguida o programa exibe as propriedades passíveis de comparação e pergunta
ao usuário qual a primeira propriedade a ser usada na comparação:

```bash
As seguintes propriedades estao disponiveis para a comparacao entre as cartas:

1. Populacao
2. Area
3. Densidade Populacional
4. PIB
5. PIB per Capta
6. Numero de pontos turisticos

Escolha o numero da primeira propriedade a ser usada na comparacao: 
```

Digamos que a propriedade escolhida foi "Área":

```bash
Escolha o numero da primeira propriedade a ser usada na comparacao: 2   # Número 2 referente à propriedade Área
```

Em seguida o programa pergunta ao usuário qual a segunda propriedade:

```bash
Escolha o numero da primeira propriedade a ser usada na comparacao: 2
Escolha o numero da segunda propriedade a ser usada na comparacao:
```

Digamos que a propriedade escolhida foi "Densidade Populacional":

```bash
Escolha o numero da segunda propriedade a ser usada na comparacao: 3   # Número 3 referente à propriedade Densidade Populacional
```

Então o programa faz e exibe a comparação da soma dos valores das propriedades
escolhidas e pergunta se o usuário desejar comparar outra propriedade:

```bash
Comparação da soma das propriedades escolhidas:
Carta 1 - Estado: A, Código: A01, Area: 1521.11, Densidade Populacional: 8102.64, Soma: 9623.75
Carta 2 - Estado: B, Código: B01, Area: 1510.08, Densidade Populacional: 99332.49, Soma: 100842.57
Resultado: Carta 2 e a vencedora!

Comparar outra propriedade? (S/N):
```

- Caso o usuário opte por comparar outra propriedade, o programa solicitará qual
o número da primeira propriedade que o usuário deseja e, em seguida, da segunda
propriedade. Então o programa fará a comparação e exibirá o resultado.
- Caso o usuário opte por não comparar outra propriedade, o programa encerrará
a sua execução.
