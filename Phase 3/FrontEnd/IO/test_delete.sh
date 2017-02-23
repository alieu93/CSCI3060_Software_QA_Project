echo "--------------------------"
echo "Testing delete function..."
echo "--------------------------"
for i in IO/Inputs/delete/*.txt;
	do echo
	let counter++
	echo "Testing test input delete$counter...."
	echo "-----------------------------------------"
	#resets the transaction file
	rm daily_transaction_file.txt
	> daily_transaction_file.txt

	rm available_tickets.txt
	rm user_accounts.txt
	cp IO/available_tickets.txt available_tickets.txt
	cp IO/user_accounts.txt user_accounts.txt
	

	#sets the input file to the program itself and outputs to a text file
	./frontend.o < IO/Inputs/delete/delete"$counter"_input.txt >> IO/Outputs/delete/actual/delete"$counter"_actout.txt

	#Copies the transaction file from that test to a separate directory
	cp daily_transaction_file.txt IO/Outputs/delete/actual/delete"$counter"_actfile_output.txt
	
	#compares the console outputs
	diff -u --ignore-all-space IO/Outputs/delete/delete"$counter"_expout.txt IO/Outputs/delete/actual/delete"$counter"_actout.txt
	
	#compares the daily transaction file outputs
	diff -u --ignore-all-space IO/Outputs/delete/delete"$counter"_expfile_output.txt IO/Outputs/delete/actual/delete"$counter"_actfile_output.txt

	#Compares UAF output files
	cp user_accounts.txt IO/Outputs/files/delete/actual/delete"$counter"_actuaf.txt

	diff -u --ignore-all-space IO/Outputs/files/delete/delete"$counter"_expuaf.txt IO/Outputs/files/delete/actual/delete"$counter"_actuaf.txt
	
done
