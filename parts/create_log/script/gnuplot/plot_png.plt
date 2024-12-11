reset
set terminal png
set output "./result/result.png"
set xtics  0,0.5,5 # x軸の最小目盛，間隔，最大値
set ytics  0,0.5,5 # y軸の最小目盛，間隔，最大値
set key top right # 凡例の場所 top(bottom) raght(left) / 図の右外：outside 図の下外：below
set title "example" #グラフのタイトル
set xlabel "{ Elapsed time, {/TimesNewRoman-Italic t} (sec)}" # x軸のタイトル
set ylabel "Temperature, {/TimesNewRoman T}({/TimesNewRoman-Italic t})" # y軸のタイトル
set xrange [0:5] # xの最小値 - 最大値
set yrange [0:5] # yの最小値 - 最大値
set arrow from 2,0.4 to 2,1.6 nohead lt 0 lw 7  # y軸と平行に点線を引く
#set tmargin 10 # tmargin:上 / bmargin:下 / lmargin:左 / rmargin:右    余白を10
f(x) = x

pl f(x) w p lc "red" pt 5 ps 1.5 title "x"
