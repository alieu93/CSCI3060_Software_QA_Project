package BackEnd;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;

/**
 * MakeNewFiles: Handles reading from the arrays we created in BackEnd and uses them
 * to create the new UAF and ATF based on the transaction from the combined DTF. 
 * BackEnd will run an instance of this after ensuring that it has read from the DTFs, the ATF and UAF
 * 
 * Input: The 3 arrays for each file type
 * Output: The new User Accounts File and the new Available tickets file
 * 
 */
public class MakeNewFiles {
	static String[] UAF;
	static String[] ATF;
	static String[] finalDTF;
	
	//Temporary arraylists for holding any changes
	static ArrayList<String> newUAF;
	static ArrayList<String> newATF;
	
	// Constructor for this class
	public MakeNewFiles(String[] finalDTF, String[] UAF, String[] ATF){
		this.finalDTF = finalDTF;
		this.UAF = UAF;
		this.ATF = ATF;
		
		// Checks for errors and outputs it if it occurs
		if(!applyTransactions()){
			ErrorLog err = new ErrorLog("fatal", "Error reading from combined DTF.");
		} 
		if(!writeToUAF()){
			ErrorLog err = new ErrorLog("fatal", "Error writing to user account file.");
		}
		if(!writeToATF()){
			ErrorLog err = new ErrorLog("fatal", "Error writing to available tickets file.");
		}
	}
	
	public static boolean applyTransactions(){
		String transaction;
		String line;
		
		//TODO: Checks for every possible transaction code
		
		//01 - create, 02 - delete, 03 - sell, 04 - buy
		//05 - refund, 06 - addCredit 00 - logout, N/A - login
		for(int i = 0; i < finalDTF.length; i++){
			line = finalDTF[i];
			transaction = (String) line.substring(0,2);
			switch (transaction){
				//create
				case "01":
					if(!create(line)){
						ErrorLog err = new ErrorLog("fatal", "Create account error");
						return false;
					}
					break;
				//delete
				case "02":
					if(!delete(line)){
						ErrorLog err = new ErrorLog("fatal", "delete account error");
						return false;
					}
					break;
				//sell
				case "03":
					if(!sell(line)){
						ErrorLog err = new ErrorLog("fatal", "sell transaction error");
					}
					break;
				//buy
				case "04":
					if(!buy(line)){
						ErrorLog err = new ErrorLog("fatal", "buy transaction error");
					}
					break;
				//refund
				case "05":
					if(!refund(line)){
						ErrorLog err = new ErrorLog("fatal", "sell transaction error");
					}
					break;
				//addCredit
				case "06":
					if(!addCredit(line)){
						ErrorLog err = new ErrorLog("fatal", "Add Credit transaction error");
					}
					break;
				//logout
				case "00":
					if(!logout(line)){
						ErrorLog err = new ErrorLog("fatal", "Logout transaction error");
					}
					break;
				//Anything besides 00 to 06
				default: 
					ErrorLog err = new ErrorLog("fatal", "Error in reading transaction.");
					break;
			}
		}
		return true;
	}
	


	public static boolean writeToUAF(){
		//TODO: Iterate through UAF array and write it to a text file
		//Also have checks for errors if it fails to write (fatal in this case)
		
		try{
			BufferedWriter outputWriter = new BufferedWriter(new FileWriter("user_accounts.txt"));
			for(int i = 0; i < UAF.length; i++){
				
				if(i == UAF.length - 1){
					outputWriter.write(UAF[i]);
				} else {
					outputWriter.write(UAF[i] + "\n");
				}
				
			}
			outputWriter.close();
		} catch (IOException e){
			ErrorLog err = new ErrorLog("fatal", "Error writing to UAF.");
			return false;
		}
		return true;
	}
	
	
	public static boolean writeToATF(){
		//TODO: Iterate through ATF array and write it to a text file
		//Also have checks for errors if it fails to write (fatal in this case)
		
		try{
			BufferedWriter outputWriter = new BufferedWriter(new FileWriter("available_tickets.txt"));
			for(int i = 0; i < ATF.length; i++){
				//System.out.println(ATF[i]);
				if(i == ATF.length - 1){
					outputWriter.write(ATF[i]);
				} else {
					outputWriter.write(ATF[i] + "\n");
				}
			}
			outputWriter.close();
		} catch (IOException e){
			ErrorLog err = new ErrorLog("fatal", "Error writing to ATF.");
			return false;
		}
		return true;
	}
	
	
	//Logout: mainly used to update credit values or any other changes
	public static boolean logout(String line) {
		newUAF = new ArrayList<String>(Arrays.asList(UAF));
		//Trimming off the transaction code since the rest is the same as in the UAF
		String DTF_Line = line.substring(3, line.length());
		String name = DTF_Line.substring(0, 15);
		
		//Replace that specific line with the new information
		for(int i = 0; i < UAF.length; i++){
			if(UAF[i].startsWith(name)){
				UAF[i] = DTF_Line;
				break;
			}
		}
		return true;
	}
	
	//Format for create, delete, addCredit: XX_UUUUUUUUUUUUUUU_TT_CCCCCCCCC
	public static boolean create(String line){
	
		//Converts UAF to an arraylist and stores it in newUAF
		newUAF = new ArrayList<String>(Arrays.asList(UAF));
		//Parses the username from that transaction line
		String nameLine = line.substring(3, line.length());
		String name = nameLine.substring(0, nameLine.indexOf("_"));
		
		//Iterates through existing UAF and checks for existing user, error if so
		for(int i = 0; i < UAF.length; i++){
			if(UAF[i].startsWith(name)){
				ErrorLog err = new ErrorLog("constraint error", "Username already exists", "Create");
				return false;
			}
		}
		
		newUAF.add(nameLine);
		//UAF = newUAF.toArray();
		UAF = (String[]) newUAF.toArray(new String[newUAF.size()]);
		return true;
	}
	
	public static boolean delete(String line){
		//TODO: Find the line with the username and delete it, same as create but without writing to array
		
		//Converts UAF to an arraylist and stores it in newUAF
		newUAF = new ArrayList<String>(Arrays.asList(UAF));
		//Parses username from that transaction line
		String name = line.substring(3,17);
		name = name.substring(0, name.indexOf("_"));
		boolean deleteFlag = false;
		
		
		Iterator<String> iter = newUAF.iterator();
		while(iter.hasNext()){
			if(iter.next().contains(name)){
				iter.remove();
				deleteFlag = true;
			}
		}
		
		//Error checking for username not found
		if(!deleteFlag){
			ErrorLog err = new ErrorLog("constraint error", "Username not found", "Delete");
		}
		
		UAF = (String []) newUAF.toArray(new String[newUAF.size()]);
		
		return true;
	}
	
	public static boolean addCredit(String line){
		//TODO: Get username and credit amount and add amount accordingly then write to UAF
		StringBuilder sb = new StringBuilder();
		
		String UAF_Line = null;
		String temp;
		
		newUAF = new ArrayList<String>(Arrays.asList(UAF));
		
		//Get information from DTF
		String name = line.substring(3,17);
		name = name.substring(0, name.indexOf("_"));
		String addAmount = line.substring(22,31);
		addAmount = addAmount.replaceAll("^0+", "");
		int add = Integer.parseInt(addAmount);
		
		//Get the line from the UAF, then remove it so we can readd it later with updated information
		Iterator<String> iter = newUAF.iterator();
		while(iter.hasNext()){
			temp = iter.next().toString();
			if(temp.contains(name)){
				UAF_Line = temp;
				iter.remove();
			}
		}
		
		//Error if it cannot find the username on UAF
		if(UAF_Line == null){
			ErrorLog err = new ErrorLog("constraint error", "Cannot find username.", "addCredit");
			return false;
		}
		
		//A lot of converting strings to ints and vice versa to add the specified credits
		String UAF_Credits = UAF_Line.substring(19, UAF_Line.length());
		int credits = Integer.parseInt(UAF_Credits);
		credits += add;		
		String newCredits = Integer.toString(credits);
		
		// Padding the string with strings again
		while(newCredits.length() < 9){
			newCredits = "0" + newCredits;
		}
		
		//Convert it back to a string and into the proper format for the UAF
		String newUAF_Line = UAF_Line.substring(0, 18);
		newUAF_Line += "_" + newCredits;
		
		newUAF.add(newUAF_Line);
		UAF = (String[]) newUAF.toArray(new String[newUAF.size()]);
		
		
		return true;
	}
	
	//Format: XX_UUUUUUUUUUUUUUU_SSSSSSSSSSSSSSS_CCCCCCCCC
	public static boolean refund(String line){
		//TODO: Get buyer and seller name and credits for both and update their credit amounts
		//Write to UAF twice, one for seller losing money and one for buyer getting money back
		newUAF = new ArrayList<String>(Arrays.asList(UAF));

		String buyerName = line.substring(3, 18);
		String sellerName = line.substring(19, 34);
		buyerName = buyerName.substring(0, buyerName.indexOf("_"));
		sellerName = sellerName.substring(0, sellerName.indexOf("_"));
		
		String refundAmount = line.substring(35, 44);
		refundAmount = refundAmount.replaceAll("^0+", "");
		int refAmt = Integer.parseInt(refundAmount);
		
		//UAF reference: UUUUUUUUUUUUUUU_TT_CCCCCCCCC
		//Applying transaction for seller
		for(int i = 0; i < UAF.length; i++){
			if(UAF[i].startsWith(sellerName)){
				String oldSellLine = UAF[i];
				//Cutting the line from UAF such that we can work with the credit amount
				//Will combine them back later
				String oldSeller = oldSellLine.substring(0, 19);
				String newCredit = oldSellLine.substring(19, 28);
				newCredit = newCredit.replaceAll("^0+", "");
				
				//Subtracting credits refunded from seller
				int credits = Integer.parseInt(newCredit);
				credits -= refAmt;
				
				//Check for error and output it if seller does not have enough cash
				if(credits < 0){
					ErrorLog err = new ErrorLog("constraint error", "Seller does not have enough money", "Sell");
					return false;
				}
				
				newCredit = Integer.toString(credits);
				
				//Padding with zeros
				while(newCredit.length() < 9){
					newCredit = "0" + newCredit;
				}
				//Combining the pieces back together
				UAF[i] = oldSeller + newCredit;
			}
		}
		
		//Transaction for the buyer's credits
		for(int i = 0; i < UAF.length; i++){
			if(UAF[i].startsWith(buyerName)){
				String oldBuyLine = UAF[i];
				String oldBuyer = oldBuyLine.substring(0, 19);
				String newCredit = oldBuyLine.substring(19, 28);
				//Regular Expression for removing leading zeroes
				newCredit = newCredit.replaceAll("^0+", "");
				
				int credits = Integer.parseInt(newCredit);
				credits += refAmt;
				
				newCredit = Integer.toString(credits);
				
				//Padding with zeros
				while(newCredit.length() < 9){
					newCredit = "0" + newCredit;
				}
				//combining the pieces back together
				UAF[i] = oldBuyer + newCredit;
			}
		}
		return true;
	}
	
	//Format: XX_EEEEEEEEEEEEEEEEEEE_SSSSSSSSSSSSSSS_TTT_PPPPPP
	public static boolean sell(String line){
		//TODO: Same as create but with event, can probably just cut XX_ from the line and just check for existing event
		
		newATF = new ArrayList<String>(Arrays.asList(ATF));
		
		//Parsing the information
		String sellLine = line.substring(3, line.length());
		String eventName = sellLine.substring(0, sellLine.indexOf("_"));
		
		//Iterates through existing ATF and checks for existing event, error if so
		for(int i = 0; i < ATF.length; i++){
			if(ATF[i].startsWith(eventName)){
				ErrorLog err = new ErrorLog("constraint error", "Event already exists", "Sell");
				return false;
			}
		}
		
		newATF.add(sellLine);
		ATF = (String[]) newATF.toArray(new String[newATF.size()]);
		return true;
	}
	
	public static boolean buy(String line){
		//TODO: Get buyer's credits and name, get seller's credits and name, subtract buyer's credits, add to seller's credits and subtract amount of tickets remaining
		newUAF = new ArrayList<String>(Arrays.asList(UAF));
		newATF = new ArrayList<String>(Arrays.asList(ATF));
		
		String eventName = line.substring(3,22);
		String sellerName = line.substring(23, 38);
		String numTickets = line.substring(39, 42);
		int numT = Integer.parseInt(numTickets);
		String priceTickets = line.substring(43, 49);
		int pTicks = Integer.parseInt(priceTickets);

		int ticketsBought = 0;
		
		//Update ticket amount from the transaction
		//Format: EEEEEEEEEEEEEEEEEEE_SSSSSSSSSSSSSSS_TTT_PPPPPP
		for(int i = 0; i < ATF.length; i++){
			if(ATF[i].startsWith(eventName) && ATF[i].contains(eventName)){
				String ticketsL = ATF[i].substring(36, 39);
				int ticketsLeft = Integer.parseInt(ticketsL);
				
				ticketsBought = ticketsLeft - numT;

				if(ticketsBought < 0){
					ErrorLog err = new ErrorLog("Constraint error", "Not enough tickets", "Buy");
					return false;
				}
				
				String remTicks = Integer.toString(numT);
				if(remTicks.length() < 3){
					remTicks = "0" + remTicks;
				}
				ATF[i] = eventName + "_" + sellerName + "_" + remTicks + "_" + priceTickets;
			}
		}
		
		//Updates seller's credit amount from the transaction
		for(int i = 0; i < UAF.length; i++){
			if(UAF[i].startsWith(sellerName)){
				String oldSellLine = UAF[i];
				//Cutting the line from UAF such that we can work with the credit amount
				//Will combine them back later
				String oldSeller = oldSellLine.substring(0, 19);
				String newCredit = oldSellLine.substring(19, 28);
				newCredit = newCredit.replaceAll("^0+", "");
				
				//Subtracting credits refunded from seller
				int credits = Integer.parseInt(newCredit);
				credits += (ticketsBought * pTicks);
				
				
				newCredit = Integer.toString(credits);
				
				//Padding with zeros
				while(newCredit.length() < 9){
					newCredit = "0" + newCredit;
				}
				//Combining the pieces back together
				UAF[i] = oldSeller + newCredit;
			}
		}
		
		
		return true;
	}
	
	
	
}
