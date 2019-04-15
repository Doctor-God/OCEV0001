#sh testes.sh "./a.out ..." arquivo_base nro_testes

#zerar o arquivo
printf "" > "./testes/$2-resultados"

for ((i = 0; i < $3; i++))
do
    printf "Execução $i:\n" >> "./testes/$2-resultados"
    eval "$1 -o ./testes/$2-$i" >> "./testes/$2-resultados"
    printf "\n" >> "./testes/$2-resultados"
done
