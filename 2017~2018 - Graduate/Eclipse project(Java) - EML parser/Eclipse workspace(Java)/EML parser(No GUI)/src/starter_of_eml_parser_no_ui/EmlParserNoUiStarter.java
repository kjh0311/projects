package starter_of_eml_parser_no_ui;

import eml_parser_no_ui.EmlParserNoUi;

public class EmlParserNoUiStarter
{
	private static final String
		INPUT_EML_DIR = "alaska_mail_11_12",
		OUTPUT_CSV_DIR = "result_csvs";
	
	public static void main(String args[]){
		EmlParserNoUi parser;		
		parser = new EmlParserNoUi();
		parser.parse(INPUT_EML_DIR, OUTPUT_CSV_DIR);
	}
}
