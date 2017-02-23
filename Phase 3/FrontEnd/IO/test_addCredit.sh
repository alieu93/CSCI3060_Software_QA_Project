echo "--------------------------"
echo "Testing addCredit function..."
echo "--------------------------"
for i in IO/Inputs/addCredit/*.txt;
	do echo
	let counter++
	echo "Testing test input addCredit$counter...."
	echo "-----------------------------------------"
	#Deletes transaction file again
	rm daily_transaction_file.txt
	> daily_transaction_file.txt

	rm available_tickets.txt
	rm user_accounts.txt
	cp IO/available_tickets.txt available_tickets.txt
	cp IO/user_accounts.txt user_accounts.txt


	#Sets the input file to the program itself
	./frontend.o < IO/Inputs/addCredit/addCredit"$counter"_input.txt >> IO/Outputs/addCredit/actual/addCredit"$counter"_actout.txt
	
	#Copies the transaction file from that test to a folder
	cp daily_transaction_file.txt IO/Outputs/addCredit/actual/addCredit"$counter"_actfile_output.txt
	
	#compares the console outputs
	diff -u --ignore-all-space IO/Outputs/addCredit/addCredit"$counter"_expout.txt IO/Outputs/addCredit/actual/addCredit"$counter"_actout.txt

	#compares the daily transaction file outputs
	diff -u --ignore-all-space IO/Outputs/addCredit/addCredit"$counter"_expfile_output.txt IO/Outputs/addCredit/actual/addCredit"$counter"_actfile_output.txt

	#Compares UAF output files
	cp user_accounts.txt IO/Outputs/files/addCredit/actual/addCredit"$counter"_actuaf.txt

	diff -u --ignore-all-space IO/Outputs/files/addCredit/addCredit"$counter"_expuaf.txt IO/Outputs/files/addCredit/actual/addCredit"$counter"_actuaf.txt

done
