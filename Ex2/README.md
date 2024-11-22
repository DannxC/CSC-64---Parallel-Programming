# CSC 64

## Exercício 2

Sua tarefa é paralelizar a versão sequencial do Crivo de Eratóstenes usando OpenMP no Santos Dumont.

O Crivo de Eratóstenes é um algoritmo clássico para encontrar todos os inteiros primos no intervalo [2:N], dado N. O algoritmo assume que todos os inteiros no intervalo são primos e remove todos os múltiplos existentes, restando apenas os primos.

### Descrição detalhada

1. Todos os inteiros no intervalo são inicialmente marcados como primos.
2. Inicializa a base com o menor primo no intervalo (2).
3. Desmarca todos os múltiplos da base.
4. Enquanto a base for menor que N, avança para o próximo inteiro que ainda está marcado como primo e desmarca todos os múltiplos da nova base.
5. Quando todas as bases forem exauridas, os números que ainda estiverem marcados são os primos.

### Implementação

Foi fornecido o tarball `CrivoParaOpenMP.tgz`. Este deve ser transferido para o diretório `$SCRATCH` no SDumont antes de abri-lo. Ao desempacotar, será gerado o diretório `CrivoParaOpenMP` contendo nove arquivos, incluindo um `Makefile`, um script de submissão (`Xmit.py`), o arquivo `main.c`, e três pares de arquivos `.c` e `.h`.

- O par `WallTime` provê funções para medir o tempo de execução.
- O par `Marcador` contém um tipo abstrato que implementa a sequência de primos como um array de bool (true se primo, false se múltiplo) e operações nessa sequência.
- O par `Crivo` implementa o Crivo de Eratóstenes utilizando as funções dos outros dois pares de arquivos.

No arquivo `main.c`, a variável `numMax` representa o valor de N. Existem dois valores de `numMax`, um pequeno para seu desenvolvimento e outro grande para medição de tempos de execução e criação do relatório. O programa cria um marcador, invoca o procedimento do Crivo e verifica a correção dos resultados, imprimindo os tempos de inicialização, computação e final.

### Otimizações no procedimento Crivo

O procedimento Crivo contém duas otimizações:

1. Desmarca os múltiplos da base a partir do quadrado da base, já que todos os múltiplos inferiores ao quadrado já foram desmarcados.
2. A maior base possível é a raiz quadrada de N, pois qualquer número não primo maior que a raiz quadrada de N é produto de fatores primos, sendo pelo menos um desses fatores menor que a raiz quadrada de N e já foi desmarcado.

### Compilação

Utilize `make` para compilar o código, gerando o executável `Primos.exe`. O script Python `Xmit.py` submete o executável à fila do Santos Dumont. Este script requer o número de threads como argumento: `python Xmit.py <nThreads>`. A saída é armazenada no arquivo `Out_Primos_<nThreads>.txt`.

### Paralelização

Paralelize o procedimento do Crivo utilizando OpenMP. Trabalhe apenas no procedimento `Crivo`, ignorando os demais arquivos fonte. Garanta a correção do paralelismo utilizando um valor pequeno para `numMax` durante o desenvolvimento.

### Execuções e Coleta de Dados

Após finalizar a paralelização, execute a versão OpenMP com o maior valor de `numMax` e utilize os seguintes números de threads: 1, 2, 4, 8, 12, 16, 20, 24. Colete os tempos de computação (tempo impresso após `comp=`) em uma planilha e calcule os speed-ups.

### Entrega

1. Componha um arquivo `.tgz` contendo os programas fonte e os arquivos de saída das execuções e envie junto de seu relatório.
2. Entregue o relatório em PDF contendo:
   - Explicação breve do paralelismo implementado com OpenMP;
   - Tempos de execução e os speed-ups;
   - Sua análise dos tempos e speed-ups;
   - Seus comentários sobre o exercício.

A entrega deve ser realizada até meia-noite do dia anterior à próxima aula.
