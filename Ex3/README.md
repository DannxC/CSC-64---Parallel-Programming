# CSC 64

## Exercício 3

Paralelizar o Jogo da Vida utilizando MPI.

## Arquivos

Encontre o arquivo anexo `src.tar.xz`. Transporte-o para sua área `$SCRATCH` no Santos Dumont. Desempacotar esse arquivo cria o diretório `src` contendo:

- `Makefile`
- Script `Xmit.sh`
- Arquivos fonte do Jogo da Vida preparados para MPI: `ModVida.c`, `ModVida.h`, `WallTime.c`, `WallTime.h`, e `Tempo.c`

O script `Xmit.sh` recebe como argumento o número de processos MPI e gera um arquivo de saída `OutTempo_<X>_MPI`, onde `<X>` é o número de processos MPI utilizados na execução.

## Ambiente

Antes de compilar o programa utilizando `make`, carregue a biblioteca MPI digitando:
```bash
module load openmpi/gnu/2.0.4.2
```
Este comando deve ser executado a cada novo login.

## Trecho Fornecido da Paralelização MPI

A paralelização MPI do Jogo da Vida envolve:

- Particionar o domínio entre os processos MPI
- Paralelizar o avanço do tabuleiro entre gerações
- Paralelizar a inicialização, verificação da correção, e impressão de um trecho do tabuleiro

O programa fornecido já contém todos esses procedimentos paralelizados, exceto o avanço do tabuleiro (`UmaVida`). Este programa produzirá resultados corretos somente com um processo MPI. Sua tarefa é terminar a paralelização de `UmaVida`.

Para entender o paralelismo MPI fornecido e ser capaz de paralelizar `UmaVida`, basta entender o programa principal.

O programa principal no arquivo `Tempo.c` inicia inscrevendo-se na computação MPI.
Desta forma, há múltiplas execuções simultâneas do programa principal, uma para cada processo MPI.

O tamanho do lado do tabuleiro (variável `tam`) é $tam = 2^{POW}$. Após conhecer o tamanho do lado do tabuleiro, o programa principal descobre quantos processos MPI (variável `numProc`) existem na execução e qual é o número do processo (variável `myId`). Segue determinando o número do processo MPI imediatamente anterior e imediatamente posterior (o processo 0 não tem antecessor e o processo `numProc − 1` não tem sucessor).

Lembre-se que o tabuleiro do Jogo da Vida possui bordas. Em execuções sequenciais o tabuleiro possui (`tam + 2`) linhas com (`tam + 2`) colunas por linha. O interior do tabuleiro são as linhas `[1: tam]`. A linha 0 é a borda superior e a linha `tam + 1` é a borda inferior. As bordas não são alteradas entre gerações (células permanentemente mortas).

Os arquivos fornecidos particionam apenas as linhas no interior do tabuleiro, sem incluir as bordas. Admitindo que a divisão de `tam` por `numProc` tenha resto nulo, o quociente $tamLocal = \frac{tam}{numProc}$ é o número de linhas em cada processo MPI. Desta forma, o processo 0
conhece apenas as linhas `[1: tamLocal]` do tabuleiro total, o processo 1 conhece apenas as linhas `[tamLocal + 1: 2 x tamLocal]` do tabuleiro total e assim por diante.

Denominarei *tabuleiro local* o trecho do tabuleiro total conhecido por cada processo.

Para avançar uma geração no tabuleiro local, todos os processos MPI aplicam as regras do Jogo da Vida a todas as células de cada linha do seu tabuleiro local. As regras requerem o conhecimento da linha atual, da linha imediatamente anterior e da linha imediatamente posterior. Entretanto, a linha imediatamente anterior à primeira linha do tabuleiro local e a linha imediatamente posterior à última linha do tabuleiro local não estão presentes no tabuleiro local, pois são conhecidas apenas dos processos vizinhos. Para armazenar cópias dessas linhas, o tabuleiro local é alocado com `tamLocal + 2` linhas, com a linha 0 e a linha `tamLocal + 1` armazenando cópias das linhas dos tabuleiros vizinhos. Essas duas linhas são denominadas *ghost zone* do tabuleiro local.

Observe que o primeiro processo não tem vizinho anterior e o último processo não tem vizinho posterior. Nesses processos, a linha aparentemente excedente da ghost zone armazena as bordas do tabuleiro total, que permanecem inalteradas durante toda a computação. Ou seja, a linha 0 do processo 0 armazena a borda superior do tabuleiro total e a linha `tamLocal + 1` do processo `numProc - 1` armazena a borda inferior do tabuleiro total.

O programa principal segue particionando o tabuleiro, calculando tamLocal, a quantidade de linhas do tabuleiro neste processo. O cálculo de `tamLocal` considera o resto da divisão de `tam` por `numProc`, repartindo o resto da divisão pelos primeiros processos MPI de forma a minimizar a diferença de tamanhos dos tabuleiros locais.

Encerra-se o cálculo da partição calculando a posição da primeira linha do tabuleiro local (linha 1) no tabuleiro global. Esse valor é armazenado na variável `desloc`. Observe que esse valor
é o deslocamento a ser somado ao número da linha local para obter o número da linha global.

O programa principal prossegue alocando os tabuleiros locais. Conforme explicado acima, observe que o tabuleiro local obrigatoriamente possui ghost zones, ou seja, o tabuleiro local possui `tamLocal + 2` linhas. Quanto à indexação do tabuleiro local, volto a observar que a linha `i` do tabuleiro local é a linha `i + desloc` do tabuleiro total.

A computação prossegue inicializando os tabuleiros locais, colocando o veleiro na sua posição inicial. Perceba que trechos do veleiro podem estar em diversos tabuleiros locais, mesmo em ghost zones.

Gerações consecutivas do tabuleiro são calculadas invocando o procedimento `UmaVida`. A interface fornecida desse procedimento já possui todas as variáveis necessárias para a paralelização MPI, mas o corpo desse procedimento não está paralelizado. Falta atualizar as ghost zones.

A computação termina verificando se o veleiro está na posição devida do tabuleiro, ou seja, se a codificação MPI está correta ou não. Caso não esteja, a computação é interrompida emitindo mensagem. Caso esteja correta, o processo 0 imprime o número de processos MPI, o tamanho total do tabuleiro e os quatro tempos de execução usuais (inicialização, computação, finalização e tempo total).

## Seu Trabalho

Codifique o MPI no interior de `UmaVida`.

Observe que a primeira invocação de `UmaVida` recebe o tabuleiro local corretamente inicializado, incluindo as ghost zone. Entretanto, `UmaVida` computa apenas as linhas internas do tabuleiro local, mas não atualiza as ghost zone próprias e dos processos vizinhos com a nova geração. Sua tarefa é atualizar a ghost zone do tabuleiro `TabulOut` de cada processo MPI após o cálculo da nova geração. Insira os comandos necessários no interior de `UmaVida`.

Se precisar depurar, imprima trechos do tabuleiro global invocando `DumpTabul`.

Após obter o paralelismo MPI correto, execute `Xmit.sh` com 1, 2, 4, 8, 12, 24, e 48 processos MPI, e reserve os arquivos resultantes.

## Solicitações

Entregue um arquivo `.tgz` com o programa paralelizado e um relatório em PDF contendo:

1. Breve descrição da codificação MPI de `UmaVida`.
2. Avaliação do speed-up do paralelismo MPI. Crie uma tabela com os tempos de execução e speed-up em função do número de processos MPI, usando apenas os tempos reportados por `comp=`.
3. Contraste o esforço de programação entre esta versão MPI e a versão OpenMP do exercício anterior. Considere limitações no número de núcleos utilizáveis nas duas versões. Em quais circunstâncias vale a pena cada versão?
4. Avalie a possibilidade de uma versão com ambos paralelismos (MPI e OpenMP) e indique onde e como o paralelismo OpenMP poderia ser adicionado ao programa fonte MPI.
