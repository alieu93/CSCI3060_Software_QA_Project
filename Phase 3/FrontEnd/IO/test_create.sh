echo "--------------------------"
echo "Testing create function..."
echo "--------------------------"
for i in IO/Inputs/create/*.txt;
	do echo
	let counter++
	echo "Testing test create $counter...."
	echo "-----------------------------------------"
	#Resets the daily transaction file
	rm daily_transaction_file.txt
	> daily_transaction_file.txt

	rm available_tickets.txt
	rm user_accounts.txt
	cp IO/available_tickets.txt available_tickets.txt
	cp IO/user_accounts.txt user_accounts.txt

	
	#sets the input file to the program itself and outputs to text file
	./frontend.o < IO/Inputs/create/create"$counter"_input.txt >> IO/Outputs/create/actual/create"$counter"_actout.txt
	
	#copies the transaction file from that test to a separate folder
	cp daily_transaction_file.txt IO/Outputs/create/actual/create"$counter"_actfile_output.txt

	#compares the console outputs
	diff -u --ignore-all-space IO/Outputs/create/create"$counter"_expout.txt IO/Outputs/create/actual/create"$counter"_actout.txt
	
	#compares the daily transaction file outputs
	diff -u --ignore-all-space IO/Outputs/create/create"$counter"_expfile_output.txt IO/Outputs/create/actual/create"$counter"_actfile_output.txt

	#Compares UAF output files
	cp user_accounts.txt IO/Outputs/files/create/actual/create"$counter"_actuaf.txt

	diff -u --ignore-all-space IO/Outputs/files/create/create"$counter"_expuaf.txt IO/Outputs/files/create/actual/create"$counter"_actuaf.txt
	
done
