package actions.file;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import actions.chooser_dialogs.SheetFileChooser;
import data_controller.SheetDataController;

public class FileSaver
{	
	public void save(SheetDataController sheet_data_controller)
	{
		File loadedFile;
		
		loadedFile = sheet_data_controller.getLoadedSheetFile();
		if ( loadedFile == null ) {
			saveAs(sheet_data_controller);
		} else {
			sheet_data_controller.save();
			
		}		
	}
	

	public void saveAs(SheetDataController sheet_data_controller)
	{
		SheetFileChooser chooser;
		File sheetFile;
		
		chooser = new SheetFileChooser();
		sheetFile = chooser.showSaveDialog();
		if (sheetFile!=null) {
			String path;			
			path = sheetFile.getAbsolutePath();
			if (!path.endsWith(".csv")) {
				sheetFile = new File(path+".csv");
			}			
			sheet_data_controller.setLoadedSheetFile(sheetFile);
			save(sheet_data_controller);
		}		
	}

}
