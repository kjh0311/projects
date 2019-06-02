package actions.file;

import java.io.File;

import actions.chooser_dialogs.EmlFilesDirChooser;
import actions.chooser_dialogs.SheetFileChooser;
import data_controller.SheetDataController;



public class FileLoader
{
	public void loadEmls(SheetDataController sheet_data_controller)
	{
		EmlFilesDirChooser chooser;
		File dir_of_eml_files;		
		
		chooser = new EmlFilesDirChooser();		
		dir_of_eml_files = chooser.showOpenDialog();
		if (dir_of_eml_files != null) {
			System.out.println("eml 파일 있음");
			sheet_data_controller.loadEmls(dir_of_eml_files);
		}
	}
	

	public void loadSheet(SheetDataController sheet_data_controller)
	{
		SheetFileChooser chooser;
		File sheet_file;
		
		chooser = new SheetFileChooser();
		sheet_file = chooser.showOpenDialog();
		
		if (sheet_file != null) {
			sheet_data_controller.loadSheet(sheet_file);
		}
	}
}
