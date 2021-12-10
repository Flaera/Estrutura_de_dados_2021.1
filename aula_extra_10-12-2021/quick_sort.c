Senão Se (n = 1)
Então imprime v[0]
Senão { pivo = v[0]
para (i=1; i<10;i++){
se (v[i] <= pivo)
Então j = j + 1;
x[j]= v[i];
Senão z = z + 1;
y[z]= v[i];
}
quick_sort(j+1,x);
quick_sort(z+1,y);
}
Return false
}