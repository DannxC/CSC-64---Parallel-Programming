# CSC 64

## Exercício 4

Neste exercício, você irá simular uma linha de produção (“pipeline”) em OpenMP.
Suponha uma linha de produção com $n$ estágios, onde cada estágio requer $t$ segundos para processar um produto e cada estágio requeira um único operador. Para confeccionar $p$ produtos, são necessários $(n + p - 1)t$ segundos.

Forneço simulação incompleta de linha de produção com $n$ estágios gerando $p$ produtos. Falta simular a operação simultânea dos estágios, que exige paralelismo. Sua tarefa é completar a simulação utilizando OpenMP.

## Instalação

Obtenha o tarball `src.tgz` nesta atividade. Copie o arquivo para o diretório adequado no Santos Dumont. Desempacotar o tarball cria o diretório `src`, contendo:

- `Makefile`
- Script de submissão `Xmit.sh`
- Quatro arquivos fonte: `WallTime.h`, `WallTime.c`, `Pipe.h` e `Main.c`, que implementam a simulação incompleta da linha de produção.

## Fontes, Compilação e Execução

Neste exercício utilizaremos carregar um módulo no SDumont. Caso tenha curiosidade, pode verificar os módulos via `module avail`. Para carregar nossos módulos, faça:

```bash
module load sequana/current
module load gcc/14.2.0_sequana
```

Atenção: Lembre-se que esse módulo deve ser carregado a cada acesso ao SDumont.

### Compilação

Para compilar no Santos Dumont, basta utilizar o comando:

```bash
make
```

### Descrição dos Arquivos

O arquivo `Pipe.h` contém apenas o procedimento `Estagio`, que simula um estágio da linha de produção. Este procedimento impõe que um estágio demande $t = 1$ segundo de execução, retornando após decorrer esse tempo. Os três argumentos do procedimento são desnecessários, mas foram incluídos para eventual depuração.

O Programa Principal lê como argumentos de entrada o número de estágios ($n$, representado pela variável `nEsta`) e a quantidade de produtos ($p$, representada pela variável `nProd`). Prossegue passando, sequencialmente, todos os produtos por todos os estágios, imprimindo o tempo de término da fabricação de cada produto.

### Execução

O script de execução `Xmit.sh` requer como único argumento o número de threads OpenMP.
A execução de `Xmit.sh T`, onde $T$ é o número de threads OpenMP, gera o arquivo de saída `Out_Pipe_T_OMP`.

O script atribui valores fixos a $n$ e $p$, padronizando os tempos de fabricação.

## Seu Trabalho

Sua tarefa é completar o programa principal utilizando OpenMP, de forma a simular corretamente a linha de produção. Correção significa que, para número de threads maior ou igual a um certo valor, o programa imprime os tempos de execução corretos para cada produto.

Utilize os valores de $n$ e $p$ definidos no script. Entretanto, sua solução OpenMP deve ser correta para quaisquer valores inteiros não nulos de $n$ e $p$, com o número de threads variando caso a caso.

Experimente sua solução para diversos valores de $n$ e $p$. Quando se convencer que obteve a solução correta:
1. Retorne $n$ e $p$ aos valores originais;
2. Execute o script utilizando o menor número de threads que simula corretamente a linha de produção;
3. Reserve o arquivo resultante.

## Relatório

Comprimir em um único arquivo `.tgz` os arquivos fonte da sua solução e o arquivo reservado resultante da execução. **Não inclua seu relatório PDF nesse arquivo.**
Envie os arquivos `.tgz` e o relatório PDF separadamente.

O relatório deve conter:

1. **Breve descrição da paralelização OpenMP**, justificando a correção do paralelismo implementado. Inclua (`cut and paste`) o trecho paralelo do programa principal que implementa a linha de produção.
2. Informe qual é o **menor número de threads** que simula corretamente a linha de produção para os valores de $n$ e $p$ definidos no script. Inclua (`cut and paste`) o texto do arquivo de saída reservado (execução com tais valores de $n$, $p$ e número de threads).
3. Mantendo os valores de $n$ e $p$ definidos no script, execute seu programa com número de threads menor e maior do que o número mínimo de threads que produz solução correta. Baseado nesse experimento, sugira uma **interpretação para o número de threads** em uma linha de produção real. Ou seja, o número de threads representa qual entidade em uma linha de produção? Justifique sua interpretação.
4. Insira seus **comentários e sua avaliação** deste exercício.

Retorne seu relatório e o arquivo fonte do programa.
