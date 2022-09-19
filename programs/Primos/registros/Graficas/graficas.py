from tkinter import Y, Grid
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

primos=pd.read_csv('primos.csv')

cores=np.array([2,4,8,16,28])
N=2**np.arange(10,23)

columnsCores= ['c','n','Tiempo de Ejecución']
# for i in cores: columnsCores.append(f't_{i}')
# print(columnsCores)

result=pd.DataFrame(columns=columnsCores)
for core in cores:
    for n in N:
        query=f'c=={core} and n=={n}'
        df_query=primos.query(query)
        df_new_row = pd.DataFrame({
            'c':[core],
            'n':[n],
            'Tiempo de Ejecución':[df_query['t'].mean()]
        })

        result = pd.concat([result, df_new_row])


for n in N:
    query=result.query(f'n=={n}')[['c','Tiempo de Ejecución']]
    ax = query.plot(x='c', 
            kind='bar', 
            xlabel='Cantidad de Hilos',
            stacked=False, 
            title=f'Comparativa de rendimiento de la busqueda\n de numeros primos para N = {n}') 
    ax2 = ax.twinx()
    ax2.plot(query['Tiempo de Ejecución'].values, linestyle='-', linewidth=1.0,color='gray')
    ax2.get_yaxis().set_visible(False)
    plt.savefig(f'Primos_{n}')
