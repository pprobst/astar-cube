---------------------------
|      A* em um cubo      |
---------------------------
Autor: Pedro Probst Minini 201710013
Data:  Setembro/2020

Conteúdo:
- Código do programa (POO, legível, comentado JavaDoc, parametrizado);
    - Especificamente, a implementação do A* está em search.cpp.

- Estatísticas anotadas (times.csv);

- Script em Python para criar o gráfico a partir das estatísticas (stats.py);

- Gráfico detalhando resultados de tempo x distância (graph.png).
    - Observação: foram considerados apenas as distâncias que obtiveram >= 50 ocorrências.

---------------------------
|        Execução:        |
---------------------------

$ make

Para rodar com configuração default (100x100x100, 40% blockers, random start, random goal):
$ ./astar

Para rodar com configuração customizada:
$ ./astar -d CUBE_DIMENSION -b BLOCKER_PERCENT -s START_X START_Y START_Z -g GOAL_X GOAL_Y GOAL_Z

Por exemplo, para a seguinte configuração "50x50x50, 10% blockers, start at (12, 12, 12), goal at (30, 30, 30)":
$ ./astar -d 50 -b 10 -s 12 12 12 -g 30 30 30

obs.: se você quiser gravar o resultado em times.csv, colocar -r como primeiro argumento.

-----------------------------------------
| Configurações do computador de testes | 
-----------------------------------------
OS: Arch Linux x86_64
Kernel: 5.8.7-arch1-1
CPU: AMD Ryzen 5 3600 (12) @ 3.600GHz
GPU: AMD ATI Radeon RX 5700 XT
RAM: 16GiB

---------------------------
|  Referências utilizadas |
---------------------------
- https://www.youtube.com/watch?v=icZj67PTFhc
- https://www.redblobgames.com/pathfinding/a-star/introduction.html 
E outras pesquisas que fiz por conta para esclarecer alguns pontos (explicados em código).
