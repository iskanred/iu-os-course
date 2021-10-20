touch ex3.txt
touch _ex3.txt

echo "Iskander" > _ex3.txt

chmod a-x _ex3.txt
ls -l _ex3.txt >> ex3.txt

chmod uo=rwx _ex3.txt
ls -l _ex3.txt >> ex3.txt

chmod g=u _ex3.txt
ls -l _ex3.txt >> ex3.txt

# Answers on questions
echo "1) 660 = (rw- for owner) , (rw- for group) , (--- for others)" >> ex3.txt
echo "2) 775 = (rwx for owner) , (rwx for group) , (r-x for others)" >> ex3.txt
echo "3) 777 = (rwx for onwer) , (rwx for group) , (rwx for others)" >> ex3.txt
