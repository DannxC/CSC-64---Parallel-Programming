# CSC 64

## Exercício 1

### Finalidade
Paralelizar com OpenMP a versão sequencial do Jogo da Vida no Santos Dumont, avaliando a redução do tempo de execução por meio do paralelismo.

### Arquivos Originais

- Obtenha o tarball `JogoDaVidaOMPNoSDumont.tgz`.
- Transfira o tarball (sem desempacotar) para sua conta no Santos Dumont e mova o arquivo para o diretório `$SCRATCH`.
- Desempacote utilizando `tar –xzvf JogoDaVidaOMPNoSDumont.tgz`.
- Cria-se o diretório `Exercicio02`, contendo quatro arquivos fonte (`wall_time.c`, `ModVida.c`, `Funciona.c` e `Tempo.c`), Makefile e dois scripts de execução preparados para o sistema de submissão batch do Santos Dumont (`XmitFunciona.sh` e `XmitTempo.sh`).

Os arquivos fonte diferem dos utilizados no Exercício 01 apenas no preparo para uso de OpenMP e no fato que há dois programas principais. Já os scripts e Makefile são diferentes.

### Seu Trabalho

Compile os programas fonte utilizando `make`. Resultam dois arquivos executáveis: `Funciona.exe` e `Tempo.exe`, um para cada programa principal (`Funciona.c` e `Tempo.c`). Os dois executáveis computam o Jogo da Vida da mesma forma, mas com finalidades diferentes.

O script `XmitFunciona.sh` submete o executável `Funciona.exe` ao Santos Dumont. Requer, como único argumento, a quantidade de threads desejada na execução. Produz o arquivo de saída `OutFunciona_XOMP`, com uma execução do Jogo da Vida para X threads. Por exemplo, o comando `./XmitFunciona.sh 04` executa `Funciona.exe` com quatro threads e produz o arquivo de saída `OutFunciona_04OMP`. Não execute com mais de 6 threads. O programa principal `Funciona.c` foi confeccionado para desenvolver sua versão OpenMP do Jogo da Vida e para avaliar automaticamente a correção do seu trabalho. Por exemplo, imprime passo a passo o tabuleiro de tamanho pequeno (6), permitindo depuração. Imprime, na última linha, se o resultado está correto ou não. Utilize o script correspondente para essa finalidade.

O script `XmitTempo.sh` submete o executável `Tempo.exe` à mesma fila, variando o tamanho do tabuleiro de 2^3 a 2^9 em potências de 2. Requer, como único argumento, a quantidade de threads desejada na execução. Produz o arquivo de saída `OutTempo_XOMP`, onde X é o número de threads. O arquivo de saída contém uma linha para cada tamanho do tabuleiro, imprimindo a correção do resultado, o número de threads, o número de núcleos, o tamanho do tabuleiro e quatro tempos de execução: inicialização, computação, finalização e tempo total. Utilize esse script para medir o tempo de computação de sua versão OpenMP do Jogo da Vida. Utilize esse script apenas após garantir a correção de seu trabalho em `Funciona.exe`.

Após instalar e compilar, faça as seguintes atividades:

1. Paralelize com OpenMP o procedimento `UmaVida`. Certifique-se da correção do seu trabalho executando `XmitFunciona.sh` com todas as quantidades de threads possíveis (de 1 a 6) e observando a correção dos resultados impressa pelo programa.
2. Meça o tempo de computação de sua versão paralela executando `XmitTempo.sh` com 1, 2, 4, 8 e 16 threads. Reserve os arquivos de saída. Monte tabela(s) com os tempos de computação do Jogo da Vida (apenas os tempos impressos com o rótulo “comp=”) para cada tamanho de tabuleiro em função do número de threads. Reserve a(s) tabela(s). Para cada tamanho de tabuleiro, utilize a(s) tabela(s) para calcular o speed-up apenas do tempo de computação.

Componha relatório em pdf contendo:

1. Breve explicação sobre como inseriu paralelismo OpenMP em `UmaVida`;
2. O procedimento `UmaVida` paralelizado (cut and paste do fonte);
3. A(s) tabela(s) com os tempos de computação e os speed-up calculados, fixando cada tamanho de tabuleiro e variando o número de threads. Se quiser, adicione gráficos;
4. Sua análise da redução nos tempos de execução por paralelismo;
5. Sua avaliação do exercício.

Entregue relatório em pdf como atividade realizada. Anexe à atividade o arquivo `.tgz` com os arquivos fonte do seu programa paralelizado.

Entregue até a meia-noite anterior à próxima aula.