# FlappyJackBOT ⛵
#### Desenvolvido por: **[DanieLuan](https://github.com/DanieLuan) e [Rocha-Lee](https://github.com/Rocha-Lee)**

---

## Introdução

O FlappyJack foi desenvolvido como projeto final da disciplina de **Introdução às Técnicas de Programação** (ITP). Nele foram utilizados diversos conhecimentos adquiridos durante toda a duração a disciplina.

O bot funciona imprimindo comandos para o *ocma.js*, utilizando nodejs para executar o jogo. Para ter mais informações do OCMA, acesse o repositório https://github.com/amccampos/ocma.

Resumidamente, o OCMA é um mapa onde cada bot é um barco, e o objetivo é pescar e vender o máximo de peixes até: 

* ou atingir os R$ 10.000,00;
* ou atingir o número máximo de rounds.

No jogo, haverá um mapa onde terão portos e locais de pesca. A cada round o bot deverá executar uma ação:

* Movimentar;
* Pescar 1kg de peixe;
* Vender o peixe no porto;

Cada peixe possui o seu devido valor, e esse ponto foi extremamente importante para o desenvolvimento do FlappyJack.

---

## Funcionamento

FlappyJack funciona com base em **estados**. De acordo com o estado do bot, ele estará executando uma ação diferente, e esse estado é definido de acordo com a leitura do mapa feita e atualizada à cada início de rodada.

O fluxograma explica de forma sucinta os estados e a ação de acordo com cada estado:

<img src="https://i.imgur.com/ClIyYZV.png" alt="Fluxograma" width="600"/>

---

## Compilação

O FlappyJack foi desenvolvido apenas em ambiente **unix-like**, portanto as instruções de compilação não abrangem outros sistema.
Além disso, você também precisará ter o [Node.js](https://nodejs.org/en/) instalado na sua máquina para executar o *ocma.js*.

### Via terminal
**OBS**: Antes de executar os comandos a seguir, certifique-se de estar no diretório */src*, onde estão todos arquivos, ocma.js e o Makefile.
Para compilar, basta utilizar o comando:

    make all

Assim que tudo for compilado, basta executar utilizando:

    make exec

### Pelo Replit
Você pode executar o programa dando fork no projeto no replit, disponível em https://replit.com/@DANIELLIMA40/FlappyJackBOT.
Quando abrir, o terminal já estará com o node ativo, portanto abra o shell (ao lado do console), e entre no diretório */src*.
Quando o feito, apenas compilar usando o comando:

    make all

e executar utilizando o comando:

    make exec
    
---

###### Qualquer coisa, pode entrar em contato comigo, estou sempre disponível para tirar dúvidas e receber críticas 🙂
