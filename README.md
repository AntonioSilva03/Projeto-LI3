## Projeto da UC de Laboratórios de Informática III - 2022/2023
# Descrição
Este programa permite executar querys e obter estatísticas sobre um sistema de viagens (tipo Uber) onde existem Utilizadores, Condutores e Viagens.
# Requisitos para funcionamento
No modo batch (automático) é necessário ter os ficheiros de dados .csv guardados na máquina e um ficheiro .txt com as querys as ser executadas.
No modo interativo apenas os ficheiros de dados são necessários.
No modo de testes são necessários os ficheiros de dados, input e uma pasta com os resultados das querys para comparação.
# Instruções de execução
Primeiramente deve ser executada a Makefile que vai gerar os executáveis principal e de teste (dentro da pasta "trabalho-pratico"):
```
make
```
Depois deve ser executado um dos programas.
Para executar o modo batch (automático):
```
./programa-principal "caminho para a pasta com os ficheiros de dados" "caminho para o ficheiro de input"
```
Para executar o modo interativo:
```
./programa-principal
```
Para executar o modo de testes:
```
./programa-testes "caminho para a pasta com os ficheiros de dados" "caminho para o ficheiro de input" "caminho para pasta com os resultados das querys"
```
# Execução das querys
O modo de instrução das querys está no modo interativo. Este deve ser executado, e no menu deve ser selecionada a opção 1.
# Limpeza do programa
No final da execução do programa os executáveis podem ser limpos com o comando clean:
```
make clean
```
# Conclusão
Trabalho realizado por Pedro Silva, António Silva e Diogo Barros com o auxílio dos docentes da UC de Laboratórios de Informática III, aos quais agradecemos.

