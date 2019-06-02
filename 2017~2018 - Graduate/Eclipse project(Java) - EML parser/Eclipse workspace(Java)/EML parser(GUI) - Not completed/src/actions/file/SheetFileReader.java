package actions.file;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class SheetFileReader
{
	
	public String read(File sheet_file)
	{
		char[] data = null;
		BufferedReader reader;
		try {
			reader = new BufferedReader(new FileReader(sheet_file));
			data = new char[(int) sheet_file.length()];
			reader.read(data);
			reader.close();			
		} catch (IOException e) {
			e.printStackTrace();
		}		
		return new String(data);
	}
}
