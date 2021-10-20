touch _ex1.txt
echo "Iskander" >> _ex1.txt
ln _ex1.txt _ex1_1.txt
ln _ex1.txt _ex1_2.txt

touch ex1.txt
ls -i _ex1.txt >> ex1.txt
ls -i _ex1_1.txt >> ex1.txt
ls -i _ex1_2.txt >> ex1.txt
