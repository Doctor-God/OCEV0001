#sh testes.sh "./a.out ..." arquivo_base nro_testes

# echo "Serial:"

for ((i = 0; i < $3; i++))
do
    eval $1 > "./testes/$2-$i"
done
