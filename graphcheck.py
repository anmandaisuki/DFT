# matplotlibでDFT出力をグラフ化してチェックする。
# ソースデータもあるので、それをpythonでfft()して比較する。

import numpy as np
import matplotlib.pyplot as plt

N = 256

# pythonでfftするプロセス
f = open('SRC.csv','r')

#読み込みデータ格納用
srcdata_array = []

for i in range(N):
    comp = f.readline()
    comp_array = comp.split(' ')
    srcdata_array.append(float(comp_array[0]))

F = np.fft.fft(srcdata_array)

# DFTの結果の読み込み
F_cpp_DFT = []
f = open('DFT.csv')
for i in range(N):
    comp = f.readline()
    comp_array = comp.split(' ')
    F_cpp_DFT.append(complex(float(comp_array[0]),float(comp_array[1])))

# IDFTの結果の読み込み
F_cpp_IDFT = []
f = open('IDFT.csv')
for i in range(N):
    comp = f.readline()
    comp_array = comp.split(' ')
    F_cpp_IDFT.append(complex(float(comp_array[0]),float(comp_array[1])))

F_abs_cpp_dft = np.abs(F_cpp_DFT)
F_abs_cpp_idft = np.array(F_cpp_IDFT)
plt.plot(F_abs_cpp_dft,label = "DFT")
plt.plot(F_abs_cpp_idft,label = "IDFT")
plt.legend()
plt.show()
