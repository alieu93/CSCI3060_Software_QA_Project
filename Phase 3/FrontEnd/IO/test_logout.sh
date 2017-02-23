echo "---------------------------"
echo "Testing logout function..."
echo "---------------------------"
for i in IO/Inputs/logout/*.txt;
	do echo
	let counter++
	echo "Testing test input logout$counter...."
	echo "-----------------------------------------"
	#Resets the daily transaction file
	rm daily_transaction_file.txt
	> daily_transaction_file.txt

	rm available_tickets.txt
	rm user_accounts.txt
	cp IO/available_tickets.txt available_tickets.txt
	cp IO/user_accounts.txt user_accounts.txt
	
	#Sets the input file to the program itself and outputs to a separate directory
	./frontend.o < IO/Inputs/logout/logout"$counter"_input.txt >> IO/Outputs/logout/actual/logout"$counter"_actout.txt
	
	#Copies the transaction file from that test to a separate directory
	cp daily_transaction_file.txt IO/Outputs/logout/actual/logout"$counter"_actfile_output.txt
	
	#compares the console outputs
	diff -u --ignore-all-space IO/Outputs/logout/logout"$counter"_expout.txt IO/Outputs/logout/actual/logout"$counter"_actout.txt
	
	#compares the daily transaction file outputs
	diff -u --ignore-all-space IO/Outputs/logout/logout"$counter"_expfile_output.txt IO/Outputs/logout/actual/logout"$counter"_actfile_output.txt

done
