package BackEnd;
import java.util.*;
import java.io.*;

/**
 * BackEnd: Main part of the BackEnd component 
 * Calls all the methods and classes required for the backend to function
 * Takes in all daily transaction files and the user account and available tickets files and ..
 * .. merges the daily transaction files together and applies the transactions
 * 
 * User account and available ticket files are changed accordingly to the transactions
 * 
 * Inputs: All DTFs in directory, UAF and ATF in directory
 * Outputs: Merged DTF, new UAF and new ATF
 * 
 * Also outputs errors if any problem occurs
 *
 */
public class BackEnd {
	//Arrays to contain all lines from the files
	static private String[] DTF;
	static private String[] UAF;
	static private String[] ATF;
	//static private String dtfName = "daily_transaction";
	//static private String atfName = "available_tickets.txt";
	//static private String uafName = "user_accounts.txt";
	
	/**
	 * Main method: Calls all three methods that reads all DTFs, ATF and UAF in the current directory
	 * If any of them are missing or cannot be read, then an error will be produced by calling ErrorLog
	 * Afterwards, calls another method that handles the reading of the merged DTF and makes changes to the UAF and ATF
	 * If any problems occur with that method, an error will be produced by calling ErrorLog 
	 */
	public static void main(String[] args){
		//Have them output errors via ErrorLog
		String dtfFile = null;
		String uafFile = null;
		String atfFile = null;
		
		if(args.length < 3){
				dtfFile = "daily_transaction";
				uafFile = "user_accounts.txt";
				atfFile = "available_tickets.txt";
		} else {
				dtfFile = args[0];
				uafFile = args[1];
				atfFile = args[2];
		}
		if(!readDTF(dtfFile)){
			ErrorLog err = new ErrorLog("fatal", "Cannot open daily transaction file(s).");
		} else if(!readUAF(uafFile)){
			ErrorLog err = new ErrorLog("fatal", "Cannot open User Accounts File.");
		} else if(!readATF(atfFile)){
			ErrorLog err = new ErrorLog("fatal", "Cannot open Available Tickets File.");
		} else {
			newFiles();
		}
	}

	/**
	 * Called after the methods for reading each type of file are called and no errors have occurred
	 * 
	 */
	public static void newFiles(){
		MakeNewFiles file = new MakeNewFiles(DTF, UAF, ATF);
		if(!file.applyTransactions()){
			ErrorLog err = new ErrorLog("fatal", "Error reading from combined DTF.");
		}
		return;
	}
	
	/**
	 * Reads all daily transaction files and stores them in the DTF array
	 * For the sake of simplicity, we will assume that if there are multiple DTFs, they will be read such that..
	 * .. their contents are sequential, merged sequentially and that their names reflect this (e.g.: DTF1.txt, DTF2.txt)
	 * This requires clarification
	 * 
	 * Returns true if all DTFs are read
	 * Returns false if no DTFs are present in current directory
	 */
	public static boolean readDTF(String file){
		ArrayList<String> tempDTF = new ArrayList<String>();

		//Filters out all text files except for DTFs in the directory and adds their names to an array
		File[] dir = new File(".").listFiles();
		/*File[] foundDTF = dir.listFiles(new FilenameFilter() {
			public boolean accept(File dir, String name){
				//return name.startsWith("daily_transaction") && name.endsWith(".txt");
				return name.startsWith(file) && name.endsWith(".txt");
			}
		});*/
		if(dir == null){
			return false;
		}
		ArrayList<String> foundDTF = new ArrayList<String>();
		for(File temp : dir){
			if(temp.isFile()){
				if(temp.getName().startsWith(file) && temp.getName().endsWith(".txt")){
					foundDTF.add(temp.getName());
					System.out.println(temp.getName());
				}
			}
		}
		
		//Check if array is zero, means that there are no DTFs in directory which cannot happen
		if(foundDTF.size() == 0){
			return false;
		}
		// Iterates through each DTF and concatenates their contents into an arraylist
		FileInputStream in = null;
		BufferedReader br = null;
		try{
			for(int i = 0; i < foundDTF.size(); i++){
				//System.out.println(foundDTF.get(i));
				in = new FileInputStream(foundDTF.get(i));
				br = new BufferedReader(new InputStreamReader(in));
				String line;
				while((line = br.readLine()) != null){
					//System.out.println(line);
					tempDTF.add(line);
				}
				
			}
			in.close();
			br.close();
		} catch (IOException e){
			System.out.println(e);
			return false;
		} 
		
		DTF = tempDTF.toArray(new String[tempDTF.size()]);
		return true;
	}
	
	/**
	 * Reads the User Accounts File and stores it in the UAF array
	 * 
	 * Returns true if UAF is read and stored onto the temporary
	 * Returns false if UAF cannot be read or does not exist
	 */
	public static boolean readUAF(String file){
		ArrayList<String> tempUAF = new ArrayList<String>();

		FileInputStream in = null;
		BufferedReader br = null;
		try{
			//File directory = new File(path);
			//FileInputStream in = new FileInputStream("user_accounts.txt");
			in = new FileInputStream (file);
			br = new BufferedReader(new InputStreamReader(in));
			String line;
			while((line = br.readLine()) != null){
				//System.out.println(line);
				tempUAF.add(line);
			}
			in.close();
			br.close();
		} catch (IOException e){
			System.out.println(e);
			return false;
		}
		UAF = tempUAF.toArray(new String[tempUAF.size()]);
		return true;
		
	}
	
	/**
	 * Reads the Available Tickets File and stores in the ATF array
	 * 
	 * Returns true if ATF is read and contents stored in temporary directory
	 * Returns false if ATF cannot be read or if it does not exist
	 */
	public static boolean readATF(String file){
		ArrayList<String> tempATF = new ArrayList<String>();
		
		FileInputStream in = null;
		BufferedReader br = null;
		try{
			//FileInputStream in = new FileInputStream("available_tickets.txt");
			in = new FileInputStream(file);
			br = new BufferedReader(new InputStreamReader(in));
			String line;
			while((line = br.readLine()) != null){
				tempATF.add(line);
			}
			in.close();
			br.close();
		} catch (IOException e){
			System.out.println(e);
			return false;
		}
		ATF = tempATF.toArray(new String[tempATF.size()]);
		return true;
	}
}
