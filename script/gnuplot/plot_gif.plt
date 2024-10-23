reset
set terminal gif animate delay 1
set output "./result/result.gif"
f(x) = exp(-(x-t)**2)
do for [i=1:50]{
t=0.2*i
plot f(x)
}