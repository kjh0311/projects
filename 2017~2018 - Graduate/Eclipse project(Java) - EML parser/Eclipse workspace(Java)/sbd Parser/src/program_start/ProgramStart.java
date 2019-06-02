package program_start;


import java.io.File;
import java.io.IOException;


public class ProgramStart
{
	private static final String
		EXTRACTED_SBD_FILES_DIR = "sbd 파일 모음/201801";
	public static void main(String args[]){
		new ProgramStart();
	}
	
	
	ProgramStart(){
		File sbd_dir, sbd_files[];
		ResultFilesWriter writer;	
		
		
		sbd_dir = new File(EXTRACTED_SBD_FILES_DIR);
		sbd_files = sbd_dir.listFiles();
		writer = new ResultFilesWriter();
		for (File sbd_file: sbd_files) {
			writer.write(sbd_file);		
		}
		writer.close();
	}
}
