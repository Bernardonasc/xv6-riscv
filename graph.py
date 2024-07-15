import matplotlib.pyplot as plt
import pandas as pd

# Função para ler os dados do arquivo
def ler_dados_do_arquivo(arquivo):
    with open(arquivo, 'r') as f:
        data = f.read()
    return data

# Caminho para o arquivo de dados
caminho_arquivo = 'python.txt'

# Ler os dados do arquivo
data = ler_dados_do_arquivo(caminho_arquivo)

# Converter os dados em um DataFrame
lines = data.strip().split('\n')
columns = lines[0].split()
rows = [line.split() for line in lines[1:]]
df = pd.DataFrame(rows, columns=columns).astype(int)

# Agrupar por TICKETS e coletar os ticks
grouped = df.groupby('TICKETS')['TICKS'].apply(list)

# Plotar os dados
plt.figure(figsize=(10, 6))
for tickets, ticks in grouped.items():
    plt.plot(range(len(ticks)), ticks, label=f'{tickets} Tickets')

plt.xlabel('Etapas')
plt.ylabel('Ticks')
plt.title('Evolução dos Ticks por Quantidade de Tickets')
plt.legend()
plt.grid(True)

# Salvar o gráfico em um arquivo
plt.savefig('evolucao_ticks.png')