package eml_parser_no_ui;

import java.io.File;

public class EmlParserNoUi
{
	private static final String 
	DIR_NOT_FOUND = "파일 또는 폴더가 없음";
	

	public void parse(final String str_input_eml_dir, final String outputCsvDir)
	{
		File input_eml_dir, input_eml_files[];
		
		
		input_eml_dir = new File(str_input_eml_dir);
		input_eml_files = input_eml_dir.listFiles();		
		if (input_eml_files == null){
			System.out.println(str_input_eml_dir+DIR_NOT_FOUND);
		}else{
			OneEmlFileParser one_file_parser;
			
			one_file_parser = new OneEmlFileParser(outputCsvDir);
			
			for (int i=0; i<input_eml_files.length; i++){
			//for (int i=0; i<1; i++){
				one_file_parser.parse(input_eml_files[i]);
			}
			
			one_file_parser.close();
		}
		
	}
	
}
