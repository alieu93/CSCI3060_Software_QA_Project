echo "--------------------------"
echo "Testing sell function..."
echo "--------------------------"
for i in IO/Inputs/sell/*.txt;
	do echo
	let counter++
	echo "Testing test input sell$counter...."
	echo "-----------------------------------------"
	rm daily_transaction_file.txt
	> daily_transaction_file.txt
	
	rm available_tickets.txt
	rm user_accounts.txt
	cp IO/available_tickets.txt available_tickets.txt
	cp IO/user_accounts.txt user_accounts.txt


	./frontend.o < IO/Inputs/sell/sell"$counter"_input.txt >> IO/Outputs/sell/actual/sell"$counter"_actout.txt

	cp daily_transaction_file.txt IO/Outputs/sell/actual/sell"$counter"_actfile_output.txt

	diff -u --ignore-all-space IO/Outputs/sell/sell"$counter"_expout.txt IO/Outputs/sell/actual/sell"$counter"_actout.txt

	diff -u --ignore-all-space IO/Outputs/sell/sell"$counter"_expfile_output.txt IO/Outputs/sell/actual/sell"$counter"_actfile_output.txt

	#Compares ATF output files
	cp available_tickets.txt IO/Outputs/files/sell/actual/sell"$counter"_actatf.txt

	diff -u --ignore-all-space IO/Outputs/files/sell/sell"$counter"_expatf.txt IO/Outputs/files/sell/actual/sell"$counter"_actatf.txt
	
done
