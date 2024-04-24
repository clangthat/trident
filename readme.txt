# Trident - Prototype
Protótipo de algorítmo para o projeto Trident.

# Objetivo
Desenvolver um algorítimo capaz de descobrir a melhor combinação
de 90 números para forçar 3 cartelas específicas a ganharem nas 
posições específicas (1st, 2nd e 3rd). 

# Começar
Para compilar o projeto, basta estar no mesmo diretório que o 
arquivo "Makefile" e digitar:

    :~$ make clean && make  # make clean não necessário

Ou se preferir, compile com as opções de depuração ativada:

    :~$ make clean && make DEBUG=1  # make clean não necessário

O binário será compilado em build/.

# Estrutura
O projeto está estruturado assim:

├── includes
│   └── util.h      <-- header módulo principal
├── LICENSE
├── Makefile        <-- não há necessidade de editar aqui.
├── readme.txt
└── src
    ├── main.cpp    <-- entry point, livre para modificar
    └── util.cpp    <-- módulo principal, não há necessidade de modificar

O código fonte em 'util.cpp' é responsável pelo objeto de cartela e sorteio,
também realiza o sorteio de forma mais simples.

A ideia é implementar o algorítmo dentro de main.cpp. Também não há necessidade
de editar o Makefile, os sources são compilados automaticamentes, desde que
possuam a extensão .cpp e estejam dentro de src/ e seus headers dentro de includes/.

