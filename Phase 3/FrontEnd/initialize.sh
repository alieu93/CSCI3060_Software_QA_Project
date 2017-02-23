#Compiles the program
rm frontend.o
g++ -std=c++11 frontend.cpp -o frontend.o

#Deletes the current DTF and makes a new one, this is used for the purpose of testing
#On a blank slate
rm daily_transaction_file.txt
> daily_transaction_file.txt

#Deleting all actual output text files so we can set up new ones
rm IO/Outputs/login/actual/*.txt
rm IO/Outputs/logout/actual/*.txt
rm IO/Outputs/create/actual/*.txt
rm IO/Outputs/delete/actual/*.txt
rm IO/Outputs/addCredit/actual/*.txt
rm IO/Outputs/refund/actual/*.txt
rm IO/Outputs/buy/actual/*.txt
rm IO/Outputs/sell/actual/*.txt

#Deleting all actual output ATF and UAF files so we can set up new ones
rm IO/Outputs/files/addCredit/actual/*.txt
rm IO/Outputs/files/buy/actual/*.txt
rm IO/Outputs/files/create/actual/*.txt
rm IO/Outputs/files/delete/actual/*.txt
rm IO/Outputs/files/refund/actual/*.txt
rm IO/Outputs/files/sell/actual/*.txt


#Executes all tests in sequence
chmod +x IO/test_login.sh
./IO/test_login.sh

chmod +x IO/test_logout.sh
./IO/test_logout.sh

chmod +x IO/test_create.sh
./IO/test_create.sh

chmod +x IO/test_delete.sh
./IO/test_delete.sh

chmod +x IO/test_addCredit.sh
./IO/test_addCredit.sh

chmod +x IO/test_refund.sh
./IO/test_refund.sh

chmod +x IO/test_buy.sh
./IO/test_buy.sh

chmod +x IO/test_sell.sh
./IO/test_sell.sh



echo "-------------------"
echo "Finished all tests!"
echo "-------------------"
